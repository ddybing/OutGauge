#define no_init_all deprecated
#define DEFAULT_BUFLEN 512
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "include\OutGauge.hpp"
#pragma comment(lib, "ws2_32.lib")


class InstrumentCluster
{
public:

	// DL = Dash light, the individual lights in the instrument clusters (oil pressure, parking brake, check engine)
	// 0 = OFF, 1 = ON
	int DL_INDICATOR_LEFT;
	int DL_INDICATOR_RIGHT;
	int DL_OIL_WARNING;
	int DL_HIGH_BEAM;
	int DL_PARKING_BRAKE;
	int DL_ABS;
	int DL_BACKLIGHT;

	float GAUGE_FUEL;
	float GAUGE_TACH;
	float GAUGE_SPEEDO;
	float GAUGE_TEMP;

	// Class functions

	void setDashLight(std::string LIGHT, int STATE)
	{


	}

};


struct dashLights
{
	// This struct describes the different fields in the dashLights field of the OutGauge packet. 
	// It shows which dash lights are available by the game, e.g. oil lamp, ABS etc
	int DL_SHIFT = 0; // Bit 0,  Shift light is turned
	int DL_FULLBEAM = 1; // Bit 1, Full Beam dashlight is on.
	int DL_HANDBRAKE = 2; // Bit 2, Handbrake dashlight is on.
	int DL_PITSPEED = 3; // Bit 3, Pit speed limiter, negligible in most games.
	int DL_TC = 4; // Bit 4, Traction control.
	int DL_SIGNAL_L = 5; // Bit 5, Left indicator.
	int DL_SIGNAL_R = 6; // Bit 6, Right indicator.
	int DL_SIGNAL_ANY = 7; // Bit 7, Shared turn signal (guessing hazards).
	int DL_OILWARN = 8; // Bit 8, oil pressure warning light.
	int DL_BATTERY = 9; // Bit 9, battery warning.
	int DL_ABS = 10; // Bit 10, ABS active or switched off.
	int DL_SPARE = 11; // Bit 11, not in use

};


struct showLights
{
	// This struct describes the different fields in the showLights field of the OutGauge packet.
	// It shows which dash lights are turned on, e.g. oil lamp, hand brake, ABS etc

	int DL_SHIFT = 0; // Bit 0,  Shift light is turned
	int DL_FULLBEAM = 1; // Bit 1, Full Beam dashlight is on.
	int DL_HANDBRAKE = 2; // Bit 2, Handbrake dashlight is on.
	int DL_PITSPEED = 3; // Bit 3, Pit speed limiter, negligible in most games.
	int DL_TC = 4; // Bit 4, Traction control.
	int DL_SIGNAL_L = 5; // Bit 5, Left indicator.
	int DL_SIGNAL_R = 6; // Bit 6, Right indicator.
	int DL_SIGNAL_ANY = 7; // Bit 7, Shared turn signal (guessing hazards?).
	int DL_OILWARN = 8; // Bit 8, oil pressure warning light.
	int DL_BATTERY = 9; // Bit 9, battery warning.
	int DL_ABS = 10; // Bit 10, ABS active or switched off.
	int DL_SPARE = 11; // Bit 11, not in use


};






int main()
{

	char buffer[96] = { 0 };
	struct sockaddr_in serveraddr = { 0 };
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);
	SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(4444);
	serveraddr.sin_addr.s_addr = INADDR_ANY;

	
	int rc = bind(sockfd, (const struct sockaddr *)&serveraddr, sizeof(serveraddr));

	if (rc == -1)
	{
		std::cout << "Error!" << std::endl;
	}
	while (true)
	{
		recv(sockfd, (char *)&buffer, sizeof(buffer), 0);
		
		struct OutGaugePacket car;

		float fuel;
		char g[] = { buffer[28], buffer[29], buffer[30], buffer[31] };
		memmove(&fuel, &g, sizeof(fuel));
		float rpm; 
		char b[] = { buffer[16], buffer[17], buffer[18], buffer[19] };
		memcpy(&rpm, &b, sizeof(rpm));

		float speed;
		char c[] = { buffer[12], buffer[13], buffer[14], buffer[15] };
		memcpy(&speed, &c, sizeof(speed));
		float real_speed = speed * 3.6;
		car.gear = buffer[10];
		car.speed = buffer[15, 14, 13, 12];
		car.rpm = (float)buffer[16, 17, 18, 19];
		car.engTemp = buffer[24, 25, 26, 27];

		float engtemp; 
		char d[] = { buffer[24], buffer[25], buffer[26], buffer[27] };
		memcpy(&engtemp, &d, sizeof(engtemp));

		float oilt;
		char e[] = { buffer[36], buffer[37], buffer[38], buffer[39] };
		memcpy(&oilt, &e, sizeof(oilt));
		
		unsigned int showLights;
		char showLightsArray[] = { buffer[44], buffer[45], buffer[46], buffer[47] };
		memcpy(&showLights, &showLightsArray, sizeof(showLights));

		std::cout << "RPM: " << rpm << std::endl;
		std::cout << "Km/t: " << real_speed << std::endl;
		std::cout << "Eng temp: " << engtemp << std::endl;
		std::cout << "Oil temp: " << oilt << std::endl;
		std::cout << "Fuel: " << fuel << std::endl;
		std::cout << "Hazards: " << (showLights & (1 << 6)) << std::endl;
		
	
	}
	closesocket(sockfd);

	std::cout << "Ending socket successfully";
	return 0;
}
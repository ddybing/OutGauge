#pragma once

#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>

struct OutGaugePacket
{
	// This struct describes the different fields of an OutGauge packet (LFS, BeamNG etc)


	unsigned int time; // Time in milliseconds
	char car[4]; // Current car name
	unsigned short flags; // Flags 
	char gear; // Current gear, Reverse = 0, Neutral = 1, First = 2 and so on. 
	char plid; // Current Player ID 
	float speed; // Speed measured in meters per second
	float rpm; // Engine RPM
	float turbo; // Turbo pressure measured in bar
	float engTemp; // Engine/coolant temperature in Celsius 
	float fuel; // Fuel level, 0 is empty, 1 is full. 
	float oilPressure; // Oil pressure measured in bar.
	float oilTemp; // Oil temperature measured in Celsius.
	unsigned int dashLights; // DashLights available
	unsigned int showLights; // Dashlights that are currently switched on
	float throttle; // Throttle position, 0 is not throttle, 1 is "pedal to the metal".
	float brake; // Brake position, 0 to 1.
	float clutch; // Clutch position, 0 to 1.
	char display1[16]; // Usually fuel
	char display2[16]; // Usually settings
	int id; // This is an optional setting

};


float castToFloat(float byte0, float byte1, float byte2, float byte3)
{
	float castedFloat;
	char bytes[] = { byte0, byte1, byte2, byte3};
	memcpy(&castedFloat, &bytes, sizeof(castedFloat));
	return castedFloat;
}

unsigned int castToUnsignedInt(char byte0, char byte1, char byte2, char byte3)
{
	unsigned int castedUnsignedInt;
	char bytes[] = { byte0, byte1, byte2, byte3 };
	memcpy(&castedUnsignedInt, &bytes, sizeof(castedUnsignedInt));
	return castedUnsignedInt;

}

void unpackOutGaugePacket(int *&buffer, int *&structpointer)
{
	int packet[96] = { 0 };
	OutGaugePacket beamng;

	// Time in milliseconds
	beamng.time = packet[0];

	// Name of the current car
	beamng.car[0, 1, 2, 3] = { 0 };
	
	// Flags
	beamng.flags = 0;
	
	// Current gear
	beamng.gear = packet[10];
	
	// Current player ID 
	beamng.plid = packet[11];
	
	// Current speed in M/S
	beamng.speed = castToFloat(packet[12], packet[13], packet[14], packet[15]);

	// Current RPM in 1:1. 
	beamng.rpm = castToFloat(packet[16], packet[17], packet[18], packet[19]);

	// Turbo charger pressure
	beamng.turbo = castToFloat(packet[20], packet[21], packet[22], packet[23]);

	// Current engine/coolant temperature
	beamng.engTemp = castToFloat(packet[24], packet[25], packet[26], packet[27]);

	// Current fuel level from 0 to 1 (0=E, 1=F)
	beamng.fuel = castToFloat(packet[28], packet[29], packet[30], packet[31]);

	// Current oil pressure
	beamng.oilPressure = castToFloat(packet[32], packet[33], packet[34], packet[35]);

	// Current oil temperature
	beamng.oilTemp = castToFloat(packet[36], packet[37], packet[38], packet[39]);

	// Dashboard lights available
	beamng.dashLights = castToUnsignedInt(packet[40], packet[41], packet[42], packet[43]);

	// Dashboard lights currently lit. 0 = not lit, 1 = lit.
	beamng.showLights = castToUnsignedInt(packet[44], packet[45], packet[46], packet[47]);

	// Current throttle position, 0 to 1. 
	beamng.throttle = castToFloat(packet[48], packet[49], packet[50], packet[51]);

	// Current brake position, 0 to 1. 
	beamng.brake = castToFloat(packet[52], packet[53], packet[54], packet[55]);

	// Current clutch position, 0 to 1.
	beamng.clutch = castToFloat(packet[56], packet[57], packet[58], packet[59]);





	





	// return struct with unpacked data in the future
}
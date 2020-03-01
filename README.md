# OutGauge

OutGauge is a personal project in which I will use data from the OutGauge telemetry protocol used in games like BeamNG, Live For Speed and Forza Horizon, in order to control an analog instrument cluster. 



There will be two main components of this project - the **Host** and the **Arduino**. The Host is a small client that can run either on the same computer as the game, or on a separate computer on the LAN. The main task for this component is to receive telemetry packets from the game, unpack the information and send commands to the Arduino. 

The Arduino will control the actual gauges and dashboard lights using relays and transistors.



The Host and the Arduino will communicate over a USB serial port. 


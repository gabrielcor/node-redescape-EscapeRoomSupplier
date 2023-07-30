# UPC API Emulator for ESP32

## API 
This is a full emulation of the UPC API, this way the ESP32 can behave as an UPC device on the network.

It emulates two methods and it returns compatible JSON:

* Actual State: <a href="https://wiki.escaperoomsupplier.com/wiki/Upc-api-v2.0.0#Actual_state_info">Actual State ERS Wiki</a>
* UPC State Change: <a href="https://wiki.escaperoomsupplier.com/wiki/Upc-api-v2.0.0#UPC_state_change">State Change ERS Wiki</a>

For those methods it only returns the "machine state" based on the "Puzzle State" that can be "SOLVED" or "UNSOLVED".

It also emulates the behavior that allows a server to find the UPC device on the network
It implements the functionality described at <a href="https://wiki.escaperoomsupplier.com/wiki/Upc-api-v2.0.0#How_to_find_UPC_on_local_network.3F">How to find UPC ERS Wiki</a> but only the initial discovery, it does not send subsequent packets to the server as described.

## ESP32 Website

If you go to the IP address of the Arduino, it shows a page like the one below where you can interact with the puzzle state
!["ESP32 webpage"](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/ArduinoUPCEmulator01.png)

## UPC webhook
Webhook is in  development 


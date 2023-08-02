# UPC API Emulator for ESP32

## API 
This is a full emulation of the UPC API, this way the ESP32 can behave as an UPC device on the network.

It emulates two methods and it returns compatible JSON:

* Actual State: <a href="https://wiki.escaperoomsupplier.com/wiki/Upc-api-v2.0.0#Actual_state_info">Actual State ERS Wiki</a>
* UPC State Change: <a href="https://wiki.escaperoomsupplier.com/wiki/Upc-api-v2.0.0#UPC_state_change">State Change ERS Wiki</a>

For those methods it only returns the "machine state" based on the "Puzzle State" that can be "SOLVED" or "UNSOLVED".

It also emulates the behavior that allows a server to find the UPC device on the network
It implements the functionality described at <a href="https://wiki.escaperoomsupplier.com/wiki/Upc-api-v2.0.0#How_to_find_UPC_on_local_network.3F">How to find UPC ERS Wiki</a> it not only replies on discovery but also keeps sending packets to the server every 10 seconds.
You can test the functionality with <a href="https://packetsender.com/download">Packet sender tool</a> sending a packet to the port 9811 on the broadcast address.
You can see the result below
!["Packet Sender results"](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/PacketSender.png)

## ESP32 Website

If you go to the IP address of the Arduino, it shows a page like the one below where you can interact with the puzzle state
!["ESP32 webpage"](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/ESP32UPCEmulator.png)

## UPC webhook
Webhook is in  development 


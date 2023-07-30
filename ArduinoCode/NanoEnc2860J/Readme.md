# UPC API Emulator for Arduino Nano with Enc2860J Shield 

## API 
This is a basic emulator of the UPC API, this way the Nano can behave as an UPC device on the network.

It emulates two methods and it returns compatible JSON:

* Actual State: <a href="https://wiki.escaperoomsupplier.com/wiki/Upc-api-v2.0.0#Actual_state_info">Actual State ERS Wiki</a>
* UPC State Change: <a href="https://wiki.escaperoomsupplier.com/wiki/Upc-api-v2.0.0#UPC_state_change">State Change ERS Wiki</a>

For those methods it only returns the "machine state" based on the "Puzzle State" that can be "SOLVED" or "UNSOLVED".

It also emulates the behavior that allows a server to find the UPC device on the network
It implements the functionality described at <a href="https://wiki.escaperoomsupplier.com/wiki/Upc-api-v2.0.0#How_to_find_UPC_on_local_network.3F">How to find UPC ERS Wiki</a> but only the initial discovery, it does not send subsequent packets to the server as described.

## Arduino Website

If you go to the IP address of the Arduino, it shows a page like the one below where you can interact with the puzzle state
!["Arduino webpage"](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/ArduinoUPCEmulator01.png)

## UPC webhook
This development does not implement the webhook described in the ERS API

## Warning
In the process of making this work, we found that the different implementations of the ethernet layer are not very stable.
We don't know if it is because of the Enc2860 shield, or the software implementations but we have run into DHCP issues, and different
problems with the Nano board that suddenly stopped recognizing the shield.

We will be focusing on other boards (mostly ESP32) because they're more stable and have more memory available, but at least this is a decent
implementation and when it works, it might prove useful.

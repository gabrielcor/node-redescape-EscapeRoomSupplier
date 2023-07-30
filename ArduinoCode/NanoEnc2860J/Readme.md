# UPC API Emulator for Arduino Nano with Enc2860J Shield 

## Notes
This is a basic emulator of the UPC API, this way the Nano can behave as an UPC device on the network.

It emulates two methods and it returns compatible JSON:

* Actual State: <a href="https://wiki.escaperoomsupplier.com/wiki/Upc-api-v2.0.0#Actual_state_info">Actual State ERS Wiki</a>
* UPC State Change: <a href="https://wiki.escaperoomsupplier.com/wiki/Upc-api-v2.0.0#UPC_state_change">State Change ERS Wiki</a>

For those methods it only returns the "machine state" based on the "Puzzle State" that can be "SOLVED" or "UNSOLVED".

If you go to the IP address of the Arduino, it shows a page like the one below where you can interact with the puzzle state
!["Arduino webpage"](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/InitialDashboard.png)


## Warning
In the process of making this work, we found that the different implementations of the ethernet layer are not very stable.
We don't know if it is because of the Enc2860 shield, or the software implementations but we have run into DHCP issues, and different
problems with the Nano board that suddenly stopped recognizing the shield.

We will be focusing on other boards (mostly ESP32) because they're more stable and have more memory available, but at least this is a decent
implementation and when it works, it might prove useful.

# UPC API Emulator for ESP32

## API 
This is a full emulation of the UPC API, this way the ESP32 can behave as an UPC device on the network.

It emulates two methods and it returns compatible JSON:

* Actual State: <a href="https://wiki.escaperoomsupplier.com/wiki/Upc-api-v2.0.0#Actual_state_info">Actual State ERS Wiki</a>
* UPC State Change: <a href="https://wiki.escaperoomsupplier.com/wiki/Upc-api-v2.0.0#UPC_state_change">State Change ERS Wiki</a>

### 
Universal State - Input States implementation.
UPC uses the convention where 0 is triggered and 1 is not triggered (I don't know why is inverted, but that's the way it is)
Input state is the decimal representation of a 16 bit map for 16 inputs, where 65535 is all 16 1's.

We only implemented 5 inputs for ESP32 board to be on the safe side, but you can add more if it's needed. We used pins 5,16,17,18 and 19 
as they are deemed safe in <a href="https://randomnerdtutorials.com/esp32-pinout-reference-gpios/">This article</a>
!["ESP32 GPIOs"](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/ESP32_Gpio_Ports.png)


## Discovery
It also emulates the behavior that allows a server to find the UPC device on the network
It implements the functionality described at <a href="https://wiki.escaperoomsupplier.com/wiki/Upc-api-v2.0.0#How_to_find_UPC_on_local_network.3F">How to find UPC ERS Wiki</a> it not only replies on discovery but also keeps sending packets to the server every 10 seconds.
You can test the functionality with <a href="https://packetsender.com/download">Packet sender tool</a> sending a packet to the port 9811 on the broadcast address.

You can see the result below
!["Packet Sender results"](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/PacketSender.png)

## ESP32 Website

If you go to the IP address of the Arduino, it shows a page like the one below where you can interact with the puzzle state
!["ESP32 webpage"](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/ESP32UPCEmulator.png)


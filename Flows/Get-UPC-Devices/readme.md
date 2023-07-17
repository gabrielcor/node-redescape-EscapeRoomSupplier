# GET UPC Devices List 

This flow list all the UPC devices that founds in the network.
One **undocumented** feature of the UPC devices is that they broadcast their id and presence in the network if they receive a specific command via UDP broadcast.

The command is "Hello_from_ERCC" to UDP port 9811.
Once an UPC recognizes this command, it sends it's id within a message that starts with "UNIVERSAL" to UDP port 9811 of the broadcast message originator.

## Flow 
This flow doesn't need any configuration, as it sends the message to the broadcast port and listens to the response.
!["Flow"](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/GETUPCDevices01.png)

It has a dashboard componente that shows all the detected devices.

## IMPORTANT NOTICE
As it uses broadcast by design, it will not work if it has to travel through routers, even if you have "ping" to the UPC, if, for example you have a 192.168.1.45 address and the UPC is at 192.168.5.128, you'll be able to ping the UPC and call it's API but you'll probably not be able to detect it with this method.


!["Device detected via UDP"](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/GETUPCDevices02.png)


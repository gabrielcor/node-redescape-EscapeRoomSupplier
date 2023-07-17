# UPC Emulator

## What's with the emulator?

The idea behind an UPC emulator is two fold:
* Enable experimentation with UPC functionality without having one
* Add virtual UPCs to your environment so that you can test and prototype an Escape Room without the physical devices

Also it is fairly easy to emulate an UPC, as it is only a matter of emulating the "state" API and then have the "state" of the virtual UPC device in the flow context.

## Emulator
UPC Emulator is just an API with one method published on the standard port of node-red via the "http in" node.

!["UPC Emulator"](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/UPCEmulator01.png)

### Configuration
For this emulator to work, we need to configure two nodes
* Initialize Device (change node): where we need to give a deviceId to the virtual device. Note that we give a number starting with "99" so that it don't clash with real UPC devices
* UPC API (http in node): put the URL of where (with the base address of the node-red server) this API will be listening for requests. It is advisable to use the convention upc/mock/nnn where nn = the deviceId

!["Initialize device node"](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/UPCEmulator02.png)

!["UPC API http node"](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/UPCEmulator03.png)

Once it is deployed, we can call the API in the same way we called an UPC device, just with the updated URL
!["Call from Postman"](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/UPCEmulator04.png)

### Running
Please note that the emulator have a dashboard component where you can solve and reset the UPC, to emulate reset and resolution of the puzzles
!["Dashboard componente"](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/UPCEmulator05.png)

If we want to add it to the monitored UPC dashboard, we just have to copy the GET_UPC_State flow and change the target URL
!["GET_UPC_State flow "](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/UPCEmulator06.png)

And we can see real UPCs and virtual UPCs side by side in the dashboard
!["Devices dahsboard tab "](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/UPCEmulator07.png)

# Get UPC State of Keypad

This flow gets the UPC state of the Keypad Emulator and shows the result in a Devices Tab in the Dashboard.


![Get UPC State Keypad](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/GetKeypad0.png)


To acomplish that, we initialize the following flow variables
### deviceUrl: the URL of the UPC device in the network including all the GET command. This device is http://127.0.0.1/?command=state which is conected at 127.0.0.1

* IMPORTANT! Take into account that the IP address should be changed if necessary.

###  deviceName: the name that we want to show for the device, ESRS-TEST06.

###  description: Keypad.

![Initialize target URL & device data flow properties](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/GetKeypad1.png)


The rest of the flow is pretty straightforward and you don't have to modify it unless you want specific behavior for the dashboard.

* Basically what it does is:

1) Connect to the "tick" event so that every second is invoked.
2) Set the http request to the target URL we set up on initialization.
3) Call the API on the UPC device and get the JSON.
4) Convert the JSON to an object.
5) Parse the JSON and send it to display in the dashboard.


![View on dashboard](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/GetKeypad2.png)

### In the last screenshot, you can see the newly added reset and solve buttons, which allow interaction with the UPS from the dashboard where its status is displayed.
# Get Universal Puzzle Controller State ogging
## Official documentation 

The official documentation is at <a href="https://wiki.escaperoomsupplier.com/wiki/Universal_Puzzle_Controller_API_v1.0.0">Escape Room Supplier documentation API</a>. Problem is that the documentation for the most part of the invocation is wrong. 
Nevertheless, at least for the "Actual state info","UPC state change",  the values of the response are accurate.
Please note that the "input states" value is a bit operation of the binary version of the actual input states, and it actually suggests to use <a href=" https://www.rapidtables.com/convert/number/decimal-to-binary.html">this calculus</a> to get the actual state.

Also there is an "UPC input override" method that is not documented and that we have detected using Wireshark and the Escape Room Supplier software.

There is a POSTMAN collection in this folder, that you can use to control an UPC device if you have one connected to the network.
This postman collection is tested with hv=5, sv=01.01.06 of the UPC controllers

## Getting an UPC state from node-red
This flow gets the UPC state and shows the result in a Devices Tab in the Dashboard

!["GET_UPC_State"](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/GetUPCState01.png)

To acomplish that, we initialize the following flow variables
* deviceUrl: the URL of the UPC device in the network including all the GET command (e.g.:http://192.168.1.124?command=state for a UPC device that is at 192.168.1.124)
* deviceName: the name that we want to show for the device
* description: the description for this particular device.

!["Update flow variables"](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/GetUPCState00.png)

The rest of the flow is pretty straightforward and you don't have to modify it unless you want specific behavior for the dashboard.

Basically what it does is:
* Connect to the "tick" event so that every second is invoked
* Set the http request to the target URL we set up on initialization
* Call the API on the UPC device and get the JSON
* Convert the JSON to an object
* Parse the JSON and send it to display in the dashboard.

Note: it only displays the state of the UPC controller, not each individual input state

!["Dashboard"](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/GetUPCState02.png)

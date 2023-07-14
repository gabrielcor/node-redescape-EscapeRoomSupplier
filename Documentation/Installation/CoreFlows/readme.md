# How to Install Core Flows
## What are "Core Flows"
Core Flows are the ones that have the basic functionality and trigger the basic events for all other flows.
Without this Core Flows most of the other recipes will not work (if any) because they all asume this flows have been installed and instantiated.

## Install Core Flows
Download the file <a href="https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/tree/main/Flows/Core">ERS_Core.json</a> to a local directory.

Open the import nodes dialog and select "select a file to import" selecting the ERS_Core.json file on the directory where you have downloaded it. !["Select File "](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/ImportNodes.png)

After the import finishes correctly, you should have on your node-red server something similar to this:
!["Main Screen "](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/CoreFlows01.png)

You must have three flows:

* Main: this has the System Events to initialize and execute every second. Dashboard nodes to enable interaction with the Game State and the timer, and finally globally relevant nodes like CSS-styles, global exception handling and the MQTT server node
* In-Game Display: This is a provided solution to have a display that you can put on your Room, to give hints and/or display the timer. It uses a uibuilder node, so it must be configured as depicted below if you wish to use it.
* ERS_Logging: Log solution, this allows all MQTT traffic to be logged. It is a useful tool so that every event that we want to log for future audit or stats gets persisted.


## Configure In-Game Display  
To configure In-Game Display, go to In-Game Display and double-clic on the room_display node.
!["Room display "](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/CoreFlows02.png)

Once you've done that, you should see a folder where the uibuilder expects the source file to be 
!["Core Files "](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/CoreFlows03.png)

Go to that directory with the Windows Explorer
!["Explorer "](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/CoreFlows04.png)
and substitute the content with the files that you will find at <a href="https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/tree/main/uibuilder/room_display/src" >Uibuilder files</a> 

Clic on the "Libraries" tab and add the libraries
* bootstrap
* bootstrap-vue
* jquery
* vue

using the "+ add" link in the bottom of the dialog
!["Explorer "](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/CoreFlows05.png)

If all the configuration was done correctly, after you Deploy the solution you must be able to clic the "Open" button in the uibuilder dialog and see something similar to the following display
!["Explorer "](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/CoreFlows06.png)

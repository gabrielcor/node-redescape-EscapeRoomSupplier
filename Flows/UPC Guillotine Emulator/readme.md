# Guillotine Emulator 

This flow is an emulator with one slider and three led lights, once the slider is moved to the correct position (number 10), it turns on the three lights, showing the puzzle es completed. 

## Emulator View on Dashboard

![Emulator View on Dashboard ](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/guillotine0.png)


## How to Solve the Puzzle

The user must move the slider to the top position, once it's there, the LED lights are turned on, showing the puzzle was solved.


![Emulators showing led lights](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/guillotine1.png)


## How Does the Emulator Works

![Emulator Nodes](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/guillotine2.png)

Once the slider ir in the top position, the switch node sends a message to the change nodes. The top one identified as flow.deviceState, changes the flow variable "deviceState" to 2, showing that the puzzle was successfully completed. The second change node sends a msg.payload to the LED lights to turn them on. 

Also, when the slider is bottom position, the switch node sends a message to the change nodes.
The bottom one identified as flow.deviceState, changes the flow variable "deviceState" to 0. 
The middle change node sends a msg.payload to the LED lights to turn them off.

### Output
After the players lower the key, it activates the entire game (electronic elements, lights, sounds, and effects). 
Once the game starts, it cannot be stopped.

### IMPORTANT
To use the LED Lights in Node-RED, installing the LED node is needed. 

![Led node](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/guillotine3.png)


## Reset Button
![Reset button](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/guillotine4.png)

For this emulator, I added a "change" node to the reset button so that when the emulator is reset, the slider is moved to the bottom position, turning off the LED lights, and changing the flow variable "deviceState" to 0. 


## Full Flow View 
![Full Flow View](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/guillotine5.png)


### CSS Styles
CSS style is inside the node template identified as "Style".
 
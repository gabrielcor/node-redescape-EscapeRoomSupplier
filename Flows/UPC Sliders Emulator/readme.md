# Sliders Emulator

This flow is an emulator of 6 sliders that, when placed in the correct position, modifies the flow variable 'deviceState' to 2.

## Emulator View on Dashboard
![Emulator view on dashboard](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/SliderEmulator1.png)

## Emulator View on Node Red
![Emulator view on node red](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/sliderEmulator2.png)

Firstly, from the "dashboard" palette, I used six "Slider" nodes. These, when moved and released to a specific position, inject a message with the position number to the "set flow.sliderNumberNN" node they are connected to. This node sets a flow variable with the obtained number.

To have it send the slider's position number when released in the desired position, you need to edit the "Slider" node in the "Output" property and select "only on release".

![Slider node configuration](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/sliderEmulator3.png)

## Validation
![Slider node configuration](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/sliderEmulator4.png)

The number that needs to be formed with the positions is 241091.

The "inject" node sends a message every second to the "function (validation)" node, which checks every second if each set flow variable represents the correct number.

If you guess the number, the node returns the msg.payload "resolved" which proceeds to the "Switch" node. 
The "Switch" node evaluates whether it's the correct message and proceeds to the "set flow.deviceState" node, which modifies the value of the flow variable "deviceState" to 2, indicating that the puzzle is complete.

The code inside the node function for validation is written in JavaScript.

```javascript
let slider1 = flow.get("sliderNumber1")
let slider2 = flow.get("sliderNumber2")
let slider3 = flow.get("sliderNumber3")
let slider4 = flow.get("sliderNumber4")
let slider5 = flow.get("sliderNumber5")
let slider6 = flow.get("sliderNumber6")


msg.payload = (slider1 == 2 && slider2 == 4 && slider3 == 1 && slider4 == 0 && slider5 == 9 && slider6 == 1) ? "resolved" : "wrong";
return msg
```

### Correct Position of Sliders
![Correct position of sliders](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/sliderEmulator5.png)

### Flow Variables of the Emulator
![Correct position of sliders](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/sliderEmulator6.png)

### Full Flow View
![Full Flow view](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/sliderEmulator7.png)

### CSS Style
CSS style is inside the node template identified as "Style Slider Emulator".
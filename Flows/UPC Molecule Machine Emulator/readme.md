# Molecule Machine Emulator

This flow is an emulator with 16 buttons and 4 gauges which, once the molecule composition is guessed correctly, increase their value and change color to indicate that the combination worked and the puzzle is solved.    

## Emulator View on Dashboard 

![Emulator View on Dashboard ](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/moleculeMachine0.png)

## How to Solve the Puzzle

The user must arrange 'H2 - N - C2 - H2,' starting from left to right, selecting the correct option in each group of four buttons.

Once the combination is guessed correctly, the gauges change as follows:

![Emulators showing green gauges](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/moleculeMachine1.png)

## Flow Variables Established by the Emulator

![Flow Variables Established by the Emulator](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/moleculeMachine2.png)


## How Does the Emulator Works

![Buttons](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/moleculeMachine3.png)

First step, set the value of the flow variables 'simbolNN.'. Every time the user clicks on one of the buttons, the payload of the button is sent to the 'set flow.simbolNN' node, which sets it as a flow variable sent by any of the four connected buttons.


Second step, use the flow variables:

![flow valitation](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/moleculeMachine4.png)


The "timestamp" node injects flow every second.

The "validation" node checks every second that the value of the flow variables "simbolNN" is correct and sends the message "ok" to the switch node, which in turn performs a new validation of this message, and finally transmits it to the "set flow.deviceState" node, changing the flow variable "deviceState" to 2, indicating that the puzzle has been solved.

Validation Node JS Code
```javascript
let element1 = flow.get('simbol1')
let element2 = flow.get('simbol2')
let element3 = flow.get('simbol3')
let element4 = flow.get('simbol4')

msg.payload = (element1 === "H2" && element2 === "N" && element3 === "C2" && element4 === "H2") ? "ok" : "not";
return msg
```

The "check symbols" node also verifies every second that the value of the flow variables "simbolNN" is correct, and in case of a positive outcome, it sends four different values to the gauges to change their value and color. The purpose is purely aesthetic, allowing the user to visually perceive that the puzzle is complete.

Check Symbols Node JS Code
```javascript
let element1 = flow.get('simbol1')
let element2 = flow.get('simbol2')
let element3 = flow.get('simbol3')
let element4 = flow.get('simbol4')

if(element1 == "H2" && element2 == "N" && element3 == "C2" && element4 == "H2"){
    
    let m1 = { payload: 95 };
    let m2 = { payload: 98 };
    let m3 = { payload: 97 };
    let m4 = { payload: 94 };

    return [m1, m2, m3, m4]
} else{
    let m1 = { payload: 9 }
    let m2 = { payload: 8 }
    let m3 = { payload: 7 }
    let m4 = { payload: 4 }
    return [m1, m2, m3, m4]
}
```

## Reset Button
![Reset button](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/moleculeMachine5.png)

For this emulator, I added a "change" node to the reset button so that when the emulator is reset, the global variables "simbolNN" have their values modified, causing the gauges to return to their original measurements.


## Full Flow View 
![Full Flow View](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/moleculeMachine6.png)


### CSS Styles
CSS style is inside the node template identified as "molecule machine style".
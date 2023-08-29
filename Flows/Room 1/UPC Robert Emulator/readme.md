# Robert Emulator

This flow is an emulator comprised of a slider that, when moved, changes the background color of the 'robert' div, which starts in black. 
As the slider is moved, the background color gradually lightens, revealing the hidden word 'robert.' The actual word that users need to discover has not yet been defined, so the name of the puzzle was used.

## Emulator View on Dashboard 

![Emulator View on Dashboard ](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/robert0.png)


## How to Solve the Puzzle

The user must move the slider until they can read the word. After doing so, they should type it into the input labeled 'Answer.' If correct, below that input, the puzzle will display 'Correct'; if incorrect, it will display 'Incorrect.'

In the case of a correct answer, it will modify the 'deviceState' to 2, indicating that the puzzle is complete


![Emulators showing correct answer](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/robert1.png)


## How Does the Emulator Works

![Full Flow](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/robert2.png)


Firstly, when the slider is moved, it sends the value of its position in the msg.payload to the function node.

The function node validates the received value and based on it, adjusts the background of the "Robert" div until the hidden word becomes visible.

![Slider and function node's](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/robert3.png)


### Function Node JS

```javascript
let sliderValue = msg.payload

if (sliderValue == 1 || sliderValue == 2 || sliderValue == 0){
    msg.payload = "#000000"
    return msg
}

if (sliderValue == 3 || sliderValue == 4 ) {
    msg.payload = "#020202"
    return msg
}

if (sliderValue == 5) {
    msg.payload = "#121111"
    return msg
}

if (sliderValue == 6) {
    msg.payload = "#121111"
    return msg
}

if (sliderValue == 7) {
    msg.payload = "#1f1c1c"
    return msg
}

if (sliderValue == 8) {
    msg.payload = "#2e2727"
    return msg
}

if (sliderValue == 9) {
    msg.payload = "#382e2e"
    return msg
}
if (sliderValue == 10) {
    msg.payload = "#635050"
    return msg
}
```

![Second part of the flow](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/moleculeMachine4.png)

Secondly, the text input node labeled "answer" receives the user's response and sends it to the function node for validation.

If the response is incorrect, it sends the string "INCORRECTO" to the text input node to display on the dashboard.
If the response is correct, it sends the string "CORRECTO" to the text input node for display on the dashboard and also to the switch node. 
The switch node then validates if it's the indicated word and sends a msg.payload to the change node. The change node ultimately modifies the flow variable "deviceState" to 2, indicating that the puzzle is solved.

Function node JS code   
```javascript
let inputMessage = msg.payload

if(inputMessage == "ROBERT" || inputMessage == "robert" || inputMessage == "Robert"){

    msg.payload = "RESOLVED!"
    return msg
} else {
    msg.payload = "INCORRECT!"
    return msg
}
```

Also, when the answer is correct, the switch node sends a msg.payload to the change node, that clears the text input node where the user types their answer.


## Reset button

![Reset button with change nodes](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/robert5.png)

When pressed, in addition to changing the flow variable 'deviceState' to 0, it sends its 'msg.payload' to two change nodes.
One of them resets the slider to position 0.
The second one clears the text input that informs whether the answer is correct or incorrect.


## Output
The users receive a clue for puzzle 1019.
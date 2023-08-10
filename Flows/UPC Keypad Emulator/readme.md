# Keypad Emulator

This flow is a keypad emulator with buttons from 1 to 9, Clear, and Evaluate. Below the keypad, there is a text input that informs whether the user entered the password correctly after clicking the evaluate button.

## Emulator View on Dashboard 

![Emulator View on Dashboard](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/Keypad0.png)

### How to Solve The Puzzle
The password that the user needs to enter is '241091' and press the 'evaluate' button. After that, below the keypad, the result can be seen, which can be either 'CORRECTO' or 'INCORRECTO'.

If the useres think they entered the password incorrectly, they can press the 'clear' button and start over.

## Emulator After Wrong Answer
![Emulator After Wrong Answer](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/Keypad1.png)


## Emulator View on Node Red
![Emulator View on Node Red](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/Keypad2.png)


## How does it work?
The button nodes send their value to the 'evaluate password' function node.

### Evaluate password JS code

```javascript
let correctPassword = "241091";

if (msg.payload === "CLEAR") {
    flow.set("enteredPassword", "");
} else if (msg.payload === "EVALUATE") {
    let enteredPassword = flow.get("enteredPassword") || "";
    if (enteredPassword === correctPassword) {
        
        msg.payload = "Correcto"
        flow.set("enteredPassword", "");
        return msg
    } else {
        msg.payload = "Incorrecto"
        flow.set("enteredPassword", "");
        return msg
    }
} else {
    let enteredPassword = (flow.get("enteredPassword") || "") + msg.payload;
    flow.set("enteredPassword", enteredPassword);
}

return msg;
```

First, it evaluates whether the received payload is 'CLEAR,' and if positive, it assigns the value '' to the 'enteredPassword' flow variable.

Secondly, it evaluates whether the received payload is 'EVALUATE,' which compares the password stored in the 'correctPassword' variable with the password stored in the 'enteredPassword' flow variable. In the event that both passwords match, it sends 'Correct' as msg.payload and simultaneously assigns the value '' to the 'enteredPassword' flow variable.

In the case of a negative match, it sends 'Incorrect' as msg.payload and also assigns the value '' to the 'enteredPassword' flow variable.

Finally, in the 'enteredPassword' variable, each msg.payload that enters the node and doesn't fall into the mentioned if statements accumulates in that variable and is later set as a flow variable.

## Switch Nodes Adter Evaluate Password
![Switch Nodes Adter Evaluate Password](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/Keypad3.png)

If the msg.payload is correct or incorrect, the switch nodes are connected to the 'text input' node, which displays the mentioned messages on the dashboard, according to the puzzle's resolution.

## Puzzle Resolution 
![Puzzle Resolution](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/Keypad4.png)
If the msg.payload of the function node is 'Correct,' it proceeds through the switch node to the 'set flow.deviceState' node and assigns the value '2' to the flow variable 'deviceState,' indicating that the puzzle has been completed and resolved.



 ## Full Flow View 
![Full Flow View](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/Keypad5.png)

### CSS Styles
CSS style is inside the node template identified as "STYLE".
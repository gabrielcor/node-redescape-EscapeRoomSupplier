# Piano Emulator

This flow is a piano emulator, where to solve the puzzle, the user has to perform a specific musical combination. 

## Emulator View on Dashboard

![Emulator View on Dashboard](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/pianoEmulator0.png)

## Puzzle solving method

In this case, the user must derive from a story/poem (is in spanish)the sequence in which they should press the piano keys. Each key plays the sound corresponding to the notation written on it.

### Story/Poem:

"En las teclas del piano encontrarás la pista
En sus notas encontrarás la salida
Comienza un sueño de avendura **do**...
donde encontrarás lugares **re** pensar el temor 
un tercer tono te lleva a **mi** fantasía
y seguidamente **fa**scinado quedarás
y extrañarás volver a ver el **sol**
arma tus notas y decifra el enigma en paz
o aquí por siempre atrapado quedarás"

The clues are highlighted to make them easy to identify. The user must form the string 'doremifasol' by pressing the keys in order.

If successful, the word 'CORRECTO!' will appear below the piano; otherwise, it will show 'INCORRECTO!'

The concept of obtaining the keys from a story or poem can be modified or expanded to add more difficulty. I also thought about playing music that users can listen to and try to replicate the order using the keys. There seem to be numerous possibilities for puzzle-solving involving a piano.

## Full Flow View 
![Full Flow View ](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/pianoEmulator1.png)



# IMPORTANT --> Play Audio Node.
Firstly, in order for it to work, you need to install the "Play Audio" node for the palette, that receives a sound and plays it.

![Play Audio Node ](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/pianoEmulator2.png)

## How Does the Emulator Works


![Buttons and get file ](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/pianoEmulator3.png)
First, there are the buttons that send their payloads to two places simultaneously.

Let me explain the 'read file' node first. This node is configured to search for the sound corresponding to each key. In this case, I downloaded the sounds to my computer, and for the node to locate them, you need to provide the absolute path to the file.

This path is loaded into the 'filename,' and also in the 'output,' you need to select the option as shown.

![get file config ](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/pianoEmulator4.png)

After finding the file, this node sends it to the 'play sound' node and plays it for the user to hear.

Furthermore, the buttons are connected to a 'function' node that performs payload validation and compares it with the correct combination.

Initially, the received payload is set as the flow variable 'enteredPiano' Once this variable reaches 11 characters, it compares its content with the 'correct' combination and resets the value of 'enteredPiano' to an empty string.

Upon a successful match, as mentioned before, it sends the payload 'CORRECTO!' Otherwise, it sends 'INCORRECTO!'.

## Funcion Node JS Code
```javascript
let pianoCombination = "doremifasol"

let enteredPiano = (flow.get("enteredPiano") || "") + msg.payload;
flow.set("enteredPiano", enteredPiano);

if(enteredPiano.length == 11){
    if (enteredPiano == "doremifasol"){
        msg.payload = "CORRECT!"
        flow.set("enteredPiano", "")
        return msg
    } else {
        msg.payload = "INCORRECT!"
        flow.set("enteredPiano", "")
        return msg
    }
}

if (enteredPiano.length > 11){
    flow.set("enteredPiano", "")
    msg.payload = "exceso arreglado"
    return msg
}
```

The 'function' node is connected to three 'Switch' nodes. The top one evaluates whether the payload is 'CORRECT!' and then sends it to the 'change' node to update the value of 'deviceState' to 2, indicating that the puzzle is solved.

The remaining two 'Switch' nodes serve the purpose of sending the received payload to the 'input text' node, allowing the user to see it on the screen

![switch](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/pianoEmulator5.png)

### CSS
CSS style is inside the node template identified as "piano emulator style".

## Piano Sounds were added to this folder
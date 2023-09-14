# "Cyberpunk Machine" Node RED solution.

This is a Node RED solution for the "Cyberpunk Machine" where participants can view images, videos, and clues sent by the host/game master.

I designed and implemented it with the goal of making it user-friendly, simple, and intuitive. Also, to occupy the least amount of space possible on the dashboard.

While videos are currently sent manually here, the solution can be automated once the videos corresponding to the act are available, reducing human intervention to a minimum.

## Dashboard View

![Dashboard View](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/cyberpunk0.png)

![Get UPC State Sliders](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/GetSlider0.png)

### Clues
The game master, in the "Clue Picker" dropdown menu, can choose one of the predefined clues, which will be displayed in written form on the screen. If needed, below the dropdown menu, the Game Master can type a custom clue to assist the users. These clues will appear on top of videos or images without affecting their functionality for a duration of 5 seconds, after which they will disappear.

### Images 
The game master, in the "Img Picker" dropdown menu, should select one of the predefined images. One of the options is "clear," which, when selected, turns the screen completely black.

### Videos 
The game master, in the "Video Picker" dropdown menu, should choose one of the predefined videos. One of the options is "clear," which, if selected while a video is playing, cancels the playback and displays one of the images as the background. In this case, the "bat" image is configured.

![Img Picker dropdown menu extended](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/cyberpunk1.png)


## Node-RED Solution

Images, videos, and clues are all sent to the ui_builder node for rendering.

![ui_builder](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/cyberpunk2.png)

## Clues 

![clues flow](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/cyberpunk3.png)

This flow is quite intuitive. The dropdown node, labeled as "Clue Picker," contains predefined clues that can be added or removed on-demand during the game.

Next, there's a text input node labeled as "Escribe Pista," where the Game Master can input custom clues.

These nodes are linked to a "trigger" node that performs two main actions:

Initially, it lets the msg.payload pass through to a "change" node, which sends the received message within the "msg.displayText" field to the ui_builder node for rendering the text.

After 5 seconds, the trigger node sends the value " " (a space character), clearing the message on the screen by setting "msg.displayText" to an empty string.

Additionally, these nodes are also connected to a "read file" node labeled as "getfilewithSound." This node retrieves a sound from a local folder and plays it when the message is rendered to alert or draw attention to the users.

IMPORTANT: To obtain the sound, you must specify the absolute path to the sound file in the configuration of the "read file" node.

Finally, the "trigger" node below the dropdown and text input, after 5 seconds of sending the clue, returns to its original value in the dropdown and clears the text input field.

## Images 

![images flow](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/cyberpunk4.png)

The dropdown node labeled as "Img Picker" contains predefined image options and also includes an option "clear" that turns the screen black.

Once the game master selects one of the options, the dropdown node sends the corresponding msg.payload to all the switch nodes, but only the switch node configured for that option will let the message pass through.

Then, the message is received by the "change" node, which sends the image path within "msg.imageSrc" to the ui_builder node for rendering. The images are stored in a folder within the ui_builder node.

### Example of the configuration of one of the 'change' nodes.

![change node example](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/cyberpunk5.png)

The trigger node, just like in the clues flow, returns to the dropdown menu to its initial value after 5 seconds.

## Videos 

![Videos flow](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/cyberpunk6.png)

IMPORTANT: This flow works for manually sending videos, as well as for combining audio and video. It will be modified so that some of the videos are played automatically, taking data from the UPC to initiate or modify playback.


![manual video flow](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/cyberpunk7.png)


The dropdown node labeled as "Video Picker" includes predefined video options and also features a "clear" option that sets the screen to the bat imgage.

Once the game master selects one of the options, the dropdown node sends the corresponding msg.payload to all the switch nodes, but only the switch node configured for that option allows the message to pass through.

Then, the message is received by the "change" node, which sends the video path within "msg.videoOverlaySrc" to the ui_builder node for rendering. Additionally, with video playback, it removes the selected background image, leaving the screen black to avoid distracting from the video.

In the last image attached to the flow, the video lasts for 10 seconds. Therefore, the trigger node, configured to trigger after this mentioned time, sends a message to the "change" node to set "msg.videoOverlaySrc" to " ", which removes the video once it has finished. Additionally, the trigger node is connected to another "change" node that loads the bat image once the video is removed.

### Video + Audio 

![manual video flow](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/cyberpunk8.png)


In case it's needed, I added a variation where, before playing the video, an audio is played. When the audio finishes, the trigger node sends a message to the change node to play the corresponding video. In this case, the video is configured to loop.

### Clear Video

![manual video flow](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/cyberpunk9.png)

As previously explained, if the game master selects the "clear" option, the video is removed, and the bat image is rendered.

## CSS Style on dashboard
 
![manual video flow](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/cyberpunk10.png)


## Full Node RED solution 

![manual video flow](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/cyberpunk11.png)



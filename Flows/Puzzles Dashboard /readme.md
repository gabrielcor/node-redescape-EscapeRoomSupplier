# New Puzzle Dashboard for the Game Master

I've designed a flow that displays the puzzles for each room in order on the dashboard, allowing real-time tracking of user progress.

For each puzzle, the dashboard showcases its UPC, description, deviceName, ID, status (armed and solved), start time, and completion time.

Furthermore, I've incorporated "reset" and "solve" buttons for each puzzle, enabling the Game Master to interact with them.

This dashboard is presented on a newly created tab named "Devices Dashboard."

IMPORTANT: If you intend to change the tab's name, you'll need to update the JSON file located within the buttons, as explained below.

![View of Dashboard](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/dashboard0.png)


## Flow View on Node RED

![Flow View on Node RED](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/dashboard1.png)


## How to Display Puzzles for Each Room

Firstly, in the "Get_UPC_State" flows for each puzzle, I've set up the final template where the received data is displayed for viewing on the new dashboard.

Next, each button you see (Room 1, Room 2, and Room 3), when pressed, displays the puzzles belonging to the corresponding group for the selected room.

To execute this action, within the msg.payload of each button, a JSON file is configured, indicating which room to show and which ones to hide.

NOTE: "Group" in this context refers to the set of puzzles associated with each room. Please replace "group" with the accurate term if applicable in your context.

```json
{
    "group": {
        "hide": [
            "Devices_Dashboard_Room_2",
            "Devices_Dashboard_Room_3"
        ],
        "show": [
            "Devices_Dashboard_Room_1"
        ]
    }
}
```

The preceding JSON object needs to be modified for each button based on the room you want to display.

To achieve this, you need to load an object that has the key "group," which in turn contains an object with keys "hide" and "show," each with an array containing each room you want to show/hide.

IMPORTANT: To show/hide each room, you must first write the name of the tab where the groups are located, followed by the name of the room.

Devices_Dashboard_ --> tab name
Room_1 --> group name

## UI Control Node

All buttons are connected to a "ui control" node. This node enables dynamic control of the dashboard, which functions to display the corresponding room upon receiving the msg.payload from the buttons. This doesn't require any additional configuration in this case.

## CSS Styles

Within the following node, you will find the CSS styles.

![CSS Style](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/develop_Rodrigo/Documentation/screenshots/dashboard2.png)
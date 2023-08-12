# node-redescape-EscapeRoomSupplier
## Introduction
This project aims to create several templates to use in node-red to control <a href="https://www.escaperoomsupplier.com/">Escape Room Supplier</a> devices.

## Architecture
This is a "recipe based" approach, where each "recipe" will be a json file that contains a node-red definition for a flow that can be used in a stand-alone way.
There will be some dependencies on previous flows but that will only be to the flows that are part of the "core" architecture and we will try to keep them to a minimum.
This "base" flows will take care of handling common operations and ensure that all recipes follow the same patterns & practices.

## Objectives
* Create a browser-based dashboard for gamesmasters that shows the status of all puzzles in the room, providing options to remotely solve or reset them
* Integrate UPC (Universal Puzzle Controller) Boards to the dashboard enabling the solve/reset functionality
* Use the APIs of the UPC (Universal Puzzle Controller) boards to see and modify the state of the sensors / puzzles.
* Start/stop a game timer, make manual adjustments, and display time remaining on an in-room display for players that can be styled to match the theme of your room
* Display pre-defined or custom hints on various devices - a monitor, LCD display, printer etc.
* Provide the ability to emulate an UPC, enabling the modeling of an Escape Room with that devices in mind
* Provide more "creative" and increase the density of puzzles that we can create for each UPC 
* Enable recording of telemetry data to analyze escape room behavior
* Provide Escape Room state persistence in a database (SQL)

## Screenshots
### Dashboard
!["Example GM Dashboard"](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/InitialDashboard.png)

## Features
* Free and open source - Completely free to download and use. 

## To Get Started
### Install node-red and basic Palette
To install node-red and basic palette we have this <a href="https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/tree/main/Documentation/Installation">Tutorial</a>

### Install Core Flows 
To install Core Flows follow this <a href="https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/tree/main/Documentation/Installation/CoreFlows">Tutorial</a>

### Flow documentation
Documentation is at  <a href="https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/tree/main/Flows">Flows</a>

To use a Flow download the json file from the site and import it on  your own Node-RED instance. 

## UPC Emulation
All the samples are based on the API exposed by UPC devices v2 as documented at <a href="https://wiki.escaperoomsupplier.com/wiki/Upc-api-v2.0.0">UPC API v2.0</a>

We implemented two versions of the emulator:
* ESP32 (recommended): <a href="https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/tree/main/ESP32Code">ESP32 UPC API v2.0 Emulator</a> 
* Arduino Nano with ENC2860J Shield:  <a href="https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/tree/main/ArduinoCode/NanoEnc2860J">Arduino Nano Enc2860J UPC API v2.0 Emulator</a> 


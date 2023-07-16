# Logging
## Enabling logging in flows

The logging flow, has two ways to detect messages that we want to log.
!["Example GM Dashboard"](https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/Logging01.png)

Any Link Out that we connect to the Link in Called "Log" (with the "Log Event" comment in the picture) gets logged if logging is enabled.
Also if MQTT log is enabled, all MQTT traffic will be logged.

## Example
The flow "Main" has examples of both options. 
* On Initialization
* Start: this one has the two options implemented so you can see how it's done via MQTT
* Stop
* Reset
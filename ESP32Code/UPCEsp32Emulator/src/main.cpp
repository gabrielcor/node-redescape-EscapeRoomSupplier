#include <WiFi.h>
#include <WifiUdp.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <wifi_config.h>


// GPIO to check this version will always check 5 pins (5,16,17,18,19)
// https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
// or https://github.com/gabrielcor/node-redescape-EscapeRoomSupplier/blob/main/Documentation/screenshots/ESP32_Gpio_Ports.png

const byte numSensors = 5;
const byte sensorPins[numSensors] = {5,16,17,18,19};
// Create an array to keep track of the last state of the pins
byte lastState[numSensors] = {0,0,0,0,0};
// The current state of the all sensors if they were 16 (just to be compatible with ERS UPC)
byte currentState[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int currentStateDecimal = 65535;

WiFiServer server(80);
char deviceMacAddress[18]; // MAC address of the device

// Variables to emulate UPC
char* EstadoPuzzle="UNSOLVED";

// Variables to work with HTTP
char stringReceived[100];
char postReceived[100];
int lugReceived = 0;
int lugpostReceived = 0;
bool ComandoState = false;
bool ComandoPost = false;

// Variables to work with UDP
WiFiUDP udp;
const unsigned int udpPort PROGMEM = 9811;
char packetBuffer[24];  // buffer to hold incoming packet,
char ReplyBuffer[30]; 

bool UDPReceived = false; // Flag to indicate that a UDP packet has been received and we have to send a reply every 10 seconds
IPAddress remoteUdpServer; 
unsigned long lastUDPTime = millis();


void setup() {
 
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  // Print the IP address
  Serial.print(F("IP Address: "));
  Serial.println(WiFi.localIP());

  // Get Mac Address and assign it to deviceMacAddress
  Serial.print(F("MAC Address: "));
  sprintf(deviceMacAddress, "%02X:%02X:%02X:%02X:%02X:%02X", WiFi.macAddress()[0], WiFi.macAddress()[1], WiFi.macAddress()[2], WiFi.macAddress()[3], WiFi.macAddress()[4], WiFi.macAddress()[5]);
  deviceMacAddress[17] = '\0';
  Serial.println(deviceMacAddress);
  
  // Intitialize the input pins
  for(int i=0; i<numSensors; i++){
    pinMode(sensorPins[i], INPUT_PULLUP);
  }


  // Start Udp server
  udp.begin(udpPort);
  Serial.print(F("UDP server started at port "));
  Serial.println(udpPort);
  ReplyBuffer[30] = '\0';


  server.begin();
}



void SendMessage2(WiFiClient client)
{

          char elapsedSecondsStr[12];
          sprintf(elapsedSecondsStr, "%lu", millis()/1000);


          if (!ComandoState)
          {
            client.println(F("HTTP/1.1 200 OK"));
            client.println(F("Content-Type: text/html"));
            client.println(F("Connection: close"));  // the connection will be closed after completion of the response
            client.println(F("Refresh: 15"));  // refresh the page automatically every 5 sec
            client.println();
            client.println(F("<!DOCTYPE HTML>"));

            client.println(F("<html>"));
            client.println(F("</html>"));
        
            client.print(F("<html><head><title>Emulando UPC</title></head><body><div style='text-align:center;'><h1>ESP32 UPC emulator mac address - "));
            client.print(deviceMacAddress);
            client.print(F(" </h1>Tiempo transcurrido : "));
            client.print(elapsedSecondsStr);
            client.print(F(" segundos<br /><br />Estado del Puzzle: "));
            client.print(EstadoPuzzle);
            client.print(F(" <br /><a href=\"/?status=SOLVED\"><input type=\"button\" value=\"SOLVED\"></a><a href=\"/?status=UNSOLVED\"><input type=\"button\" value=\"UNSOLVED\"></a><br /><br /></body></html>"));
          }
          else
          {
            char* machineState = "0";
            char* outputState = "0";
            if (EstadoPuzzle == "SOLVED")
            {
              machineState = "2";
              outputState = "1";
            }

            client.print(F("HTTP/1.0 200 OK\r\n"));
            client.println(F("Content-Type: text/json\r\n"));
             client.print(F("{ \"id\":\""));
             client.print(deviceMacAddress);
             client.print(F("\", \"sv\":\"01.01.06\", \"hv\":\"5\", \"puzzle_state\":{ \"number_of_steps\":\"10\", \"current_step\":\"9\", \"attempt_number\":\"0\"}, \"universal_state\":{ \"machine_state\":\""));
             client.print(machineState);
             client.print(F("\", \"output_state\":\""));
             client.print(outputState);
             client.print(F("\", \"input_states\":\""));
             client.print(currentStateDecimal);
             client.println(F("\", \"overwritten_inputs\":\"0\"}, \"message\":{ \"type\":\"info\", \"content\":\"OK!\"} }"));
          }
}

void sendUdpUpdate()
{
  // Send a reply to the IP address and port that sent us the packet we received
  udp.beginPacket(remoteUdpServer, udpPort);
  sprintf(ReplyBuffer, "UNIVERSAL_%s-", deviceMacAddress);
  Serial.print(F("Enviando paquete UDP: "));
  Serial.println(ReplyBuffer);
  udp.print(ReplyBuffer);
  udp.endPacket();
}

void CheckSensors()
{
    // Loop over every sensor
    for(int i=0; i<numSensors; i++){
        // Read the current value
        byte currentState = !digitalRead(sensorPins[i]);
        // Preserve state 
        lastState[i] = currentState;
    }
    // transfer the values from the lastState array to the currentState array switching 1 and 0
    for(int i=0; i<numSensors; i++){
        if (lastState[i] == 1) {
          currentState[i] = 0;
        } else {
          currentState[i] = 1;
        }
    }
  // Calculate the decimal value of the currentState array
  currentStateDecimal = 0;
  for(int i=0; i<16; i++){
    currentStateDecimal += currentState[i] * pow(2,i);
  }

}

void CheckUdp()
{
   // Check if a UDP packet has been received
  int packetSize = udp.parsePacket();
  if (packetSize) {
    Serial.print(F("Received packet of size "));
    Serial.println(packetSize);
    Serial.print(F("From "));
    IPAddress remoteIp = udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(F(", port "));
    Serial.println(udp.remotePort());

    // read the packet into packetBufffer
    int len = udp.read(packetBuffer, 24);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    Serial.println(F("Contents:"));
    Serial.println(packetBuffer);

    // Check if the packet contains the string "Hello_from_ERCC"
    if (strstr(packetBuffer, "Hello_from_ERCC") != nullptr) {
      // Send a reply to the IP address and port that sent us the packet we received
      remoteUdpServer  = udp.remoteIP();
      sendUdpUpdate();
      UDPReceived = true;
      lastUDPTime = millis();
    }

  }

  
  if (UDPReceived && (millis() - lastUDPTime) > 10000) {
    // Send a reply to the IP address and port that sent us the packet we received
    lastUDPTime = millis();
    sendUdpUpdate();
  }
 
}

void CheckHttpClients()
{
  // Listen for incoming clients on port 80
// Check if a client has connected
 WiFiClient client = server.available();

  if (client) {
    bool currentLineIsBlank = false;
    ComandoState = false;
    ComandoPost = false;
    lugReceived = 0;
    lugpostReceived = 0;

    // Hack to enable multiple clients to work without using an array of clients or something like that
    // Keep track of the time when entering the loop Don't let any client be "connected" more than 5 seconds
    // This is not a great solution, but it works (for now?)
    unsigned long startTime = millis();

    while (client.connected()  && (millis() - startTime) < 5000) {
      if (client.available()) {
        char c = client.read();
        if (!(lugReceived > 99)) {
          stringReceived[lugReceived] = c;
          lugReceived++;
        }

        if (c == '\n' && currentLineIsBlank) {

          if (ComandoPost) {
            lugpostReceived = 0;
            while (client.available()) {
              postReceived[lugpostReceived] = client.read();
              lugpostReceived++;
            }
            postReceived[lugpostReceived] = '\0'; // Null-terminate the postReceived string
            Serial.print(postReceived);

            if (strstr(postReceived, "\"universal_set\":{\"machine_state\":") != nullptr) {
              Serial.println(F("Comando POST de cambio reconocido"));
              ComandoState = true; // we have to return the JSON
              if (strstr(postReceived, ":2}") != nullptr) {
                Serial.println(F("Comando SOLVED recibido"));
                EstadoPuzzle = "SOLVED";
              }
              if (strstr(postReceived, ":0}") != nullptr) {
                Serial.println(F("Comando UNSOLVED recibido"));
                EstadoPuzzle = "UNSOLVED";
              }
            }
          }
          
          SendMessage2(client);
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          stringReceived[lugReceived] = '\0'; // Null-terminate the stringReceived string
          Serial.print(stringReceived);
          if (strstr(stringReceived, "GET /?command=state") != nullptr) {
            Serial.println(F("Comando state recibido"));
            ComandoState = true;

          }
          if (strstr(stringReceived, "GET /?status=SOLVED") != nullptr) {
            Serial.println(F("Comando SOLVED recibido"));
            EstadoPuzzle = "SOLVED";
          }
          if (strstr(stringReceived, "GET /?status=UNSOLVED") != nullptr) {
            Serial.println(F("Comando UNSOLVED recibido"));
            EstadoPuzzle = "UNSOLVED";
          }
          if (strstr(stringReceived, "POST / HTTP/1.1") != nullptr) {
            Serial.println(F("Comando POST recibido"));
            ComandoPost = true;
          }
          lugReceived = 0;
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }

    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }

}
void loop() {

   CheckSensors();

   CheckUdp();
    
   CheckHttpClients();

}


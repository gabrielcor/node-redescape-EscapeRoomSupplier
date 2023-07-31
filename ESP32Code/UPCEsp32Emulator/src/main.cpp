#include <WiFi.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <wifi_config.h>

char deviceMacAddress[33]; // MAC address of the device

WiFiServer server(80);
String macAddress;


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
const unsigned int udpPort PROGMEM = 9811;
char packetBuffer[24];  // buffer to hold incoming packet,
char ReplyBuffer[30]; 



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
  macAddress = WiFi.macAddress();
  macAddress.toCharArray(deviceMacAddress, 32);
  deviceMacAddress[32] = '\0';

  Serial.println(deviceMacAddress);
  
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
             client.println(F("\", \"input_states\":\"65535\", \"overwritten_inputs\":\"0\"}, \"message\":{ \"type\":\"info\", \"content\":\"OK!\"} }"));
          }
}

void loop() {

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


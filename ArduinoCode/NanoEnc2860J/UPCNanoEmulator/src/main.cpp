
#include <SPI.h>
#include <EthernetENC.h>
 #define DHCPSETUP

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDA, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);
char* EstadoPuzzle="UNSOLVED";
char stringReceived[100];
char postReceived[100];
int lugReceived = 0;
int lugpostReceived = 0;
bool ComandoState = false;
bool ComandoPost = false;

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH Shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit FeatherWing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit FeatherWing Ethernet

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println(F("Ethernet WebServer Example"));

  // start the Ethernet connection and the server:
#ifdef DHCPSETUP
// start the Ethernet connection:
  Serial.println(F("Initialize Ethernet with DHCP:"));
  if (Ethernet.begin(mac) == 0) 
  {
     Serial.println(F("ERROR can't configure via DHCP"));
  }
  else
  {
    // print your local IP address:
    Serial.print(F("My IP address: "));
    Serial.println(Ethernet.localIP());
  }

#else
  Ethernet.begin(mac, ip);
#endif
  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println(F("Ethernet shield was not found.  Sorry, can't run without hardware. :("));
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println(F("Ethernet cable is not connected."));
  }

  // start the server
  server.begin();
  Serial.print(F("server is at "));
  Serial.println(Ethernet.localIP());
}


void SendMessage2(EthernetClient client)
{
          char macAddress[18];
          sprintf(macAddress, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
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
        
            client.print(F("<html><head><title>Emulando UPC</title></head><body><div style='text-align:center;'><h1>Arduino UPC emulator mac address - "));
            client.print(macAddress);
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
//             client.print(F("{ \"id\":\"3\"} \r\n"));
             client.print(F("{ \"id\":\""));
             client.print(macAddress);
             client.print(F("\", \"sv\":\"01.01.06\", \"hv\":\"5\", \"puzzle_state\":{ \"number_of_steps\":\"10\", \"current_step\":\"9\", \"attempt_number\":\"0\"}, \"universal_state\":{ \"machine_state\":\""));
             client.print(machineState);
             client.print(F("\", \"output_state\":\""));
             client.print(outputState);
             client.println(F("\", \"input_states\":\"65535\", \"overwritten_inputs\":\"0\"}, \"message\":{ \"type\":\"info\", \"content\":\"OK!\"} }"));
          }
}

void loop()
{
  EthernetClient client = server.available();
  if (client) {
    bool currentLineIsBlank = false;
    ComandoState= false;
    ComandoPost = false;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (!(lugReceived > 99)) {
           stringReceived[lugReceived] = c;
           lugReceived++;
        }

        if (c == '\n' && currentLineIsBlank) {
          if (ComandoPost)
          {
            lugpostReceived = 0;
            while(client.available())
            {
              postReceived[lugpostReceived] = client.read();
              lugpostReceived++;
            }
            Serial.println(postReceived);
            
             if(strstr((char *)postReceived, "\"universal_set\":{\"machine_state\":") != 0) {
                Serial.println(F("Comando POST de cambio reconocido"));
                if (strstr((char *)postReceived, ":2}") != 0)
                {
                  Serial.println(F("Comando SOLVED recibido"));
                  EstadoPuzzle = "SOLVED";
                }
                if (strstr((char *)postReceived, ":0}") != 0)
                {
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
          Serial.println(stringReceived);
          if(strstr((char *)stringReceived, "GET /?command=state") != 0) {
            Serial.println(F("Comando state recibido"));
            ComandoState = true;
          }
          if(strstr((char *)stringReceived, "GET /?status=SOLVED") != 0) {
            Serial.println(F("Comando SOLVED recibido"));
            EstadoPuzzle = "SOLVED";
          }
          if(strstr((char *)stringReceived, "GET /?status=UNSOLVED") != 0) {
            Serial.println(F("Comando UNSOLVED recibido"));
            EstadoPuzzle = "UNSOLVED";
          }
          if(strstr((char *)stringReceived, "POST / HTTP/1.1") != 0) {
            Serial.println(F("Comando POST recibido"));
            ComandoPost = true;
          }
          lugReceived=0;
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


#include <WiFi.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <wifi_config.h>

WiFiClient networkClient;
char *deviceMacAddress; // MAC address of the device
char deviceNamestr[] = "";
char *deviceName = deviceNamestr;       // Name of the device
char deviceIDstr[] = "UNCONFIGURED";
char *deviceID = deviceIDstr;


// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
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
  String macAddress = WiFi.macAddress();
  macAddress.toCharArray(deviceMacAddress, 32);
  Serial.println(macAddress);
  // REMOVE ":" from macAddress
  macAddress.replace(":", "");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.write("Hello World!\n");
  delay(1000);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}
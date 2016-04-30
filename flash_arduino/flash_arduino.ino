/*
 *  Simple HTTP get webclient test
 */
 
#include <ESP8266WiFi.h>
 
// Your Settings
const char* ssids[] = {"Superplexus", "Guest", "Nancy's iPhone"};
const char* passwords[] = {"WolfBabyDog", "", "WolfBabyDog"};
const char* host = "www.nyl.io";
const char* url = "/espbuttonpress.php";

// The program
void setup() {
  int max_try = 5; // number of seconds to try connecting to a network before giving up
  Serial.begin(115200);
  delay(100);
 
  // We start by connecting to a WiFi network
  for (int i = 0; i < sizeof(ssids); i++) {
    if (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssids[i], passwords[i]);
      Serial.println();
      Serial.println();
      Serial.print("Connecting to ");
      Serial.println(ssids[i]);
      int ctr = 0;
      while (WiFi.status() != WL_CONNECTED && ctr <= max_try) {
        delay(1000);
        Serial.print(ctr);
        ctr++;
        if (ctr == max_try) {
          WiFi.disconnect();
        }
      }
      // Infinite cycles through SSIDs
      if (WiFi.status() != WL_CONNECTED && i == sizeof(ssids)-1) {
        i = 0;
      }
    }
  }
  
  
  
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 
int value = 0;
 
void loop() {
  delay(5000);
  ++value;
 
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  
  // Read all the lines of the reply from server and print them to Serial
//  while(client.available()){
//    String line = client.readStringUntil('\r');
//    Serial.print(line);
//  }
  
  Serial.println();
  Serial.println("closing connection");
  ESP.deepSleep(0,WAKE_RF_DEFAULT);
  delay(2000);
  Serial.println("shouldn't see this");
}

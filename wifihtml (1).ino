

#include<SoftwareSerial.h>
#include <ESP8266WiFi.h>
 
const char* ssid = "ASUS_X00TD";
const char* password = "kiritokumar";
WiFiServer server(80);
 
void setup() {
  Serial.begin(9600);
  delay(10);
  WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED)
 {
    delay(500);}
    server.begin();
 Serial.print(WiFi.localIP());
  }
 
void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    }
 String request = client.readStringUntil('\r');
 client.flush();
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)
  { 
    value = HIGH;
    Serial.write("1");
  
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    value = LOW;
    Serial.write("0");
     }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led pin is now: ");
 
  if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
 client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");  
  client.println("</html>");
}
 

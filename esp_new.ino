#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>


WiFiClient client;
const char* ssid = "embedded";
const char* password = "qwertyuiop";
WiFiServer server(80);

int bulb_state = 0;
int fan_state = 0;
int door_state = 0;

void setup()
{
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("...");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  Serial.print('X');
  Serial.println("start");
}


void loop()
{
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  while (!client.available()) {
    delay(1);
  }
  String request = client.readStringUntil('\r');
  client.flush();
  Serial.println(request.substring(5, request.lastIndexOf(' ', request.length()-3)));
   client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  // client.println("Refresh: 15");  // refresh the page automatically every 5 sec
  client.println();
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("This is my home :)");
  client.println("<br><br>");
  client.println("temperature of room =  ");
  client.println("23");
  client.println("<br><br>");
  client.println("Humidity of room =  ");
  client.println("45%");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<a href=\"/light_on\"\"><button>Bulb On </button></a>");
  client.println("<a href=\"/light_off\"\"><button>Bulb Off </button></a><br />");
  client.println("<a href=\"/fan_on\"\"><button>Fan On</button></a>");
  client.println("<a href=\"/fan_off\"\"><button>Fan Off </button></a><br />");
  client.println("<a href=\"/open_door\"\"><button>Open Door</button></a>");
  client.println("<a href=\"/close_door\"\"><button>Close Door</button></a><br />");
  //client.println("</html>");
  delay(1);
}

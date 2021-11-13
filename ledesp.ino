#include <WiFi.h>

const char* WIFI_NAME= "292-Cosmic Network 0317-1201410"; 
const char* WIFI_PASSWORD = "xuesheng717#";
WiFiServer server(80);
String header;

String LED_ONE_STATE = "off";
String LED_TWO_STATE = "off";
String LED_THREE_STATE = "off";


const int GPIO_PIN_NUMBER_27 = 27;
const int GPIO_PIN_NUMBER_25 = 25;
const int GPIO_PIN_NUMBER_14 = 14;


void setup() {
Serial.begin(115200);
pinMode(GPIO_PIN_NUMBER_27, OUTPUT);
pinMode(GPIO_PIN_NUMBER_25, OUTPUT);
pinMode(GPIO_PIN_NUMBER_14, OUTPUT);

digitalWrite(GPIO_PIN_NUMBER_27, LOW);
digitalWrite(GPIO_PIN_NUMBER_25, LOW);
digitalWrite(GPIO_PIN_NUMBER_14, LOW);


Serial.print("Connecting to ");
Serial.println(WIFI_NAME);
WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.println("Trying to connect to Wifi Network");
}
Serial.println("");
Serial.println("Successfully connected to WiFi network");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
server.begin();
}

void loop(){
WiFiClient client = server.available(); 
if (client) { 
Serial.println("New Client is requesting web page"); 
String current_data_line = ""; 
while (client.connected()) { 
if (client.available()) { 
char new_byte = client.read(); 
Serial.write(new_byte); 
header += new_byte;
if (new_byte == '\n') { 
         
if (current_data_line.length() == 0) 
{
            
client.println("HTTP/1.1 200 OK");
client.println("Content-type:text/html");
client.println("Connection: close");
client.println();
            
if (header.indexOf("LED0=ON") != -1) 
{
Serial.println("GPIO23 LED is ON");
LED_ONE_STATE = "ON";
digitalWrite(GPIO_PIN_NUMBER_27, HIGH);
} 
if (header.indexOf("LED0=OFF") != -1) 
{
Serial.println("GPIO23 LED is OFF");
LED_ONE_STATE = "OFF";
digitalWrite(GPIO_PIN_NUMBER_27, LOW);
} 
if (header.indexOf("LED1=ON") != -1)
{
Serial.println("GPIO23 LED is ON");
LED_TWO_STATE = "ON";
digitalWrite(GPIO_PIN_NUMBER_25, HIGH);
}
if (header.indexOf("LED1=OFF") != -1) 
{
Serial.println("GPIO23 LED is OFF");
LED_TWO_STATE = "OFF";
digitalWrite(GPIO_PIN_NUMBER_25, LOW);
}
if (header.indexOf("LED2=ON") != -1) 
{
Serial.println("GPIO15 LED is ON");
LED_THREE_STATE = "ON";
digitalWrite(GPIO_PIN_NUMBER_14, HIGH);
}
if(header.indexOf("LED2=OFF") != -1) {
Serial.println("GPIO15 LED is OFF");
LED_THREE_STATE = "OFF";
digitalWrite(GPIO_PIN_NUMBER_14, LOW);
}
            
client.println("<!DOCTYPE html><html>");
client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
client.println("<link rel=\"icon\" href=\"data:,\">");
client.println("<style>html { color: white; font-family: system-ui; background-image: url(https://img.wallpapersafari.com/desktop/1920/1080/28/53/Yy4Xlj.jpg); display: inline-block; margin: 0px auto; text-align: center;}");
client.println(".button { background-color: TRANSPARENT; FONT-FAMILY: system-ui; border: 2px solid #FFFF; color: #fffdfd; padding: 10px 40px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 20px; cursor: pointer; }");
client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}"); 
// Web Page Heading
client.println("</style></head>");
client.println("<body><center><h1>IOT BASED ELECTRICAL DEVICE CONTROL</h1></center>");
client.println("<center><h2>Welcome To IOT Appliance Control Homepage</h2></center>" );
client.println("<center><h2>Press ON To Turn On Switch & OFF to Turn OFF The Switch</h3></center>");
client.println("<form><center>");
client.println("<p> SWITCH 1 is " + LED_ONE_STATE + "</p>");
// If the PIN_NUMBER_22State is off, it displays the ON button 
client.println("<center> <button class=\"button\" name=\"LED0\" value=\"ON\" type=\"submit\">SWITCH 1 ON</button>") ;
client.println("<button class=\"button\" name=\"LED0\" value=\"OFF\" type=\"submit\">SWITCH 1 OFF</button><br><br>");
client.println("<p>SWITCH 2 is " + LED_TWO_STATE + "</p>");
client.println("<button class=\"button\" name=\"LED1\" value=\"ON\" type=\"submit\">SWITCH 2 ON</button>");
client.println("<button class=\"button\" name=\"LED1\" value=\"OFF\" type=\"submit\">SWITCH 2 OFF</button> <br><br>");
client.println("<p>SWITCH 3 is " + LED_THREE_STATE + "</p>");
client.println ("<button class=\"button\" name=\"LED2\" value=\"ON\" type=\"submit\">SWITCH 3 ON</button>");
client.println ("<button class=\"button\" name=\"LED2\" value=\"OFF\" type=\"submit\">SWITCH 3 OFF</button></center>");
client.println("</center></form></body></html>");
client.println();
break;
} 
else 
{ 
current_data_line = "";
}
} 
else if (new_byte != '\r') 
{ 
current_data_line += new_byte; 
}
}
}
// Clear the header variable
header = "";
// Close the connection
client.stop();
Serial.println("Client disconnected.");
Serial.println("");
}
}

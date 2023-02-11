#define trigPin D6 // vysielac
#define echoPin D7 // prijimac
 
long duration, distance; // premenne pouzite na urcenie vzdialenosti
const float onecmtime = 58.2; // konstanta casu potrebneho na 1cm

#include <ESP8266WiFi.h>//zahrnie kniznicu na pracu s WiFi modulom
#include <ESP8266WebServer.h> //zahrnie kniznicu na pracu s webserverom

const char* nazov ="Gries"; //konstanta s nazvom WiFi siete
const char* heslo ="12345678"; //konstanta s heslom do WiFi siete

ESP8266WebServer server(80); //cislo 80 je predvoleny port pre HTTP

void setup()
{
  Serial.begin (9600);

  Serial.print("Pripajam sa k sieti... ");
  Serial.println(nazov); //vypise nazov siete, ktory sme uviedli vyssie
  WiFi.begin(nazov,heslo); //pripaja sa do lokalnej WiFi siete

  while (WiFi.status()!=WL_CONNECTED) 
    delay(1000); //pockame kym bude wifi pripojena
  
  server.on("/", pripojeny); //obsluzna funkcia ak webserver bezi
  server.onNotFound(nepripojeny); //obsluzna funkcia ak nebezi

  server.begin(); //spusti server
}
 
void loop()
{
  server.handleClient();
}

void nepripojeny()
{
  server.send(404, "text/plain", "Server nebezi"); 
}






//funkcia, ktora spracovava dotazy na webserver a odpoveda HTML strankou
void pripojeny() 
{
  String ptr = "";
  ptr +="<!DOCTYPE html>\n";
  ptr +="<html>\n";
  ptr +="  <head>\n";
  ptr +="    <title>nazov stranky</title>\n";
  ptr +="  </head>\n";
  ptr +="  <body>\n";
  ptr +="    <p><strong>Vzdialenost hladiny zumpy je XXX cm.</strong></p>\n";
  ptr +="  </body>\n";
  ptr +="</html>\n";

  server.send(200, "text/html", ptr); 
}

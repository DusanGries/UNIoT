#include <ESP8266WiFi.h>//zahrnie kniznicu na pracu s WiFi modulom
#include <ESP8266WebServer.h> //zahrnie kniznicu na pracu s webserverom

#define trigPin D6 // vysielac
#define echoPin D7 // prijimac
 
long duration, distance; // premenne pouzite na urcenie vzdialenosti
const float onecmtime = 58.2; // konstanta casu potrebneho na 1cm

const char* nazov ="Gries"; //konstanta s nazvom WiFi siete
const char* heslo ="12345678"; //konstanta s heslom do WiFi siete

ESP8266WebServer server(80); //cislo 80 je predvoleny port pre HTTP

void setup()
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

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
  /* reset vysielaca - ticho */
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  /* vysielac vysiela 10ms */
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  /* vypnutie vysielaca*/
  digitalWrite(trigPin, LOW);

  /* cakame na odozvu */
  duration = pulseIn(echoPin, HIGH);

  /* urcenie vzdialenosti v cm podla rychlosti zvuku za ktoru prejde 1cm */
  distance = duration/onecmtime;
  /* vystup na consolu */
  Serial.println(distance);
  
  String ptr = "";
  ptr +="<!DOCTYPE html>\n";
  ptr +="<html>\n";
  ptr +="  <head>\n";
  ptr +="    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no\">\n";
  ptr +="    <meta name=\"HandheldFriendly\" content=\"true\">\n";
  ptr +="    <title>Vzdialenost hladiny</title>\n";
  ptr +="  </head>\n";
  ptr +="  <body style=\"background-image: url('https://rb.gy/tx0zbd'); background-repeat: no-repeat; background-size: 100% auto;\">\n";
  ptr +="    <p style=\"text-align: center; font-size: 100px\">" + String(distance) + " cm</p>\n";
  ptr +="  </body>\n";
  ptr +="</html>\n";

  server.send(200, "text/html", ptr); 
}

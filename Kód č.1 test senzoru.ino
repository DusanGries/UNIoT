#define trigPin D6 // vysielac
#define echoPin D7 // prijimac
 
long duration, distance; // premenne pouzite na urcenie vzdialenosti
const float onecmtime = 58.2; // konstanta casu potrebneho na 1cm

void setup()
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop()
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
  /* vystup do seriovy monitor */
  Serial.println(distance);
  /* pauza 50ms pre dalsim koleckom */
  delay(50);
}

int ROJO = 13;
int DETECTOR = 7;

void setup()
{
  pinMode(ROJO, OUTPUT);
  pinMode(DETECTOR,INPUT);
}

void loop()
{
  int estado = digitalRead(DETECTOR);
  digitalWrite(ROJO,estado);
}

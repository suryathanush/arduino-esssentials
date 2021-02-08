float Vacross,Iamp = 0.0000;
const int Shunt_Res = 2.2;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Vacross = analogRead(A0);
  //Serial.println(Vacross);
  Vacross = (Vacross * 5.0) / 1023.0;
  Iamp = (Vacross * 1000) / Shunt_Res;
  Serial.println(Vacross,6);
  Serial.print("Current = ");
  Serial.print(Iamp);
  Serial.println("mA");
  delay(500);
}

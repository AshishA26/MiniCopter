int VRx = A0;
int VRy = A1;
int VRx2 = A2;
int VRy2 = A3;
int SW = 3;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;
int xPosition2 = 0;
int yPosition2 = 0;
int SW_state2 = 0;
int mapX2 = 0;
int mapY2 = 0;

void setup() {
  Serial.begin(115200);

  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(VRx2, INPUT);
  pinMode(VRy2, INPUT);
  pinMode(SW, INPUT_PULLUP);

}

void loop() {
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);

  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print(" | Button: ");
  Serial.print(SW_state);

  xPosition2 = analogRead(VRx2);
  yPosition2 = analogRead(VRy2);
  mapX2 = map(xPosition2, 0, 1023, -512, 512);
  mapY2 = map(yPosition2, 0, 1023, -512, 512);

  Serial.print(" | X2: ");
  Serial.print(mapX2);
  Serial.print(" | Y2: ");
  Serial.print(mapY2);
  Serial.print(" | Button2: ");
  Serial.println(SW_state2);
}

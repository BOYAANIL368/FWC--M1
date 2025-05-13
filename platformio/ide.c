// Input pins
const int pinA0 = 2;
const int pinA1 = 3;
const int pinC  = 4;

// 7-segment segment pins (common cathode display)
const int segmentPins[7] = {5, 6, 7, 8, 9, 10, 11};

// Segment patterns for digits 0 and 1
// a b c d e f g
const byte digits[2][7] = {
  // 0
  {1, 1, 1, 1, 1, 1, 0},
  // 1
  {0, 1, 1, 0, 0, 0, 0}
};

void setup() {
  pinMode(pinA0, INPUT);
  pinMode(pinA1, INPUT);
  pinMode(pinC, INPUT);

  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  Serial.begin(9600);
}

void loop() {
  int A0_val = digitalRead(pinA0);
  int A1_val = digitalRead(pinA1);
  int C_val  = digitalRead(pinC);

  int X_val = (C_val == 0) ? A0_val : A1_val;

  displayDigit(X_val);

  // Optional debug
  Serial.print("C: "); Serial.print(C_val);
  Serial.print(" A0: "); Serial.print(A0_val);
  Serial.print(" A1: "); Serial.print(A1_val);
  Serial.print(" --> X: "); Serial.println(X_val);

  delay(200);
}

void displayDigit(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], digits[num][i]);
  }
}

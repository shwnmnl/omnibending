const int trigPin = 12;
const int echoPin = 11;

long duration;
float distance;

const float MIN_CM = 5.0;
const float MAX_CM = 80.0;

float lastValid = 60.0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000); // timeout ~5m

  if (duration == 0) {
    // No echo, reuse last valid value
    Serial.println(lastValid);
    delay(30);
    return;
  }

  distance = duration * 0.0343 / 2.0;

  // Clamp to sane range
  if (distance < MIN_CM) distance = MIN_CM;
  if (distance > MAX_CM) distance = MAX_CM;

  // Simple spike rejection
  if (abs(distance - lastValid) > 40) {
    distance = lastValid;
  }

  lastValid = distance;

  // IMPORTANT: only print the number
  Serial.println(distance);

  delay(50);
}

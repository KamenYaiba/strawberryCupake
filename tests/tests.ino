// Define pins for the HC-SR04
const int trigPin = A1;
const int echoPin = 3;

// Variables to hold distance and duration
long duration;
int distance;

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);

  // Set the trigPin as an output and echoPin as an input
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(0, INPUT);
}

void loop() {
  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Set the trigPin HIGH for 10 microseconds to trigger the ultrasonic pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin, returns the time it took for the pulse to return
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance based on the duration
  // Distance = (duration / 2) * speed of sound (in cm/us)
  // Speed of sound is approximately 0.034 cm/us
  distance = duration * 0.034 / 2;
  
  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Wait for a while before taking another measurement
  delay(500);
}

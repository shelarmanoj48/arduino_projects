// Define PWM pin
#define PWM_PIN 1

// Variables for PWM
const int pwmFrequency = 5000;  // Frequency in Hz
const int pwmDutyCycle = 50; // Duty cycle in percentage (0-100)

void setup() {
  // Set PWM pin as output
  pinMode(PWM_PIN, OUTPUT);
}

void loop() {
  // Calculate the ON and OFF times based on the frequency and duty cycle
  unsigned long period = 1000000 / pwmFrequency; // Total period in microseconds
  unsigned long onTime = (period * pwmDutyCycle) / 100; // ON time in microseconds
  unsigned long offTime = period - onTime; // OFF time in microseconds

  // Generate the PWM signal
  digitalWrite(PWM_PIN, HIGH); // Turn ON the signal
  delayMicroseconds(onTime);   // Wait for the ON time
  digitalWrite(PWM_PIN, LOW);  // Turn OFF the signal
  delayMicroseconds(offTime);  // Wait for the OFF time
}

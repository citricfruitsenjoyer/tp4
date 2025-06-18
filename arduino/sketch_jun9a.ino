#include <PID_v1.h>

// === Pin Definitions ===
const int TEMP_PIN = A0;     // Analog pin for MCP9700
const int IN1_PIN = 7;       // H-bridge input 1
const int IN2_PIN = 8;       // H-bridge input 2

// === Temperature Targets ===
const float TEMP_MAX = 50.0;     // °C
const float TEMP_MIN = -15.0;    // °C
const float DESIRED_SLOPE = 0.1; // °C/s

// === PID Control Period ===
const unsigned long CONTROL_PERIOD = 1000; // ms

// === PID Variables ===
double slopeInput = 0;
double pidOutput = 0;
double slopeSetpoint = DESIRED_SLOPE;
double Kp = 100.0, Ki = 0.0, Kd = 0.0;
PID slopePID(&slopeInput, &pidOutput, &slopeSetpoint, Kp, Ki, Kd, DIRECT);

// === State Variables ===
unsigned long lastTime = 0;
float lastTemp = 0.0;
bool goingUp = true;
unsigned long controlStart = 0;

void setup() {
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  Serial.begin(9600);

  lastTime = millis();
  lastTemp = readTemperature();

  slopePID.SetMode(AUTOMATIC);
  slopePID.SetOutputLimits(0, 255);
}

void loop() {
  unsigned long now = millis();
  float deltaTime = (now - lastTime) / 1000.0;
  if (deltaTime < 0.1) return;

  float currentTemp = readTemperature();
  slopeInput = (currentTemp - lastTemp) / deltaTime;

  slopeSetpoint = goingUp ? DESIRED_SLOPE : -DESIRED_SLOPE;
  slopePID.Compute(); // pidOutput: 0–255

  // === Time-Proportional Control Logic ===
  if (now - controlStart >= CONTROL_PERIOD) {
    controlStart = now;
  }

  unsigned long onTime = (pidOutput / 255.0) * CONTROL_PERIOD;

  if (now - controlStart < onTime) {
    // TURN ON — set direction pins accordingly
    if (goingUp) {
      digitalWrite(IN1_PIN, HIGH);
      digitalWrite(IN2_PIN, LOW);
    } else {
      digitalWrite(IN1_PIN, LOW);
      digitalWrite(IN2_PIN, HIGH);
    }
  } else {
    // TURN OFF — both inputs LOW
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, LOW);
  }

  // === Switch polarity at limits ===
  if (goingUp && currentTemp >= TEMP_MAX) {
    goingUp = false;
    resetPID();
  } else if (!goingUp && currentTemp <= TEMP_MIN) {
    goingUp = true;
    resetPID();
  }

  // === Debug Output ===
  Serial.print("Temp: "); Serial.print(currentTemp, 2);
  Serial.print(" °C | Slope: "); Serial.print(slopeInput, 3);
  Serial.print(" °C/s | ON time: "); Serial.print(onTime);
  Serial.print(" ms | Direction: ");
  Serial.println(goingUp ? "UP" : "DOWN");

  lastTemp = currentTemp;
  lastTime = now;
  delay(100);
}

void resetPID() {
  slopePID.SetMode(MANUAL);
  pidOutput = 0;
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  slopePID.SetMode(AUTOMATIC);
}

// === MCP9700 Temperature Conversion ===
float readTemperature() {
  int adc = analogRead(TEMP_PIN);
  float voltage = adc * (5.0 / 1023.0);
  return (voltage - 0.5) * 100.0;  // °C for MCP9700
}

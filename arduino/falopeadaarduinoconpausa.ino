const int peltierPin1 = 7;  // Calentar
const int peltierPin2 = 8;  // Enfriar
const int tempPin = A0;

float tempObjetivo[] = {65.0, 20.0, -18.0, 20.0}; // Secuencia de objetivos
int etapa = 0;

float pendienteDeseada = 0.5; // °C por segundo (ajustar para más rápido o lento)
unsigned long tiempoCiclo = 40000; // Tiempo de cada ciclo en ms

float leerTemperatura() {
  int adc = analogRead(tempPin);
  float volt = adc * 5.0 / 1023.0;
  return (volt - 0.5) * 100.0;
}

void setup() {
  pinMode(peltierPin1, OUTPUT);
  pinMode(peltierPin2, OUTPUT);
  digitalWrite(peltierPin1, LOW);
  digitalWrite(peltierPin2, LOW);
  Serial.begin(9600);
  Serial.println("Inicio control térmico lineal");
}

void loop() {
  static float tempAnterior = leerTemperatura();
  float tempActual = leerTemperatura();
  float objetivo = tempObjetivo[etapa];

  // Calcular diferencia
  float delta = objetivo - tempActual;
  float signo = (delta > 0) ? 1 : -1;

  // Determinar dirección del flujo térmico
  if (delta > 0.5) {
    // Calentar
    digitalWrite(peltierPin1, HIGH);
    digitalWrite(peltierPin2, LOW);
  } else if (delta < -0.5) {
    // Enfriar
    digitalWrite(peltierPin1, LOW);
    digitalWrite(peltierPin2, HIGH);
  } else {
    // Muy cerca del objetivo → apagar
    digitalWrite(peltierPin1, LOW);
    digitalWrite(peltierPin2, LOW);

    etapa++;
    if (etapa > 3) etapa = 0; // Reinicia el ciclo completo
    delay(3000); // Espera entre fases
    return;
  }

  // Simular modulación del ciclo para ajustar la pendiente
  float velocidadActual = (tempActual - tempAnterior) / (tiempoCiclo / 1000.0); // °C/s
  float errorPendiente = pendienteDeseada - abs(velocidadActual);

  // Ajustar duty cycle
  int tiempoON = constrain((int)(tiempoCiclo * (0.5 + signo * errorPendiente)), 100, tiempoCiclo);
  int tiempoOFF = tiempoCiclo - tiempoON;

  delay(tiempoON);

  // Apagar Peltier para el tiempo restante del ciclo
  digitalWrite(peltierPin1, LOW);
  digitalWrite(peltierPin2, LOW);

  delay(tiempoOFF);

  tempAnterior = tempActual;

  // Mostrar datos
  Serial.print("T: "); Serial.print(tempActual);
  Serial.print(" °C | Objetivo: "); Serial.print(objetivo);
  Serial.print(" | Vel: "); Serial.print(velocidadActual, 3);
  Serial.println(" °C/s");
}

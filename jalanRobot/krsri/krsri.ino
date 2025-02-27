#define PIN_TRIG 6  // Sensor Ultrasonik Trig
#define PIN_ECHO 7  // Sensor Ultrasonik Echo

int motor1pin1 = 2;  // IN1 Motor Kiri
int motor1pin2 = 3;  // IN2 Motor Kiri
int motor2pin1 = 4;  // IN3 Motor Kanan
int motor2pin2 = 5;  // IN4 Motor Kanan

int ENA = 9;  // PWM Motor Kiri
int ENB = 10; // PWM Motor Kanan

void setup() {
  Serial.begin(9600);
  
  // Setup Sensor Ultrasonik
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  
  // Setup Motor
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

// Fungsi membaca jarak dari sensor ultrasonik
long bacaJarak() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  
  long duration = pulseIn(PIN_ECHO, HIGH);
  long distance = duration / 58; // Konversi ke cm
  return distance;
}

// Fungsi untuk maju
void maju() {
  analogWrite(ENA, 170); // Kecepatan motor kiri
  analogWrite(ENB, 170); // Kecepatan motor kanan
  
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}
void majuSedang() {
  analogWrite(ENA, 120); // Kecepatan motor kiri
  analogWrite(ENB, 120); // Kecepatan motor kanan
  
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}

// Fungsi untuk belok kiri
void belokKiri() {
  analogWrite(ENA, 170);
  analogWrite(ENB, 170);
  
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH); // Motor kiri mundur
  
  digitalWrite(motor2pin1, HIGH); // Motor kanan maju
  digitalWrite(motor2pin2, LOW);
}

// Fungsi untuk berhenti
void berhenti() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}

void loop() {
  long jarak = bacaJarak();
  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");

  if (jarak <= 55){
    jalanSedang();
  }else if (jarak <= 35) {
    // Serial.println(" Halangan! Belok kiri.");
    belokKiri();
    delay(700); // Waktu belok
  } else {
    // Serial.println("Jalan Maju.");
    maju();
  }
  
  delay(200);
}

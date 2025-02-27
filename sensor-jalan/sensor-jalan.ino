int motor1pin1 = 2; //in1
int motor1pin2 = 3; //in2
int motor2pin1 = 4; //in3
int motor2pin2 = 5; //in4

// Pin sensor (pastikan tidak overlap dengan pin motor/PWM)
const int trigKiri = 6;    // Sensor kiri
const int echoKiri = 7;
const int trigDepan = 8;   // Sensor depan
const int echoDepan = 9;
const int trigKanan = 10;  // Sensor kanan
const int echoKanan = 11;

// Pin PWM (ENA/ENB harus pin PWM)
int ENA = 3;  // Motor kiri
int ENB = 5;  // Motor kanan

void setup() {
  // Setup motor
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  
  // Setup sensor
  pinMode(trigKiri, OUTPUT);
  pinMode(echoKiri, INPUT);
  pinMode(trigDepan, OUTPUT);
  pinMode(echoDepan, INPUT);
  pinMode(trigKanan, OUTPUT);
  pinMode(echoKanan, INPUT);
  
  // Setup PWM
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

long bacaJarak(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034/2;
}

void maju() {
  analogWrite(ENA, 150); // Kecepatan motor kiri
  analogWrite(ENB, 150); // Kecepatan motor kanan
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}

void belokKiri() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(motor1pin1, LOW);  // Motor kiri mundur
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, HIGH); // Motor kanan maju
  digitalWrite(motor2pin2, LOW);
}

void belokKanan() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(motor1pin1, HIGH); // Motor kiri maju
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);  // Motor kanan mundur
  digitalWrite(motor2pin2, HIGH);
}

void berhenti() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}

void loop() {
  long jarakKiri = bacaJarak(trigKiri, echoKiri);
  long jarakDepan = bacaJarak(trigDepan, echoDepan);
  long jarakKanan = bacaJarak(trigKanan, echoKanan);
  
  if(jarakDepan <= 15 || jarakKiri <= 10 || jarakKanan <= 10) {
    // Prioritas 1: Jika ada halangan di depan
    if(jarakDepan <= 15) {
      if(jarakKanan > jarakKiri) {
        belokKanan(); // Belok kanan jika ruang kanan lebih lapang
        delay(500);
      } else {
        belokKiri(); // Belok kiri jika ruang kiri lebih lapang
        delay(500);
      }
    }
    // Prioritas 2: Jika ada halangan di samping
    else if(jarakKiri <= 10) {
      belokKanan();
      delay(300);
    }
    else if(jarakKanan <= 10) {
      belokKiri();
      delay(300);
    }
    berhenti();
  }
  else {
    maju();
  }
}
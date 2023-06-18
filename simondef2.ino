#define LED1 13
#define LED2 12
#define LED3 11
#define LED4 10
#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 4
#define BUTTON4 5

int InitialLevel = 1;
int Speed = 500;
const int MaxLevel = 10;
int Seccuence[MaxLevel];
int UserSeccuence[MaxLevel];
int Score = 0;

void configuracionInicial() {
  pinMode(LED1, INPUT);
  pinMode(LED2, INPUT);
  pinMode(LED3, INPUT);
  pinMode(LED4, INPUT);
  pinMode(BUTTON1, OUTPUT);
  pinMode(BUTTON2, OUTPUT);
  pinMode(BUTTON3, OUTPUT);
  pinMode(BUTTON4, OUTPUT);
  digitalWrite(BUTTON1, LOW);
  digitalWrite(BUTTON2, LOW);
  digitalWrite(BUTTON3, LOW);
  digitalWrite(BUTTON4, LOW);
}

void loop() {
  if (InitialLevel == 1) {
    generarSecuencia();
    mostrarSecuencia();
    leerSecuencia();
  }
  if (InitialLevel != 1) {
    mostrarPuntuacion();
    mostrarSecuencia();
    leerSecuencia();
  }
}

void mostrarPuntuacion() {
  Serial.begin(9600);
  Serial.print("Puntuación actual: ");
  Serial.println(Score);
}

void mostrarSecuencia() {
  digitalWrite(BUTTON1, LOW);
  digitalWrite(BUTTON2, LOW);
  digitalWrite(BUTTON3, LOW);
  digitalWrite(BUTTON4, LOW);
  for (int i = 0; i < InitialLevel; i++) {
    int ledPin = Seccuence[i];
    digitalWrite(ledPin, HIGH);
    delay(Speed);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
}

void leerSecuencia() {
  int Flag = 0;
  for (int i = 0; i < InitialLevel; i++) {
    Flag = 0;
    while (Flag == 0) {
      if (digitalRead(LED4) == LOW) {
        digitalWrite(BUTTON4, HIGH);
        UserSeccuence[i] = BUTTON4;
        Flag = 1;
        delay(200);
        if (UserSeccuence[i] != Seccuence[i]) {
          procesarError();
          return;
        }
        digitalWrite(BUTTON4, LOW);
      }
      if (digitalRead(LED3) == LOW) {
        digitalWrite(BUTTON3, HIGH);
        UserSeccuence[i] = BUTTON3;
        Flag = 1;
        delay(200);
        if (UserSeccuence[i] != Seccuence[i]) {
          procesarError();
          return;
        }
        digitalWrite(BUTTON3, LOW);
      }
      if (digitalRead(LED2) == LOW) {
        digitalWrite(BUTTON2, HIGH);
        UserSeccuence[i] = BUTTON2;
        Flag = 1;
        delay(200);
        if (UserSeccuence[i] != Seccuence[i]) {
          procesarError();
          return;
        }
        digitalWrite(BUTTON2, LOW);
      }
      if (digitalRead(LED1) == LOW) {
        digitalWrite(BUTTON1, HIGH);
        UserSeccuence[i] = BUTTON1;
        Flag = 1;
        delay(200);
        if (UserSeccuence[i] != Seccuence[i]) {
          procesarError();
          return;
        }
        digitalWrite(BUTTON1, LOW);
      }
    }
  }
  procesarCorrecto();
}

void generarSecuencia() {
  randomSeed(millis());
  for (int i = 0; i < MaxLevel; i++) {
    Seccuence[i] = random(BUTTON1, BUTTON4 + 1);
  }
}

void procesarError() {
  digitalWrite(BUTTON1, HIGH);
  digitalWrite(BUTTON2, HIGH);
  digitalWrite(BUTTON3, HIGH);
  digitalWrite(BUTTON4, HIGH);
  delay(250);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  delay(250);
  reiniciar();
  Serial.println("¡Fallaste! Inténtalo de nuevo.");
}

void procesarCorrecto() {
  InitialLevel++;
  Speed -= 50;
  Score++;
  delay(200);

  if (InitialLevel >= MaxLevel) {
    reiniciar();
    Serial.println("¡Felicidades! Has completado el juego.");
  }
}

void reiniciar() {
  InitialLevel = 1;
  Speed = 500;
  Score = 0;
}

void setup() {
  configuracionInicial();
}

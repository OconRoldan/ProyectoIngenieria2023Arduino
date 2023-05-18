#define L1 13
#define L2 12
#define L3 11
#define L4 10
#define B1 2
#define B2 3
#define B3 4
#define B4 5

int NivelA = 1;
int Vel = 500;
const int NivelM = 10;
int Sec[NivelM];
int SecU[NivelM];

void configuracionInicial() {
  pinMode(L1, INPUT);
  pinMode(L2, INPUT);
  pinMode(L3, INPUT);
  pinMode(L4, INPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(B3, OUTPUT);
  pinMode(B4, OUTPUT);
  digitalWrite(B1, LOW);
  digitalWrite(B2, LOW);
  digitalWrite(B3, LOW);
  digitalWrite(B4, LOW);
}

void loop() {
  if (NivelA == 1) {
    generarSecuencia();
    mostrarSecuencia();
    leerSecuencia();
  }
  if (NivelA != 1) {
    mostrarSecuencia();
    leerSecuencia();
  }
}

void mostrarSecuencia() {
  digitalWrite(B1, LOW);
  digitalWrite(B2, LOW);
  digitalWrite(B3, LOW);
  digitalWrite(B4, LOW);
  for (int S = 0; S < NivelA; S++) {
    digitalWrite(Sec[S], HIGH);
    delay(Vel);
    digitalWrite(Sec[S], LOW);
    delay(200);
  }
}

void leerSecuencia() {
  int Fg = 0;
  for (int S = 0; S < NivelA; S++) {
    Fg = 0;
    while (Fg == 0) {
      if (digitalRead(L4) == LOW) {
        digitalWrite(B4, HIGH);
        SecU[S] = B4;
        Fg = 1;
        delay(200);
        if (SecU[S] != Sec[S]) {
          procesarError();
          return;
        }
        digitalWrite(B4, LOW);
      }
      if (digitalRead(L3) == LOW) {
        digitalWrite(B3, HIGH);
        SecU[S] = B3;
        Fg = 1;
        delay(200);
        if (SecU[S] != Sec[S]) {
          procesarError();
          return;
        }
        digitalWrite(B3, LOW);
      }
      if (digitalRead(L2) == LOW) {
        digitalWrite(B2, HIGH);
        SecU[S] = B2;
        Fg = 1;
        delay(200);
        if (SecU[S] != Sec[S]) {
          procesarError();
          return;
        }
        digitalWrite(B2, LOW);
      }
      if (digitalRead(L1) == LOW) {
        digitalWrite(B1, HIGH);
        SecU[S] = B1;
        Fg = 1;
        delay(200);
        if (SecU[S] != Sec[S]) {
          procesarError();
          return;
        }
        digitalWrite(B1, LOW);
      }
    }
  }
  procesarCorrecto();
}

void generarSecuencia() {
  randomSeed(millis());
  for (int S = 0; S < NivelM; S++) {
    Sec[S] = random(2, 6);
  }
}

void procesarError() {
  digitalWrite(B1, HIGH);
  digitalWrite(B2, HIGH);
  digitalWrite(B3, HIGH);
  digitalWrite(B4, HIGH);
  delay(250);
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(L3, LOW);
  digitalWrite(L4, LOW);
  delay(250);
  reiniciarJuego();
}

void procesarCorrecto() {
  if (NivelA < NivelM) {
    NivelA++;
    Vel -= 50;
    delay(200);
  }
}

void reiniciarJuego() {
  NivelA = 1;
  Vel = 500;
}

void setup() {
  configuracionInicial();
}

// Definición de pines para los LEDs
const int LED_PIN_1 = 2;
const int LED_PIN_2 = 3;
const int LED_PIN_3 = 4;
const int LED_PIN_4 = 5;

// Definición de pines para los botones
const int BUTTON_PIN_1 = 6;
const int BUTTON_PIN_2 = 7;
const int BUTTON_PIN_3 = 8;
const int BUTTON_PIN_4 = 9;

// Arreglos para almacenar la secuencia y las entradas del jugador
int sequence[10];
int playerSequence[10];

// Variables para controlar el juego
int sequenceLength = 1;
int playerIndex = 0;
bool gameStarted = false;
bool gameOver = false;

void setup() {
  // Configurar pines de los LEDs como salidas
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT);

  // Configurar pines de los botones como entradas con resistencias de pull-up
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_3, INPUT_PULLUP);
  pinMode(BUTTON_PIN_4, INPUT_PULLUP);

  // Inicializar secuencia y jugador
  resetGame();
  
  // Iniciar comunicación serial a 9600 baudios (opcional)
  Serial.begin(9600);
}

void loop() {
  if (!gameStarted) {
    // Esperar a que el jugador presione cualquier botón para comenzar el juego
    if (digitalRead(BUTTON_PIN_1) == LOW || digitalRead(BUTTON_PIN_2) == LOW ||
        digitalRead(BUTTON_PIN_3) == LOW || digitalRead(BUTTON_PIN_4) == LOW) {
      startGame();
    }
  } else {
    // Mostrar la secuencia actual
    displaySequence();
    
    // Obtener las entradas del jugador
    getPlayerInput();

    // Comprobar si el jugador completó la secuencia correctamente
    if (checkPlayerInput()) {
      // El jugador completó la secuencia correctamente
      sequenceLength++;
      playerIndex = 0;
      delay(1000); // Retraso para mostrar la última luz antes de la siguiente ronda
      Serial.println("Correct!");
    } else {
      // El jugador cometió un error
      gameOver = true;
      Serial.println("Game Over");
    }
    
    // Comprobar si se alcanzó el máximo de la secuencia
    if (sequenceLength > 9) {
      gameOver = true;
      Serial.println("Congratulations! You won!");
    }
  }

  // Reiniciar el juego si es necesario
  if (gameOver) {
    delay(2000);
    resetGame();
  }
}

void resetGame() {
  sequenceLength = 1;
  playerIndex = 0;
  gameStarted = false;
  gameOver = false;

  // Limpiar las secuencias
  for (int i = 0; i < 10; i++) {
    sequence[i] = 0;
    playerSequence[i] = 0;
  }

  // Apagar todos los LEDs
  digitalWrite(LED_PIN_1, LOW);
  digitalWrite(LED_PIN_2, LOW);
  digitalWrite(LED_PIN_3, LOW);
  digitalWrite(LED_PIN_4, LOW);
}

void startGame() {
  resetGame();
  gameStarted = true;
  Serial.println("Game Started");
}

void displaySequence() {
  for (int i = 0; i < sequenceLength; i++) {
    int led = sequence[i];
    
    // Encender el LED correspondiente
    switch (led) {
      case 1:
        digitalWrite(LED_PIN_1, HIGH);
        delay(500);
        digitalWrite(LED_PIN_1, LOW);
        break;
      case 2:
        digitalWrite(LED_PIN_2, HIGH);
        delay(500);
        digitalWrite(LED_PIN_2, LOW);
        break;
      case 3:
        digitalWrite(LED_PIN_3, HIGH);
        delay(500);
        digitalWrite(LED_PIN_3, LOW);
        break;
      case 4:
        digitalWrite(LED_PIN_4, HIGH);
        delay(500);
        digitalWrite(LED_PIN_4, LOW);
        break;
    }
    
    // Retraso entre luces
    delay(200);
  }
}

void getPlayerInput() {
  while (playerIndex < sequenceLength) {
    if (digitalRead(BUTTON_PIN_1) == LOW) {
      playerSequence[playerIndex] = 1;
      playerIndex++;
      delay(200); // Retraso para evitar la detección múltiple de botones
    } else if (digitalRead(BUTTON_PIN_2) == LOW) {
      playerSequence[playerIndex] = 2;
      playerIndex++;
      delay(200);
    } else if (digitalRead(BUTTON_PIN_3) == LOW) {
      playerSequence[playerIndex] = 3;
      playerIndex++;
      delay(200);
    } else if (digitalRead(BUTTON_PIN_4) == LOW) {
      playerSequence[playerIndex] = 4;
      playerIndex++;
      delay(200);
    }
  }
}

bool checkPlayerInput() {
  for (int i = 0; i < sequenceLength; i++) {
    if (playerSequence[i] != sequence[i]) {
      return false; // El jugador cometió un error
    }
  }
  return true; // El jugador completó la secuencia correctamente
}

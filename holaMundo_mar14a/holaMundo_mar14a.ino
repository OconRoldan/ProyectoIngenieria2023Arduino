int LEDPin =  13;      // Definimos que trabajaremos con el pin 13 de las digitales

void setup() {
  
  pinMode(LEDPin, OUTPUT);  //definimos el pin 13 como salida
  
}

void loop() { //Bucle principal, todo lo de dentro se repetirá infinitamente. 
  
  	digitalWrite(LEDPin, HIGH); //hacemos que el pin13 emita un pulso electrónico de 5V gracias al valor "High" (alto en castellano)
 
delay(5000);      //hacemos que el programa quede congelado con la última instrucción durante 1000ms (1 segundo). El LED estará encendido durante un segundo. 
  
digitalWrite(LEDPin, LOW);  //hacemos que el pin13 no emita ningun pulso (0V)gracias al valor "Low" (“bajo” en castellano)
  
delay(5000);  //hacemos que el programa quede congelado con la última instrucción durante 1000ms (1 segundo). El LED estará apagado durante un segundo. 

}
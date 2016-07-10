/* Pablo Sánchez Carmona - TFG - Universidad de Granada
 * Prueba de comunicación Arduino - Android
 */
#include <arduino.h>
#define INTERRUPCION_BT 4

char buffer[5];
static char saludo = 'D';
static char fin = '%';
static char coma = ',';

// Interrupción
void leeDatos(){
  static byte ultima_lectura;
  int count = 0;
  while(Serial1.available() > 0){
    buffer[count] = ultima_lectura =  Serial1.read();
    if(ultima_lectura == '%') break;
    else count++;
    if(count == 255) count = 0;
  }
  envioDatos();
}

void setup() {
  delay(500);
  Serial.begin(9600);
  Serial1.begin(9600);
  attachInterrupt(INTERRUPCION_BT, leeDatos, CHANGE);
}

void loop() {}

// Envía los datos vía bluetooth
void envioDatos(){
  Serial1.write(saludo);
  Serial1.write(coma);
  Serial1.write(fin);
}



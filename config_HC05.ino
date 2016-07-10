/*
 Pablo Sánchez Carmona - TFG - Universidad de Granada
 Configurar modulo BLUETOOTH HC-05 con Arduino MEGA.

 1. Conectamos los pins RXD,TDX del módulo Bluetooth al Serial1 (18 y 19).
    - Pin 18TX1 al RXD del módulo con un divisor resistivo (5k y 10k por ejemplo)
    - Pin 19RX1 al TXD del módulo directamente.
 2. Cargamos este programa al MEGA y desconectamos la energía del módulo Bluetooth.
 3. Presionamos el botón del módulo y luego volvemos a dar energía, debe quedar el led rojo titilando lentamente. 
 4. Debemos cambiar la velocidad del COM usado por el Mega.
    - Ir a Panel de control de windows, administrador de dispositivos y cambiar la velocidad (según se desee).
 */

void setup() {
  delay(500);
  Serial1.begin(38400);
  Serial.begin(9600);
  Serial.println("Envía comandos AT:");
}

void loop() {

  if (Serial1.available()){
    Serial.write(Serial1.read()); 
  }

  if (Serial.available()){
    Serial1.write(Serial.read()); 
  }
}

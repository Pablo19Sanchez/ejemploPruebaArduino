/* Pablo Sánchez Carmona - TFG - Universidad de Granada
Obtener el ángulo de inclinación del sensor MPU-6050 */

#include <Wire.h> // Protocolo I2C
int16_t AcX, AcY, AcZ, GyX, GyY, GyZ, Tmp; // Valores sin refinar
float Acc[2], Gy[2], Angle[2]; // Ángulos

#define MPU 0x68 // dirección I2C del acelerómetro

// Ratios de conversion
#define A_R 16384.0
#define G_R 131.0
#define RAD_A_DEG = 57.295779 // Conversion de radianes a grados 180/PI
 
void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(38400);
}

void loop() {
  // Leer los valores del Acelerómetro
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // Pide el registro correspondiente al AcX
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true); // A partir del valor 0x3B se piden 6 registros
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  // Se calculan los ángulos X e Y
  Acc[0] = atan((AcY/A_R)/sqrt(pow((AcX/A_R),2) + pow((AcZ/A_R),2)))*RAD_TO_DEG;
  Acc[1] = atan(-1*(AcX/A_R)/sqrt(pow((AcY/A_R),2) + pow((AcZ/A_R),2)))*RAD_TO_DEG;
  // Se obtienen los ángulos del giroscopio
  Gy[0] = GyX/G_R;
  Gy[1] = GyY/G_R;
  // Se aplica el filtro complementario
  Angle[0] = 0.98*(Angle[0] + Gy[0]*0.010) + 0.02*Acc[0];
  Angle[1] = 0.98*(Angle[1] + Gy[1]*0.010) + 0.02*Acc[1];
  // Pasamos la temperatura a grados centígrados
  Tmp = Tmp/340.00 + 36.53;
  // Mostramos los valores por consola
  Serial.print("Angle X: "); Serial.print(Angle[0]); Serial.print("\n");
  Serial.print("Angle Y: "); Serial.print(Angle[1]); Serial.print("\n");
  Serial.print("Temperature: "); Serial.print(Tmp); Serial.print("\n----------\n");
  delay(10); 

}

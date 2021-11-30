//use esp32 with mpu6050,scl-d22,sda-d21
//body referred from--
//https://howtomechatronics.com/tutorials/arduino/arduino-and-mpu6050-accelerometer-and-gyroscope-tutorial/

//work successful until print(roll) #19 Nov
#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
float x, y, z; //acceleration on axis xyz
int roll, pitch; //angle of your head, in the middle, roll = 0

Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

void setup() {
  Serial.begin(115200);
  //check the circuit,not important
  Serial.println("MPU6050 TEST");
  if (!mpu.begin()) {
    Serial.println("Sensor init failed");
    while (1)
      yield();
  }
  Serial.println("Found a MPU-6050 sensor");
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  //display setting, cannot delate and i dont konw why
  display.display();
  delay(100); // Pause for 2 seconds
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setRotation(0);
}

//IMPORTANT
void loop() {
  //read data
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  //unknown function
  display.clearDisplay();
  display.setCursor(0, 0);

  //check data
  //  Serial.print("Accelerometer ");
  //  Serial.print("X: ");
  //  Serial.print(a.acceleration.x, 1);
  //    Serial.print(" m/s^2, ");
  //  Serial.print("Y: ");
  //  Serial.print(a.acceleration.y, 1);
  //  Serial.print(" m/s^2, ");
  //    Serial.print("Z: ");
  //    Serial.print(a.acceleration.z, 1);
  //  Serial.print(" m/s^2");
  //
  //  display.println("Accelerometer - m/s^2");
  //    display.print(a.acceleration.x, 1);
  //    display.print(", ");
  //  display.print(a.acceleration.y, 1);
  //    display.print(", ");
  //    display.print(a.acceleration.z, 1);
  //  display.println("");

  display.display();
  delay(1000);//how to match the music?

  x = a.acceleration.x;//shorthand
  y = a.acceleration.y;
  z = a.acceleration.z;
  //caculate roll and pitch then transfer data to int
  roll = (atan(y / sqrt(pow(x, 2) + pow(z, 2))) * 180 / PI);
  pitch = (atan(-1 * x / sqrt(pow(y, 2) + pow(z, 2))) * 180 / PI);
  Serial.println(roll);//roll has range from -90 to 90
  //Serial.println(pitch);
}

////more playful function--vibration volume change with roll
//int motorPin = **;    // vibration motor digital pin
//void setup()
//{
//  pinMode(motorPin, OUTPUT );
//}
//void loop()
//{
//  //digitalWrite(motorPin,HIGH);
//  //delay(1000);
//  //digitalWrite(motorPin,LOW);
//  //delay(1000);
//  //digitalWrite
//  dacWrite(motorPin, **);//how to get analogWrite on esp32
//  delay(1000);
//  dacWrite(motorPin, **);
//  delay(1000);
//}

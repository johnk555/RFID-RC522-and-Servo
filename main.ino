#include <MFRC522.h>
#include <SPI.h>
#include <Servo.h>
#define RST_PIN 5
#define SS_PIN 10
Servo sg90;

MFRC522 mfrc522(SS_PIN, RST_PIN);
byte i;
byte datoUID[4];
byte llavero[4] = {0xBC,0x73,0x9F,0x63};

byte tag[4] = {0x33,0xF0,0x20,0x0D};

void setup(){
  Serial.begin(9600);

  SPI.begin();
  sg90.attach(3);
  sg90.write(0);
  mfrc522.PCD_Init();
  Serial.println(F("Place card for scanning"));
}

void loop(){
  if ( ! mfrc522.PICC_IsNewCardPresent())
  return;

  if ( ! mfrc522.PICC_ReadCardSerial())
  return; 
  Serial.println("UID:");

  for (byte i = 0; i < mfrc522.uid.size; i++){
    if (mfrc522.uid.uidByte[i] < 0x10){
      Serial.print("0");
    }else {
      Serial.print("");
    }

    Serial.print(mfrc522.uid.uidByte[i], HEX);
    datoUID[i]=mfrc522.uid.uidByte[i];
  }
  mfrc522.PICC_HaltA();
  if (datoUID[i] != llavero[i]){
    Serial.print("Card");
    for (int j=0; j <=180; j++){
      sg90.write(j);
      delay(5);
    }
  }
}

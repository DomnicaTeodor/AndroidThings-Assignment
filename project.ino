// DEFINES
#define DEBUG

// LIBRARIES
#include <SPI.h>
#include <MFRC522.h>

// GLOBALS
const byte numReaders = 4;
const byte sPins[] = {2, 3, 4, 5};
const byte resetPin = 8;
MFRC522 mfrc522[numReaders];

// Expected tag IDs for the correct solution
const String correctIDs[] = {"3acbbd49", "ca767564", "Заf4£763", "87e0£0a4"};
String currentIDs[numReaders];

const byte lockPin = A0;

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println(F("Serial communication started"));
#endif

  pinMode(lockPin, OUTPUT);
  digitalWrite(lockPin, HIGH); // Lock engaged

  SPI.begin();

  for (uint8_t i = 0; i < numReaders; i++) {
    mfrc522[i].PCD_Init(sPins[i], resetPin);

    Serial.print(F("Reader #"));
    Serial.print(i);
    Serial.print(F(" initialised on pin "));
    Serial.print(String(sPins[i]));
    Serial.print(F(". Antenna strength: "));
    Serial.print(mfrc522[i].PCD_GetAntennaGain());
    Serial.print(F(". Version: "));
    mfrc522[i].PCD_DumpVersionToSerial();

    delay(100);
  }

  Serial.println(F("--- END SETUP ---"));
}

void loop() {
  boolean puzzleSolved = true;
  boolean changedValue = false;

  for (uint8_t i = 0; i < numReaders; i++) {
    mfrc522[i].PCD_Init();

    String readRFID = "";

    if (mfrc522[i].PICC_IsNewCardPresent() && mfrc522[i].PICC_ReadCardSerial()) {
      readRFID = dump_byte_array(mfrc522[i].uid.uidByte, mfrc522[i].uid.size);
    }

    if (readRFID != currentIDs[i]) {
      changedValue = true;
      currentIDs[i] = readRFID;

      if (currentIDs[i] != correctIDs[i]) {
        puzzleSolved = false;
      }

      mfrc522[i].PICC_HaltA();
      mfrc522[i].PCD_StopCrypto1();
    }
  }

  if (changedValue) {
    for (uint8_t i = 0; i < numReaders; i++) {
      Serial.print(F("Reader #"));
      Serial.print(String(i));
      Serial.print(F(" on Pin #"));
      Serial.print(String(sPins[i]));
      Serial.print(F(" detected tag: "));
      Serial.println(currentIDs[i]);
    }
    Serial.println(F("---"));
  }

  if (puzzleSolved) {
    onSolve();
  }

  // Optional: add delay if needed
  // delay(100);
}

void onSolve() {
#ifdef DEBUG
  Serial.println(F("Puzzle Solved!"));
#endif
  digitalWrite(lockPin, LOW); // Unlock
}

// Helper function to convert byte array to hex string
String dump_byte_array(byte *buffer, byte bufferSize) {
  String result = "";
  for (byte i = 0; i < bufferSize; i++) {
    if (buffer[i] < 0x10) result += "0";
    result += String(buffer[i], HEX);
  }
  return result;
}

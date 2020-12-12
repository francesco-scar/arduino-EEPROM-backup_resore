#include <EEPROM.h>

//#define WRITE

byte dataArray[] = {69, 42};


void writeData(byte *data){
  int i = 0;
  
  while (i < sizeof(data) && i < EEPROM.length()){
    EEPROM.update(i, data[i]);
    i++;
  }
}


byte eepromCheckSum(int maxAddress){
  byte checkSum = 0;
  int i = 0;
  
  while (i < maxAddress && i < EEPROM.length()){
    checkSum ^= EEPROM.read(i);
    i++;
  }
  
  return checkSum;
}


byte arrayCheckSum(byte *data){
  byte checkSum = 0;
  int i = 0;
  
  while (i < sizeof(data)){
    checkSum ^= data[i];
    i++;
  }
  
  return checkSum;
}



void setup () {
  delay(5000);
  
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  #ifdef WRITE
  
    writeData(dataArray);

    if (eepromCheckSum(sizeof(dataArray)) != arrayCheckSum(dataArray)) {
      Serial.println("Writing error, trying again...");
      setup();
    } else {
      Serial.println("Data correctly written!");
    }
    
  #else
  
    int addr = 0;
    byte checkSum = 0;
    byte val;

    Serial.print("Memory dump array:\n{");
    while (addr < EEPROM.length()){
      val = EEPROM.read(addr);

      Serial.print(val, DEC);
      checkSum ^= val;

      addr++;

      if (addr < EEPROM.length()){
        Serial.print(',');
      }
    }
    Serial.println('}');

    if (eepromCheckSum(EEPROM.length()) != checkSum){
      Serial.println("Read error, trying read again...");
      setup();
    } else {
      Serial.println("Reading verified!");
    }
      
  #endif
}


void loop () {

}

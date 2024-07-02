////////////////////////////////////////////////////////
///////// FIRMWARE EDIT BY: MATHIAS SOUZA /////////////
////////  DATE MODIFY: 20/09/19           ////////////
/////////////////////////////////////////////////////

#include <DS18B20.h>
DS18B20 ds(22); //define pin 22


void setup() {
  Serial.begin(9600);
  Serial.println("\n-- INIT PROG 18B20---");
  Serial.print("Devices disponiveis: ");
  Serial.println(ds.getNumberOfDevices());
  Serial.println();
}

void loop() {
  int id=0;
  while (ds.selectNext()) {
    Serial.println("----- ID:"+String(id)+" -----");
    switch (ds.getFamilyCode()) {
      case MODEL_DS18S20:
        Serial.println("Model: DS18S20/DS1820");
        break;
      case MODEL_DS1822:
        Serial.println("Model: DS1822");
        break;
      case MODEL_DS18B20:
        Serial.println("Model: DS18B20");
        break;
      default:
        Serial.println("Unrecognized Device");
        break;
    }

    uint8_t address[8];
    ds.getAddress(address);

    Serial.print("Address:");
    for (uint8_t i = 0; i < 8; i++) {
      Serial.print(" ");
      Serial.print(address[i]);
    }
    Serial.println();

    Serial.print("Resolution: ");
    Serial.println(ds.getResolution());

    Serial.print("Power Mode: ");
    if (ds.getPowerMode()) {
      Serial.println("External");
    } else {
      Serial.println("Parasite");
    }
    //--------PRINT ALARMS-------
    Serial.print("getAlarmeLow: ");
    Serial.println(ds.getAlarmLow());
    Serial.print("getAlarmeHigh: ");
    Serial.println(ds.getAlarmHigh());
    Serial.print("hasAlarm: ");
    Serial.println(ds.hasAlarm());
    
    //-------PRINT TEMPERATURE------
    Serial.print("Temperature: ");
    Serial.print(ds.getTempC());
    Serial.print(" C / ");
    Serial.print(ds.getTempF());
    Serial.println(" F");
    Serial.println();
    
    Serial.println("ID:"+String(id)+" - Wait command set");
    char rx;
    for(int i=0;i<5000;i++){ ///delay 5000
      rx=' ';
      if(Serial.available()>0){
        rx=Serial.read();
      }
       //--------GRAVA E2PROM 18B20
      if(rx=='a'){
         int low=random(10,15);
         int high=random(20,25);
        ////-------LOW,HIGH---
        ds.setAlarms(low,high);
        Serial.print("Set Alarms a(10~15)(20~25) |Low:"+String(low)+"|High:"+String(high));
      }
      //--------GRAVA E2PROM 18B20 ALARMS---
      else if(rx=='b'){
        int low=random(20,25);
        int high=random(30,35);
        ////-------LOW,HIGH---
        ds.setAlarms(low,high);
        Serial.print("Set Alarms b(20~25)(30~35)|Low:"+String(low)+"|High:"+String(high));
      }
     
      //--------GRAVA E2PROM 18B20
      else if(rx=='c'){
         int low=random(80,85);
         int high=random(90,95);
        ////-------LOW,HIGH---
        ds.setAlarms(low,high);
        Serial.print("Set Alarms c (80~85)(90~95)|Low:"+String(low)+"|High:"+String(high));
      }
      //----------------------------------------------------
      //--------GRAVA RESOLUTION E2PROM 18B20
      else if(rx=='1'){
        ds.setResolution(9);
        Serial.print("Set resolution 1: 9bits | 94ms convert");
      }
      //--------GRAVA RESOLUTION E2PROM 18B20
      else if(rx=='2'){
        ds.setResolution(10);
        Serial.print("Set resolution 2: 10bits | 188ms convert");
      }
      //--------GRAVA RESOLUTION E2PROM 18B20
      else if(rx=='3'){
        ds.setResolution(11);
        Serial.print("Set resolution 3: 11bits | 375ms convert");
      }
      else if(rx=='4'){
        ds.setResolution(12);
        Serial.print("Set resolution 4: 12bits | 750ms convert");
      }
      delay(1);
    }
    Serial.println("Finish timeout command set");
    id++;
  }
}

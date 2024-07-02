//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////MATHIAS SOUZA 06/04/2024////////////////////////////////////////////////////////////////////////////
////ESSE CÓDIGO TEM CAPACIDADE DE LER MULTIPOS DS18B20, NO ENTANTO FOI USADO APENAS 1 NESSE EXEMPLO/////
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <DS18B20.h>
DS18B20 ds(8); //define pin 8

///----variaveis----
uint32_t timeMillis=0;
uint8_t temperatura;
bool firstLoop=true;
uint8_t bufferOut[4]={0,0,0,0};
uint8_t bufferIn[2]={0,0};

// Definição dos pinos
const int led1Pin = 3; // Pino do primeiro LED
const int led2Pin = 4; // Pino do segundo LED
const int buttonPin = 2; // Pino do botão
const int ds18b20Pin = 8; // Pino do DS18B20 (você pode ajustar o pino conforme sua configuração)
//----prototipos funcao-----
void DS18b20Read();


void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600); // Inicializa a comunicação serial
  /*Serial.println("\n-- INIT PROG 18B20---");
  Serial.print("Devices disponiveis: ");
  Serial.println(ds.getNumberOfDevices());
  Serial.println();*/
  timeMillis=millis();
}

void loop() {
  // Lê o estado do botão
  bool buttonState = digitalRead(buttonPin);
  
  ///----Recebimento de dados da porta Serial-----
  if(Serial.available()>0){
    delay(50);
    uint8_t idx=0;
    while(Serial.available()>0){
      bufferIn[idx++]=Serial.read();
    }
    //-Processamento dos dados
    switch(bufferIn[0]){ //Seleciona qual dos leds
      case 1:
        digitalWrite(led1Pin,bufferIn[1]);
      break;
      case 2:
        digitalWrite(led2Pin,bufferIn[1]);
      break;
    }
  }
  //-----------------------------------------------

  //-----A cada 1/2 segundos OU no Inicio do programa----
  if(millis()-timeMillis>500 || firstLoop){
     DS18b20Read();
     //--Enviar pela Serial os dados---
     bufferOut[0]=digitalRead(led1Pin);
     bufferOut[1]=digitalRead(led2Pin);
     bufferOut[2]=!buttonState;
     bufferOut[3]=temperatura;
     Serial.write(bufferOut,sizeof(bufferOut));
     //---------------------------------
     timeMillis=millis();
     firstLoop=false;
  }
 
}

void DS18b20Read(){
  int id=0;
  while (ds.selectNext()) {
    uint8_t address[8];
    ds.getAddress(address);
    //-------PRINT TEMPERATURE------
    //Serial.print("Temperature: ");
    //Serial.print(ds.getTempC());
    //Serial.print(" C / ");
    temperatura=ds.getTempC();
    id++;
  }
}

//Bu yazılım Melih Hilmi ULUDAG tarafından kodlanmıştır.
#include<RFID.h>
#include<SPI.h>
#include <Servo.h>
/*
Ek bilgi:
Kendi rfid kartinizdan bilgileri almak icin void loop ta aciklama satirina dusurdugum satirlari kullanin
Kart numaralarınızı aldıktan sonra kart1, kart2, .... dizilerini kendi kartiniza gore ayarlayabilirsiniz
*/
RFID rfidModul(10,9);
byte kart1[5]={166,146,191,50,185};
byte kart2[5]={4,220,177,101,12};
byte kart3[5]={34,87,.......}; // okul kartim sonucta geri kalan bitler bende sakli kalsin ;)
boolean izin,denendi,izin2,izin3,kart1Durum,kart2Durum,kart3Durum;
byte kLed=2, yLed=3,mLed=4, buzzerPin=6; boolean kapi=true; boolean birkere=true;
Servo servoMotor;
const byte calistirmaPini=5;
byte cP_oku;

void setup() {
 // izin=true, izin2=true,izin3=true; denendi=false,kart1Durum=false,kart2Durum=false,kart3Durum=false;
   servoMotor.attach(7);
       pinMode(buzzerPin,OUTPUT);//ses yayacak
           pinMode(kLed,OUTPUT);//k isik yakacak
            pinMode(yLed,OUTPUT);//y isik yakacak
             pinMode(mLed,OUTPUT);//m isik yakacak
             
  Serial.begin(9600);
  SPI.begin();
rfidModul.init();

}

void kapiyiAc(){

  
  Serial.println("kapi acilir");
  digitalWrite(yLed,1);digitalWrite(buzzerPin,1);


delay(200);

  servoMotor.write(10);
  
    
      
digitalWrite(yLed,0);digitalWrite(buzzerPin,0);
  }

  
void kapiyiAcilmaz(){
  Serial.println("kapi acilmaz");
  digitalWrite(kLed,1);digitalWrite(buzzerPin,1);

delay(150);
digitalWrite(kLed,0);digitalWrite(buzzerPin,0);


   digitalWrite(kLed,1);digitalWrite(buzzerPin,1);

delay(150);
digitalWrite(kLed,0);digitalWrite(buzzerPin,0);

  }

    
void kapiyiKapat(){
  Serial.println("kapi acilir");
  digitalWrite(mLed,1);digitalWrite(buzzerPin,1);

servoMotor.write(25);
delay(200);
  
    servoMotor.write(50);
      
   digitalWrite(mLed,0);digitalWrite(buzzerPin,0);
  }


  

void loop() {


  
cP_oku=digitalRead(calistirmaPini);

  denendi=false; izin=false; izin2=false,izin3=false; kart1Durum=false,kart2Durum=false,kart3Durum=false;

  if(kapi==false){
    
if(rfidModul.isCard()){
 
  if(rfidModul.readCardSerial()){
  /* Serial.print("Kart ID:");// -------
    Serial.print(rfidModul.serNum[0]); Serial.print("-");
      Serial.print(rfidModul.serNum[1]);Serial.print("-");
    Serial.print(rfidModul.serNum[2]);Serial.print("-");
    Serial.print(rfidModul.serNum[3]);Serial.print("-");
    Serial.print(rfidModul.serNum[4]); 
  
    Serial.println("");*/ // ------- 
        


        // ------- // ------- // ------- 
      //1.kart kontrolu, anahtarlık
      if(kart2Durum==false && kart3Durum==false){
for( byte i=0;i<5;i++){
  if(rfidModul.serNum[i] != kart1[i]){
    izin=false;denendi=false;
     
    }       
  else{denendi=true;// kart saglandi
  izin=true;izin2=false;izin3=false;
  kart1Durum=true; kart2Durum=false,kart3Durum=false;
  Serial.println("1.kart");
  }
  }
      }

     // ------- // ------- // ------- 
        
        //2.kart kontrolu,beyaz kart 
        
if(kart1Durum==false && kart3Durum==false){
       
for( byte j=0;j<5;j++){
  if(rfidModul.serNum[j] != kart2[j]){
    izin2=false;denendi=false;
     
    }       
  else{denendi=true; 
   izin=false;izin2=true;izin3=false;
  kart2Durum=true; kart1Durum=false,kart3Durum=false;
  Serial.println("2.kart");
  }
  }
  }

 // ------- // ------- // ------- 
        //3.kart kontrolu,okul kart
        
if(kart1Durum==false && kart2Durum==false){
  
      for( byte l=0;l<5;l++){
  if(rfidModul.serNum[l] != kart3[l]){
    izin3=false;denendi=false;
     
    }       
  else{
       izin=false;izin2=false;izin3=true;
    denendi=true; kart3Durum=true; kart1Durum=false,kart2Durum=false;
  Serial.println("3.kart");
  }
  }
  }


   


            if(denendi){
              
              if(kart1Durum){
              if(izin){
                kapiyiAc();kapi=true;
                
                }
                }
               else if(kart2Durum){
                 if(izin2){
                kapiyiAc();kapi=true;
                
                }
                }

                else if(kart3Durum){
                 if(izin3){
                kapiyiAc();kapi=true;
                
                }
                }
                
              }
              
              else{kapiyiAcilmaz();}

        
  rfidModul.halt();
  }
}

  }

if(cP_oku==0){// kapı açıktır kapanmak isteniyordur
if(kapi==true){
kapiyiKapat();}
kapi=false;
}


  }




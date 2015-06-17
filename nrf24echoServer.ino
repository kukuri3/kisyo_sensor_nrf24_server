//-------------------------------------------------------------------
// nRF24 echo server
//------------------------------ written by iizuka   Japan ----------
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#define LED_PIN (8)

// コンストラクタ呼び出し CEピンとCSピン番号の設定
RF24 radio(10,9);

unsigned long mtime=0;

void setup(void)
{
  // 通信開始
  radio.begin();

  // リトライ回数の設定
  radio.setRetries(15,15);
  
  // 書き込み用のパイプを開く
  radio.openWritingPipe(0xF0F0F0F0D2LL);
  // 読み込み用のパイプを開く
  radio.openReadingPipe(1, 0xF0F0F0F0E1LL);
  
//  radio.startListening();
  
    Serial.begin(115200);
    pinMode(LED_PIN,OUTPUT);
}

void loop(void)
{
  char c;
  //send trigger to client
  unsigned long now=millis();
  
  if((now-mtime)>1000){   
    c='t';
    radio.stopListening();
    radio.write( &c, sizeof(char) );
    radio.startListening();
    delay(100);  //これが300ms以下だと返信が遅くなる
    mtime=now;
    digitalWrite(LED_PIN, 1);
    delay(10);
    digitalWrite(LED_PIN, 0);
   
  }


  if ( radio.available() ) {
    bool done = false;
    while (!done) {
      done = radio.read( &c, sizeof(char) );
//        Serial.write("receive=");
        Serial.write(c);
//        Serial.write("\r\n"); 
        //delay(20);

    }
  }
} 
//-------- end of program -----------------------------------------

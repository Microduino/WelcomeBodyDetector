#include"userDef.h"
#include <JQ6500.h>
#include <JQ6500_def.h>

#ifdef AUDIO_SoftSerial
#include<SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX
JQ6500 Audio(&mySerial);     //音频控制类实例,使用软串口（2，3）
#else
JQ6500 Audio(&Serial1);
#endif

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);//设置彩灯个数，引脚
uint32_t color[9] =
{
  strip.Color(0, 0, 0),
  strip.Color(255, 0, 0),
  strip.Color(248, 141, 30),
  strip.Color(255, 255, 0),
  strip.Color(0, 255, 0),
  strip.Color(0, 127, 255),
  strip.Color(0, 0, 255),
  strip.Color(139, 0, 255),
  strip.Color(255, 255, 255)
};

int i = 1;

boolean FLAG_1 = 0;  //是否coming
boolean FLAG_2 = 0;   //是否go out

void setup() {
  // initialize serial:
  Serial.begin(9600);
  pinMode(BODY_PIN1, INPUT);
  pinMode(BODY_PIN2, INPUT);

  Audio.init(DEVICE_FLASH, MODE_ONE_STOP, MUSICVOL);//初始化audio

  strip.begin();	//初始化LED
  strip.show(); // Initialize all pixels to 'off'

  for (int i = 0; i < 9; i++)
  {
    colorWipe(color[i]);
    delay(300);
  }
  colorWipe(color[0]);
}

void loop() {
  FLAG_1 = judgeDetect(digitalRead(BODY_PIN1), digitalRead(BODY_PIN2));
  FLAG_2 = judgeDetect2(digitalRead(BODY_PIN1), digitalRead(BODY_PIN2));

  if ((digitalRead(BODY_PIN1)) && (digitalRead(BODY_PIN2)) && (  FLAG_1 ))  //如果条件触发coming
  {
    colorWipe(color[random(1, 10)]);
    Audio.choose(1);
    Serial.print("COMING IN");
    Serial.print("  , ");
    Serial.print(digitalRead(BODY_PIN1));
    Serial.print("  , ");
    Serial.print(digitalRead(BODY_PIN2));
    Serial.print("  , ");
    Serial.println(millis());
    FLAG_1 = 0;
    delay(1100);
  }
  if ((digitalRead(BODY_PIN1)) && (digitalRead(BODY_PIN2)) && (  FLAG_2))//如果条件触发go out
  {
    colorWipe(color[random(1, 10)]);
    Audio.choose(2);
    Serial.print("GOING OUT");
    Serial.print("  , ");
    Serial.print(digitalRead(BODY_PIN1));
    Serial.print(digitalRead(BODY_PIN2));
    Serial.print("  , ");
    Serial.println(millis());
    FLAG_2 = 0;
    delay(1100);
  }
  if (!digitalRead(BODY_PIN1) && !digitalRead(BODY_PIN2)) //无触发
  {
    colorWipe(color[0]);
    FLAG_1 = 0;
    FLAG_2 = 0;
  }
}

void colorWipe(uint32_t c) {      //彩灯随机发光
  for (uint16_t i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, c);
    strip.show();
  }
}

boolean judgeDetect(uint8_t inputA, uint8_t inputB )   //判断是否coming
{
  if ((inputA == 1) && (inputB == 0))
  {
    //FLAG_1 = 1;
    delay(200);
    return 1;
  }
  else
  {
    delay(200);
    return 0;
  }
}

boolean judgeDetect2(uint8_t _inputA, uint8_t _inputB )  //判断是否go out
{
  if ((_inputA == 0) && (_inputB == 1))
  {
    //FLAG_2 = 1;
    delay(200);    //2000
    return 1;
  }
  else
  {
    delay(200);
    return 0;
  }
}


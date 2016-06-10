#include <Arduino.h>

//Core和CoreUSB默认使用软串口
#define AUDIO_SoftSerial
#define MUSICVOL 25  //初始音量0~30

//Core+默认使用Serial1
//JQ6500 Audio(&Serial1);

#define PIN A0 //彩灯引脚

#define BODY_PIN1 4  //IR引脚定义
#define BODY_PIN2 6


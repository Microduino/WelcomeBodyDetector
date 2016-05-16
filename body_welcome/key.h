#include <arduino.h>

boolean key[NUM_DIGITAL_PINS];			//����
boolean key_cache[NUM_DIGITAL_PINS];		//��ⰴ���ɿ�����

void key_init()
{
  for(int a=0;a<NUM_DIGITAL_PINS;a++)
  {
    key[a]=LOW;
    key_cache[a]=HIGH;
  }
}

boolean key_get(int _key_pin,boolean _key_type)
{
  key_cache[_key_pin]=key[_key_pin];		//�������ж���

  key[_key_pin]=!digitalRead(_key_pin);	//����ʱ

  switch(_key_type)
  {
  case 0:
    if(!key[_key_pin] && key_cache[_key_pin])		//�����ɿ���
      return true;
    else
      return false;
    break;
  case 1:
    if(key[_key_pin] && !key_cache[_key_pin])		//�����ɿ���
      return true;
    else
      return false;
    break;
  }
}
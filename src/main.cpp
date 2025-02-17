#include <Arduino.h>
#include <Servo.h>

#define dt_pin          2
#define clk_pin         4
#define sw_pin          7
#define led_rojo        9
#define led_verde       10
#define led_azul        11
#define steps           5

int led_rojo_value = 0;
int led_verde_value = 0;
int led_azul_value = 0;

int clk_old = 0;
int led_selector = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(dt_pin, INPUT);
  pinMode(clk_pin, INPUT);
  pinMode(sw_pin, INPUT);
}

void loop() 
{
  bool dt = digitalRead(dt_pin);
  bool clk = digitalRead(clk_pin);
  bool selector = digitalRead(sw_pin);
  
  if(!selector){
    led_selector++;
    if(led_selector > 2){
      led_selector = 0;
    }
    while(!selector){
      selector = digitalRead(sw_pin);
      delay(100);
    };
  }
  
  if(clk != clk_old)
  {
    if(clk != dt)
    {
      switch (led_selector)
      {
      case 0:
        led_rojo_value += steps;
        if(led_rojo_value > 255)
        {
          led_rojo_value = 255;
        }
        break;
      case 1:
        led_verde_value += steps;
        if(led_verde_value > 255)
        {
          led_verde_value = 255;
        }
        break;
      case 2:
        led_azul_value += steps;
        if(led_azul_value > 255)
        {
          led_azul_value = 255;
        }
        break;
      default:
        break;
      }
    }
    if(clk == dt)
    {
      switch (led_selector)
      {
      case 0:
        led_rojo_value -= steps;
        if(led_rojo_value < 0)
        {
          led_rojo_value = 0;
        }
        break;
      case 1:
        led_verde_value -= steps;
        if(led_verde_value < 0)
        {
          led_verde_value = 0;
        }
        break;
      case 2:
        led_azul_value -= steps;
        if(led_azul_value < 0)
        {
          led_azul_value = 0;
        }
        break;
      default:
        break;
      }
    }
    analogWrite(led_rojo, led_rojo_value);
    analogWrite(led_verde, led_verde_value);
    analogWrite(led_azul, led_azul_value);
    Serial.print(led_rojo_value);
    Serial.print(",");
    Serial.print(led_verde_value);
    Serial.print(",");
    Serial.println(led_azul_value);
  }
  clk_old = clk;
}
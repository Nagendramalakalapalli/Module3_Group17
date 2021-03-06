/**
 * @file main.c
 * @author Malakalapalli Nagendra
 * @brief 
 * @version 0.1
 * @date 2022-03-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "MyStm32f407xx.h"
#include <stdio.h>
#include<stdbool.h>

/**
 * @brief PREPROCESSORS
 * @author Malakalapalli Nagendra
 * 
 */
#define BUTTON_PRESS ENABLE
#define LED_ON  1
#define LED_OFF 0

int Data_Encryption()

{
   bool Flag = false;
   const int m = 934;
   const int n = 938;
   int SUM = n + m;
   if(SUM == 1872)
   {

      Flag= true;
   }
   else{

      Flag=false;
   }

   return Flag;
}

   // DELAY FUNCTION
   void delay(void)
   {
      for (uint32_t i = 0; i < 5000000; i++);
   }
   
    /**
    * @brief  LOCK - ALL LED's ON
    * @author Indrani V
    * 
    */
   void Lock(void)
      {
         GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_12, LED_ON);
         GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_13, LED_ON);
         GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_14, LED_ON);
         GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_15, LED_ON);

      }
	  
      /** 
      * @brief UNLOCK - All LED's OFF
      * @author Sahana Manguli
      * 
      */
   void Unlock(void)
   {
      GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_12, LED_OFF);
      GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_13, LED_OFF);
      GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_14, LED_OFF);
      GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_15, LED_OFF);

   }
   
    /**
    * @brief ALARM ACTIVATION/DEACTIVATION - ALL LED's ON CLOCKWISE 
    * @author Malakalapalli Nagendra
    * 
    */
   
   void Alarm_Activation_Deactivation(void)
   {

      GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
      delay();
      GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_13);
      delay();
      GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_14);
      delay();
      GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_15);
      delay();

   }
   
   /**
    * @brief APPROACH LIGHT  - ALL LED's ON ANTI-CLOCKWISE
    * @author Manojkumar Vadri
    * 
    */
   void Approach_Light(void)
   {

      GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_15);
      delay();
      GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_14);
      delay();
      GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_13);
      delay();
      GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
      delay();

   }

   /**
    * @brief Main Function
    * @author Malakalapalli Nagendra
    * @return int 
    */
   int main(void)
   {
      int count = 0;
         
		 //GREEN LED
          GPIO_Handle_t gGpioLed;
          gGpioLed.pGPIOx = GPIOD;
          gGpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
          gGpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
          gGpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
          gGpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
          GPIO_PeriClockControl(GPIOD, ENABLE);
          GPIO_Init(&gGpioLed);

          //ORANGE LED
           GPIO_Handle_t oGpioLed;
           oGpioLed.pGPIOx = GPIOD;
           oGpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
           oGpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
           oGpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
           oGpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
           GPIO_PeriClockControl(GPIOD, ENABLE);
           GPIO_Init(&oGpioLed);

           //RED LED
           GPIO_Handle_t rGpioLed;
           rGpioLed.pGPIOx = GPIOD;
           rGpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
           rGpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
           rGpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
           rGpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
           GPIO_PeriClockControl(GPIOD, ENABLE);
           GPIO_Init(&rGpioLed);

           //BLUE LED
           GPIO_Handle_t bGpioLed;
           bGpioLed.pGPIOx = GPIOD;
           bGpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
           bGpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
           bGpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
           bGpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
           GPIO_PeriClockControl(GPIOD, ENABLE);
           GPIO_Init(&bGpioLed);

           // BUTTON
           GPIO_Handle_t GpioBtn;
           GpioBtn.pGPIOx = GPIOA;
           GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
           GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
           GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
           GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
           GPIO_PeriClockControl(GPIOA, ENABLE);
           GPIO_Init(&GpioBtn);

      if (Data_Encryption())
      {

         while (1)
         {
            if (GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) == BUTTON_PRESS)
            {
               delay();
               count = count + 1;
            }
            if (count == 3)
            {
               Lock();
            }
            else if (count == 9)
            {
                Unlock();
            }
            else if (count==18)
            {
               Alarm_Activation_Deactivation();
            }
            else if (count==27)
            {
               Approach_Light();
            }
         }
      }
   }

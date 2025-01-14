#include "stm32f10x.h"
#include "tim.h"
#include "init.h"

GPIO_InitTypeDef     GPIO_InitStrue2;
GPIO_InitTypeDef     GPIO_InitStrue3;

void drive_init(void)//PA9,PA11,PA13,PA14,PE15
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  GPIO_InitStrue2.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_10|GPIO_Pin_12;
	  GPIO_InitStrue2.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStrue2.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStrue2);
	  GPIO_SetBits(GPIOA,GPIO_Pin_9);
	  GPIO_SetBits(GPIOA,GPIO_Pin_11);
	  GPIO_ResetBits(GPIOA,GPIO_Pin_10);
	  GPIO_ResetBits(GPIOA,GPIO_Pin_12);
	
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); 
		GPIO_InitStrue3.GPIO_Pin = GPIO_Pin_15;
		GPIO_InitStrue3.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStrue3.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOE, &GPIO_InitStrue3);     
		GPIO_ResetBits(GPIOE,GPIO_Pin_15);
	
	  TIM2_Init();
}	

void led_init(void)//PE5
{
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); 
		GPIO_InitStrue3.GPIO_Pin = GPIO_Pin_5;
		GPIO_InitStrue3.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStrue3.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOE, &GPIO_InitStrue3);     
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);
}

void Usart3_Init(u32 bound){
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE, ENABLE);	
  
  //USART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
  GPIO_Init(GPIOB, &GPIO_InitStructure);
   
  //USART2_RX	  GPIOA.3
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
 
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
  NVIC_Init(&NVIC_InitStructure);	
  

  USART_InitStructure.USART_BaudRate = bound;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
 
  USART_Init(USART3, &USART_InitStructure); 
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
  USART_Cmd(USART3, ENABLE);                    
 
}

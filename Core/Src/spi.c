/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    spi.c
  * @brief   This file provides code for the configuration
  *          of the SPI instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "spi.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

SPI_HandleTypeDef hspi1;

/* SPI1 init function */
void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  SPI_AutonomousModeConfTypeDef HAL_SPI_AutonomousMode_Cfg_Struct = {0};

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 0x7;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  hspi1.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi1.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi1.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi1.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi1.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi1.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi1.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  hspi1.Init.ReadyMasterManagement = SPI_RDY_MASTER_MANAGEMENT_INTERNALLY;
  hspi1.Init.ReadyPolarity = SPI_RDY_POLARITY_HIGH;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_SPI_AutonomousMode_Cfg_Struct.TriggerState = SPI_AUTO_MODE_DISABLE;
  HAL_SPI_AutonomousMode_Cfg_Struct.TriggerSelection = SPI_GRP1_GPDMA_CH0_TCF_TRG;
  HAL_SPI_AutonomousMode_Cfg_Struct.TriggerPolarity = SPI_TRIG_POLARITY_RISING;
  if (HAL_SPIEx_SetConfigAutonomousMode(&hspi1, &HAL_SPI_AutonomousMode_Cfg_Struct) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_SPI1;
    PeriphClkInit.Spi1ClockSelection = RCC_SPI1CLKSOURCE_PCLK2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* SPI1 clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**SPI1 GPIO Configuration
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI
    */
    GPIO_InitStruct.Pin = SPI1_SCK_Pin|SPI1_MISO_Pin|SPI1_MOSI_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();

    /**SPI1 GPIO Configuration
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI
    */
    HAL_GPIO_DeInit(GPIOA, SPI1_SCK_Pin|SPI1_MISO_Pin|SPI1_MOSI_Pin);

  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

void CS_SPI_Select(void) {
  HAL_GPIO_WritePin(CS_SPI_GPIO_Port, CS_SPI_Pin, GPIO_PIN_RESET);
}

void CS_SPI_Deselect(void) {
  HAL_GPIO_WritePin(CS_SPI_GPIO_Port, CS_SPI_Pin, GPIO_PIN_SET);
}

void SPI1_Write(uint8_t data) {
  HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY);
}

void SPI1_Write_2(uint8_t data) {
	
  HAL_SPI_Transmit(&hspi1, &data, 10, HAL_MAX_DELAY);
	
	
}

uint8_t SPI1_Read(void) {
  uint8_t data;
  HAL_SPI_Receive(&hspi1, &data, 1, HAL_MAX_DELAY);
  return data;
}
//uint8_t id[ID_SIZE];



void W25M02_ReadID(void) {
	
	#define ID_COMMAND 0x9f
#define ID_SIZE 3
	uint8_t id[ID_SIZE];
  CS_SPI_Select();
	HAL_Delay(100);
  SPI1_Write(ID_COMMAND);
  SPI1_Write(0x00);//Dummy 8 pulse
  for (int i = 0; i < ID_SIZE; i++) {
    id[i] = SPI1_Read();
  }
	HAL_Delay(100);
	CS_SPI_Deselect();

	//uint8_t i=3;
	if(id[0]==0xEF) 
		{
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		HAL_Delay(300);
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		HAL_Delay(300);}
		 if(id[1]==0xBB)
			{
			HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		HAL_Delay(300);
		HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		HAL_Delay(300);}
				if(id[2]==0x21)
					{
		HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
		HAL_Delay(300);
		HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
		HAL_Delay(300);}
		
  }
	
//send and receice same time
void W25M02_ReadID_1(void){
uint8_t txData[] = {0x9F, 0x00, 0x00, 0x00, 0x00};
  uint8_t rxData[5] = {0};
  
  
  CS_SPI_Select();
	HAL_Delay(100);
   
  //  Hal_SPI_TransmitReceive($hspi,txData, rxData, sizeof(txData));
    HAL_SPI_TransmitReceive(&hspi1, txData, rxData, 5,500);
   
    HAL_Delay(100);
	CS_SPI_Deselect();
    
//	uint8_t i=2;
	if(rxData[2]==0xEF) 
		{
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		HAL_Delay(300);
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		HAL_Delay(300);}
		 if(rxData[3]==0xBB)
			{
			HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
		HAL_Delay(300);
		HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
		HAL_Delay(300);}
			if(rxData[4]==0x21)
					{
		HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		HAL_Delay(300);
		HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		HAL_Delay(300);}
		
  }

	
	void Write_Protection_SoftorHard (void)
	{ 
		// The start configuration writing for priority (Protection Register)
   //Write Status Register/---------------------------------------------
	uint8_t WRITE_ENABLE_By_WE=0X82;//It can be 0x02
		uint8_t WRITE_ENABLE_Soft=0X80;// It can be 0x00
		CS_SPI_Select();
	 HAL_Delay(10);
	 SPI1_Write(0X1F);
	 SPI1_Write(0XA0);
	 SPI1_Write(WRITE_ENABLE_By_WE);
	 HAL_Delay(10);
	CS_SPI_Deselect();
	 HAL_Delay(10);
	 // The end configuration writing for priority-------------------------
	}
	
	
	
 void SPI1_Write_W25M02IG(void) //uint16_t PAGE,uint16_t CA,uint16_t DATASIZE)
 { uint16_t DataSizeBuffer=10;
	 uint8_t DATA_Send[]={0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA};
	 
	
	 //---------------------start write in buffer maximum 2045------------------------
	 // Random Load Program Data (84h)
	 CS_SPI_Select();
	 HAL_Delay(10);
	 SPI1_Write(0X84);// WRITE to BUFFER
	 SPI1_Write(0x00);//CA1 Address HIGH
	 SPI1_Write(0x00);//CA2 Address LOW
	 for(int i=0;i<DataSizeBuffer;i++)
	 {
	 SPI1_Write(DATA_Send[i]);
	 }
	 HAL_Delay(10);
	CS_SPI_Deselect();
	 HAL_Delay(10);	 
	 //------------------------The End send Data on buffer---------------------------------
	 
	 // write enable----------------------------------
	 CS_SPI_Select();
	 HAL_Delay(10);
	 SPI1_Write(0X06);// WRITE ENABLE OX06
	 HAL_Delay(10);
	CS_SPI_Deselect();
	 HAL_Delay(10);
	//------------------------------------------------
	 
	 
	 //---------------------------------------------------------
	 //Program Execute (10h)
	 CS_SPI_Select();
	 HAL_Delay(10);
	 SPI1_Write(0X10);// Transfer from Buffer to Flash Ram
	 SPI1_Write(0x00);//Dummy
	 SPI1_Write(0x00);//Page Address High
	  SPI1_Write(0x00);//Page Address Low
	 HAL_Delay(10);
	CS_SPI_Deselect();
	HAL_Delay(10);
	 //-------------------------------------------------------------
 }
 
 //***************************ONLY for test****************************************
 void SPI1_Write_W25M02IG_2(void) //uint16_t PAGE,uint16_t CA,uint16_t DATASIZE)
 { uint16_t DataSizeBuffer=10;
	 uint8_t DATA_Send[]={0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA};
	 
	
	 //start write in buffer maximum 2048------------------------
	 // Random Load Program Data (84h)
	 CS_SPI_Select();
	 HAL_Delay(10);
	 SPI1_Write(0X84);// WRITE to BUFFER
	 SPI1_Write(0x00);//CA1 Address HIGH
	 SPI1_Write(0x00);//CA2 Address LOW
	 
	 SPI1_Write_2(*DATA_Send);
	
	 HAL_Delay(10);
	CS_SPI_Deselect();
	 HAL_Delay(10);	 
	 //The End send Data on buffer---------------------------------
	 
	 // write enable----------------------------------
	 CS_SPI_Select();
	 HAL_Delay(10);
	 SPI1_Write(0X06);// Transfer from Buffer to Flash Ram
	 HAL_Delay(10);
	CS_SPI_Deselect();
	 HAL_Delay(10);
	//------------------------------------------------
	 
	 
	 //---------------------------------------------------------
	 //Program Execute (10h)
	 CS_SPI_Select();
	 HAL_Delay(10);
	 SPI1_Write(0X10);// Transfer from Buffer to Flash Ram
	 SPI1_Write(0x00);//Dummy
	 SPI1_Write(0x00);//Page Address High
	  SPI1_Write(0x00);//Page Address Low
	 HAL_Delay(10);
	CS_SPI_Deselect();
	HAL_Delay(10);
	 //-------------------------------------------------------------
 }
 //******************************************************************************************************
 //------------------------------------------Read from Flash Ram----------------------------------------
 void SPI1_Read_W25M02IG(void)
 {
	 uint8_t Data_Read[10]={0};
	 CS_SPI_Select();
	 HAL_Delay(10);
	 SPI1_Write(0X13);// Transfer from Flash Ram to Buffer
	 SPI1_Write(0x00);//Dummy
	 SPI1_Write(0x00);//Page Address High
	  SPI1_Write(0x00);//Page Address Low
	 HAL_Delay(10);
	CS_SPI_Deselect();
	 HAL_Delay(10);
	 
	 CS_SPI_Select();
	 HAL_Delay(10);
	 SPI1_Write(0X03);// Transfer from  Buffer to Out
	 SPI1_Write(0x00);//CA Address High
	 SPI1_Write(0x00);//CA Address Low
	  SPI1_Write(0x00);//Dummy
	 for (int i = 0; i < 10; i++) {
    Data_Read[i] = SPI1_Read();
  }
		 HAL_Delay(10);
	CS_SPI_Deselect();
	 if (Data_Read[1]==0x22)
	 {
		 HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		HAL_Delay(300);
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		HAL_Delay(300);}
		 if (Data_Read[0]==0X11)
			{
			HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
		HAL_Delay(300);
		HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
		HAL_Delay(300);}
			
		if (Data_Read[2]==0X33)
			{
			HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		HAL_Delay(300);
		HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		HAL_Delay(300);}
	 }
	 
 
/*void Get_ID_25M02(void)
 //  {
//	  #define CS_SPI_Pin GPIO_PIN_4
//#define CS_SPI_GPIO_Port GPIOA

  uint8_t id[ID_SIZE];

  while (1) {
    W25M02_ReadID(id);

    

    HAL_Delay(1000);
 // }
}
   */
/* USER CODE END 1 */

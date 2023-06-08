/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    octospi.c
  * @brief   This file provides code for the configuration
  *          of the OCTOSPI instances.
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
#include "octospi.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

OSPI_HandleTypeDef hospi1;

/* OCTOSPI1 init function */
void MX_OCTOSPI1_Init(void)
{

  /* USER CODE BEGIN OCTOSPI1_Init 0 */

  /* USER CODE END OCTOSPI1_Init 0 */

  OSPIM_CfgTypeDef sOspiManagerCfg = {0};
  HAL_OSPI_DLYB_CfgTypeDef HAL_OSPI_DLYB_Cfg_Struct = {0};

  /* USER CODE BEGIN OCTOSPI1_Init 1 */

  /* USER CODE END OCTOSPI1_Init 1 */
  hospi1.Instance = OCTOSPI1;
  hospi1.Init.FifoThreshold = 1;
  hospi1.Init.DualQuad = HAL_OSPI_DUALQUAD_DISABLE;
  hospi1.Init.MemoryType = HAL_OSPI_MEMTYPE_MICRON;
  hospi1.Init.DeviceSize = 32;
  hospi1.Init.ChipSelectHighTime = 1;
  hospi1.Init.FreeRunningClock = HAL_OSPI_FREERUNCLK_DISABLE;
  hospi1.Init.ClockMode = HAL_OSPI_CLOCK_MODE_0;
  hospi1.Init.WrapSize = HAL_OSPI_WRAP_NOT_SUPPORTED;
  hospi1.Init.ClockPrescaler = 1;
  hospi1.Init.SampleShifting = HAL_OSPI_SAMPLE_SHIFTING_NONE;
  hospi1.Init.DelayHoldQuarterCycle = HAL_OSPI_DHQC_DISABLE;
  hospi1.Init.ChipSelectBoundary = 0;
  hospi1.Init.DelayBlockBypass = HAL_OSPI_DELAY_BLOCK_BYPASSED;
  hospi1.Init.MaxTran = 0;
  hospi1.Init.Refresh = 0;
  if (HAL_OSPI_Init(&hospi1) != HAL_OK)
  {
    Error_Handler();
  }
  sOspiManagerCfg.ClkPort = 1;
  sOspiManagerCfg.IOLowPort = HAL_OSPIM_IOPORT_1_LOW;
  sOspiManagerCfg.Req2AckTime = 1;
  if (HAL_OSPIM_Config(&hospi1, &sOspiManagerCfg, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_OSPI_DLYB_Cfg_Struct.Units = 0;
  HAL_OSPI_DLYB_Cfg_Struct.PhaseSel = 0;
  if (HAL_OSPI_DLYB_SetConfig(&hospi1, &HAL_OSPI_DLYB_Cfg_Struct) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN OCTOSPI1_Init 2 */

  /* USER CODE END OCTOSPI1_Init 2 */

}

void HAL_OSPI_MspInit(OSPI_HandleTypeDef* ospiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(ospiHandle->Instance==OCTOSPI1)
  {
  /* USER CODE BEGIN OCTOSPI1_MspInit 0 */

  /* USER CODE END OCTOSPI1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_OSPI;
    PeriphClkInit.OspiClockSelection = RCC_OSPICLKSOURCE_MSIK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* OCTOSPI1 clock enable */
    __HAL_RCC_OSPIM_CLK_ENABLE();
    __HAL_RCC_OSPI1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    /**OCTOSPI1 GPIO Configuration
    PB0     ------> OCTOSPIM_P1_IO1
    PE12     ------> OCTOSPIM_P1_IO0
    PE14     ------> OCTOSPIM_P1_IO2
    PE15     ------> OCTOSPIM_P1_IO3
    PB10     ------> OCTOSPIM_P1_CLK
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPI1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPI1;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPI1;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* USER CODE BEGIN OCTOSPI1_MspInit 1 */

  /* USER CODE END OCTOSPI1_MspInit 1 */
  }
}

void HAL_OSPI_MspDeInit(OSPI_HandleTypeDef* ospiHandle)
{

  if(ospiHandle->Instance==OCTOSPI1)
  {
  /* USER CODE BEGIN OCTOSPI1_MspDeInit 0 */

  /* USER CODE END OCTOSPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_OSPIM_CLK_DISABLE();
    __HAL_RCC_OSPI1_CLK_DISABLE();

    /**OCTOSPI1 GPIO Configuration
    PB0     ------> OCTOSPIM_P1_IO1
    PE12     ------> OCTOSPIM_P1_IO0
    PE14     ------> OCTOSPIM_P1_IO2
    PE15     ------> OCTOSPIM_P1_IO3
    PB10     ------> OCTOSPIM_P1_CLK
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0|GPIO_PIN_10);

    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_12|GPIO_PIN_14|GPIO_PIN_15);

  /* USER CODE BEGIN OCTOSPI1_MspDeInit 1 */

  /* USER CODE END OCTOSPI1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void CS_OSPI_Select(void) {
  HAL_GPIO_WritePin(CS_OSPI_GPIO_Port, CS_OSPI_Pin, GPIO_PIN_RESET);
}

void CS_OSPI_Deselect(void) {
  HAL_GPIO_WritePin(CS_OSPI_GPIO_Port, CS_OSPI_Pin, GPIO_PIN_SET);
}


void OctaSPI_GetID(void)
	
{
	//uint8_t txData = 0x9F; // Command to send
     uint16_t DATA_READ_OSPI=3;
    OSPI_RegularCmdTypeDef cmd;
    cmd.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG ;
    cmd.FlashId = HAL_OSPI_FLASH_ID_1;
    cmd.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	  cmd.Instruction = 0x9F; /* Read Identification command */
    cmd.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
    cmd.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    cmd.AddressMode = HAL_OSPI_ADDRESS_NONE;
    cmd.AddressSize = HAL_OSPI_ADDRESS_24_BITS;
    cmd.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
    cmd.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    cmd.DataMode = HAL_OSPI_DATA_1_LINE;
	  cmd.DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE;
    cmd.DQSMode = HAL_OSPI_DQS_DISABLE;
    cmd.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
     cmd.DummyCycles = 8;
	  cmd.NbData = 3;
    
    uint8_t rxData1[3] = {0}; // Buffer to store the received data
 
    CS_OSPI_Select();
HAL_Delay(10);
    HAL_OSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY);
  
     for (int i = 0; i < DATA_READ_OSPI; i++) {
         HAL_OSPI_Receive(&hospi1, &rxData1[i], HAL_MAX_DELAY);
           }
		 
  HAL_Delay(10);
	CS_OSPI_Deselect();
	 if (rxData1[0]==0xEF)
	 {
		 HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		HAL_Delay(300);
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		HAL_Delay(300);}
		 if (rxData1[1]==0XBB)
			{
			HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
		HAL_Delay(300);
		HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
		HAL_Delay(300);}
			
		if (rxData1[2]==0X21)
			{
			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
		HAL_Delay(300);
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
		HAL_Delay(300);}
	 }
	 
 

  void OSPI_READ_W25M02IG(void)
	
{
	// READ FLASH TO BUFFER
    // uint16_t DATA_READ_OSPI=10;
    OSPI_RegularCmdTypeDef cmd;
    cmd.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG ;
    cmd.FlashId = HAL_OSPI_FLASH_ID_1;
    cmd.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	  cmd.Instruction = 0x1300; /* Read Identification command */
    cmd.InstructionSize = HAL_OSPI_INSTRUCTION_16_BITS;
    cmd.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    cmd.AddressMode = HAL_OSPI_ADDRESS_1_LINE;
    cmd.AddressSize = HAL_OSPI_ADDRESS_16_BITS;
    cmd.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
    cmd.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
   // cmd.DataMode = HAL_OSPI_DATA_1_LINE;
   	cmd.DataMode = HAL_OSPI_DATA_NONE;
	  cmd.DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE;
    cmd.DQSMode = HAL_OSPI_DQS_DISABLE;
    cmd.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
    cmd.DummyCycles = 0;
	  cmd.NbData = 0;
    cmd.Address = 0x000A;//WRITE PAGE ADDRESS only 2047 BYTES TO BUFFER
    uint8_t rxData1[10] = {0}; // Buffer to store the received data
 uint8_t txData;
		HAL_Delay(10);
    CS_OSPI_Select();
HAL_Delay(10);
    HAL_OSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY);
  // uint8_t txData = 0x00;
	//	 HAL_OSPI_Transmit(&hospi1, &txData, HAL_MAX_DELAY);//WRITE PAGE ADDRESS TO BUFFER (PA HIGH)
	//	txData = 0x02;
		// HAL_OSPI_Transmit(&hospi1, &txData, HAL_MAX_DELAY);//WRITE PAGE ADDRESS TO BUFFER (PA LOW)
		
HAL_Delay(1);
				CS_OSPI_Deselect();
		//READ BUFFER TO OUT
HAL_Delay(10);
		CS_OSPI_Select();
HAL_Delay(1);
		uint16_t DATA_READ_OSPI=10;
    cmd.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG ;
    cmd.FlashId = HAL_OSPI_FLASH_ID_1;
    cmd.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	  cmd.Instruction = 0x03; /* Read Identification command */
    cmd.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
    cmd.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    cmd.AddressMode = HAL_OSPI_ADDRESS_1_LINE;
    cmd.AddressSize = HAL_OSPI_ADDRESS_16_BITS;
    cmd.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
    cmd.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    cmd.DataMode = HAL_OSPI_DATA_1_LINE;
   //	cmd.DataMode = HAL_OSPI_DATA_NONE;
	  cmd.DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE;
    cmd.DQSMode = HAL_OSPI_DQS_DISABLE;
    cmd.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
    cmd.DummyCycles = 8;
	  cmd.NbData = 10;
    cmd.Address = 0x0000;//READ CA ADDRESS 2047 BYTE TO OUT
  
		HAL_OSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY);
     for (int i = 0; i < DATA_READ_OSPI; i++) {
         HAL_OSPI_Receive(&hospi1, &rxData1[i], HAL_MAX_DELAY);
           }
		 
  HAL_Delay(1);
	CS_OSPI_Deselect();
			 HAL_Delay(10);		 
	 if (rxData1[0]==0x7A)
	 {
		 HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		HAL_Delay(300);
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		HAL_Delay(300);}
		 if (rxData1[1]==0X7B)
			{
			HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
		HAL_Delay(300);
		HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
		HAL_Delay(300);}
			
		if (rxData1[2]==0X7C)
			{
			HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		HAL_Delay(300);
		HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		HAL_Delay(300);}
	 } 

	 void OSPI_Erase128K_W25M02IG(void)
	 {
		 //-----------------------WRITE ENABLE CONFIGORATION(Protection Register_1) ----------------------
		CS_OSPI_Select();
    HAL_Delay(10); 
		 OSPI_RegularCmdTypeDef cmd;
    cmd.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG ;
    cmd.FlashId = HAL_OSPI_FLASH_ID_1;
    cmd.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	  cmd.Instruction = 0xD800; /* Read Identification command */
    cmd.InstructionSize = HAL_OSPI_INSTRUCTION_16_BITS;
    cmd.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    cmd.AddressMode = HAL_OSPI_ADDRESS_1_LINE;
    cmd.AddressSize = HAL_OSPI_ADDRESS_16_BITS;
    cmd.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
    cmd.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
   // cmd.DataMode = HAL_OSPI_DATA_1_LINE;
   	cmd.DataMode = HAL_OSPI_DATA_NONE;
	  cmd.DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE;
    cmd.DQSMode = HAL_OSPI_DQS_DISABLE;
    cmd.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
    cmd.DummyCycles = 0;
	  cmd.NbData = 0;
    cmd.Address = 0x0000;
    			
    HAL_OSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY);
	    
    		HAL_Delay(1);
				CS_OSPI_Deselect();
        HAL_Delay(10);
				
			}
				
	 void OSPI_WRITE_W25M02IG(void)
	 {
		 //-----------------------WRITE ENABLE CONFIGORATION(Protection Register_1) ----------------------
		CS_OSPI_Select();
    HAL_Delay(10); 
		 OSPI_RegularCmdTypeDef cmd;
    cmd.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG ;
    cmd.FlashId = HAL_OSPI_FLASH_ID_1;
    cmd.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	  cmd.Instruction = 0x1FAA82; /* Read Identification command */
    cmd.InstructionSize = HAL_OSPI_INSTRUCTION_24_BITS;
    cmd.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    cmd.AddressMode = HAL_OSPI_ADDRESS_NONE;
    cmd.AddressSize = HAL_OSPI_ADDRESS_16_BITS;
    cmd.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
    cmd.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
   // cmd.DataMode = HAL_OSPI_DATA_1_LINE;
   	cmd.DataMode = HAL_OSPI_DATA_NONE;
	  cmd.DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE;
    cmd.DQSMode = HAL_OSPI_DQS_DISABLE;
    cmd.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
    cmd.DummyCycles = 0;
	  cmd.NbData = 0;
    cmd.Address = 0x0000;
    	
		
    HAL_OSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY);
	                               	/*uint8_t txData = 0xA0;
                               		 HAL_OSPI_Transmit(&hospi1, &txData, HAL_MAX_DELAY);
														   		txData = 0x02;
                              		 HAL_OSPI_Transmit(&hospi1, &txData, HAL_MAX_DELAY);*/
		
    		HAL_Delay(10);
				CS_OSPI_Deselect();
        HAL_Delay(10);
		
		//--------------------------THE END WRITE ENABLE CONFIGORATION (Protection Register)-----------
	 
                                //  
		//---------------------start write in buffer maximum 2045 ADDRESS CA------------------------
                	// -------- Random Load Program Data (84h)------------
		 CS_OSPI_Select();
     HAL_Delay(10);
		 uint16_t DATA_READ_OSPI=10;
		 uint8_t DATA_Send[]={0x7A,0x7B,0x7C,0x7D,0x75,0x76,0x77,0x70,0x88,0x99};
   
    cmd.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG ;
    cmd.FlashId = HAL_OSPI_FLASH_ID_1;
    cmd.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	  cmd.Instruction = 0x84; // Read Identification command 
    cmd.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
    cmd.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    cmd.AddressMode = HAL_OSPI_ADDRESS_1_LINE;
    cmd.AddressSize = HAL_OSPI_ADDRESS_16_BITS;
    cmd.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
    cmd.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    cmd.DataMode = HAL_OSPI_DATA_1_LINE;
   //	cmd.DataMode = HAL_OSPI_DATA_NONE;
	  cmd.DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE;
    cmd.DQSMode = HAL_OSPI_DQS_DISABLE;
    cmd.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
    cmd.DummyCycles = 0;
	  cmd.NbData = 10;
    cmd.Address = 0x0000;// WRITE BUFFER CA ADDRESS
   // uint8_t rxData1[10] = {0}; // Buffer to store the received data
   // uint8_t txData;
		HAL_OSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY);
     for (int i = 0; i < DATA_READ_OSPI; i++) {
         HAL_OSPI_Transmit(&hospi1, &DATA_Send[i], HAL_MAX_DELAY);
			 
           }
		 
					 HAL_Delay(10);
				CS_OSPI_Deselect();
    HAL_Delay(10);
		 //------------------------The End send Data on buffer---------------------------------
			

					 // write enable (0X06)----------------------------------
	 CS_OSPI_Select();
	 HAL_Delay(10);
	 // uint8_t txData = 0x06;
   // HAL_OSPI_Transmit(&hospi1, &txData, HAL_MAX_DELAY);			 
	  cmd.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	  cmd.Instruction = 0x06; // Read Identification command 
    cmd.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
    cmd.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    cmd.AddressMode = HAL_OSPI_ADDRESS_NONE;
    cmd.AddressSize = HAL_OSPI_ADDRESS_16_BITS;
    cmd.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
    cmd.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    //cmd.DataMode = HAL_OSPI_DATA_1_LINE;
   	cmd.DataMode = HAL_OSPI_DATA_NONE;
	  cmd.DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE;
    cmd.DQSMode = HAL_OSPI_DQS_DISABLE;
    cmd.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
    cmd.DummyCycles = 0;
	  cmd.NbData = 0;
    cmd.Address = 0x000A;		 
	 HAL_OSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY);// WRITE ENABLE 0X06
	  
	 HAL_Delay(10);
	CS_OSPI_Deselect();
	 
	//-------------------------------------- THE End write enbale---------------
  
	 //-----------------------------------Program Execute (10h) PAGE ADDRESS-----------------
	 HAL_Delay(10);
	CS_OSPI_Select();
	 HAL_Delay(10);
	 cmd.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
	  cmd.Instruction = 0x1000; //Read Identification command and Dummy
    cmd.InstructionSize = HAL_OSPI_INSTRUCTION_16_BITS;
    cmd.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    cmd.AddressMode = HAL_OSPI_ADDRESS_1_LINE;
    cmd.AddressSize = HAL_OSPI_ADDRESS_16_BITS;
    cmd.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
    cmd.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    //cmd.DataMode = HAL_OSPI_DATA_1_LINE;
   	cmd.DataMode = HAL_OSPI_DATA_NONE;
	  cmd.DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE;
    cmd.DQSMode = HAL_OSPI_DQS_DISABLE;
    cmd.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
    cmd.DummyCycles = 0;
	  cmd.NbData = 0;
    cmd.Address = 0x0000;//WRITE TO FLASHRAM PAGE ADDRESS
		
	 HAL_OSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY);
	                          // txData = 0x00;
                            //   		 HAL_OSPI_Transmit(&hospi1, &txData, HAL_MAX_DELAY);
														//	    	HAL_OSPI_Transmit(&hospi1, &txData, HAL_MAX_DELAY);
                              //		 HAL_OSPI_Transmit(&hospi1, &txData, HAL_MAX_DELAY);
	 HAL_Delay(10);
	CS_OSPI_Deselect();
	 HAL_Delay(10);
	 //---------------------The END PROGRAM EXCIUT-------------------------------
	 	 
	 
	 }
	 
/* USER CODE END 1 */

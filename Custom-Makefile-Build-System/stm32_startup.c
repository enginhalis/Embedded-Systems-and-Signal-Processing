#include <stdint.h>

#define SRAM_START 		0X20000000
#define SRAM_SIZE 		(128 * 1024)
#define SRAM_END		( (SRAM_START) + (SRAM_SIZE) )

#define STACK_START 	SRAM_END

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _la_data;

int main(void);

void __libc_init_array(void);

void Reset_Handler(void);

void NMI_Handler 					(void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler 					(void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler   				(void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void WWDG_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void PVD_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));             
void TAMP_STAMP_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));      
void RTC_WKUP_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));                               
void RCC_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));             
void EXTI0_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));           
void EXTI1_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));           
void EXTI2_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));           
void EXTI3_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));           
void EXTI4_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));           
void DMA1_Stream0_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Stream1_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Stream2_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Stream3_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Stream4_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Stream5_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Stream6_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void ADC_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));             
void CAN1_TX_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));         
void CAN1_RX0_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));        
void CAN1_RX1_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));        
void CAN1_SCE_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));        
void EXTI9_5_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));         
void TIM1_BRK_TIM9_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));   
void TIM1_UP_TIM10_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));   
void TIM1_TRG_COM_TIM11_IRQHandler 	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));         
void TIM2_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));            
void TIM3_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));            
void TIM4_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));            
void I2C1_EV_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));         
void I2C1_ER_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));         
void I2C2_EV_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));         
void I2C2_ER_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));         
void SPI1_IRQHandler  				(void) __attribute__ ((weak, alias("Default_Handler")));           
void SPI2_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));            
void USART1_IRQHandler  			(void) __attribute__ ((weak, alias("Default_Handler")));         
void USART2_IRQHandler  			(void) __attribute__ ((weak, alias("Default_Handler")));        
void USART3_IRQHandler   			(void) __attribute__ ((weak, alias("Default_Handler")));        
void EXTI15_10_IRQHandler   		(void) __attribute__ ((weak, alias("Default_Handler")));     
void RTC_Alarm_IRQHandler    		(void) __attribute__ ((weak, alias("Default_Handler")));    
void OTG_FS_WKUP_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler"))); 
void TIM8_BRK_TIM12_IRQHandler   	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_UP_TIM13_IRQHandler    	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_TRG_COM_TIM14_IRQHandler 	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_CC_IRQHandler          	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream7_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void FSMC_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void SDIO_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM5_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void SPI3_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void UART4_IRQHandler            	(void) __attribute__ ((weak, alias("Default_Handler")));
void UART5_IRQHandler            	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM6_DAC_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM7_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream0_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream1_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream2_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream3_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream4_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void ETH_IRQHandler              	(void) __attribute__ ((weak, alias("Default_Handler")));
void ETH_WKUP_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_TX_IRQHandler          	(void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_RX0_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_RX1_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_SCE_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_IRQHandler           	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream5_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream6_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream7_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void USART6_IRQHandler           	(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_EV_IRQHandler          	(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_ER_IRQHandler          	(void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_EP1_OUT_IRQHandler   	(void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_EP1_IN_IRQHandler    	(void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_WKUP_IRQHandler      	(void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_IRQHandler           	(void) __attribute__ ((weak, alias("Default_Handler")));
void DCMI_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void CRYP_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void HASH_RNG_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_IRQHandler              	(void) __attribute__ ((weak, alias("Default_Handler"))); 

uint32_t vectors[] __attribute__((section(".isr_vector"))) = {
    STACK_START,                     // 0x00: Stack Pointer başlangıcı
    (uint32_t)&Reset_Handler,        // 0x04: Reset
    (uint32_t)&NMI_Handler,          // 0x08: NMI
    (uint32_t)&HardFault_Handler,    // 0x0C: Hard Fault
    (uint32_t)&MemManage_Handler,    // 0x10: MPU Fault
    (uint32_t)&BusFault_Handler,     // 0x14: Bus Fault
    (uint32_t)&UsageFault_Handler,   // 0x18: Usage Fault
    0,                               // 0x1C: Reserved
    0,                               // 0x20: Reserved
    0,                               // 0x24: Reserved
    0,                               // 0x28: Reserved
    (uint32_t)&SVC_Handler,          // 0x2C: SVCall
    (uint32_t)&DebugMon_Handler,     // 0x30: Debug Monitor
    0,                               // 0x34: Reserved
    (uint32_t)&PendSV_Handler,       // 0x38: PendSV
    (uint32_t)&SysTick_Handler,      // 0x3C: SysTick

    /* Harici (Peripheral) Kesmeler */
    (uint32_t)&WWDG_IRQHandler,                  // 0: Window Watchdog
    (uint32_t)&PVD_IRQHandler,                   // 1: PVD through EXTI Line detection
    (uint32_t)&TAMP_STAMP_IRQHandler,            // 2: Tamper and TimeStamp interrupts
    (uint32_t)&RTC_WKUP_IRQHandler,             // 3: RTC Wakeup interrupt through EXTI
	0,
    (uint32_t)&RCC_IRQHandler,                   // 5: RCC global interrupt
    (uint32_t)&EXTI0_IRQHandler,                 // 6: EXTI Line0 interrupt
    (uint32_t)&EXTI1_IRQHandler,                 // 7: EXTI Line1 interrupt
    (uint32_t)&EXTI2_IRQHandler,                 // 8: EXTI Line2 interrupt
    (uint32_t)&EXTI3_IRQHandler,                 // 9: EXTI Line3 interrupt
    (uint32_t)&EXTI4_IRQHandler,                 // 10: EXTI Line4 interrupt
    (uint32_t)&DMA1_Stream0_IRQHandler,          // 11: DMA1 Stream0 global interrupt
    (uint32_t)&DMA1_Stream1_IRQHandler,          // 12: DMA1 Stream1 global interrupt
    (uint32_t)&DMA1_Stream2_IRQHandler,          // 13: DMA1 Stream2 global interrupt
    (uint32_t)&DMA1_Stream3_IRQHandler,          // 14: DMA1 Stream3 global interrupt
    (uint32_t)&DMA1_Stream4_IRQHandler,          // 15: DMA1 Stream4 global interrupt
    (uint32_t)&DMA1_Stream5_IRQHandler,          // 16: DMA1 Stream5 global interrupt
    (uint32_t)&DMA1_Stream6_IRQHandler,          // 17: DMA1 Stream6 global interrupt
    (uint32_t)&ADC_IRQHandler,                   // 18: ADC1, ADC2 and ADC3 global interrupts
    (uint32_t)&CAN1_TX_IRQHandler,               // 19: CAN1 TX interrupts
    (uint32_t)&CAN1_RX0_IRQHandler,              // 20: CAN1 RX0 interrupts
    (uint32_t)&CAN1_RX1_IRQHandler,              // 21: CAN1 RX1 interrupts
    (uint32_t)&CAN1_SCE_IRQHandler,              // 22: CAN1 SCE interrupt
    (uint32_t)&EXTI9_5_IRQHandler,               // 23: EXTI Line[9:5] interrupts
    (uint32_t)&TIM1_BRK_TIM9_IRQHandler,         // 24: TIM1 Break interrupt and TIM9
    (uint32_t)&TIM1_UP_TIM10_IRQHandler,         // 25: TIM1 Update interrupt and TIM10
    (uint32_t)&TIM1_TRG_COM_TIM11_IRQHandler,    // 26: TIM1 Trigger/Commutation and TIM11
    (uint32_t)&TIM1_CC_IRQHandler,               // 27: TIM1 Capture Compare interrupt
    (uint32_t)&TIM2_IRQHandler,                  // 28: TIM2 global interrupt
    (uint32_t)&TIM3_IRQHandler,                  // 29: TIM3 global interrupt
    (uint32_t)&TIM4_IRQHandler,                  // 30: TIM4 global interrupt
    (uint32_t)&I2C1_EV_IRQHandler,               // 31: I2C1 event interrupt
    (uint32_t)&I2C1_ER_IRQHandler,               // 32: I2C1 error interrupt
    (uint32_t)&I2C2_EV_IRQHandler,               // 33: I2C2 event interrupt
    (uint32_t)&I2C2_ER_IRQHandler,               // 34: I2C2 error interrupt
    (uint32_t)&SPI1_IRQHandler,                  // 35: SPI1 global interrupt
    (uint32_t)&SPI2_IRQHandler,                  // 36: SPI2 global interrupt
    (uint32_t)&USART1_IRQHandler,                // 37: USART1 global interrupt
    (uint32_t)&USART2_IRQHandler,                // 38: USART2 global interrupt
    (uint32_t)&USART3_IRQHandler,                // 39: USART3 global interrupt
    (uint32_t)&EXTI15_10_IRQHandler,             // 40: EXTI Line[15:10] interrupts
    (uint32_t)&RTC_Alarm_IRQHandler,             // 41: RTC Alarms (A and B) through EXTI
    (uint32_t)&OTG_FS_WKUP_IRQHandler,           // 42: USB On-The-Go FS Wakeup through EXTI
    (uint32_t)&TIM8_BRK_TIM12_IRQHandler,        // 43: TIM8 Break interrupt and TIM12
    (uint32_t)&TIM8_UP_TIM13_IRQHandler,         // 44: TIM8 Update interrupt and TIM13
    (uint32_t)&TIM8_TRG_COM_TIM14_IRQHandler,    // 45: TIM8 Trigger/Commutation and TIM14
    (uint32_t)&TIM8_CC_IRQHandler,               // 46: TIM8 Capture Compare interrupt
    (uint32_t)&DMA1_Stream7_IRQHandler,          // 47: DMA1 Stream7 global interrupt
    (uint32_t)&FSMC_IRQHandler,                  // 48: FSMC global interrupt
    (uint32_t)&SDIO_IRQHandler,                  // 49: SDIO global interrupt
    (uint32_t)&TIM5_IRQHandler,                  // 50: TIM5 global interrupt
    (uint32_t)&SPI3_IRQHandler,                  // 51: SPI3 global interrupt
    (uint32_t)&UART4_IRQHandler,                 // 52: UART4 global interrupt
    (uint32_t)&UART5_IRQHandler,                 // 53: UART5 global interrupt
    (uint32_t)&TIM6_DAC_IRQHandler,              // 54: TIM6 global interrupt, DAC1 and DAC2
    (uint32_t)&TIM7_IRQHandler,                  // 55: TIM7 global interrupt
    (uint32_t)&DMA2_Stream0_IRQHandler,          // 56: DMA2 Stream0 global interrupt
    (uint32_t)&DMA2_Stream1_IRQHandler,          // 57: DMA2 Stream1 global interrupt
    (uint32_t)&DMA2_Stream2_IRQHandler,          // 58: DMA2 Stream2 global interrupt
    (uint32_t)&DMA2_Stream3_IRQHandler,          // 59: DMA2 Stream3 global interrupt
    (uint32_t)&DMA2_Stream4_IRQHandler,          // 60: DMA2 Stream4 global interrupt
    (uint32_t)&ETH_IRQHandler,                   // 61: Ethernet global interrupt
    (uint32_t)&ETH_WKUP_IRQHandler,              // 62: Ethernet Wakeup through EXTI line
    (uint32_t)&CAN2_TX_IRQHandler,               // 63: CAN2 TX interrupts
    (uint32_t)&CAN2_RX0_IRQHandler,              // 64: CAN2 RX0 interrupts
    (uint32_t)&CAN2_RX1_IRQHandler,              // 65: CAN2 RX1 interrupts
    (uint32_t)&CAN2_SCE_IRQHandler,              // 66: CAN2 SCE interrupt
    (uint32_t)&OTG_FS_IRQHandler,                // 67: USB On-The-Go FS global interrupt
    (uint32_t)&DMA2_Stream5_IRQHandler,          // 68: DMA2 Stream5 global interrupt
    (uint32_t)&DMA2_Stream6_IRQHandler,          // 69: DMA2 Stream6 global interrupt
    (uint32_t)&DMA2_Stream7_IRQHandler,          // 70: DMA2 Stream7 global interrupt
    (uint32_t)&USART6_IRQHandler,                // 71: USART6 global interrupt
    (uint32_t)&I2C3_EV_IRQHandler,               // 72: I2C3 event interrupt
    (uint32_t)&I2C3_ER_IRQHandler,               // 73: I2C3 error interrupt
    (uint32_t)&OTG_HS_EP1_OUT_IRQHandler,        // 74: USB On-The-Go HS End Point 1 Out
    (uint32_t)&OTG_HS_EP1_IN_IRQHandler,         // 75: USB On-The-Go HS End Point 1 In
    (uint32_t)&OTG_HS_WKUP_IRQHandler,           // 76: USB On-The-Go HS Wakeup through EXTI
    (uint32_t)&OTG_HS_IRQHandler,                // 77: USB On-The-Go HS global interrupt
    (uint32_t)&DCMI_IRQHandler,                  // 78: DCMI global interrupt
    (uint32_t)&CRYP_IRQHandler,                  // 79: CRYP crypto global interrupt
    (uint32_t)&HASH_RNG_IRQHandler,              // 80: Hash and Rng global interrupt
    (uint32_t)&FPU_IRQHandler,                   // 81: FPU global interrupt
};

void Default_Handler(void){
	while(1);
}

void Reset_Handler(void){
	
	//copy .data section to SRAM
	uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
	
	uint8_t *pDst = (uint8_t*)&_sdata;	//sram
	uint8_t *pSrc = (uint8_t*)&_la_data;	//flash
	
	for(uint32_t i=0; i < size; i++){
		
		*pDst++ = *pSrc++;
	}
	
	//Init the .bss section to 0 in SRAM
	size = &_ebss - &_sbss;
	pDst = (uint8_t*)&_sbss;
	for(uint32_t i=0; i < size; i++){
		
		*pDst++ = 0;
	}
	
	__libc_init_array();
	
	main();
}
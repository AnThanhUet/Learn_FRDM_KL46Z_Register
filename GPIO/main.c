#include <stdio.h>
#include <stdint.h>

/*===================================================
                    SIM - CLOCK
=====================================================*/
typedef struct 
{
    uint32_t SOPT1;
    uint32_t SOPT1CFG;
    uint8_t RESERVED_0[4092];
    uint32_t SOPT2;
    uint8_t RESERVED_1[4];
    uint32_t SOPT4;
    uint32_t SOPT5;
    uint8_t RESERVED_2[4];
    uint32_t SOPT7;
    uint8_t RESERVED_3[8];
    uint32_t SDID;
    uint8_t RESERVED_4[12];
    uint32_t SCGC4;
    uint32_t SCGC5;
    uint32_t SCGC6;
    uint32_t SCGC7;
    uint32_t CLKDIV1;
    uint8_t RESERVED_5[4];
    uint32_t FCFG1;
    uint32_t FCFG2;
    uint8_t RESERVED_6[4];
    uint32_t UIDMH;
    uint32_t UIDML;
    uint32_t UIDL;
    uint8_t RESERVED_7[156];
    uint32_t COPC;
    uint32_t SRVCOP;
} SIM_Type;

#define SIM_ADDRESS            0x40047000
SIM_Type * SIM = (SIM_Type *)SIM_ADDRESS;

/*===================================================
                    PORT BASE
=====================================================*/
typedef struct 
{
    uint32_t PCR[32];
	uint32_t GPCLR;
	uint32_t GPCHR;
	uint8_t REVSER[24];
	uint32_t ISFR;
} PORT_Type;

#define PORTA_ADDRESS            0x40049000               /* PORT A address */
PORT_Type * PORTA = (PORT_Type *)PORTA_ADDRESS;           /* PORT A pointer */

#define PORTB_ADDRESS            0x4004A000               /* PORT B address */
PORT_Type * PORTB = (PORT_Type *)PORTB_ADDRESS;           /* PORT B pointer */

#define PORTC_ADDRESS            0x4004B000               /* PORT C address */
PORT_Type * PORTC = (PORT_Type *)PORTC_ADDRESS;           /* PORT C pointer */

#define PORTD_ADDRESS            0x4004C000               /* PORT D address */
PORT_Type * PORTD = (PORT_Type *)PORTD_ADDRESS;           /* PORT D pointer */

#define PORTE_ADDRESS            0x4004D000               /* PORT E address */
PORT_Type * PORTE = (PORT_Type *)PORTE_ADDRESS;           /* PORT E pointer */


#define PORT_MUX_MASK       7
#define PORT_MUX_SHIFT      8       /* vi tri*/

/*===================================================
                    GPIO BASE
=====================================================*/
typedef struct 
{
    uint32_t PDOR;
    uint32_t PSOR;
    uint32_t PCOR;
    uint32_t PTOR;
    uint32_t PDIR;
    uint32_t PDDR;
} GPIO_Type;

#define GPIOA_ADDRESS            0x400FF000               /* GPIO A address */
GPIO_Type * GPIOA = (GPIO_Type *)GPIOA_ADDRESS;           /* GPIO A pointer */

#define GPIOB_ADDRESS            0x400FF040               /* GPIO B address */
GPIO_Type * GPIOB = (GPIO_Type *)GPIOB_ADDRESS;           /* GPIO B pointer */

#define GPIOC_ADDRESS            0x400FF080               /* GPIO C address */
GPIO_Type * GPIOC = (GPIO_Type *)GPIOC_ADDRESS;           /* GPIO C pointer */

#define GPIOD_ADDRESS            0x400FF0C0               /* GPIO D address */
GPIO_Type * GPIOD = (GPIO_Type *)GPIOD_ADDRESS;           /* GPIO D pointer */

#define GPIOE_ADDRESS            0x400FF100               /* GPIO E address */
GPIO_Type * GPIOE = (GPIO_Type *)GPIOE_ADDRESS;           /* GPIO E pointer */

/* Config pin on - off */
#define LED_ON  GPIOD -> PDOR |= (1 << 5)
#define LED_OFF  GPIOD -> PDOR &= ~(1 << 5)

void Delay_ms(uint16_t time)
{
    uint32_t time_n = time * 12000;
    while(time_n != 0)
    {
        time_n --;
    }
}
void GPIO_Configuration(void)
{
    /* Enable clock PORTD, PORTE */
    SIM -> SCGC5 |= (1 << 12);  /* Set bit 12 */
    SIM -> SCGC5 |= (1 << 13);  /* Set bit 13 */

    /* Configure Pin5 and Pin 29 PCR_MUX as GPIO - MUX(10-8) = 001 */
    PORTD -> PCR[5] |= (1 << 8);
    PORTE -> PCR[29] |= (1 << 8);

    /* Configure Pin5 and Pin29 output */
    GPIOD -> PDDR |= (1 << 5);
    GPIOE -> PDDR |= (1 << 29);
    LED_OFF;
}
void main(void)
{
    GPIO_Configuration();
    while (1)
    {
        LED_ON;
        Delay_ms(1000);
        LED_OFF;
        Delay_ms(1000);
    }
}



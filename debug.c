#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "debug.h"
#include "portio.h"



#define TX_BUFF_SIZE    100
#define RX_BUFF_SIZE    100


volatile uint16_t g_txBuffer[TX_BUFF_SIZE];
volatile uint8_t g_bytesToSend = 0;
volatile uint8_t g_sendIndex = 0;

volatile uint16_t g_rxBuffer[RX_BUFF_SIZE];
volatile uint8_t g_bytesReceived = 0;
volatile uint8_t g_receivedMessage = 0;



uint8_t IsStringsEqual(const uint8_t *s1, const uint8_t *s2, uint8_t fields)
{
    uint8_t i;

    for (i = 0; i < fields; ++i)
        if (s1[i] != s2[i])
            return 0;

    return 1;
}

void debug_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    //----------------------------------------------------------------
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    //----------------------------------------------------------------
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;   

    GPIO_Init(GPIOA, &GPIO_InitStructure);
    //----------------------------------------------------------------
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    
    NVIC_Init(&NVIC_InitStructure);
    //----------------------------------------------------------------
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);
   
    //we enable this interrupt only when buffer will be ready to send 
    //USART_ITConfig(USART1,USART_IT_TXE, ENABLE);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    USART_Cmd(USART1, ENABLE);
}

void debug_Print(const char *msg)
{
    uint8_t i;
    while (g_bytesToSend); //waiting for finish sending

    //copy message
    for (i = 0; i < TX_BUFF_SIZE; ++i) {
        if (msg[i] != 0)
            g_txBuffer[i] = msg[i];
        else
            break;
    }

    g_bytesToSend = i;
    g_sendIndex = 0;

    USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
}

void debug_ParseIncoming(void)
{
    if (g_receivedMessage) {
        debug_Print(":D\n\r");

        g_receivedMessage = 0;
    }
}

void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
        if (g_receivedMessage == 0) {
            g_rxBuffer[g_bytesReceived] = USART_ReceiveData(USART1);
            ++g_bytesReceived;

            if (g_rxBuffer[g_bytesReceived - 1] < 32)
                g_receivedMessage = 1;

            if (g_bytesReceived == RX_BUFF_SIZE)
                g_receivedMessage = 1;
        }
    }

    if (USART_GetITStatus(USART1, USART_IT_TXE) == SET) {
        if (g_bytesToSend) {
            portio_Led(PORTIO_LED_G, PORTIO_ON);
            USART_SendData(USART1, g_txBuffer[g_sendIndex]);
            ++g_sendIndex;

            if (g_sendIndex == g_bytesToSend) {
                USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
                g_bytesToSend = 0;
                portio_Led(PORTIO_LED_G, PORTIO_OFF);
            }
        }
    }
}


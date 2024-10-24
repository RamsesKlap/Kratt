#include "project.h"


void Delay(uint32_t ms) {
    for (volatile uint32_t i = DELAY_1MS * ms; i > 0; i--) {}
}


void I2CInit(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PCTL_PA7_I2C1SDA);
    GPIOPinConfigure(GPIO_PCTL_PA6_I2C1SCL);
    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);
    I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(), false);

    // Pull up I2C3 by PB6 and PB7 pins
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_7);
    GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD_WPU);
}


void ConfigureUART(void) {
    // Enable the GPIO Peripheral used by the UART.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Enable UART0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    // Configure GPIO Pins for UART mode.
    GPIOPinConfigure(GPIO_PCTL_PA0_U0RX);
    GPIOPinConfigure(GPIO_PCTL_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Use the internal 16MHz oscillator as the UART clock source.
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    // Initialize the UART for console I/O.
    UARTStdioConfig(0, 115200, 16000000);
}
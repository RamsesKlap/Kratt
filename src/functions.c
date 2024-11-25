#include "project.h"


void Delay(uint32_t ms) {
    for (volatile uint32_t i = DELAY_1MS * ms; i > 0; i--) {}
}

void UARTInit(void) {
    // Enable the GPIO Peripheral used by the UART.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Enable UART0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    // Configure GPIO Pins for UART mode.
    GPIOPinConfigure(GPIO_PCTL_PA0_U0RX);
    GPIOPinConfigure(GPIO_PCTL_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Use the internal 16MHz oscillator as the UART clock source.
    // UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    // Initialize the UART for console I/O.
    UARTStdioConfig(0, 115200, SysCtlClockGet());
}

void I2CInit(void) {
    // Init the peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    //SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);

    // Init the GPIO ports
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    // Configure the Ports to SCL (PB2) and SDA (PB3)
    GPIOPinConfigure(GPIO_PCTL_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PCTL_PB3_I2C0SDA);

    // Configure the pins to be I2C
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

    // Init the master
    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);

    HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;


    /*
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    UARTprintf("Pin Configure\n\r");
    GPIOPinConfigure(GPIO_PCTL_PA7_I2C1SDA);
    GPIOPinConfigure(GPIO_PCTL_PA6_I2C1SCL);
    UARTprintf("Pin Type\n\r");
    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);
    UARTprintf("Master start\n\r");
    I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(), false);
    */
}
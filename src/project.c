#include "project.h"

// The error routine that is called if the driver library encounters an error.
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

VL53L7CX_Configuration sens1;
VL53L7CX_ResultsData resSens1;

int main(void) {
    //__asm__("ldr r0, =0x20000100");
    //__asm__("mov sp, r0");

    // Setup
    ConfigureUART();
    UARTprintf("\n\nI2C start\n\r");
    I2CInit();
    UARTprintf("I2C end\n\r");
    
    UARTprintf("TOF variables\n\r");
    uint8_t status, isReady;
    UARTprintf("Variables end\n\r");
    
    UARTprintf("TOF addres and base(d)\n\r");
    sens1.platform.address = VL53L7CX_DEFAULT_I2C_ADDRESS;
    sens1.platform.baseI2C = I2C1_BASE;
    sens1.platform.baseLPn = GPIO_PORTF_BASE;
    sens1.platform.pin = GPIO_PIN_4;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);
    UARTprintf("TOF end\n\r");

    UARTprintf("TOF INIT BEGIN\n\r");
    status = vl53l7cx_init(&sens1);
    UARTprintf("TOF INIT END\n\r");

    status = vl53l7cx_start_ranging(&sens1);
    UARTprintf("Loop start\n\r");
    // Loop
    while(true) {
        UARTprintf("Loop\n");
        status = vl53l7cx_check_data_ready(&sens1, &isReady);
        
        if (isReady) {
            vl53l7cx_get_ranging_data(&sens1, &resSens1);
            for (int i = 0; i < VL53L7CX_RESOLUTION_4X4; i++) {
                UARTprintf("Distance %d: %d\n", i, resSens1.distance_mm[i]);
            }
        } 
        Delay(50);
    }
}

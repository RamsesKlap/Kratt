#include "project.h"

// The error routine that is called if the driver library encounters an error.
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif


int
main(void) {
    // Setup
    I2CInit();
    ConfigureUART();
    UARTprintf("Test");
    
    VL53L7CX_Configuration sens1;
    VL53L7CX_ResultsData resSens1;
    uint8_t status, isReady;
    
    sens1.platform.address = VL53L7CX_DEFAULT_I2C_ADDRESS;
    sens1.platform.baseI2C = I2C1_BASE;
    // sens1.platform.baseLPn = GPIO_PORTF_BASE;
    // sens1.platform.pin = GPIO_PIN_4;
    //GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);
    
    status = vl53l7cx_init(&sens1);

    status = vl53l7cx_start_ranging(&sens1);
    // Loop
    while(true) {
        //status = vl53l7cx_check_data_ready(&sens1, &isReady);
        UARTprintf("Test");
        
        /*
        if (isReady) {
            vl53l7cx_get_ranging_data(&sens1, &resSens1);
            for (int i = 0; i < VL53L7CX_RESOLUTION_4X4; i++) {
                UARTprintf("Distance %d: %d\n", i, resSens1.distance_mm[i]);
            }
        } */
        Delay(50);
    }
}

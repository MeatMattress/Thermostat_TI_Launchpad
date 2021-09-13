/*
 * Copyright (c) 2015-2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== gpiointerrupt.c ========
 */
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/I2C.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/Timer.h>

/* Driver configuration */
#include "ti_drivers_config.h"

// UART Global Variables
char output[64];
int bytesToSend;

// Driver Handles - Global variables
UART_Handle uart;
I2C_Handle i2c;
Timer_Handle timer0;

// Period timer constants
const unsigned int tasksPeriodGCD = 100000;
const unsigned int periodCheckBtnFlags = 200000;
const unsigned int periodCheckTemp = 500000;
const unsigned int periodUpdateUART = 1000000;
#define TASKSNUM 3


/* Declaring tasks struct */
typedef struct task {
  int state; // Current state of the task
  unsigned int period; // Rate at which the task should tick
  unsigned int elapsedTime; // Time since task's previous tick
  int (*TickFct)(int); // Function to call for task's tick
} task;

// Declare tasks array (number of tasks = 3)
task tasks[TASKSNUM];

int16_t setpoint = 24; // arbitrary starting temp to avoid clicking a bunch first (my current room temp)
unsigned char heat = 0;
unsigned int seconds;
int temperature;

// State definitions
enum Btn_States {Btn_HoldSetpoint, Btn_RaiseSetpoint, Btn_LowerSetpoint} Btn_State = Btn_HoldSetpoint;
enum LED_States {LED_OFF, LED_ON} LED_State = LED_OFF;
unsigned char TimerFlag = 0;

// UART Display definition
#define DISPLAY(x) UART_write(uart, &output, x);

/*
 *  ======== btnFct ========
 *  Callback function for the GPIO interrupt on CONFIG_GPIO_BUTTON_0 and CONFIG_GPIO_BUTTON_1.
 *
 *  Note: GPIO interrupts are cleared prior to invoking callbacks.
 */
void btnFct(uint_least8_t index) {
    /* Set button press flag / state
     * (Flag off if state = Btn_HoldSetpoint aka 0)
     * */
    if (index == 0) {
        Btn_State = Btn_LowerSetpoint;
    }
    else if (index == 1){
        Btn_State = Btn_RaiseSetpoint;
    }
    // Assign the state in the tasks array
    tasks[0].state = Btn_State;
}

// I2C Global Variables
static const struct {
 uint8_t address;
 uint8_t resultReg;
 char *id;
} sensors[3] = {
 { 0x48, 0x0000, "11X" },
 { 0x49, 0x0000, "116" },
 { 0x41, 0x0001, "006" }
};
uint8_t txBuffer[1];
uint8_t rxBuffer[2];
I2C_Transaction i2cTransaction;


// Make sure you call initUART() before calling this function.
void initI2C(void)
{
 int8_t i, found;
 I2C_Params i2cParams;
 DISPLAY(snprintf(output, 64, "Initializing I2C Driver - "));
 // Init the driver
 I2C_init();
 // Configure the driver
 I2C_Params_init(&i2cParams);
 i2cParams.bitRate = I2C_400kHz;
 // Open the driver
 i2c = I2C_open(CONFIG_I2C_0, &i2cParams);
 if (i2c == NULL)
 {
 DISPLAY(snprintf(output, 64, "Failed\n\r"));
 while (1);
 }
 DISPLAY(snprintf(output, 32, "Passed\n\r"));
 // Boards were shipped with different sensors.
 // Welcome to the world of embedded systems.
 // Try to determine which sensor we have.
 // Scan through the possible sensor addresses
 /* Common I2C transaction setup */
 i2cTransaction.writeBuf = txBuffer;
 i2cTransaction.writeCount = 1;
 i2cTransaction.readBuf = rxBuffer;
 i2cTransaction.readCount = 0;
 found = false;
 for (i=0; i<3; ++i)
 {
 i2cTransaction.slaveAddress = sensors[i].address;
 txBuffer[0] = sensors[i].resultReg;
 DISPLAY(snprintf(output, 64, "Is this %s? ", sensors[i].id));
 if (I2C_transfer(i2c, &i2cTransaction))
 {
 DISPLAY(snprintf(output, 64, "Found\n\r"));
 found = true;
 break;
 }
 DISPLAY(snprintf(output, 64, "No\n\r"));
 }
 if(found)
 {
 DISPLAY(snprintf(output, 64, "Detected TMP%s I2C address: %x\n\r", sensors[i].id, i2cTransaction.slaveAddress));
 }
 else
 {
 DISPLAY(snprintf(output, 64, "Temperature sensor not found, contact professor\n\r"));
 }
}
int16_t readTemp(void) {
 int16_t temperature = 0;
 i2cTransaction.readCount = 2;
 if (I2C_transfer(i2c, &i2cTransaction))
 {
 /*
 * Extract degrees C from the received data;
 * see TMP sensor datasheet
 */
 temperature = (rxBuffer[0] << 8) | (rxBuffer[1]);
 temperature *= 0.0078125;
 /*
 * If the MSB is set '1', then we have a 2's complement
 * negative value which needs to be sign extended
 */
 if (rxBuffer[0] & 0x80)
 {
 temperature |= 0xF000;
 }
 }
 else {
 DISPLAY(snprintf(output, 64, "Error reading temperature sensor (%d)\n\r",i2cTransaction.status));
 DISPLAY(snprintf(output, 64, "Please power cycle your board by unplugging USB and plugging back in.\n\r"));
 }
 return temperature;
}

void initUART(void) {
 UART_Params uartParams;
 // Init the driver
 UART_init();
 // Configure the driver
 UART_Params_init(&uartParams);
 uartParams.writeDataMode = UART_DATA_BINARY;
 uartParams.readDataMode = UART_DATA_BINARY;
 uartParams.readReturnMode = UART_RETURN_FULL;
 uartParams.baudRate = 115200;
 // Open the driver
 uart = UART_open(CONFIG_UART_0, &uartParams);
 if (uart == NULL) {
 /* UART_open() failed */
 while (1);
 }
}

void timerCallback(Timer_Handle myHandle, int_fast16_t status) {
    // Raise timer flag
    TimerFlag = 1;
}

void initTimer(void)
{
 Timer_Params params;
 // Init the driver
 Timer_init();
 // Configure the driver
 Timer_Params_init(&params);
 params.period = 100000;
 params.periodUnits = Timer_PERIOD_US;
 params.timerMode = Timer_CONTINUOUS_CALLBACK;
 params.timerCallback = timerCallback;
 // Open the driver
 timer0 = Timer_open(CONFIG_TIMER_0, &params);
 if (timer0 == NULL) {
 /* Failed to initialized timer */
 while (1) {}
 }
 if (Timer_start(timer0) == Timer_STATUS_ERROR) {
 /* Failed to start timer */
 while (1) {}
 }
}



/* Task tick function definitions */

// Write the data to the UART in the format specified.
// Professor: Pleeeease tell me why this format %04d is giving me 1 trailing 0 for seconds.
// It doesn't trail zeroes on any other formatted value except seconds.
int writeUART(int placeholder){
    DISPLAY(snprintf(output, 64, "<%02d,%02d,%d,%04d>\n\r", readTemp(), setpoint, heat, seconds));
    return placeholder;
}

// Button press task using the enumerated flag set by the button press ISR
int tickBtn(Btn_State) {
    switch(Btn_State) {
    case 0: break;
    case 1:
        ++setpoint;
        Btn_State = 0;
        break;
    case 2: --setpoint;
        Btn_State = 0;
        break;
    }
    return Btn_State;
}

// LED task
int tickLED(LED_State) {
    temperature = readTemp();
    if (temperature > setpoint) {
        LED_State = 1;
    }
    else {
        LED_State = 0;
    }

    switch(LED_State) {
    case 0:
        GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF);
        heat = 0;
        break;
    case 1:
        GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);
        heat = 1;
        break;
    }
    return LED_State;
}

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    /* Call driver init functions */
    GPIO_init();


    /* Configure the LED and button pins */
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_BUTTON_0, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

    /* Turn on user LED */
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF);

    /* Install Button callback */
    GPIO_setCallback(CONFIG_GPIO_BUTTON_0, btnFct);

    /* Enable interrupts */
    GPIO_enableInt(CONFIG_GPIO_BUTTON_0);

    /*
     *  If more than one input pin is available for your device, interrupts
     *  will be enabled on CONFIG_GPIO_BUTTON1.
     */
    if (CONFIG_GPIO_BUTTON_0 != CONFIG_GPIO_BUTTON_1) {
        /* Configure BUTTON1 pin */
        GPIO_setConfig(CONFIG_GPIO_BUTTON_1, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

        /* Install Button callback */
        GPIO_setCallback(CONFIG_GPIO_BUTTON_1, btnFct);
        GPIO_enableInt(CONFIG_GPIO_BUTTON_1);
    }


    /* Define tasks */
    unsigned char i = 0;

    // Task 1: Button routine
    tasks[i].period = periodCheckBtnFlags;
    tasks[i].elapsedTime = 0;
    tasks[i].state = Btn_HoldSetpoint;
    tasks[i].TickFct = &tickBtn;
    ++i;
    // Task 2: Update LED
    tasks[i].period = periodUpdateUART;
    tasks[i].elapsedTime = 0;
    tasks[i].TickFct = &tickLED;
    ++i;
    // Task 3: Update UART
    tasks[i].period = periodUpdateUART;
    tasks[i].elapsedTime = 0;
    tasks[i].TickFct = &writeUART;



    // initializations for peripherals & timer
    initUART();
    initI2C();
    initTimer();


    while(1)
    {
        while (!TimerFlag){}; // Wait for timer period

        // Timer flag raised - Conduct ISR
        unsigned char i;
          for (i = 0; i < TASKSNUM; ++i) { // Heart of the scheduler code
             if (tasks[i].elapsedTime >= tasks[i].period ) { // Ready
                tasks[i].state = tasks[i].TickFct(tasks[i].state);
                tasks[i].elapsedTime = 0;
             }
             tasks[i].elapsedTime += tasksPeriodGCD;
          }
        TimerFlag = 0;
        ++seconds;
    }
}

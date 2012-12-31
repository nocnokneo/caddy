/* caddy.c
 *
 *    caddy's main loop and atmel initialization.
 *
 */

#include "caddy.h"

int main(void)
{
    initAtmel();
    loadTweakValues();
    initBotGlobals();
    resetCamera();
    initButtons();
    moveServosToStart();
    cameraWhiteBal();

#if DEBUGGING
    runDebugger();                  // allow tweaking, until red button pressed
#else
    waitFor(RED_BUTTON);
#endif
    myDelay(START_DELAY);           // wait to remove finger (or debug cable)

#if DEBUGGING
    runTest();
#else
    runBot();
#endif

    brake(BOTH);
#if DEBUGGING
    lcdWriteStr("Done            ", 0, 0);
    lcdWriteStr("                ", 1, 0);
#endif

    return 0;
}

/*
 * Timer, PWM, UART, rprintf, LCD initialization, CMUcam
 */
inline void initAtmel(void)
{
    // Initialize Timer
    timerInit();
#if DEBUGGING
    // Initialize LCD
    lcdInit();
    ourLcdControlWrite(1 << LCD_ON_CTRL | 1 << LCD_ON_DISPLAY);
    lcdWriteStr("Init:           ", 0, 0);
    lcdWriteStr("                ", 1, 0);
#endif
    // Initialize UART
    uartInit();
    uartSetBaudRate(CMU_BAUD);
    uartSetRxHandler(packetRcv);
    rprintfInit(uartSendByte);
    // Initialize PWM
    outb(DDRD, 0xff);
    timer1PWMInit(8);
    neutral();
    enableMotors();

    outb(DDRA, 0xF0);
    // Motor control and up/down buttons
    cbi(DDRD, 6);
    // red button
    cbi(DDRB, 0);
    // nest button
    cbi(DDRB, 1);
    // break beam
    sbi(PORTB, 0);
    // appies pullup resistor to PINB0
//   sbi(PORTB, 1);     // appies pullup resistor to PINB0
    sbi(PORTA, 3);
    // appies pullup resistor to PINA3
    sbi(PORTA, 2);
    // appies pullup resistor to PINA2
    sbi(PORTA, 1);
    // appies pullup resistor to PINA1
    sbi(PORTA, 0);
    // appies pullup resistor to PINA0

    // Initialize wheel encoders
    cbi(DDRD, 2);
    cbi(DDRD, 3);
    encoderInit();
}


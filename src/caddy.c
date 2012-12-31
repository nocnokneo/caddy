/*
 * This file is part of Caddy.
 *
 *  Caddy is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Caddy is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Caddy.  If not, see <http://www.gnu.org/licenses/>.
 */
/* caddy.c
 *
 *    caddy's main loop and atmel initialization.
 *
 */

#include "caddy.h"

#define START_DELAY 5

int main(void)
{
    initAtmel();
    loadTweakValues();
    initBotGlobals();
    resetCamera();
    moveServosToStart();
    cameraWhiteBal();

#if DEBUGGING
    runTetherUI();                  // allow tweaking, until red button pressed
#else
    waitFor(RED_BUTTON);
#endif
    myDelay(START_DELAY);           // wait to remove finger (or debug cable)

#if DEBUGGING
    runTest();
#else
    runRoborodentiaCourse();
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


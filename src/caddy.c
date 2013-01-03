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
/** @file
 * @brief Caddy's main loop and Atmel initialization.
 */
#include "caddy.h"

/**
 * Short delay wait for finger to be fully removed from start button (or
 * tether cable to be disconnected)
 */
#define START_DELAY 5

/*
 * @brief Initialize Timer, PWM, UART, rprintf, LCD, GPIO, and wheel encoders
 */
static inline void initAtmel(void)
{
    /*
     * Initialize Timer
     */
    timerInit();

#if DEBUGGING
    /*
     * Initialize LCD
     */
    lcdInit();
    lcdWriteStr("Init:           ", 0, 0);
    lcdWriteStr("                ", 1, 0);
#endif

    /*
     * Initialize UART for CMUcam communication
     */
    uartInit();
    uartSetBaudRate(CMU_BAUD);
    uartSetRxHandler(packetRcv);
    rprintfInit(uartSendByte);

    /*
     * Initialize PWM motor control
     */
    outb(DDRD, 0xff);
    timer1PWMInit(8);
    neutral();
    enableMotors();

    /*
     * Set data direction registers
     */
    outb(DDRA, 0xF0); // Motor control and up/down buttons
    cbi(DDRD, 6);     // red button
    cbi(DDRB, 0);     // nest button
    cbi(DDRB, 1);     // break beam

    /*
     * Apply internal pull-up resister to certain digital inputs
     */
    sbi(PORTB, 0); // internal pull-up for PINB0
    sbi(PORTA, 3); // internal pull-up for PINA3
    sbi(PORTA, 2); // internal pull-up for PINA2
    sbi(PORTA, 1); // internal pull-up for PINA1
    sbi(PORTA, 0); // internal pull-up for PINA0

    /*
     * Initialize quadrature wheel encoders
     */
    cbi(DDRD, 2);
    cbi(DDRD, 3);
    encoderInit();
}

/**
 * @brief Caddy's power-on entry function
 */
int main(void)
{
    initAtmel();
    loadTweakValues();
    initBotGlobals();
    resetCamera();
    moveServosToStart();
    cameraWhiteBal();

#if DEBUGGING
    runTetherUI();
    myDelay(START_DELAY);
    runTest();
#else
    waitFor(RED_BUTTON);
    myDelay(START_DELAY);
    runRoborodentiaCourse();
#endif

    brake(BOTH);
#if DEBUGGING
    lcdWriteStr("Done            ", 0, 0);
    lcdWriteStr("                ", 1, 0);
#endif

    return 0;
}

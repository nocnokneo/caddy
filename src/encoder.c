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
/*! \file encoder.c \brief Quadrature Encoder reader/driver. */
//*****************************************************************************
//
// File Name	: 'encoder.c'
// Title		: Quadrature Encoder reader/driver
// Author		: Pascal Stang - Copyright (C) 2003-2004
// Created		: 2003.01.26
// Revised		: 2004.06.25
// Version		: 0.3
// Target MCU	: Atmel AVR Series
// Editor Tabs	: 4
//
// NOTE: This code is currently below version 1.0, and therefore is considered
// to be lacking in some functionality or documentation, or may not be fully
// tested.  Nonetheless, you can expect most functions to work.
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************
#ifndef WIN32
#include <avr/io.h>
#include <avr/signal.h>
#include <avr/interrupt.h>
#endif

#include "global.h"
#include "encoder.h"

// Program ROM constants

// Global variables
volatile EncoderStateType EncoderState[NUM_ENCODERS];

// Functions

// encoderInit() initializes hardware and encoder position readings
//		Run this init routine once before using any other encoder functions.
inline void encoderInit(void)
{
    u08 i;

    // initialize/clear encoder data
    for (i = 0; i < NUM_ENCODERS; i++)
    {
        EncoderState[i].position = 0;
        //EncoderState[i].velocity = 0;		// NOT CURRENTLY USED
    }

    // configure direction and interrupt I/O pins:
    // - for input
    // - apply pullup resistors
    // - any-edge interrupt triggering
    // - enable interrupt

#ifdef ENC0_SIGNAL
    // set interrupt pins to input and apply pullup resistor
    cbi(ENC0_PHASEA_DDR, ENC0_PHASEA_PIN);
    sbi(ENC0_PHASEA_PORT, ENC0_PHASEA_PIN);
    // configure interrupts for any-edge triggering
    sbi(ENC0_ICR, ENC0_ISCX0);
    cbi(ENC0_ICR, ENC0_ISCX1);
    // enable interrupts
    sbi(IMSK, ENC0_INT);
    // ISMK is auto-defined in encoder.h
#endif
#ifdef ENC1_SIGNAL
    // set interrupt pins to input and apply pullup resistor
    cbi(ENC1_PHASEA_DDR, ENC1_PHASEA_PIN);
    sbi(ENC1_PHASEA_PORT, ENC1_PHASEA_PIN);
    // configure interrupts for any-edge triggering
    sbi(ENC1_ICR, ENC1_ISCX0);
    cbi(ENC1_ICR, ENC1_ISCX1);
    // enable interrupts
    sbi(IMSK, ENC1_INT);
    // ISMK is auto-defined in encoder.h
#endif
#ifdef ENC2_SIGNAL
    // set interrupt pins to input and apply pullup resistor
    cbi(ENC2_PHASEA_DDR, ENC2_PHASEA_PIN);
    sbi(ENC2_PHASEA_PORT, ENC2_PHASEA_PIN);
    // configure interrupts for any-edge triggering
    sbi(ENC2_ICR, ENC2_ISCX0);
    cbi(ENC2_ICR, ENC2_ISCX1);
    // enable interrupts
    sbi(IMSK, ENC2_INT);// ISMK is auto-defined in encoder.h
#endif
#ifdef ENC3_SIGNAL
    // set interrupt pins to input and apply pullup resistor
    cbi(ENC3_PHASEA_DDR, ENC3_PHASEA_PIN);
    sbi(ENC3_PHASEA_PORT, ENC3_PHASEA_PIN);
    // set encoder direction pin for input and apply pullup resistor
    cbi(ENC3_PHASEB_DDR, ENC3_PHASEB_PIN);
    sbi(ENC3_PHASEB_PORT, ENC3_PHASEB_PIN);
    // configure interrupts for any-edge triggering
    sbi(ENC3_ICR, ENC3_ISCX0);
    cbi(ENC3_ICR, ENC3_ISCX1);
    // enable interrupts
    sbi(IMSK, ENC3_INT);// ISMK is auto-defined in encoder.h
#endif

    // enable global interrupts
    sei();
}

// encoderGetPosition() reads the current position of the encoder
u16 encoderGetPosition(u08 encoderNum)
{
    // sanity check
    if (encoderNum < NUM_ENCODERS)
        return EncoderState[encoderNum].position;
    else
        return 0;
}

// encoderSetPosition() sets the current position of the encoder
void encoderSetPosition(u08 encoderNum, u16 position)
{
    // sanity check
    if (encoderNum < NUM_ENCODERS)
        EncoderState[encoderNum].position = position;
    // else do nothing
}

#ifdef ENC0_SIGNAL
//! Encoder 0 interrupt handler
SIGNAL(ENC0_SIGNAL)
{
    /********************************************/
    /* Modified by Taylor                       */
    /********************************************/
    EncoderState[0].position++;
}
#endif

#ifdef ENC1_SIGNAL
//! Encoder 1 interrupt handler
SIGNAL(ENC1_SIGNAL)
{
    /********************************************/
    /* Modified by Taylor                       */
    /********************************************/
    EncoderState[1].position++;
}
#endif

#ifdef ENC2_SIGNAL
//! Encoder 2 interrupt handler
SIGNAL(ENC2_SIGNAL)
{
    // encoder has generated a pulse
    // check the relative phase of the input channels
    // and update position accordingly
    if( ((inb(ENC2_PHASEA_PORTIN) & (1<<ENC2_PHASEA_PIN)) == 0) ^
        ((inb(ENC2_PHASEB_PORTIN) & (1<<ENC2_PHASEB_PIN)) == 0) )
    {
        EncoderState[2].position++;
    }
    else
    {
        EncoderState[2].position--;
    }
}
#endif

#ifdef ENC3_SIGNAL
//! Encoder 3 interrupt handler
SIGNAL(ENC3_SIGNAL)
{
    // encoder has generated a pulse
    // check the relative phase of the input channels
    // and update position accordingly
    if( ((inb(ENC3_PHASEA_PORTIN) & (1<<ENC3_PHASEA_PIN)) == 0) ^
        ((inb(ENC3_PHASEB_PORTIN) & (1<<ENC3_PHASEB_PIN)) == 0) )
    {
        EncoderState[3].position++;
    }
    else
    {
        EncoderState[3].position--;
    }
}
#endif

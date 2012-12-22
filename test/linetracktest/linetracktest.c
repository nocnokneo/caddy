//*****************************************************************************
// linetracktest.c
//
//*****************************************************************************

#include "linetracktest.h"

void myDelay(u16 outerDelay)
{
   u16 i, j;
   for(i=0; i<outerDelay; i++)
   {
      for(j=0; j<MAX_U16; j++)
      {
	     ;
      }
   }
}


void setServo(u08 servoNum, u08 servoPos)
{
   rprintf("sv %d %d\r", servoNum, servoPos);
}


void disableServo(u08 servoNum)
{
   rprintf("so %d 0\r", servoNum);
}


void setPose(u08 pose)
{
   switch (pose)
   {
   case DRIVE_OPEN:
      // set servos to initial positions
      setServo(PAN, PAN_CENTER);
      setServo(BOOM, MAX_BOOM_UP);
      setServo(TILT, TILT_VERT);
      setServo(DOOR, DOOR_CLOSED);
      myDelay(30);
      setServo(LIFT, LIFT_OPEN);
      myDelay(20);
      disableServo(PAN);
      disableServo(BOOM);
      disableServo(TILT);
      disableServo(DOOR);
      disableServo(LIFT);
      lcdWriteStr("Drive Open", 0, 0);
      break;
   case DRIVE_UP:
      // set servos to initial positions
      setServo(PAN, PAN_CENTER);
      setServo(BOOM, BOOM_UP);
      setServo(TILT, TILT_VERT);
      setServo(DOOR, DOOR_CLOSED);
      myDelay(30);
      setServo(LIFT, LIFT_UP);
      myDelay(50);
      disableServo(PAN);
      disableServo(BOOM);
      disableServo(TILT);
      disableServo(DOOR);
      disableServo(LIFT);
      lcdWriteStr("Drive UP", 0, 0);
      break;
   default:
      lcdWriteStr("ERROR", 0, 0);
      break;
   }
}


void grabBonusBall()
{
   // Get in position
   //setPose(BB_READY);
   setServo(TILT, TILT_BACK);
   setServo(LIFT, LIFT_BB_READY);
   myDelay(40);
   
   // Drive up to the corner
   timer1PWMASet(255);
   timer1PWMBSet(255);
   forward();
   myDelay(20);
   brake();

   // Execute the pickup sequence
   setServo(BOOM, BOOM_BB_GRAB);
   myDelay(10);
   setServo(TILT, TILT_BB_GRAB);
   myDelay(10);
   setServo(BOOM, BOOM_UP);
   myDelay(15);
   setServo(LIFT, LIFT_UP);
   myDelay(0);
   
   // Back away from the corner
   timer1PWMASet(200);
   timer1PWMBSet(200);
   reverse();
   myDelay(15);
   brake();
}


void packetRcv(u08 c)
{
   static u08 mode = NEW_PACKET;
   
   switch (mode)
   {
   case FE_RCV:
      lineMode2Rcv(c);
      if (c == 0xfd)
      {
         mode = NEW_PACKET;
      }
      break;
   case T_RCV:
   case ACK_RCV:
   case NCK_RCV:
   case ASCII_RCV:
      if (c == '\r')
      {
         mode = NEW_PACKET;
      }
      break;
   case NEW_PACKET:
      switch (c)
      {
      case 0xfe:
         mode = FE_RCV;
         break;
      case 'T':
         mode = T_RCV;
         break;
      case 'A':
         mode = ACK_RCV;
         break;
      case 'N':
         mode = NCK_RCV;
         break;
      default:
         mode = ASCII_RCV;
         break;
      }
   }
}

/*
void analyzeTopStrip(u08 stipStats[], u08 numRows) 
{
   u08 mean = getMean(stipStats, numRows);
   if (mean == 0) 
   {
      topLost = TRUE;
   }
   else
   {
      topLost = FALSE;
      topPosition = mean;
   }
}


void analyzeBottomStrip(u08 stipStats[], u08 numRows) 
{
   u08 mean = getMean(stipStats, numRows);
   if (mean == 0) 
   {
      bottomLost = TRUE;
   }
   else
   {
      bottomLost = FALSE;
      bottomPosition = mean;
   }
}
*/

BOOL isGoodScan(u08 y)
{
   u08 i = 0;
   
   for (i = y; i < y + SCAN_WIDTH; i++)
   {
      if (statsBuf[i][X_MEAN] == 0 ||
          statsBuf[i][X_MIN] < VW_X1_LINE+5 ||
          statsBuf[i][X_MAX] > VW_X2_LINE-5 ||
          statsBuf[i][LINE_COUNT] > 9)
      {
         return FALSE;
      }
   }
   return TRUE;
}

void analyzeStatsBuf(void) 
{
   u08 i = 0;
   u16 sum = 0;
   u08 y = 0;
   
   u08 lineY1;
   u08 lineX1;
   u08 lineY2;
   u08 lineX2;
   double m;
   
   // get line 1's X and Y values
   y = 0;
   while(y < VW_Y_SIZE_LINE - SCAN_WIDTH + 1 && !isGoodScan(y))
   {
      y++;
   }
   lineY1 = y;
   for(i = y ; i < y+SCAN_WIDTH; i++)
   {
      sum += statsBuf[i][X_MEAN];
   }
   lineX1 = sum / SCAN_WIDTH;
   
   // get line 2's X and Y values
   sum = 0;
   y = VW_Y_SIZE_LINE - SCAN_WIDTH + 1;
   while(y > lineY1 && !isGoodScan(y))
   {
      y--;
   }
   lineY2 = y;
   for(i = y ; i < y+SCAN_WIDTH; i++)
   {
      sum += statsBuf[i][X_MEAN];
   }
   lineX2 = sum / SCAN_WIDTH;
   
   m = (double)(lineX2 - lineX1) / (double)(lineY2 - lineY1);
   lineSlope = (s16)(SLOPE_COEF * m);
   lineOffset = LINE_X_CENTER - (m * (LINE_Y3 - lineY1) + lineX1);
   
   //dx = lineX2 - lineX1;
   //dy = lineY2 - lineY1;
   //lineSlope = (s16) ((SLOPE_COEF * (s16)dx) / dy );
   //lineOffset = LINE_X_CENTER - ( (dx * (LINE_Y3 - lineY1))/dy + lineX1 );
   
   //lcdWriteStr("y1:", 0, 0);
   lcdPrintHex(lineY1, 0, 0);
   //lcdWriteStr("x1:", 0, 6);
   lcdPrintHex(lineX1, 0, 3);
   
   //lcdWriteStr("y2:", 1, 0);
   lcdPrintHex(lineY2, 1, 0);
   //lcdWriteStr("x2:", 1, 6);
   lcdPrintHex(lineX2, 1, 3);
   
   //lcdWriteStr("s:", 0, 12);
   lcdPrintHex( lineSlope>>8, 0, 8);
   lcdPrintHex( lineSlope, 0, 10);
   //lcdWriteStr("x3:", 1, 11);
   lcdPrintHex(lineOffset, 0, 13);
   
   statsBufProcessed = TRUE;
}

u08 getMean(u08 stripStats[], u08 numRows)
{
   u08 i = 0;
   u16 sum = 0;
   u08 count = 0;
   for(i = 0; i < numRows; i++)
   {
      if (stripStats[i] != 0)
      {
         sum += stripStats[i];
         count++;
      }
   }
   if (count == 0)
   {
      return 0;
   }
   return sum / count;
}   


void lineMode2Rcv(u08 c) 
{
   static u16 byteNum = 0;
   
   if (c == 0xfd) 
   {
      statsBufProcessed = FALSE;      
      byteNum = 0;
      //uartSetRxHandler(packetRcv);
   }   
   else //if (byteNum != 0)
   {
      /*
      if (byteNum < 5)
      {
         lcdPrintHex(c, 1, byteNum*3);
      }
      */
      if (!statsBufProcessed)
      {
         // beep
      }
      statsBuf[(byteNum-1)/STAT_BUF_COLS][(byteNum-1)%STAT_BUF_COLS] = c;
      byteNum++;
   }
}


/*
void sendCommand(char *command)
{
   gotAck = 0;
   gotNck = 0; 
   rprintf(command);
   while (gotAck == 0 && gotNck == 0)
   {
      lcdWriteStr("waiting...", 0, 0);
   }
   lcdWriteStr("ACK:  ", 1, 0);
   lcdPrintHex(gotAck, 1, 4);
   lcdWriteStr("NCK:  ", 1, 8);
   lcdPrintHex(gotNck, 1, 12);
   myDelay(20);
}
*/

void cmuInit()
{
   //myDelay(10); // wait for the CMU to power up
   
   //lcdWriteStr("CMU Init", 0, 0);
   // Set high res mode
   rprintf("hr 1\r");

   //lcdWriteStr("White bal ON", 1, 0);
   // turn white balance on p.31
   rprintf("cr 18 44\r");
   myDelay(200);
   //lcdWriteStr("White bal OFF", 1, 0);
   // turn white balance off p.31
   rprintf("cr 18 40\r");
}


void trackLineInit() 
{
   // Assume we start on the center of the line
   lineSlope = 0;
   lineOffset = 0;

   topLost = TRUE;
   bottomLost = TRUE;
   statsBufProcessed = TRUE;
   // Set pan, tilt, boom postions
   setServo(BOOM, BOOM_UP);
   setServo(PAN, PAN_CENTER);
   setServo(TILT, TILT_FORWARD);
   myDelay(5);
   // Initialize wheel speeds to some base speed
   setLeftPWM(LEFT_BASE_SPEED);
   setRightPWM(RIGHT_BASE_SPEED);

   // Set Low Resolution
   rprintf("hr 0\r");
   // Downsample the image
   rprintf("DS %d %d\r", DS_X_LINE, DS_Y_LINE);
   // Line mode type 0, mode 2
   // "per row statistics in the tracked region" p.41
   rprintf("lm 0 2\r");
   // Output mask hides everything but, mean p.45
   rprintf("om 5 15\r");
   // set black line tracking parameters p.51
   rprintf("st 16 70 16 70 16 60\r");
   // set virtual window
   rprintf("vw %d %d %d %d\r", VW_X1_LINE, VW_Y1_LINE, VW_X2_LINE, VW_Y2_LINE);
   
   // start the tracking (Track Color)
   rprintf("tc\r");
}


void servoInit()
{
   // set servos to initial positions
   setServo(PAN, PAN_CENTER);
   setServo(BOOM, BOOM_UP);
   setServo(TILT, TILT_FORWARD);
   setServo(DOOR, DOOR_CLOSED);
   myDelay(30);
   setServo(LIFT, LIFT_UP);
   myDelay(50);
   disableServo(PAN);
   disableServo(BOOM);
   disableServo(TILT);
   disableServo(DOOR);
   disableServo(LIFT);
}


void init(void)
{
   // Initialize Timer
   timerInit();
   // Initialize LCD
   lcdInit();
   ourLcdControlWrite(1<<LCD_ON_CTRL | 1<<LCD_ON_DISPLAY);
   // Initialize UART
	uartInit();
	uartSetBaudRate(CMU_BAUD);
	uartSetRxHandler(packetRcv);
   rprintfInit(uartSendByte);
   // Initialize PWM
   outb(DDRD, 0xFF);	// set all port D pins to output
   timer1PWMInit(8);
	timer1PWMAOn();
   timer1PWMBOn();
   // Initialize  Servos
   servoInit();
   // Initialize CMU
   lcdWriteStr("CMUcam2 init", 0, 0);
   cmuInit();
}


void setLeftPWM(u08 pwm)
{
   leftPWM = pwm;
   timer1PWMBSet(pwm);
}


void setRightPWM(u08 pwm)
{
   rightPWM = pwm;
   timer1PWMASet(pwm);
}

void trackLine()
{
   s08 correction = 0;
   
   forward();
   
   /*
   if (lineOffset >= -3 && lineOffset <= 3) 
   {
      setRightPWM(BASE_SPEED);
      setLeftPWM(BASE_SPEED);
   }
   else if (lineOffset < -3) 
   {
      setRightPWM(50);
      setLeftPWM(BASE_SPEED-20);
   }
   else  
   {
      setRightPWM(BASE_SPEED-20);
      setLeftPWM(50);
   }
   */
   
   if (!statsBufProcessed)
   {
      analyzeStatsBuf();
      
      correction = MIN(MAX(lineSlope + lineOffset, -1*SPEED_RANGE), SPEED_RANGE);
      setLeftPWM(LEFT_BASE_SPEED - correction);
      setRightPWM(RIGHT_BASE_SPEED + correction);
      
      lcdPrintHex( leftPWM, 1, 8);
      lcdPrintHex(rightPWM, 1,11);
      lcdPrintHex(correction, 1, 14);
      
      /*
      lcdPrintHex(statsBuf[0][X_MEAN], 1, 0);
      lcdPrintHex(statsBuf[1][X_MIN], 1, 3);
      lcdPrintHex(statsBuf[2][X_MAX], 1, 6);
      lcdPrintHex(statsBuf[3][LINE_COUNT], 1, 9);
      */

      /*
      lcdWriteStr("l:", 1, 0);
      lcdPrintHex(bottomPosition, 1, 2);
      lcdWriteStr("o:", 1, 5);
      lcdPrintHex(bottomOffset, 1, 7);
      */
   }
   
   /*
   lcdWriteStr("left:", 0, 0);
   lcdPrintHex(leftPWM, 0, 5);
   lcdWriteStr("right:", 0, 8);
   lcdPrintHex(rightPWM, 0, 14);
   */
}


int main(void)
{
   neutral();
   init();
   lcdWriteStr("                ", 0, 0);
   lcdWriteStr("                ", 1, 0);

   trackLineInit();
   while(1) 
   {
      trackLine();
   }


/*
   // Bonus ball pickup sequence:
   setPose(DRIVE_UP);
   myDelay(30);
   
   grabBonusBall();
*/
   
/* 
   // Grounb ball pickup sequence:
   setPose(DRIVE_OPEN);
   
   // move, pickup, and brake
   forward();
   myDelay(60);
   setServo(LIFT, MAX_LIFT_UP);
   //disableServo(LIFT);
   myDelay(60);
   brake();
   myDelay(10);
   
   // drop balls and return to initial position
   setServo(DOOR, DOOR_OPEN);
   myDelay(60);
   setServo(DOOR, DOOR_CLOSED);
   myDelay(30);
   setServo(LIFT, MAX_LIFT_OPEN);
   //myDelay(5);
   //disableServo(DOOR);
   //disableServo(LIFT);
*/

   //lcdWriteStr("End", 1, 0);
   brake();

	return 0;
}

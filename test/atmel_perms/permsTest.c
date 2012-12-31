
#include "ourLcd.h"
#include "perms.h"
#include "buttons.h"


int main( void )
{
   initButtons();
   
   // Initialize LCD
   timerInit();
   lcdInit();
   ourLcdControlWrite(1<<LCD_ON_CTRL | 1<<LCD_ON_DISPLAY);
   lcdWriteStr("                ", 0, 0);
   lcdWriteStr("                ", 1, 0);
   
   // declare/init vars
   uint8_t i;
   const uint8_t N = 4;
   uint8_t curPerm[N];
   for( i = 0; i < N; i++ )
   {
      curPerm[i] = i;
   }
   
   do
   {
      // print perm
      for( i = 0; i < N; i++ )
      {
         lcdPrintDecU08(curPerm[i],0,3*i);
      }
      waitFor(RED_BUTTON);
   }
   while( next_permutation(curPerm, curPerm + N) );
   
   
   lcdWriteStr("done            ",0,0);
   
   return 0;
}

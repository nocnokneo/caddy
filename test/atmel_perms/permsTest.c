
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
   u08 i;
   const u08 N = 4;
   u08 curPerm[N];
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

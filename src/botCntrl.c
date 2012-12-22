/* botCntrl.c
 *
 *    Decides what Alf should be doing.
 *
 */

#include "botCntrl.h"

u08 botNode = START_NODE;
s08 botHeading = START_HEADING;
u08 numUnreachedGoals = NUM_GOALS;

inline void runBot( void )
{
   BOOL justTurned = FALSE;
   
   // run through first leg, skipping positionBot
   junctionCode();
   moveToJunction(1, justTurned);
   
   // Lower lift           // skipped junction code, so lower lift incase ball at node 1
   liftDown = TRUE;
   
#if DEBUGGING
      if( lcdMode == NAV_LCD_MODE )
      {
         lcdWriteStr("                ", 0, 0);
         lcdWriteStr("                ", 1, 0);
         lcdPrintDecU08(botNode, 1, 0);
         lcdPrintDecS08(botHeading, 1, 3);
      }
#endif

   
   // run through arena
   while( pathList[pathListIndex+1] != STOP_NODE )
   {
      junctionCode();                  // ball search, bonous ball pickup, best path code
      
      justTurned = positionBot();      // turning, preparing for linetracking
      
#if DEBUGGING
      if( lcdMode == NAV_LCD_MODE )
      {
         lcdPrintDecS08(botHeading, 1, 3);
      }
#endif

      moveToJunction(1, justTurned);   // linetracking, ground ball pickup
      
#if DEBUGGING
      if( lcdMode == NAV_LCD_MODE )
      {
         lcdPrintDecU08(botNode, 1, 0);
      }
#endif

   }
   
   if( pathList[pathListIndex+1] == STOP_NODE )
   {
      positionBot();   
      nestSequence();
   }
}


/*
 *  Initializes some of bot's global variables
 */
void initBotGlobals(void)
{
   u08 i;
   
   // init bot's path to INITIAL_PATH_LIST
   pathListIndex = 0;
   pathListSize = INITIAL_PATH_LIST_SIZE;
   // (pathList initialized in updatePath.c)
   
   // init checkedList to FALSE
   for( i = 0; i < NUM_BALL_NODES; i++ )
   {
      checkedList[i] = FALSE;
   }
   
   initGoalList();
   numKnownGoals = NUM_FIXED_GOALS;
   
   liftDown = FALSE;
}


/*
 * Turns bot at junctions and, if necessarry, ball nodes.
 * Maintains botHeading, performs bonus ball pickup, liftDown
 *
 * Returns true when bot just turned.  (Used to tell moveToJunction to
 * begin looking for next junction immediately.)
 *
 * PRE: camera is not streaming
 */
inline BOOL positionBot(void)
{
   s08 nextHeading;           // next botHeading
   s08 bradsToTurn;           // number of brads to turn
   s08 ticksToTurn;           // number of ticks to turn
   BOOL justTurned = TRUE;    // return value
   
   nextHeading = getNextHeading(pathList[pathListIndex + 1]);
   bradsToTurn = nextHeading - botHeading;
   
   // BB PICKUP CHECK
   if( botNode == BONUS_BALL_1 && isInGoalList(BONUS_BALL_1) )
   {
      bbPositioning(BB1_HEADING, nextHeading);
      removeFromGoalList(BONUS_BALL_1);
      numUnreachedGoals--;
   }
   else if( botNode == BONUS_BALL_2 && isInGoalList(BONUS_BALL_2) )
   {
      bbPositioning(BB2_HEADING, nextHeading);
      removeFromGoalList(BONUS_BALL_2);
      numUnreachedGoals--;
   }
   
   // TURN/STRAIGHT CHECK
   else if( bradsToTurn != 0 )
   {
      if( bradsToTurn == -128 )
      {
         tankTurn(245, -120);      
      }
      else
      {
         // fixed ticks forward here?
         
         // convert brads to turn to ticks and turn
         if( bradsToTurn < 0 )
         {
            ticksToTurn = bradsToTurn + turnSubtract;
         }
         else
         {
            ticksToTurn = bradsToTurn - turnSubtract;
         }
         tractorTurn(255, ticksToTurn);
      }
   }
   else
   {
      justTurned = FALSE;
   }
   
   if( botNode == SENSOR_NODE )
   {
      removeFromGoalList(SENSOR_NODE);
      numUnreachedGoals--;
   }
   
   // update botHeading
   botHeading = nextHeading;
   
   // GB PICKUP CHECK: lower lift, if bot knows it will travel over ball
   if( nextBallNodesInGoalList() )
   {
      //brake(BOTH);            // need to brake here?
      //msDelay(600);
      setServo(LIFT, LIFT_OPEN);
      //msDelay(600);
      
      liftDown = TRUE;
   }
   
   return justTurned;
}


/*
 * Returns absolute heading of next node given botNode and the next botNode.
 */
inline s08 getNextHeading(u08 nextBotNode)
{
   NODE nextNode;            // info about nodes adjacent to botNode
   s08 nextNodeIndex;        // nextNode offset to nextBotNode
   s08 nextHeading;          // absolute direction to nextBotNode
   
   // get absolute direction of nextBotNode from node list
   getNode(botNode, &nextNode);
   if( &nextNode == NULL )
   {
      #if DEBUGGING
         lcdWriteStr("nodeList error  ",0,0);
      #endif
      while(1) ;
   }
   nextNodeIndex = getIndex(nextBotNode, nextNode.adjNodes, nextNode.numAdjNodes);

   // get next heading or report error  
   if( nextNodeIndex == -1 )
   {
#if DEBUGGING
      lcdWriteStr("pathList error  ",0,0);
#endif
      brake(BOTH);
      while(1) ;
   }
   nextHeading = nextNode.adjHeadings[nextNodeIndex];
   
   return nextHeading;
}


/* Rotates bot before and after bb grab
 *    bbHeading   - heading bot must have for bb pickup.
 *    nextHeading - heading bot must have after bb pickup
 */
inline void bbPositioning( s08 bbHeading, s08 nextHeading )
{
   // move forward (camera will be over junction at this point)
   // May or may not need to move foward (requires testing)
   //    Some are fine without foward, some seem to need it
   //    Right now, only -32 case moves forward
   
   // rotate by (bbHeading - botHeading)
   switch( (s08)(bbHeading - botHeading) )   
   {
      case 96:
         // example of 96 brad rotation
         tickWheels(28, 0, 250);  // allows fluid motion (no overshoot correction)
         tankTurn(250, 58);
         break;
      case -96:
         tickWheels(0, 28, 250);  // allows fluid motion (no overshoot correction)
         tankTurn(250, -58);
         break;
      case -32:
         tickWheels(5, 5, 240);   // Move bot forward a few ticks to make it correctly aligned
         tickWheels(0, 28, 250);
         break;
      default:
         #if DEBUGGING
            lcdWriteStr("ERROR:          ", 0, 0);
            lcdWriteStr("Turn Amt =      ", 1, 0);
            lcdPrintDecS08(bbHeading - botHeading, 1, 11);
            brake(BOTH);
            while(1) ;
         #endif
         break;
   }
   
   grabBonusBall(); // Grab the BB
         
   // Rotate by (nextHeading - bbHeading)
   // (This should only be 32, -32, or -96)
   tankTurn(250, nextHeading - bbHeading);  // May need adjusting for brads turned?
}


/*
 * Moves to next junction in pathList.
 */
inline void moveToJunction( u08 numJunctions, BOOL justTurned )
{
   BOOL onLine = TRUE;
   BOOL juncApproaching = FALSE;
   u08 juncCount = 0;
   
   u08 ignoreJuncCount;
   if ( !justTurned )
   {
      ignoreJuncCount = 3;
   }
   else 
   {
      ignoreJuncCount = 0;
   }
   
   //u08 ballCheckCounter = 0;
   
   //u08 ballConfidence = 0;
   //BOOL approachingBall = FALSE;
      
   trackLineInit();
   
   // Linetrack, until bot is at junction or nest.
   // If see ground ball, pickup it up and continue linetracking.
   while ( onLine ) 
   {
      while(lineStatsProcessed);
      
      analyzeLineStats();
      adjustPWM();      
      
      // CURRENT JUNCTION IGNORE
      if( ignoreJuncCount > 0 && junctionY == 0 )
      {
         ignoreJuncCount--;
      }
      
      // JUNCTION CHECK
      if ( ignoreJuncCount == 0 && junctionY != 0 )
      {
         if( junctionY < turnPoint )
         {
            juncApproaching = TRUE;
         }
         else if( juncApproaching )
         {
            juncApproaching = FALSE;
            juncCount++;
            
            //stopBotOverJunction();  // <- move this to junction code, see if need ball search
                        
            // set botNode to next junction in pathList
            do
            {
               pathListIndex++;
               botNode = pathList[pathListIndex];
            } while( !isJunction(botNode) );
            
            // Break out of line tracking
            if( juncCount >= numJunctions )
            {
               onLine = FALSE;
            }
            
            //lcdWriteStr("botNode now =  ",0,0);
            //lcdPrintDec(botNode,0,14);
            //brake(BOTH);
            //myDelay(30);
            
            //lcdWriteStr("botHeading =  ",1,0);
            //lcdPrintHex(botHeading,1,14);
            //myDelay(60);
         }
      }
      
      // BALL CHECK
      if( liftDown /* && BREAK_BEAM_TRIGGERED && !startedPickup */ )
      {
         liftDown = FALSE;
         /*
         // Perhaps raise it slowly if there are pick-up problems
         setServo(LIFT, LIFT_UP); // Raise the Lift
         msDelay(3000);           // Give the lift time to move up
         
         // Set new botnode to node where this ball is with below function
         //botNode = findAndRemoveNextGoalFromGoalList();
         
         numUnreachedGoals--;
         
         streamModeOff();  // Turn off line tracking
         positionBot();    // In case we want to make a -128 brad turn after picking up ball
         trackLineInit();  // Turn line tracking back on
         */
      }
      
      /* OLD BALL CHECK
      ballCheckCounter = (ballCheckCounter + 1) % BALL_CHECK_RAIO;
      if( onLine && ballCheckCounter == 0 )
      {
         streamModeOff();
         
         if( getBallY() > PICK_UP_POINT )
         {
            // Change this -> make it move up slowly til it shuts
            setServo(LIFT, LIFT_UP);
         }
         
         restartLineMode();
      }
      */
      
      /*
      if ( possibleBallY > 0 ) 
      {
         ballConfidence++;
         if (ballConfidence > 5)
         {
            approachingBall = TRUE;
         }
         // Picks-up ball, updates various global variables, and turns, if needed
         // TODO: see flow chart
         //trackLineInit();
      }
      if (approachingBall && possibleBallY == 0) 
      {
         //disableMotors();
         approachingBall = FALSE;
      }
      */
   }
   
   streamModeOff();
   
   // Make sure lift is up (in case we missed a ball or incorrectly thought one was there)
   if( liftDown )
   {
      /*
      setServo(LIFT, LIFT_UP);    // Raise the lift
      msDelay(300);               // Give the lift time to rise
      disableServo(LIFT);         // Disable the servo
      
      // fix bot node and pathListIndex
      */
      liftDown = FALSE;
   }
}

void stopBotOverJunction ()
{
   //PWM_LEFT(0);
   //PWM_RIGHT(0);
   //while(1);
   
   disableMotors();
}

void nestSequence( void )
{
   // line track, until NEST_BUTTON is pressed
   trackLineInit();
      
   while ( !justPressed(NEST_BUTTON) )
   {
      if( !lineStatsProcessed )
      {
         analyzeLineStats();
         adjustPWM();
      }
      
      debounceButtons();
   }
   
   brake(BOTH);
   streamModeOff();
   setServo(LIFT, LIFT_UP);       // Turn lift on
   msDelay(300);

   // Open door, back up, close door
   setServo(DOOR, DOOR_OPEN);
   moveStraight(-1,255);              // Back up to take pressure off button
   brake(BOTH);
   //myDelay(25);                     // Let balls roll out
   msDelay(3000);
   setServo(DOOR, DOOR_CLOSED);       // Leaves door closed, so lift and door don't colide on power up.
   //myDelay(10);                     // Wait for door to close
   msDelay(1000);
   
   // Disable all servos
   disableServo(PAN);
   disableServo(TILT);
   disableServo(BOOM);
   disableServo(LIFT);
   disableServo(DOOR);
}

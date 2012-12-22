//
// CONFIG Defines
//
#define CMU_BAUD              38400
#define COLOR_SPACE
#define WHITE_BALANCE
#define AUTO_GAIN
#define CAMERA_RESOLUTION
#define PIXEL_DIFFERENCE
#define INVERTED_TRACKING
#define FRAME_STREAM
#define HIRES_FRAME_DIFF
#define DIFF_CHANNEL
#define LINE_MODES
#define BUFFER_MODE
#define NOISE_FILTER
#define DS_X_LINE             1
#define DS_Y_LINE             4
#define VW_X1_LINE            10
#define VW_Y1_LINE            1
#define VW_X2_LINE            77
#define VW_Y2_LINE            35
#define VW_X_SIZE_LINE             VW_X2_LINE-VW_X1_LINE+1
#define VW_Y_SIZE_LINE             VW_Y2_LINE-VW_Y1_LINE+1

#define LINE_STAT_MASK        0Xf
#define STAT_BUF_COLS         4  // must correspond to bits in LINE_STAT_MASK
#define STAT_BUF_ROWS         VW_Y_SIZE_LINE
#define X_MEAN                0
#define X_MIN                 1
#define X_MAX                 2
#define LINE_COUNT            3
#define SCAN_WIDTH            4
#define LINE_X_CENTER         (VW_X2_LINE - VW_X1_LINE)/2 + 4
#define LINE_Y3               49
#define SLOPE_COEF            256

#define TOP_STRIP_MIN         1
#define TOP_STRIP_MAX         20
#define TOP_STRIP_SIZE        (TOP_STRIP_MAX-TOP_STRIP_MIN+1)
#define BOTTOM_STRIP_MIN      234
#define BOTTOM_STRIP_MAX      254
#define BOTTOM_STRIP_SIZE     (BOTTOM_STRIP_MAX-BOTTOM_STRIP_MIN+1)


#define NEW_PACKET   0
#define FE_RCV       1
#define T_RCV        2
#define ACK_RCV      3
#define NCK_RCV      4
#define ASCII_RCV    5

//
// COLOR Defines
//


//
// SERVO Defines
//
#define PAN    0
#define TILT   1
#define BOOM   2
#define LIFT   3
#define DOOR   4

#define PAN_CENTER         130

#define TILT_BB_GRAB       114
#define TILT_VERT          93   // requires boom to be MAX_UP
#define TILT_BACK          MAX_TILT_BACK
#define TILT_FORWARD       MAX_TILT_FORWARD

#define BOOM_UP            MAX_BOOM_UP
#define BOOM_BB_GRAB       144   // cup 2.32 inches off ground

#define LIFT_OPEN          MAX_LIFT_OPEN
#define LIFT_UP            MAX_LIFT_UP
#define LIFT_BB_READY      110   // "V" 3 inces off ground

#define DOOR_CLOSED        74    // touches closed at 73
#define DOOR_OPEN          MAX_DOOR_OPEN

//
// SERVO LIMITS
//
#define MAX_PAN_LEFT       50
#define MAX_PAN_RIGHT      195

#define MAX_TILT_BACK      195
#define MAX_TILT_FORWARD   70

#define MAX_BOOM_UP        45
#define MAX_BOOM_DOWN      148

#define MAX_LIFT_OPEN      171
#define MAX_LIFT_UP        68

#define MAX_DOOR_CLOSED    62
#define MAX_DOOR_OPEN      184

// 
// Pose Defines
//
#define DRIVE_OPEN         1
#define DRIVE_UP           2
#define BB_READY           3



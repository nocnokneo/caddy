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
#define DOWN_SAMPLE_X
#define DOWN_SAMPLE_Y
#define VIRTUAL_WINDOW_X1
#define VIRTUAL_WINDOW_Y1
#define VIRTUAL_WINDOW_X2
#define VIRTUAL_WINDOW_Y2


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

#define PAN_CENTER         120

#define TILT_BB_GRAB       114
#define TILT_VERT          96   // requires boom to be MAX_UP
#define TILT_BACK          MAX_TILT_BACK
#define TILT_FORWARD       MAX_TILT_FORWARD

#define BOOM_UP            MAX_BOOM_UP
#define BOOM_BB_GRAB       144   // cup 2.32 inches off ground

#define LIFT_OPEN          MAX_LIFT_OPEN
#define LIFT_UP            MAX_LIFT_UP
#define LIFT_BB_READY      115   // "V" 3 inces off ground

#define DOOR_CLOSED        74    // touches closed at 73
#define DOOR_OPEN          MAX_DOOR_OPEN

//
// SERVO LIMITS
//
#define MAX_PAN_LEFT       50
#define MAX_PAN_RIGHT      195

#define MAX_TILT_BACK      195
#define MAX_TILT_FORWARD   93

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



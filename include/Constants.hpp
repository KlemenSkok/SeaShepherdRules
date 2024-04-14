
// Constants.hpp

#define GAME_TITLE "Sea Shepherd Rules"

#define PROJECT_PATH std::filesystem::current_path().string() + "/"

// player constants
#define PLAYER_HEALTH 100
#define PLAYER_SPEED 5
#define VISIBILITY_RADIUS 300

// pirate
#define PIRATE_IDLE_SPEED 1.5
#define PIRATE_ATTACK_SPEED 7
#define PIRATE_DAMAGE 3
#define PIRATE_COUNT 4
#define ATTACK_COOLDOWN 2000

// game constants
#define BASE_WHALER_COUNT 4
#define WHALER_SPEED 3.5

// iceberg
#define BASE_ICEBERG_COUNT 5
#define ICEBERG_SPEED 2

// atol
#define BASE_ATOL_COUNT 5
#define ATOL_GROW_SPEED 1

#define INITIAL_WINDOW_WIDTH  1024
#define INITIAL_WINDOW_HEIGHT 576

#define SECTOR_COUNT_X 20
#define SECTOR_COUNT_Y 10

#define HINT_TIME_TO_DISPLAY 450 // 300 ticks = ~5 seconds

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

#define MAX_FRAME_TIME 5 * FRAME_TARGET_TIME
#define MIN_FRAME_TIME 1 * FRAME_TARGET_TIME

#define NUMBER_OF_LEVELS 3

// level exit codes
#define STATE_GAME_SCREEN 0x00
#define STATE_PAUSE_MENU 0x01
#define STATE_MAIN_MENU 0x02
#define STATE_VICTORY_SCREEN 0x03
#define STATE_DEFEAT_SCREEN 0x04

// main loop exit codes
#define EXIT_CODE_CONTINUE 0x10
#define EXIT_CODE_RETRY 0x11
#define EXIT_CODE_QUIT 0x12
#define EXIT_CODE_RESTART 0x13


// types for replay system
// struct ReplayObject

// control types
#define START_FRAME '6'
#define END_FRAME '9'

// object types
#define TYPE_PLAYER 'P'
#define TYPE_PIRATE 'g'
#define TYPE_WHALER 'w'
#define TYPE_ICEBERG 'i'
#define TYPE_ATOL 'a'
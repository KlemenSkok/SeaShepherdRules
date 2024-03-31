
// Constants.hpp

#define GAME_TITLE "Sea Shepherd Rules"

#define PROJECT_PATH std::filesystem::current_path().string() + "/"

// player constants
#define PLAYER_HEALTH 100
#define PLAYER_SPEED 5

// pirate
#define PIRATE_IDLE_SPEED 1.5
#define PIRATE_ATTACK_SPEED 7
#define PIRATE_DAMAGE 20
#define BASE_PIRATE_COUNT 5

// game constants
#define BASE_WHALER_COUNT 4
#define WHALER_SPEED 3.5

// iceberg
#define BASE_ICEBERG_COUNT 5
#define ICEBERG_SPEED 2

// atol
#define BASE_ATOL_COUNT 5
#define ATOL_GROW_SPEED 1

#define INITIAL_WINDOW_WIDTH  800
#define INITIAL_WINDOW_HEIGHT 600

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

#define MAX_FRAME_TIME 5 * FRAME_TARGET_TIME
#define MIN_FRAME_TIME 1 * FRAME_TARGET_TIME

#define NUMBER_OF_LEVELS 3

// main loop entry codes (positive numbers reserved for levels)
#define STATE_GAME_SCREEN -1
#define STATE_PAUSE_MENU -2
#define STATE_MAIN_MENU -3
#define STATE_VICTORY_SCREEN -4
#define STATE_DEFEAT_SCREEN -5

// main loop exit codes
#define EXIT_CODE_CONTINUE 0
#define EXIT_CODE_RETRY 1
#define EXIT_CODE_QUIT 2

// level exit codes


// Constants.hpp

#define GAME_TITLE "Sea Shepherd Rules"

#define PROJECT_PATH std::filesystem::current_path().string() + "/"

// player constants
#define PLAYER_HEALTH 100
#define PLAYER_SPEED 5

// enemy constants
#define ENEMY_HEALTH 50
#define ENEMY_SPEED 2
#define ENEMY_DAMAGE 20

// game constants
#define BASE_WHALER_COUNT 4

#define INITIAL_WINDOW_WIDTH  800
#define INITIAL_WINDOW_HEIGHT 600

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

#define MAX_FRAME_TIME 5 * FRAME_TARGET_TIME
#define MIN_FRAME_TIME 1 * FRAME_TARGET_TIME

#define NUMBER_OF_LEVELS 3

// main loop entry codes (positive numbers reserved for levels)
#define ENTRY_CODE_MAIN_MENU 0
#define ENTRY_CODE_GAME_SCREEN -1
#define ENTRY_CODE_PAUSE_MENU -2
#define ENTRY_CODE_VICTORY_SCREEN -3
#define ENTRY_CODE_DEFEAT_SCREEN -4

// main loop exit codes
#define EXIT_CODE_CONTINUE 0
#define EXIT_CODE_RETRY 1
#define EXIT_CODE_QUIT 2

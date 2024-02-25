
// Constants.hpp

#define GAME_TITLE "Sea Shepherd Rules"

//#define PROJECT_PATH "C:/Users/Klemen/Documents/Klemen/Sola/3.letnik/RPA/SeaShepherdRules/"
#include <filesystem>
#define PROJECT_PATH std::filesystem::current_path().string() + "\\"

// player constants
#define PLAYER_HEALTH 100
#define PLAYER_SPEED 5

// enemy constants
#define ENEMY_HEALTH 50
#define ENEMY_SPEED 3
#define ENEMY_DAMAGE 20

// game constants
#define LEVEL_1_ENEMY_COUNT 5
#define LEVEL_2_ENEMY_COUNT 7
#define LEVEL_3_ENEMY_COUNT 10

#define INITIAL_WINDOW_WIDTH  800
#define INITIAL_WINDOW_HEIGHT 600

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)
#define MAX_FRAME_TIME 5 * FRAME_TARGET_TIME
#define MIN_FRAME_TIME 1 * FRAME_TARGET_TIME

#define NUMBER_OF_LEVELS 3

#define MAIN_MENU 0
#define GAME_SCREEN 1
#define PAUSE_MENU 2
#define VICTORY_SCREEN 3
#define DEFEAT_SCREEN 4

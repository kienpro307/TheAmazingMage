#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <windows.h>
#include <string>
#include <SDL_image.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <SDL_mixer.h> 
#include "TextObject.h"

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

static Mix_Music* g_music = NULL;
static Mix_Chunk* g_sound_bullet = NULL;
static Mix_Chunk* g_beep_sound = NULL;
static SDL_Surface* g_img_menu = NULL;

// Screen
const int FRAME_PER_SECOND = 30; //fps
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167; 
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0Xff ; 


#define BLANK_TILE 0
#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define STATE_MONEY 4
#define GATE 5

struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;
 };

struct Map
{
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	std::string file_name_;
};
	
namespace SDLCommonFunc
{
	SDL_Surface* LoadImage(std::string file_path);
	SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
	int ShowMenu(SDL_Surface* des, TTF_Font* font);
	bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
}

#endif

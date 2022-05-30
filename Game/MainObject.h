#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include <vector>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define GRAVITY_SPEED 100
#define MAX_FALL_SPPED 400
#define PLAYER_SPEED 16
#define X_WASTE_FRAME 1 
#define Y_WASTE_FRAME 1
#define PLAYER_JUMP_VAL 20
#define COME_BACK_TIME 20

class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();
	enum WalkType
	{
		WALK_NONE = 0,
		WALK_RIGHT = 0,
		WALK_LEFT = 1
	};
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* bullet_sound, Mix_Chunk* beep_sound);
	void set_clips(int num_frame_);

	void DoPlayer(Map& map_data);
	void CheckToMap(Map& map_data);
	void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; };
	void CenterEntityOnMap(Map& map_data);
	void UpdateImagePlayer(SDL_Renderer* des);
	SDL_Rect GetRectFrame();
	int GetComeBackTime() const { return come_back_time_; }

	void set_bullet_list(std::vector<BulletObject*> bullet_list)
	{
		p_bullet_list_ = bullet_list;
	}
	std::vector<BulletObject*> get_bullet_list() const { return p_bullet_list_; }
	void HandleBullet(SDL_Renderer* des);
	void RemoveBullet(const int& idx);
	
	void IncreaseMoney();
	int GetMoneyCount()  const { return money_count; }

	void set_come_back_time(const int& cb_time) { come_back_time_ = cb_time; }
	void Player_die();
	bool die_;
	bool win = false;
	int num_die;
	bool renderMenu =true;
	bool exitGame = false;
private:

	int money_count;
	std::vector<BulletObject*> p_bullet_list_;
	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip[8];
	Input input_type_;
	int frame_;
	int status_;
	bool on_ground_;

	int map_x_;
	int map_y_;

	int come_back_time_;

	SDL_RendererFlip flipType;
};

#endif // !MAIN_OBJECT_H

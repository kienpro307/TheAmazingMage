
#include "MainObject.h";

MainObject::MainObject()
{
	num_die = 0;
	frame_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	status_ = WALK_NONE;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.jump_ = 0;
	input_type_.down_ = 0;
	input_type_.up_ = 0;
	on_ground_ = false;

	map_x_ = 0;
	map_y_ = 0;

	come_back_time_ = 0;
	money_count = 0;

	flipType = SDL_FLIP_NONE;
	renderMenu = true;
	exitGame = false;
}

MainObject::~MainObject()
{

}

//Lấy ảnh animation từ ổ cứng --------------------------------------------------------------------------------
bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret == true)
	{
		width_frame_ = rect_.w / 8;
		height_frame_ = rect_.h;
	}

	return ret;
}

SDL_Rect MainObject::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame_;
	rect.h = height_frame_;
	return rect;
}

//Animation cho nhân vật --------------------------------------------------------------------------------
void MainObject::set_clips(int num_frame_)
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		for (int i = 0; i < num_frame_; i++)
		{
			frame_clip[i].x = i * width_frame_ ;
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame_;
			frame_clip[i].h = height_frame_;
		}
	}
}

//Vẽ animation cho nhân vật --------------------------------------------------------------------------------
void MainObject::Show(SDL_Renderer* des)
{
	UpdateImagePlayer(des);
	if (status_ == WALK_LEFT)
		flipType = SDL_FLIP_HORIZONTAL;
	else
		flipType = SDL_FLIP_NONE;
	if (input_type_.left_ == 1 || input_type_.right_ == 1)
		frame_++;
	else frame_ = 0;
	if (frame_ >= 8) frame_ = 0;

	if (come_back_time_ == 0)
	{
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;

		SDL_Rect* current_clip = &frame_clip[frame_];
		SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };

		SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, NULL, NULL, flipType);
	}
	
}
//Xử lí đầu vào di chuyển cho nhân vật ---------------------------------------------------------------------
void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* bullet_sound, Mix_Chunk* beep_sound)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
			{
				status_ = WALK_RIGHT;
				input_type_.right_ = 1;
				input_type_.left_ = 0;
				UpdateImagePlayer(screen);
			}
			break;
		case SDLK_LEFT:
			{
			status_ = WALK_LEFT;
			input_type_.left_ = 1;
			input_type_.right_ = 0;
			UpdateImagePlayer(screen);
			}
			break;
		case SDLK_UP:
			{
			input_type_.jump_ = 1;
			}
			break;
		case SDLK_KP_ENTER:
		{
			Mix_PlayChannel(-1, beep_sound, 0);
			if (renderMenu) {
				renderMenu = false;
			}
		}
		break;
		case SDLK_KP_PERIOD:
		{
			Mix_PlayChannel(-1, beep_sound, 0);
			if(renderMenu)exitGame = true;
		}
		break;
		default:
			break;
		}
		

	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			input_type_.right_ = 0;
		}
		break;
		case SDLK_LEFT:
		{
			input_type_.left_ = 0;
		}
		break;
		}
	}

	if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		if (events.button.button == SDL_BUTTON_RIGHT)
		{
			;//input_type_.jump_ = 1;
		}
		else if (events.button.button == SDL_BUTTON_LEFT)
		{
			BulletObject* p_bullet = new BulletObject();
			p_bullet->set_bullet_type(BulletObject::SPHERE_BULLET);
			p_bullet->LoadImgBullet(screen);
			if (status_ == WALK_LEFT)
			{
				p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
				p_bullet->SetRect(this->rect_.x - 20, rect_.y + height_frame_ * 0.25);
			}
			else if (status_ == WALK_RIGHT)
			{
				p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
				p_bullet->SetRect(this->rect_.x + width_frame_ - 20, rect_.y + height_frame_ * 0.25);
			}

			
			p_bullet->set_x_val(20);
			p_bullet->set_y_val(20);
			p_bullet->set_is_move(true);

			p_bullet_list_.push_back(p_bullet);
			Mix_PlayChannel(-1, bullet_sound, 0);
		}
	}
}

void MainObject::HandleBullet(SDL_Renderer* des)
{
	for (int i = 0; i < p_bullet_list_.size(); i++)
	{
		BulletObject* p_bullet = p_bullet_list_.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move() == true)
			{
				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_bullet->Render(des);
			}
			else
			{
				p_bullet_list_.erase(p_bullet_list_.begin() + i);
				if (p_bullet != NULL)
				{
					delete p_bullet;
					p_bullet = NULL;
				}
			}
		}
	}
}

void MainObject::RemoveBullet(const int& idx)
{
	int size = p_bullet_list_.size();
	if (size > 0 && idx < size)
	{
		BulletObject* p_bullet = p_bullet_list_.at(idx);
		p_bullet_list_.erase(p_bullet_list_.begin() + idx);

		if (p_bullet)
		{
			delete p_bullet;
			p_bullet = NULL;
		}
	}
}

//Nhân vật di chuyển --------------------------------------------------------------------------------
void MainObject::DoPlayer(Map& map_data)
{
	if (come_back_time_ == 0)
	{
		x_val_ = 0;
		y_val_ += 0.8;

		if (y_val_ >= MAX_FALL_SPPED)
			y_val_ = MAX_FALL_SPPED;

		if (input_type_.left_ == 1)
			x_val_ -= PLAYER_SPEED;
		else if (input_type_.right_ == 1)
			x_val_ += PLAYER_SPEED;


		if (input_type_.jump_ == 1)
		{
			if (on_ground_ == true)
			{
				y_val_ = -PLAYER_JUMP_VAL;
			}

			on_ground_ = false;
			input_type_.jump_ = 0;
		}


		CheckToMap(map_data);
		CenterEntityOnMap(map_data);
	}
	
	if (come_back_time_ > 0)
	{
		come_back_time_--;
		if (come_back_time_ == 0)
		{
			on_ground_ = false;
			if (x_pos_ > 256)
			{
				x_pos_ -= 256; //4 tile map
			}
			else
			{
				x_pos_ = 0;
			}
			y_pos_ = 0;
			x_val_ = 0;
			y_val_ = 0;
		}
	}

}

// Để màn hình chạy theo nhân vật ------------------------------------------------------------------------
void MainObject::CenterEntityOnMap(Map& map_data)
{
	map_data.start_x_ = x_pos_ - (SCREEN_WIDTH / 4);
	if (map_data.start_x_ < 0)
		map_data.start_x_ = 0;
	if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
		map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;

	map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT / 2);
	if (map_data.start_y_ < 0)
		map_data.start_y_ = 0;
	else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
		map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
}

//Kiểm tra vị trí của nhân vật so với map rồi chỉnh sao cho hợp lí ------------------------------------
void MainObject::CheckToMap(Map& map_data)
{
	die_ = false;
// Giới hạn kiểm tra theo chiều x1, x2
	int x1 = 0;
	int x2 = 0;

//Giới hạn kiểm tra theo chiều y1, y2 
	int y1 = 0;
	int y2 = 0;

//Kiểm tra theo chiều ngang 

	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;
	
	x1 = (x_pos_ + x_val_ - X_WASTE_FRAME) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_ - X_WASTE_FRAME) / TILE_SIZE; 
// -X_WASTE_FRAME để bỏ đi phần thừa trong frame của nhân vật
	
	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_min - Y_WASTE_FRAME) / TILE_SIZE;

//Kiểm tra  
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
	{
		if (x_val_ > 0) //Nhân vật đang di chuyển sang phải
		{

			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];
			
			if (val1 == STATE_MONEY || val2 == STATE_MONEY || val1 == GATE || val2 == GATE)
			{
				if (val1 == GATE || val2 == GATE)
				{
					win = true;
				}
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;
				IncreaseMoney();
			}
			else
			{
				if (val1 != BLANK_TILE || val2 != BLANK_TILE)
				{
					x_pos_ = x2 * TILE_SIZE;
					x_pos_ -= width_frame_ + X_WASTE_FRAME;
					x_val_ = 0;
				}
			}
			
		}
		else if (x_val_ < 0) //Nhân vật đang di chuyển sang trái
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];

			if (val1 == STATE_MONEY || val2 == STATE_MONEY || val1 == GATE || val2 == GATE)
			{
				if (val1 == GATE || val2 == GATE)
				{
					win = true;
				}
				map_data.tile[y1][x1] = 0;
				map_data.tile[y2][x1] = 0;
				IncreaseMoney();
			}
			else
			{
				if (val1 != BLANK_TILE || val2 != BLANK_TILE)
				{
					x_pos_ = (x1 + X_WASTE_FRAME) * TILE_SIZE;
					x_val_ = 0;
				}
			}
		}
	}
//Kiểm tra theo chiều dọc
	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
	x1 = (x_pos_) / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - Y_WASTE_FRAME) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val_ > 0)
		{

			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];

			if (val1 == STATE_MONEY || val2 == STATE_MONEY || val1 == GATE || val2 == GATE)
			{
				if (val1 == GATE || val2 == GATE)
				{
					win = true;
				}
				map_data.tile[y2][x1] = 0;
				map_data.tile[y2][x2] = 0;
				IncreaseMoney();
			}
			else
			{
				if (val1 != BLANK_TILE || val2 != BLANK_TILE)
				{
					y_pos_ = y2 * TILE_SIZE;
					y_pos_ -= (height_frame_ + Y_WASTE_FRAME);
					y_val_ = 0;
					if (status_ == WALK_NONE)
					{
						status_ = WALK_RIGHT;
					}

					on_ground_ = true;
				}
			}
			
		}
		else if (y_val_ < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];

			if (val1 == STATE_MONEY || val2 == STATE_MONEY || val1 == GATE || val2 == GATE)
			{
				if (val1 == GATE || val2 == GATE)
				{
					win = true;
				}
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
				IncreaseMoney();
			}
			if (val1 != BLANK_TILE || val2 != BLANK_TILE)
			{
				y_pos_ = (y1 + Y_WASTE_FRAME) * TILE_SIZE;
				y_val_ = 0;
		
			}
		}
	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0) 
		x_pos_ = 0;
	if (x_pos_ + width_frame_ > map_data.max_x_) 
		x_pos_ = map_data.max_x_ - width_frame_ - X_WASTE_FRAME;
	if (y_pos_ > map_data.max_y_)
	{	
		die_ = true;
		come_back_time_ = COME_BACK_TIME;
	}
}

void MainObject::IncreaseMoney()
{
	money_count++; 
}

void MainObject::UpdateImagePlayer(SDL_Renderer* des)
{
	if (on_ground_ == true)
	{
			LoadImg("img/player_right.png", des);
	}
	else
	{
		if (y_val_ < 0)
			LoadImg("img//jum_up_right.png", des);
		else LoadImg("img//jum_down_right.png", des);
	}
}

void MainObject::Player_die()
{
	
	num_die++;
}

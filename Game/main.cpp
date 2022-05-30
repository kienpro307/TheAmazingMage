
#include <iostream>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "Map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "TextObject.h"
#include "PlayerPower.h"
#include "Geometric.h"

BaseObject g_background;
BaseObject menu_background;
TTF_Font* font_time = NULL;

bool InitData()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
		return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	g_window = SDL_CreateWindow("THE AMAZING MAGE",
								SDL_WINDOWPOS_UNDEFINED, 
								SDL_WINDOWPOS_UNDEFINED, 
								SCREEN_WIDTH, 
								SCREEN_HEIGHT, 
								SDL_WINDOW_SHOWN);
	if (g_window == NULL)
	{
		success = false;
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL) success = false;
		else
		{
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
				success = false;
		}

		if (TTF_Init() == -1)
		{
			success = false;
		}

		font_time = TTF_OpenFont("font//dlxfont_.ttf", 15);
		if (font_time == NULL)
		{
			success = false;
		}
	}
	 
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		success = false;
		
	//Đoc file âm thanh
	g_sound_bullet = Mix_LoadWAV("game resource//Fire1.wav");
	g_beep_sound = Mix_LoadWAV("game resource//beep_.wav");
	if (g_sound_bullet == NULL)
		success = false;
	//Đọc file music
	g_music = Mix_LoadMUS("game resource//01 - DavidKBD - Belmont Chronicles Pack - Belmont Chronicles.mp3");
	if (g_music == NULL)
		success = false;

	return success;
}

//Sửa background ở đây ------------------------------------------
bool LoadBackground()
{
	bool ret = g_background.LoadImg("img/background.png", g_screen);
	
	bool vcl = menu_background.LoadImg("img/Menu.png", g_screen);
	if (ret == false || vcl == false) return false; else return true;
}

void close()
{
	g_background.Free();
	menu_background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
		
	SDL_DestroyWindow(g_window);
	g_window = NULL;

	Mix_FreeChunk(g_sound_bullet);
	g_sound_bullet = NULL;

	Mix_FreeMusic(g_music);
	g_music = NULL;

	IMG_Quit();
	SDL_Quit();
}

std::vector<ThreatsObject*> MakeThreadList()
{
	std::vector<ThreatsObject*> list_threats;

	ThreatsObject* dynamic_threats = new ThreatsObject[20];
	for (int i = 0; i < 20; i++)
	{
		ThreatsObject* p_threat = (dynamic_threats + i);
		if (p_threat != NULL)
		{
			p_threat->LoadImg("img//threat_left.png", g_screen);
			p_threat->set_clips();
			p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
			p_threat->set_x_pos(500 + i * 1500);
			p_threat->set_y_pos(200);
			
			int pos1 = p_threat->get_x_pos() - 60;
			int pos2 = p_threat->get_x_pos() + 60;
			p_threat->SetAnimationPos(pos1, pos2);
			p_threat->set_input_left(1);
			list_threats.push_back(p_threat);
		}
	}

	ThreatsObject* threats_objs = new ThreatsObject[20];

	for (int i = 0; i < 20; i++)
	{
		ThreatsObject* p_threat = (threats_objs + i);
		if (p_threat != NULL)
		{
			p_threat->LoadImg("img//threat_level.png", g_screen);
			p_threat->set_clips();
			p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
			p_threat->set_x_pos(700 + i * 1200);
			p_threat->set_y_pos(250);
			p_threat->set_input_left(0);

			BulletObject* p_bullet = new BulletObject();
			p_threat->InitBullet(p_bullet, g_screen);
			list_threats.push_back(p_threat);
		}
	}
	return list_threats;
}

int main(int argc, char* argv[]) {
	ImpTimer fps_timer;

	if (InitData() == false) return -1;
	if (LoadBackground() == false) return -1;

//In background---------------------------------------------------

	
	GameMap game_map;
	game_map.LoadMap("map/map01.dat");
	game_map.LoadTiles(g_screen);

	MainObject p_player;
	p_player.LoadImg("img//player_right.png", g_screen);
	p_player.set_clips(8);

	PlayerPower player_power;
	player_power.Init(g_screen);

	PlayerMoney player_money;
	player_money.Init(g_screen);
	player_money.SetPos(SCREEN_WIDTH * 0.5 - 285, 8);


	std::vector<ThreatsObject*> threats_list = MakeThreadList();

	//Time text
	TextObject time_game;
	time_game.SetColor(TextObject::WHITE_TEXT);

	TextObject mark_game;
	mark_game.SetColor(TextObject::WHITE_TEXT);
	int mark_value = 0;

	TextObject money_game;
	money_game.SetColor(TextObject::WHITE_TEXT);

	Mix_PlayMusic( g_music, -1);
	
//Game loop------------------------------------------------------
	bool running = true;
	while (running)
	{
	//Bắt đầu thời gian
		fps_timer.start();

	//Xử lí hành động nhân vật ------------------------------------------------------
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				running = false;
			}

			p_player.HandleInputAction(g_event, g_screen, g_sound_bullet, g_beep_sound);
		}

		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);

		Map map_data = game_map.getMap(); // lấy map data = game_map 

		p_player.HandleBullet(g_screen);
		p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
		p_player.DoPlayer(map_data);
		p_player.Show(g_screen);

		game_map.SetMap(map_data);
		game_map.DrawMap(g_screen);

		//Draw Geometric------------------------
		GeometricFormat rectangle_size(0, 0, SCREEN_WIDTH, 40);
		ColorData color_data(36, 36, 36);
		Geometric::RenderRectangle(rectangle_size, color_data, g_screen);

		//Viền của thanh bar trên cùng màn hình, đổi màu ở color_data2 ----------- 
		GeometricFormat outLineSize(1, 1, SCREEN_WIDTH - 1, 38);
		ColorData color_data2(255, 255, 255);
		Geometric::RenderOutline(outLineSize, color_data2, g_screen);

		player_power.Show(g_screen);
		player_money.Show(g_screen);

		
		//xu ly quai vat
		for (int i = 0; i < threats_list.size(); i++)
		{
			ThreatsObject* p_threat = threats_list.at(i);
			if (p_threat != NULL)
			{
				p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
				p_threat->ImpMoveType(g_screen);
				p_threat->DoPlayer(map_data);
				p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->Show(g_screen);


				SDL_Rect rect_player = p_player.GetRectFrame();
				bool bCol1 = false;
				std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
				for (int jj = 0; jj < tBullet_list.size(); ++jj)
				{
					BulletObject* pt_bullet = tBullet_list.at(jj);
					if (pt_bullet)
					{
						bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player);
						if (bCol1)
						{
							p_threat->RemoveBullet(jj);
							break;
						}
					}
				}

				SDL_Rect rect_threat = p_threat->GetRectFrame();
				bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);

				//exit trong menu
				if (p_player.exitGame) {
				p_threat->Free();
				close();
				SDL_Quit();
				return 0;
			}
				//Nhân vật chết

				if (bCol1 || bCol2 || p_player.die_)
				{
					if (p_player.die_) p_player.die_ = false;
					p_player.Player_die();
					if (p_player.num_die <= 3)
					{
						p_player.SetRect(0, 0);
						p_player.set_come_back_time(10);
						SDL_Delay(1000);
						player_power.Decrease();
						player_power.Render(g_screen);
						continue;
					} 
					else
					{
						if (MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
						{
							p_threat->Free();
							close();
							SDL_Quit();
							return 0;
						}
					}
				}
				if (p_player.win)
				{
					p_threat->Free();
					close();
					SDL_Quit();
					return 0;
				}
			}
		}

		std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
		for (int r = 0; r < bullet_arr.size(); r++)
		{
			BulletObject* p_bullet = bullet_arr.at(r);
			if (p_bullet != NULL)
			{
				for (int t = 0; t < threats_list.size(); ++t)
				{
					ThreatsObject* obj_threat = threats_list.at(t);
					if (obj_threat != NULL)
					{
						SDL_Rect tRect;
						tRect.x = obj_threat->GetRect().x;
						tRect.y = obj_threat->GetRect().y;
						tRect.w = obj_threat->get_width_frame();
						tRect.h = obj_threat->get_height_frame();

						SDL_Rect bRect = p_bullet->GetRect();
						bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);

						if (bCol)
						{
							mark_value++;
							p_player.RemoveBullet(r);
							obj_threat->Free();
							threats_list.erase(threats_list.begin() + t);
						}
					}
				}
			}
		}
		
		// Show game time
		std::string str_time = "Time: ";
		Uint32 time_val = SDL_GetTicks() / 1000;
		Uint32 val_time = 300 - time_val;
		if (val_time <= 0)
		{
			// 	if (MessageBox(NULL, L("GAME OVER"), L"Info", MB_OK | MB_ICONSTOP) == IDOK)
			{
				running = false;
				break;
			}
		}
		else
		{
			std::string str_val = std::to_string(val_time);
			str_time += str_val;

			time_game.SetText(str_time);
			time_game.LoadFromRenderText(font_time, g_screen);
			time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
		}

		std::string val_str_mark = std::to_string(mark_value);
		std::string strMark("Mark: ");
		strMark += val_str_mark;

		mark_game.SetText(strMark);
		mark_game.LoadFromRenderText(font_time, g_screen);
		mark_game.RenderText(g_screen, SCREEN_WIDTH * 0.5 - 50, 15);

		int money_count = p_player.GetMoneyCount();
		std::string money_str = std::to_string(money_count);

		money_game.SetText(money_str);
		money_game.LoadFromRenderText(font_time, g_screen);
		money_game.RenderText(g_screen, SCREEN_WIDTH * 0.5 - 250, 15);
		//render menu
		if(p_player.renderMenu)menu_background.Render(g_screen, NULL);
		
		SDL_RenderPresent(g_screen);

		int real_imp_time = fps_timer.get_ticks();
		int time_one_frame = 1000 / FRAME_PER_SECOND; //ms
		if (real_imp_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_imp_time;
			if(delay_time >= 0)
				SDL_Delay(delay_time);
		}
		
	}

	for (int i = 0; i < threats_list.size(); i++)
	{
		ThreatsObject* p_threat = threats_list.at(i);
		if (p_threat)
		{
			p_threat->Free();
			p_threat = NULL;
		}
		
 	}

	close();
}
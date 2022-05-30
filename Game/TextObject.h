#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H

#include "CommonFunc.h"
#include "BaseObject.h"

class TextObject 
{
public:
	TextObject();
	~TextObject();

	enum TextColor
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2,
	};

	bool LoadFromFile(std::string path);
	bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
	void Free();

	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetColor(int type);

	void RenderText(SDL_Renderer* screen,
					int xp, int yp,
					SDL_Rect* cilp = NULL,
					double angle = 0.0,
					SDL_Point* center = NULL,
					SDL_RendererFlip flip = SDL_FLIP_NONE);
	int GetWidth() const { return width_; } 
	int GetHeight() const { return height_; }

	void SetText(const std::string& text) { str_val_ = text; }
	void CreateGameText(TTF_Font* font, SDL_Surface* des);

	std::string GetText() const { return str_val_; }
	SDL_Rect GetRect() const { return rect_; }
private:
	std::string str_val_;
	SDL_Color text_color_;
	SDL_Texture* texture_;
	int width_;
	int height_;
	SDL_Rect rect_;
};

#endif // !

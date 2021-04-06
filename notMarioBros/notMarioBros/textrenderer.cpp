#include "textrenderer.h"
#include <iostream>

namespace Text {

	void Initialize(SDL_Renderer* renderer) {
		if (!initialized)
		{
			fonts[FONT::ID::REGULAR] = new Texture2D(renderer);
			fonts[FONT::ID::REGULAR]->LoadFromFile("Fonts/font_regular.png");

			fonts[FONT::ID::MARIO] = new Texture2D(renderer);
			fonts[FONT::ID::MARIO]->LoadFromFile("Fonts/font_mario.png");

			fonts[FONT::ID::LUIGI] = new Texture2D(renderer);
			fonts[FONT::ID::LUIGI]->LoadFromFile("Fonts/font_luigi.png");

			fonts[FONT::ID::GOLD] = new Texture2D(renderer);
			fonts[FONT::ID::GOLD]->LoadFromFile("Fonts/font_gold.png");

			fonts[FONT::ID::SILVER] = new Texture2D(renderer);
			fonts[FONT::ID::SILVER]->LoadFromFile("Fonts/font_silver.png");

			// This should not be used in a call, but is here in the event of it being passed by accident as a parameter.
			fonts[FONT::ID::count] = new Texture2D(renderer);
			fonts[FONT::ID::count]->LoadFromFile("Fonts/font_regular.png");

			initialized = true;
		}
	}

	void Shutdown() {
		if (initialized)
		{
			delete fonts[FONT::ID::REGULAR];
			delete fonts[FONT::ID::MARIO];
			delete fonts[FONT::ID::LUIGI];
			delete fonts[FONT::ID::GOLD];
			delete fonts[FONT::ID::SILVER];
			delete fonts[FONT::ID::count];

			initialized = false;
		}
	}

	void Draw(std::string text, IntVector2D position, FONT::ID font, FONT::ALLIGNMENT allignment) {
		if (initialized) {
			int letter_count = strlen(text.c_str());
			int text_width = letter_count * CHARACTER_WIDTH;

			int text_offset = 0;
			switch (allignment)
			{
			case FONT::CENTER:
				text_offset = -(text_width / 2);
				break;
			case FONT::RIGHT:
				text_offset = -(text_width);
				break;
			default:
				break;
			}

			SDL_Rect char_rect{ 0,0,CHARACTER_WIDTH,CHARACTER_HEIGHT };
			SDL_Rect dest_rect{ position.x + text_offset,position.y,CHARACTER_WIDTH,CHARACTER_HEIGHT };

			//std::cout << "TEXT CHAR COUNT: " << letter_count << std::endl;

			for (int i = 0; i < letter_count; i++)
			{
				int char_ascii = (int)text[i];
				char_rect.x = (char_ascii % CHARACTER_ROW_COUNT)*CHARACTER_WIDTH;
				char_rect.y = (char_ascii / CHARACTER_ROW_COUNT)*CHARACTER_HEIGHT;

				fonts[font]->Render(char_rect, dest_rect, SDL_FLIP_NONE, 0.0);

				dest_rect.x += CHARACTER_WIDTH;
			}

		}
	}
}
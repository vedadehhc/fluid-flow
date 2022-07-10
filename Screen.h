#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>
// #include <SDL_image.h>
// #include <SDL_ttf.h>
// #include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <functional>

// TODO:
// - add wrapper classes for text, image, etc.
// - add vectors of these wrappers to screen
// - add interfaces to these wrappers in screen

namespace dev
{
	class Screen
	{
	private:
		// screen dimensions
		int width, height;
		std::string title;

		// Function which returns false if a quit event was detected
		std::function<bool(SDL_Event &)> eventProcessor;
		SDL_Event event;

		SDL_Window *m_window;
		SDL_Renderer *m_renderer;
		SDL_Texture *m_texture;
		Uint32 *m_buffer;

	public:
		Screen(int width, int height) : width(width), height(height), title("App") {}

		Screen(int width, int height, std::string title) : width(width), height(height), title(title) {}

		bool init();

		void clear();

		int pixelIndex(int x, int y);
		bool setPixel(int x, int y, Uint32 color);
		bool addToPixel(int x, int y, Uint32 color);

		// Returns true if at least part of this box is on screen
		bool boxInBounds(int minX, int minY, int maxX, int maxY);

		bool drawSquare(int minX, int minY, int maxX, int maxY, Uint32 color);
		bool drawFillSquare(int minX, int minY, int maxX, int maxY, Uint32 color);
		bool drawFillCircle(float cx, float cy, float radius, Uint32 color);

		void update();

		// void freeSfx()
		// {
		// 	// Mix_FreeChunk(gCollect);
		// 	// Mix_FreeChunk(gDeath);
		// 	// gCollect = NULL;
		// 	// gDeath = NULL;
		// }

		// void freeText()
		// {
		// 	// if ( gTextTexture != NULL ) {
		// 	// SDL_DestroyTexture(gTextTexture);
		// 	// gTextTexture = NULL;
		// 	// textWidth = 0;
		// 	// textHeight = 0;
		// 	// }
		// }

		// void freeFont()
		// {
		// 	// TTF_CloseFont(gFont);
		// 	// gFont = NULL;
		// }
		
		void freeTexture();
		void freeRenderer();
		void freeWindow();

		// Frees media and closes SDL
		void close();

		bool processEvents();

		// getters
		int getWidth();
		int getHeight();

		void setEventProcessor(std::function<bool(SDL_Event &)> eventProcessor);
	};
}

#endif
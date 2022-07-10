#include <SDL.h>
#include <functional>

#include "Screen.h"
#include "dev.h"

namespace dev
{
    bool Screen::init()
    {

        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        {
            printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
            return false;
        }

        // Create window
        m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if (m_window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            SDL_Quit();
            return false;
        }

        // Create renderer
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (m_renderer == NULL)
        {
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());

            freeWindow();
            SDL_Quit();

            return false;
        }

        // Create texture
        m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, width, height);
        if (m_texture == NULL)
        {
            printf("Texture could not be created! SDL Error: %s\n", SDL_GetError());

            freeRenderer();
            freeWindow();
            SDL_Quit();

            return false;
        }

        // Initialize renderer color
        // SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0xFF);
        // SDL_RenderClear(m_renderer);

        // // draw loading symbols
        // SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        // SDL_Rect one = {width / 2 - 20, height / 2, 10, 10};
        // SDL_Rect two = {width / 2, height / 2, 10, 10};
        // SDL_Rect three = {width / 2 + 20, height / 2, 10, 10};
        // SDL_RenderFillRect(m_renderer, &one);
        // SDL_RenderFillRect(m_renderer, &two);
        // SDL_RenderFillRect(m_renderer, &three);

        // // Update the renderer
        // SDL_RenderPresent(m_renderer);

        // Initialize image loading
        // int imgFlags = IMG_INIT_PNG;
        // if (!(IMG_Init(imgFlags) & imgFlags))
        // {
        // 	printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        // 	success = false;
        // }

        // // initialize font
        // if (TTF_Init() == -1)
        // {
        // 	printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        // 	success = false;
        // }

        // // initialize sound
        // if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        // {
        // 	printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        // 	success = false;
        // }

        m_buffer = new Uint32[width * height];
        clear();

        return true;
    }

    void Screen::clear()
    {
        for (int i = 0; i < width * height; i++)
        {
            m_buffer[i] = 0x000000FF;
        }
    }
    
    // Returns true if at least part of this box is on screen
    bool Screen::boxInBounds(int minX, int minY, int maxX, int maxY)
    {
        return minX < width && maxX >= 0 && minY < height && maxY >= 0;
    }

    int Screen::pixelIndex(int x, int y)
    {
        return y * width + x;
    }

    bool Screen::setPixel(int x, int y, Uint32 color)
    {
        if (x < 0 || x >= width || y < 0 || y >= height)
            return false;

        m_buffer[pixelIndex(x, y)] = color;

        return true;
    }

    bool Screen::addToPixel(int x, int y, Uint32 color)
    {
        if (x < 0 || x >= width || y < 0 || y >= height)
            return false;
        
        m_buffer[pixelIndex(x, y)] = colorOver(color, m_buffer[pixelIndex(x, y)]);
        return true;
    }

    bool Screen::drawSquare(int minX, int minY, int maxX, int maxY, Uint32 color)
    {
        if (minX > maxX || minY > maxY)
            return false;

        if (!boxInBounds(minX, minY, maxX, maxY))
            return false;

        minX = std::max(minX, 0);
        maxX = std::min(maxX, width - 1);
        minY = std::max(minY, 0);
        maxY = std::min(maxY, height - 1);

        for (int i = minX; i <= maxX; i++)
        {
            addToPixel(i, minY, color);
            addToPixel(i, maxY, color);
        }

        for (int i = minY + 1; i <= maxY - 1; i++)
        {
            addToPixel(minX, i, color);
            addToPixel(maxX, i, color);
        }

        return true;
    }

    bool Screen::drawFillSquare(int minX, int minY, int maxX, int maxY, Uint32 color)
    {
        if (minX > maxX || minY > maxY)
            return false;

        if (!boxInBounds(minX, minY, maxX, maxY))
            return false;

        minX = std::max(minX, 0);
        maxX = std::min(maxX, width - 1);
        minY = std::max(minY, 0);
        maxY = std::min(maxY, height - 1);

        for (int i = minX; i <= maxX; i++)
        {
            for (int j = minY; j <= maxY; j++)
            {
                addToPixel(i, j, color);
            }
        }

        return true;
    }

    bool Screen::drawFillCircle(float cx, float cy, float radius, Uint32 color)
    {
        int startX = floor(cx - radius);
        int endX = ceil(cx + radius);

        int startY = floor(cy - radius);
        int endY = ceil(cy + radius);

        if (!boxInBounds(startX, startY, endX, endY))
            return false;
        
        bool result = false;
        for (int i = startX; i <= endX; i++)
        {
            for (int j = startY; j <= endY; j++)
            {
                if (pointInCircle(i + 0.5, j + 0.5, cx, cy, radius))
                    result |= addToPixel(i, j, color);
            }
        }
        return result;
    }

    void Screen::update()
    {
        SDL_UpdateTexture(m_texture, NULL, m_buffer, width * sizeof(Uint32));
        SDL_RenderClear(m_renderer);
        SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
        SDL_RenderPresent(m_renderer);
    }

    void Screen::freeTexture()
    {
        SDL_DestroyTexture(m_texture);
        m_texture = NULL;
    }

    void Screen::freeRenderer()
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = NULL;
    }

    void Screen::freeWindow()
    {
        SDL_DestroyWindow(m_window);
        m_window = NULL;
    }

    // Frees media and closes SDL
    void Screen::close()
    {
        delete[] m_buffer;

        // freeSfx();
        // freeText();
        // freeFont();
        freeTexture();
        freeRenderer();
        freeWindow();

        // Quit SDL subsystems
        // Mix_Quit();
        // IMG_Quit();
        SDL_Quit();
    }

    bool Screen::processEvents()
    {
        while (SDL_PollEvent(&event))
        {
            if (!eventProcessor(event))
                return false;
        }
        return true;
    }

    // getters
    int Screen::getWidth()
    {
        return width;
    }

    int Screen::getHeight()
    {
        return height;
    }

    void Screen::setEventProcessor(std::function<bool(SDL_Event &)> eventProcessor)
    {
        this->eventProcessor = eventProcessor;
    }
}
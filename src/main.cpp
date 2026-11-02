#include <SDL2/SDL.h>
#include <orbis/Sysmodule.h>
#include <cstdio>

const int W = 1920;
const int H = 1080;

int selected = 0;

void drawTile(SDL_Renderer* r, int x, int y, bool active)
{
    SDL_Rect tile = {x, y, 220, 220};

    // خلفية المربع
    SDL_SetRenderDrawColor(r, 3, 15, 45, 255);
    SDL_RenderFillRect(r, &tile);

    // إطار نيوني
    if (active)
        SDL_SetRenderDrawColor(r, 0, 230, 255, 255);
    else
        SDL_SetRenderDrawColor(r, 0, 85, 220, 255);

    for (int i = 0; i < (active ? 7 : 3); i++)
    {
        SDL_Rect border = {
            x - i, y - i,
            220 + i * 2, 220 + i * 2
        };
        SDL_RenderDrawRect(r, &border);
    }
}

int main()
{
    setvbuf(stdout, nullptr, _IONBF, 0);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) != 0)
        return 1;

    SDL_Window* window = SDL_CreateWindow(
        "SAMIX GAMES",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        W, H, 0
    );

    if (!window) return 1;

    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    if (!renderer) return 1;

    SDL_Joystick* pad = nullptr;

    if (SDL_NumJoysticks() > 0)
        pad = SDL_JoystickOpen(0);

    bool running = true;

    while (running)
    {
        SDL_Event e;

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                running = false;

            if (e.type == SDL_JOYBUTTONDOWN)
            {
                switch (e.jbutton.button)
                {
                    case 0: // X
                        printf("Selected: %d\n", selected);
                        break;
                    case 1: // O
                        running = false;
                        break;
                    case 11: // UP
                        selected = (selected + 12 - 6) % 12;
                        break;
                    case 12: // DOWN
                        selected = (selected + 6) % 12;
                        break;
                    case 13: // LEFT
                        selected = (selected + 11) % 12;
                        break;
                    case 14: // RIGHT
                        selected = (selected + 1) % 12;
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 3, 18, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < 12; i++)
        {
            int x = 160 + (i % 6) * 270;
            int y = 220 + (i / 6) * 300;

            drawTile(renderer, x, y, i == selected);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    if (pad) SDL_JoystickClose(pad);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
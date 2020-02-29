/*
##################################################
# Scoreboard v1.1b by Bad64                      #
#                                                #
# It's super hacky and ugly, but it works !      #
# Only works on Windows though.                  #
#                                                #
##################################################
*/

#include <Windows.h>
#include <iostream>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

/* Data to display */
stringstream sstream;
int wins, losses, draws = 0;

/* SDL stuff */
SDL_Texture* scoreboard = NULL;
bool quit = false;

SDL_Texture* Regenerate(SDL_Renderer* renderer, string text)
{
    TTF_Font* font = TTF_OpenFont("font.ttf", 200);
    SDL_Color white = {255,255,255};
    SDL_Color green = {0,255,0};
    SDL_Surface* textbuf = TTF_RenderText_Shaded(font, text.c_str(), white, green);
    SDL_Texture* newtexture = SDL_CreateTextureFromSurface(renderer, textbuf);
    SDL_FreeSurface(textbuf);
    TTF_CloseFont(font);

    return newtexture;
}
int main(int argc, char* argv[])
{
    MSG message = {0};
    int w, h = 0;

    if (argc == 2)
        sstream << argv[1] << " " << wins << "W/" << losses << "L/" << draws << "D";
    else
        sstream << wins << "W/" << losses << "L/" << draws << "D";

    //Registering hotkeys
    if (RegisterHotKey(NULL, 1, 0, 0x70))
        cout << "Registered F1 as hotkey" << endl;
    if (RegisterHotKey(NULL, 2, 0, 0x71))
        cout << "Registered F2 as hotkey" << endl;
    if (RegisterHotKey(NULL, 3, 0, 0x72))
        cout << "Registered F3 as hotkey" << endl;
    if (RegisterHotKey(NULL, 4, MOD_ALT, 0x70))
        cout << "Registered ALT + F1 as hotkey" << endl;
    if (RegisterHotKey(NULL, 5, MOD_ALT, 0x71))
        cout << "Registered ALT + F2 as hotkey" << endl;
    if (RegisterHotKey(NULL, 6, MOD_ALT, 0x72))
        cout << "Registered ALT + F3 as hotkey" << endl;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Scoreboard", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event event;

    while (GetMessage(&message, NULL, 0, 0))
    {
        SDL_RenderClear(renderer);
        DispatchMessage(&message);

        while(SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    quit = true;
                }
            }
        }

        if (message.message == WM_HOTKEY)
        {
            sstream.str(std::string());
            switch (message.wParam)
            {
            case 1:
                wins++;
                break;
            case 2:
                losses++;
                break;
            case 3:
                draws++;
                break;
            case 4:
                wins--;
                break;
            case 5:
                losses--;
                break;
            case 6:
                draws--;
                break;
            default:
                break;
            }
            if (argc == 2)
                sstream << argv[1] << " " << wins << "W/" << losses << "L/" << draws << "D";
            else
                sstream << wins << "W/" << losses << "L/" << draws << "D";
        }

        if (!sstream.str().empty())
        {
            SDL_DestroyTexture(scoreboard);
            scoreboard = Regenerate(renderer, sstream.str());
            sstream.str(std::string());
        }

        SDL_QueryTexture(scoreboard, NULL, NULL, &w, &h);
        SDL_SetWindowSize(window, w, h);

        SDL_RenderCopy(renderer, scoreboard, NULL, NULL);
        SDL_RenderPresent(renderer);

        if (quit)
            break;
    }

    SDL_Quit();
    return 0;
}

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define SCREEN_SCALE 1
#define MAX_FRAMERATE 60

SDL_Window *window = NULL;
SDL_Renderer *renderTarget = NULL;
SDL_Event event;
SDL_Rect drawingRect;

// frames
float frameTime = 0;
int previousTime = 0;
int currentTime = 0;
float deltaTime = 0;

bool running = true;

int main()
{
   // window **************************************************************************************
   if(SDL_Init(SDL_INIT_VIDEO) > 0)
   {
      printf("video initialization error\n");
      return -1;
   }
   else
   {
      window = SDL_CreateWindow("Game Of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH * SCREEN_SCALE, SCREEN_HEIGHT * SCREEN_SCALE, SDL_WINDOW_SHOWN);
      if(window == NULL)
      {
         printf("window creation error\n");
         return -1;
      }
   }

   // renderer ************************************************************************************
   renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

   // image flags *********************************************************************************
   int imageFlags = IMG_INIT_PNG | IMG_INIT_JPG;
   if(!(IMG_Init(imageFlags) & imageFlags))
   {
      printf("error unknown image type\n");
      return -1;
   }

   // loop ****************************************************************************************
   while(running)
   {
      while(SDL_PollEvent(&event) != 0)
      {
         if(event.type == SDL_QUIT)
         {
            running = false;
         }
      }

      // update ***********************************************************************************
      // sets framerate
      previousTime = currentTime;
      currentTime = SDL_GetTicks();
      deltaTime = (currentTime - previousTime) / 1000.0f;

      frameTime += deltaTime;
      if(frameTime >= (float) 1 / MAX_FRAMERATE)
      {
         frameTime = 0;
         // add things here
      } 

      // render ***********************************************************************************
      // clear screen
      SDL_SetRenderDrawColor(renderTarget, 109.0f, 141.0f, 1.0f, 1.0f);
      SDL_RenderClear(renderTarget);
   }

   // clean ***************************************************************************************
   SDL_DestroyWindow(window);
   SDL_DestroyRenderer(renderTarget);
   window = NULL;
   renderTarget = NULL;
   IMG_Quit();
   SDL_Quit();

   return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define MAX_FRAMERATE 60

SDL_Window *window = NULL;
SDL_Renderer *renderTarget = NULL;
SDL_Event event;

// frames
float frameTime = 0;
int previousTime = 0;
int currentTime = 0;
float deltaTime = 0;

bool running = true;

// game data
int width = 0;
int height = 0;
float scale = 0.0f;
char *gameState = NULL;

int initialize()
{
   // window
   if(SDL_Init(SDL_INIT_VIDEO) > 0)
   {
      printf("video initialization error\n");
      return 1;
   }
   else
   {
      window = SDL_CreateWindow("Game Of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
      if(window == NULL)
      {
         printf("window creation error\n");
         return 1;
      }
   }
   
   // open start file
   FILE* in = fopen("start.txt", "r");
   if(in == NULL)
   {
      printf("file open error\n");
      return 1;
   }

   // get game width, height, and set scale
   fscanf(in, "%d", &width);
   fscanf(in, "%d", &height);
   scale = SCREEN_WIDTH / width;

   // get starting state
   gameState = malloc(sizeof(char) * width * height);
   char c = getc(in);
   unsigned int index = 0;
   while(index < width * height)
   {
      c = getc(in);
      if(c == '\n')
      {
         while(index % width != 0)
         {
            gameState[index] = ' ';
            index++;
         }
      }
      else if(c == '#')
      {
         gameState[index] = '#';
         index++;
      }
      else if(c == ' ')
      {
         gameState[index] =  ' ';
         index++;
      }
      else
      {
         gameState[index] = ' ';
         index++;
      }
   }
   fclose(in);

   // renderer 
   renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void events(SDL_Event *event)
{
   if(event->type == SDL_QUIT)
   {
      running = false;
   }
}

void update()
{
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
}

void render()
{
   // clear screen
   SDL_SetRenderDrawColor(renderTarget, 1.0f, 1.0f, 1.0f, 1.0f);
   SDL_RenderClear(renderTarget);
   SDL_SetRenderDrawColor(renderTarget, 255.0f, 255.0f, 255.0f, 1.0f);
   SDL_Rect cell = { 0, 0, scale, scale };

   unsigned int index = 0;
   for(int column = 0; column < height; column++)
   {
      for(int row = 0; row < width; row++)
      {
         index = column * width + row;
         if(gameState[index] == '#')
         {
            cell.x = row * scale;
            cell.y = column * scale;
            SDL_RenderFillRect(renderTarget, &cell);
         }
      }
   }
   SDL_RenderPresent(renderTarget);
}

void clean()
{
   SDL_DestroyWindow(window);
   SDL_DestroyRenderer(renderTarget);
   window = NULL;
   renderTarget = NULL;
   SDL_Quit();
}

int main()
{
   if(initialize() == 1)
   {
      return 1;
   }
   // loop
   while(running)
   {
      while(SDL_PollEvent(&event) != 0)
      {
         events(&event); 
      }
      update();
      render(); 
   }
   clean();

   return 0;
}

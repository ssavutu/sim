#include "main.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const double PI = 3.14159265;

void draw_circle(int h, int k, int r, SDL_Renderer* renderer){
	SDL_Point center = {h, k};
	int B = 90;
	int C;
	int x;
	int y;
	while(r > 0){
		for(int A = 0; A <= 360; A++){
			C = 180-(A+B);
			x = h+(r*sin(C*(PI/180)));
			y = k+(r*sin(A*(PI/180)));
			SDL_RenderDrawPoint(renderer, x, y);
		}
		r -= 1;
	}
}

int main(int argc, char* args[]){
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("WINDOW", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer,255,255,255,255);
	draw_circle(640/2, 480/2, 30, renderer);
	draw_circle((640/2)+50, (480/2)+50, 20, renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(10000);
	return 0;
}

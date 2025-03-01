#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

void draw_lines(SDL_Renderer* renderer, float points[][2],int size_tab){
	
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	
	for (int i = 0 ; i < size_tab ; i++ ) {
		SDL_RenderDrawLine(renderer, 
						points[i][0],
						points[i][1],
						points[(i+1)%size_tab][0],
						points[(i+1)%size_tab][1]);
	}
}

void new_coordinates(float points[][2], int size_tab, float angle, float centerX, float centerY) {
    for (int i = 0; i < size_tab; i++) {
		
		// CENTERED POINTS
        float x = points[i][0] - centerX;
        float y = points[i][1] - centerY;
        
		// ROTATION ON ITSELF
        points[i][0] = x * cos(angle) - y * sin(angle) + centerX;
        points[i][1] = x * sin(angle) + y * cos(angle) + centerY;
    }
}


int main(int argc, char *argv[]) {
    // INIT SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL Initialization Error: %s\n", SDL_GetError());
        return 1;
    }

    // CREATING THE WINDOW
    SDL_Window *window = SDL_CreateWindow("Rotating cube", 
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                          WINDOW_WIDTH, WINDOW_HEIGHT, 
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window Creation Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // RENDERER
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer Creation Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // BLACK BACKGROUND
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
	
	// POINTS
	
	float points[][2] = {
		{300,300},
		{300,200},
		{200,200},
		{200,300}};
	
	float angle = 0.02f;
	float centerX = (points[0][0] + points[2][0]) / 2;
    float centerY = (points[0][1] + points[2][1]) / 2;
	
	SDL_Event e;
		int quit = 0;
		while (!quit) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					quit = 1;
				}
			}
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
			SDL_RenderClear(renderer);
			draw_lines(renderer, points, 4);
			new_coordinates(points, 4, angle, centerX, centerY);
			SDL_RenderPresent(renderer);
			SDL_Delay(16);
			//angle += 0.001f;

		}



    // EXIT EVENT
    SDL_Event event;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
    }

    // CLEANING
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

typedef struct {
    float x, y, z;
} Point3D;

void draw_lines(SDL_Renderer* renderer, float points[][2], int size_tab) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    for (int i = 0; i < size_tab; i++) {
        SDL_RenderDrawLine(renderer, 
                           points[i][0], points[i][1],
                           points[(i+1)%size_tab][0], points[(i+1)%size_tab][1]);
    }
}

void project(Point3D points3D[], float points2D[][2], int size_tab, float distance) {
    for (int i = 0; i < size_tab; i++) {
        points2D[i][0] = (points3D[i].x * distance) / (points3D[i].z + distance) + WINDOW_WIDTH / 2;
        points2D[i][1] = (points3D[i].y * distance) / (points3D[i].z + distance) + WINDOW_HEIGHT / 2;
    }
}

void rotateX(Point3D points[], int size_tab, float angle) {
    for (int i = 0; i < size_tab; i++) {
        float y = points[i].y;
        float z = points[i].z;
        points[i].y = y * cos(angle) - z * sin(angle);
        points[i].z = y * sin(angle) + z * cos(angle);
    }
}

void rotateY(Point3D points[], int size_tab, float angle) {
    for (int i = 0; i < size_tab; i++) {
        float x = points[i].x;
        float z = points[i].z;
        points[i].x = x * cos(angle) + z * sin(angle);
        points[i].z = -x * sin(angle) + z * cos(angle);
    }
}

void rotateZ(Point3D points[], int size_tab, float angle) {
    for (int i = 0; i < size_tab; i++) {
        float x = points[i].x;
        float y = points[i].y;
        points[i].x = x * cos(angle) - y * sin(angle);
        points[i].y = x * sin(angle) + y * cos(angle);
    }
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL Initialization Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Rotating 3D Cube", 
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                          WINDOW_WIDTH, WINDOW_HEIGHT, 
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window Creation Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer Creation Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    Point3D points3D[8] = {
        {100, 100, 100}, {100, -100, 100}, {-100, -100, 100}, {-100, 100, 100},
        {100, 100, -100}, {100, -100, -100}, {-100, -100, -100}, {-100, 100, -100}
    };

    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},git 
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    float points2D[8][2];
    float angleX = 0.02f, angleY = 0.02f, angleZ = 0.02f;
    float distance = 500;

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

        rotateX(points3D, 8, angleX);
        rotateY(points3D, 8, angleY);
        rotateZ(points3D, 8, angleZ);
        project(points3D, points2D, 8, distance);

        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        for (int i = 0; i < 12; i++) {
            SDL_RenderDrawLine(renderer,
                               points2D[edges[i][0]][0], points2D[edges[i][0]][1],
                               points2D[edges[i][1]][0], points2D[edges[i][1]][1]);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
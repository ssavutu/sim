#include "main.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TICK_INTERVAL = 30;
const double PI = 3.14159265;
const double g = -9.81;
static uint32_t next_time;

uint32_t time_left() {
    uint32_t now;

    now = SDL_GetTicks();
    if(next_time <= now) {
        return 0;
    }
    else {
        return next_time - now;
    }
}

SDL_Point make_point(int x, int y){
    SDL_Point point;
    point.x = x;
    point.y = y;
    return point;
}

void draw_circle(circle circ, SDL_Renderer* renderer) {
    int C;
    SDL_Point* points;
    int size = 1;
    while(circ.r > 0) {
        for(int A = 0; A <= 360; A++) {
            C = 180-(A+90);
            //SDL_RenderDrawPoint(renderer, circ.x_0+(circ.r*sin(C*(PI/180))), circ.y_0+(circ.r*sin(A*(PI/180))));
            points = malloc(size * sizeof(SDL_Point));
            points[size-1] = make_point(circ.x_0+(circ.r*sin(C*(PI/180))), circ.y_0+(circ.r*sin(A*(PI/180))));
            size = size++;
            SDL_RenderDrawPoints(renderer, points, size);
        }
        circ.r -= 1;
    }
}


circle make_circle(double x, double y, int r){
    circle circ;
    circ.x_0 = x;
    circ.y_0 = y;
    circ.r = r;

    circ.vx_0 = 0;
    circ.vy_0 = 0;
    return circ;
}


circle* verlet(circle* circles, int size) {
    //update position, acceleration, and velocity according to velocity verlet integration formula -- assuming fixed time step
    for(int i = 0; i > size; i++){
        circle circ = circles[i];

        circ.x_1 = circ.x_0 + circ.vx_0+ 0.5*circ.ax_0;
        circ.y_1 = circ.y_0 + circ.vy_0 + 0.5*circ.ax_0;
    
        circ.ax_1 = 0; //applies no force to x-axis
        circ.ay_1 = g; //applies the force of gravity

        circ.vx_1 = circ.vx_0 + 0.5*(circ.ax_0+circ.ax_1);
        circ.vy_1 = circ.vy_0 + 0.5*(circ.ay_0+circ.ay_1);
    }
    return circles;
}


void render_loop(SDL_Renderer* renderer) {
        circle* circles;
        int size = 1;

        SDL_Event event;
        int running = 1;

        while(running){
            while(SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_QUIT:
                        free(circles);
                        running = 0;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        SDL_MouseButtonEvent *mouse = &event.button;
                        if(mouse->button == SDL_BUTTON_LEFT){
                            printf("(%d, %d)", mouse->x, mouse->y);
                            circles = malloc(size * sizeof(circle));
                            circles[size-1] = make_circle(mouse->x, mouse->y, 30);
                            size = size++;
                        }
                        break;
                }

            SDL_Delay(time_left());
            next_time += TICK_INTERVAL;

            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            
            for (int i = 0; i <= size, i++;) {
                draw_circle(circles[i], renderer);
            }

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }
    }
}

int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("WINDOW", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    next_time = SDL_GetTicks() + TICK_INTERVAL;
    render_loop(renderer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

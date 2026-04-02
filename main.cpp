#include "raylib.h"
#include "iostream"
#include "string"
using namespace std;

struct Player{
    Vector2 pos;
    float speed;
};
const float PLAYER_WIDTH = 32.0f;
const float PLAYER_HEIGHT = 32.0f;
int main()
{
    int window_width = 800;
    int window_height = 600;

    Player player1;
    player1.pos = {window_width / 2.0f, window_height / 2.0f};
    player1.speed = 200.0f;


    InitWindow(window_width,window_height,"Hello Window");
    SetTargetFPS(120);
    while (!WindowShouldClose())
    {
        float delta = GetFrameTime(); // for 120 fps. 1/120.
        // speed is 200, 200*.0083 = 3.33. makes the movement independent of the fps.

        if (IsKeyDown(KEY_S)) player1.pos.y += player1.speed * delta; // since 0,0 is at the top left, y increases downward
        if (IsKeyDown(KEY_W)) player1.pos.y -= player1.speed * delta; 
        if (IsKeyDown(KEY_A)) player1.pos.x -= player1.speed * delta; 
        if (IsKeyDown(KEY_D)) player1.pos.x += player1.speed * delta; 
        // if (IsKeyDown(KEY_S)) player1.pos.y += 2.0f;

        // TODO: limit movement to bounds of windwow


        BeginDrawing();
        ClearBackground(SKYBLUE);
        // DrawText("This is my first window",250,300,20,LIGHTGRAY);
        DrawRectangleV(player1.pos, {PLAYER_WIDTH, PLAYER_HEIGHT}, LIME);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
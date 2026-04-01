#include "raylib.h"
#include "iostream"
#include "string"
using namespace std;

int main()
{
    InitWindow(800,600,"Hello Window");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("This is my first window",250,300,20,LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
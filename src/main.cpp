#include <raylib.h>
#include "exodus.hpp"
int main(int narg,char** sarg)
{
    const int screenWidth = (720*4)/3; //GetMonitorWidth(0);
    const int screenHeight = 720;//GetMonitorHeight(0);
    InitWindow(screenWidth, screenHeight, "Exodus cart game");
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second

    Exodus exodus;
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLACK);
        exodus.Draw();
        EndDrawing();
    }
 
    CloseWindow();   // Close window and OpenGL
    return 0;
}

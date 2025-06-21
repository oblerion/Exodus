#include <raylib.h>
#include "exodus.hpp"
#include "buttonText.hpp"
#include "SQLiteManager.hpp"
int main(int narg,char** sarg)
{
    const int screenWidth = (720*4)/3; //GetMonitorWidth(0);
    const int screenHeight = 720;//GetMonitorHeight(0);
    InitWindow(screenWidth, screenHeight, "Exodus the card game by magnus oblerion");
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second

    Exodus exodus;
    int state  =0;
    ButtonText title_btnSolo(20,120,"Solo",24,GRAY);
    ButtonText title_btnLocalMulti(20,148,"Local Multi Player",24,BLUE);
    ButtonText title_btnBrowser(20,175,"Card Browser",24,RED);

    ButtonText browser_btnBack(0,0,"Back",20,GRAY);

    const char* TEXTVERSION = TextFormat("version: %s ",EXODUS_VERSION);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if(!exodus.DbIsLoad())
        {
            const char* ltext = "Error : I don't find db/exodus.db\n the game can't start without it";
            int size = MeasureText(ltext,20);
            DrawText(ltext,(GetRenderWidth()-size)/2,100,20,WHITE);
            DrawText(TEXTVERSION,
                             GetScreenWidth()-MeasureText(TEXTVERSION,18),
                             GetScreenHeight()-20,
                             18,
                             WHITE);
        }
        else
        {

            switch(state)
            {
                case 0: // title
                    DrawText("Exodus",
                            GetRenderWidth()/2-MeasureText("Exodus",45)/2,20,45,WHITE);
                    if(title_btnSolo.Draw()==ButtonPress)
                    {

                    }
                    if(title_btnLocalMulti.Draw()==ButtonPress)
                    {
                        state = 2;
                        WaitTime(0.2);
                    }
                    if(title_btnBrowser.Draw()==ButtonPress)
                    {
                        state = 1;
                    }

                    DrawText(TEXTVERSION,
                             GetScreenWidth()-MeasureText(TEXTVERSION,18),
                             GetScreenHeight()-20,
                             18,
                             WHITE);
                break;
                case 1: // card browser
                    exodus.DrawCartExplorer();
                    if(browser_btnBack.Draw()==ButtonPress)
                        state=0;
                break;

                case 2: // play
                    exodus.Draw();

                break;
                default:;
            }
        }
        EndDrawing();
    }
    CloseWindow();   // Close window and OpenGL
    return 0;
}

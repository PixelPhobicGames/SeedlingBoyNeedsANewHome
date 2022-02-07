#include "Core.hpp"

int main(void){

    MysticEngineInit();
    
    PlaySplashLogo();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        
        ClearBackground(BLACK);

        UpdateMusicStream(WorldData.Theme);

        RenderLevel();
        CoreUpdate();

        CustomLevelBehavior();


        if (IsKeyPressed(KEY_F11)){
            ToggleFullscreen();
        }


        EndDrawing();
    }
    CloseWindow();
    
}
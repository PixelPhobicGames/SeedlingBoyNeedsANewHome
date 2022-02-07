#include "Data.hpp"

int WorldDraw = false;
void RenderLevel(){
    if (WorldData.BackgroundEnabled){
        if (!WorldData.BackgroundScrollEnabled)DrawTextureEx(WorldData.Background, {0,0}, 0, MysticEngine.WindowScale, WHITE);
        else {DrawTextureEx(WorldData.Background, {MysticEngine.BackgroundXScroll * MysticEngine.WindowScale,0}, 0, MysticEngine.WindowScale, WHITE);}
    }
    for (int x = 0; x <= WorldData.Width - 1;  x ++ ){
        for (int y = 0; y <= WorldData.Height - 1;  y ++ ){
            switch (WorldData.Map[y*(WorldData.Width)+x])
            { 
                case L'1':
                    if (x == 0) DrawTextureEx(WorldData.Tile1, {((x*20) - MysticEngineCamera.X)* MysticEngine.WindowScale,((y*20) - MysticEngineCamera.Y)* MysticEngine.WindowScale}, 0, MysticEngine.WindowScale, WHITE);
                    break;
                case L'2':
                    DrawTextureEx(WorldData.Tile2, {((x*20) - MysticEngineCamera.X)* MysticEngine.WindowScale,((y*20) - MysticEngineCamera.Y)* MysticEngine.WindowScale}, 0, MysticEngine.WindowScale, WHITE);
                    break;
                case L'3':
                    DrawTextureEx(WorldData.Tile3, {((x*20) - MysticEngineCamera.X)* MysticEngine.WindowScale,((y*20) - MysticEngineCamera.Y)* MysticEngine.WindowScale}, 0, MysticEngine.WindowScale, WHITE);
                    break;
                case L'4':
                    DrawTextureEx(WorldData.Tile4, {((x*20) - MysticEngineCamera.X)* MysticEngine.WindowScale,((y*20) - MysticEngineCamera.Y)* MysticEngine.WindowScale}, 0, MysticEngine.WindowScale, WHITE);
                    break;
                case L'5':
                    DrawTextureEx(WorldData.Tile5, {((x*20) - MysticEngineCamera.X)* MysticEngine.WindowScale,((y*20) - MysticEngineCamera.Y)* MysticEngine.WindowScale}, 0, MysticEngine.WindowScale, WHITE);
                    break;
                case L'6':
                    DrawTextureEx(WorldData.Tile6, {((x*20) - MysticEngineCamera.X)* MysticEngine.WindowScale,((y*20) - MysticEngineCamera.Y)* MysticEngine.WindowScale}, 0, MysticEngine.WindowScale, WHITE);
                    break;
                case L'7':
                    DrawTextureEx(WorldData.Tile7, {((x*20) - MysticEngineCamera.X)* MysticEngine.WindowScale,((y*20) - MysticEngineCamera.Y)* MysticEngine.WindowScale}, 0, MysticEngine.WindowScale, WHITE);
                    break;
                case L'8':
                    DrawTextureEx(WorldData.Tile8, {((x*20) - MysticEngineCamera.X)* MysticEngine.WindowScale,((y*20) - MysticEngineCamera.Y)* MysticEngine.WindowScale}, 0, MysticEngine.WindowScale, WHITE);
                    break;
                case L'9':
                    DrawTextureEx(WorldData.Tile9, {((x*20) - MysticEngineCamera.X)* MysticEngine.WindowScale,((y*20) - MysticEngineCamera.Y)* MysticEngine.WindowScale}, 0, MysticEngine.WindowScale, WHITE);
                    break;
                case L'0':
                    if (!WorldData.BackgroundEnabled)DrawTextureEx(WorldData.Tile0, {((x*20) - MysticEngineCamera.X)* MysticEngine.WindowScale,((y*20) - MysticEngineCamera.Y)* MysticEngine.WindowScale}, 0, MysticEngine.WindowScale, WHITE);
                    //else {DrawTextureEx(WorldData.Tile0, {((x*20) - MysticEngineCamera.X)* MysticEngine.WindowScale,((y*20) - MysticEngineCamera.Y)* MysticEngine.WindowScale}, 0, MysticEngine.WindowScale, WHITE);}
                    break;
                case L'{':
                    DrawText("I Love You Leila!", ((x*20) - MysticEngineCamera.X)* MysticEngine.WindowScale,((y*20) - MysticEngineCamera.Y)* MysticEngine.WindowScale, 20* MysticEngine.WindowScale, WHITE);
                    break;
                default:
                    #if (defined(DEBUG))
                    if (IsKeyDown(KEY_D))DrawRectangle(((x*20) - MysticEngineCamera.X)* MysticEngine.WindowScale,((y*20) - MysticEngineCamera.Y)* MysticEngine.WindowScale, 20* MysticEngine.WindowScale , 20* MysticEngine.WindowScale , PURPLE);
                    #endif
                    break;

            }
        }
    }
}
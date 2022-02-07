#include "Renderer.hpp"
#include <cmath>


void CustomLoadBehavior();

void PlayFadeEffect(){

}

void PlaySplashLogo(){
    Texture2D SplashImage = LoadTexture("MysticEngine/Other/PixelPhobicGames.png");
    Music SplashSound = LoadMusicStream("MysticEngine/Other/PPGopen.mp3");

    int Direction = 0;

    PlayMusicStream(SplashSound);


    while(true){
        UpdateMusicStream(SplashSound);
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextureEx(SplashImage, {0,0}, 0, MysticEngine.WindowScale, FadeColor);

        if (Direction == 0){
            R += 1;
            G += 1;
            B += 1;
            if (R == 255){
                Direction = 1;
            }
        }
        else {
            R -= 1;
            G -= 1;
            B -= 1;

            if (R == 0){
                break;
            }
        }

        EndDrawing();
    }

    StopMusicStream(SplashSound);

    UnloadTexture(SplashImage);

    UnloadMusicStream(SplashSound);
}

static void LoadTiles(){

    WorldData.BackgroundEnabled = false;
    WorldData.BackgroundScrollEnabled = false;

    WorldData.Tile0 = LoadTexture(FormatText("GameData/%s/Tiles/Tile0.png" , WorldData.MapName));
    WorldData.Tile1 = LoadTexture(FormatText("GameData/%s/Tiles/Tile1.png" , WorldData.MapName));
    WorldData.Tile2 = LoadTexture(FormatText("GameData/%s/Tiles/Tile2.png" , WorldData.MapName));
    WorldData.Tile3 = LoadTexture(FormatText("GameData/%s/Tiles/Tile3.png" , WorldData.MapName));
    WorldData.Tile4 = LoadTexture(FormatText("GameData/%s/Tiles/Tile4.png" , WorldData.MapName));
    WorldData.Tile5 = LoadTexture(FormatText("GameData/%s/Tiles/Tile5.png" , WorldData.MapName));
    WorldData.Tile6 = LoadTexture(FormatText("GameData/%s/Tiles/Tile6.png" , WorldData.MapName));
    WorldData.Tile7 = LoadTexture(FormatText("GameData/%s/Tiles/Tile7.png" , WorldData.MapName));
    WorldData.Tile8 = LoadTexture(FormatText("GameData/%s/Tiles/Tile8.png" , WorldData.MapName));
    WorldData.Tile9 = LoadTexture(FormatText("GameData/%s/Tiles/Tile9.png" , WorldData.MapName));
    WorldData.Theme = LoadMusicStream(FormatText("GameData/%s/Music/Music.mp3" , WorldData.MapName));

    if (LoadConfigurationFile(FormatText("GameData/%s/Config/LevelType.mconf" , WorldData.MapName)) == L'2'){
        MysticEngine.LevelType = 2;
    }
    if (LoadConfigurationFile(FormatText("GameData/%s/Config/LevelType.mconf" , WorldData.MapName)) == L'1'){
        MysticEngine.LevelType = 1;
    }
    wstring Data;
    wifstream OutFile;
    OutFile.open(FormatText("GameData/%s/Config/Background.mconf" , WorldData.MapName));
    OutFile >> Data;

    if (Data[0] == L'1'){
        WorldData.Background = LoadTexture(FormatText("GameData/%s/Backgrounds/Background.png" , WorldData.MapName));
        WorldData.BackgroundEnabled = true;
    }

    if (Data[2] == L'1'){
        WorldData.BackgroundScrollEnabled = true;
    }

    switch (Data[4])
    {
        case L'1':
            MysticEngine.BackgroundXScrollSpeed = 1;
            break;
        case L'2':
            MysticEngine.BackgroundXScrollSpeed = 2;
            break;
        case L'3':
            MysticEngine.BackgroundXScrollSpeed = 3;
            break;
        case L'4':
            MysticEngine.BackgroundXScrollSpeed = 4;
            break;
        case L'5':
            MysticEngine.BackgroundXScrollSpeed = 5;
            break;
        case L'6':
            MysticEngine.BackgroundXScrollSpeed = 6;
            break;
        case L'7':
            MysticEngine.BackgroundXScrollSpeed = 7;
            break;
        case L'8':
            MysticEngine.BackgroundXScrollSpeed = 8;
            break;
        case L'9':
            MysticEngine.BackgroundXScrollSpeed = 9;
            break;
        default:
            MysticEngine.BackgroundXScrollSpeed = 1;
            break;
    }

}

void ScanPlayerSpawn(){
    for (int x = 0 ; x<= WorldData.Width ; x++){
        for (int y = 0 ; y <= WorldData.Height ; y++){
            if (WorldData.Map[y * WorldData.Width + x] == L'@'){
                MysticEngineCamera.X = x * 20;
                MysticPlayer.Y = y * 20;
            }
        }
    }
}
void ScanMapDimensions(){
    WorldData.Width = 0;
    WorldData.Height = 0;
    int Counter = 0;
    for (int i = 0 ; i <= WorldData.Map.size(); i++){
        if (WorldData.Map[i] == L'&'){
            WorldData.Height ++;
            if (Counter == 0){
                WorldData.Width = i;
                Counter = 1;
            }
        }
        if (WorldData.Map[i] == L'?'){
            WorldData.Height ++;
        }
    }
    WorldData.Width += 1;

    if (MysticEngine.ME1Compatable){
        WorldData.Width = 512;
        WorldData.Height = 34;
    }
}

void ScanPlayerAnimationSpeed(){

    wstring Data;
    Data = LoadFile("GameData/GameAssets/Player/AnimationSpeed.mconf");
    int NumberPlace = 0;
    int Numb = 0;

    for (int i = Data.size() ; i >= 0 ; i--){   
        if (Data[i] == L'1'){
            if (NumberPlace == 0){Numb += 1;}
            if (NumberPlace == 1){Numb += 10;}
            if (NumberPlace == 2){Numb += 100;}
            NumberPlace ++;
        }
        if (Data[i] == L'2'){
            if (NumberPlace == 0){Numb += 2;}
            if (NumberPlace == 1){Numb += 20;}
            if (NumberPlace == 2){Numb += 200;}
            NumberPlace ++;
        }
        if (Data[i] == L'3'){
            if (NumberPlace == 0){Numb += 3;}
            if (NumberPlace == 1){Numb += 30;}
            if (NumberPlace == 2){Numb += 300;}
            NumberPlace ++;
        }
        if (Data[i] == L'4'){
            if (NumberPlace == 0){Numb += 4;}
            if (NumberPlace == 1){Numb += 40;}
            if (NumberPlace == 2){Numb += 400;}
            NumberPlace ++;
        }
        if (Data[i] == L'5'){
            if (NumberPlace == 0){Numb += 5;}
            if (NumberPlace == 1){Numb += 50;}
            if (NumberPlace == 2){Numb += 500;}
            NumberPlace ++;
        }
        if (Data[i] == L'6'){
            if (NumberPlace == 0){Numb += 6;}
            if (NumberPlace == 1){Numb += 60;}
            if (NumberPlace == 2){Numb += 600;}
            NumberPlace ++;
        }
        if (Data[i] == L'7'){
            if (NumberPlace == 0){Numb += 7;}
            if (NumberPlace == 1){Numb += 70;}
            if (NumberPlace == 2){Numb += 700;}
            NumberPlace ++;
        }
        if (Data[i] == L'8'){
            if (NumberPlace == 0){Numb += 8;}
            if (NumberPlace == 1){Numb += 80;}
            if (NumberPlace == 2){Numb += 800;}
            NumberPlace ++;
        }
        if (Data[i] == L'9'){
            if (NumberPlace == 0){Numb += 9;}
            if (NumberPlace == 1){Numb += 90;}
            if (NumberPlace == 2){Numb += 900;}
            NumberPlace ++;
        }
    }
    MysticPlayer.AnimationSpeed = Numb;
}

void ScanCameraSpeed(){
    wstring Data;
    Data = LoadFile("MysticEngine/Global/Config/CameraSpeed.mconf");

    switch (Data[0])
    {
        case L'1':
            MysticEngineCamera.Speed = 1;
            break;
        case L'2':
            MysticEngineCamera.Speed = 2;
            break;
        case L'3':
            MysticEngineCamera.Speed = 3;
            break;
        case L'4':
            MysticEngineCamera.Speed = 4;
            break;
        case L'5':
            MysticEngineCamera.Speed = 5;
            break;
        case L'6':
            MysticEngineCamera.Speed = 6;
            break;
        case L'7':
            MysticEngineCamera.Speed = 7;
            break;
        case L'8':
            MysticEngineCamera.Speed = 8;
            break;
        case L'9':
            MysticEngineCamera.Speed = 9;
            break;
        default:
            MysticEngineCamera.Speed = 1;
            break;
    }
}

void ScanPlayerDimesions(){
    wstring YOffsetData;
    YOffsetData = LoadFile("GameData/GameAssets/Player/YOffset.mconf");

    int NumPlace = 0;

    for (int i = YOffsetData.size() ; i >= 0 ; i--){   
        switch (YOffsetData[i])
        {
            case L'0':
                if (NumPlace == 0)
                NumPlace ++;
                break;
            case L'1':
                if (NumPlace == 0){MysticPlayer.YOffset += 1;}
                if (NumPlace == 1){MysticPlayer.YOffset += 10;}
                if (NumPlace == 2){MysticPlayer.YOffset += 100;}
                if (NumPlace == 3){MysticPlayer.YOffset += 1000;}
                NumPlace ++;
                break;
            case L'2':
                if (NumPlace == 0){MysticPlayer.YOffset += 2;}
                if (NumPlace == 1){MysticPlayer.YOffset += 20;}
                if (NumPlace == 2){MysticPlayer.YOffset += 200;}
                if (NumPlace == 3){MysticPlayer.YOffset += 2000;}
                NumPlace ++;
                break;
            case L'3':
                if (NumPlace == 0){MysticPlayer.YOffset += 3;}
                if (NumPlace == 1){MysticPlayer.YOffset += 30;}
                if (NumPlace == 2){MysticPlayer.YOffset += 300;}
                if (NumPlace == 3){MysticPlayer.YOffset += 3000;}
                NumPlace ++;
                break;
            case L'4':
                if (NumPlace == 0){MysticPlayer.YOffset += 4;}
                if (NumPlace == 1){MysticPlayer.YOffset += 40;}
                if (NumPlace == 2){MysticPlayer.YOffset += 400;}
                if (NumPlace == 3){MysticPlayer.YOffset += 4000;}
                NumPlace ++;
                break;
            case L'5':
                if (NumPlace == 0){MysticPlayer.YOffset += 5;}
                if (NumPlace == 1){MysticPlayer.YOffset += 50;}
                if (NumPlace == 2){MysticPlayer.YOffset += 500;}
                if (NumPlace == 3){MysticPlayer.YOffset += 5000;}
                NumPlace ++;
                break;
            case L'6':
                if (NumPlace == 0){MysticPlayer.YOffset += 6;}
                if (NumPlace == 1){MysticPlayer.YOffset += 60;}
                if (NumPlace == 2){MysticPlayer.YOffset += 600;}
                if (NumPlace == 3){MysticPlayer.YOffset += 6000;}
                NumPlace ++;
                break;
            case L'7':
                if (NumPlace == 0){MysticPlayer.YOffset += 7;}
                if (NumPlace == 1){MysticPlayer.YOffset += 70;}
                if (NumPlace == 2){MysticPlayer.YOffset += 700;}
                if (NumPlace == 3){MysticPlayer.YOffset += 7000;}
                NumPlace ++;
                break;
            case L'8':
                if (NumPlace == 0){MysticPlayer.YOffset += 8;}
                if (NumPlace == 1){MysticPlayer.YOffset += 80;}
                if (NumPlace == 2){MysticPlayer.YOffset += 800;}
                if (NumPlace == 3){MysticPlayer.YOffset += 8000;}
                NumPlace ++;
                break;
            case L'9':
                if (NumPlace == 0){MysticPlayer.YOffset += 9;}
                if (NumPlace == 1){MysticPlayer.YOffset += 90;}
                if (NumPlace == 2){MysticPlayer.YOffset += 900;}
                if (NumPlace == 3){MysticPlayer.YOffset += 9000;}
                NumPlace ++;
                break;
            case L'-':
                MysticPlayer.YOffset = MysticPlayer.YOffset * -1;
                break;

            default:
                MysticPlayer.YOffset = 0;
                break;
        }
    }



    wstring PlayerData;
    PlayerData = LoadFile("GameData/GameAssets/Player/Dimensions.mconf");
    int Width = 0;
    int Height = 0;

    int NumberMode = 0;

    int Mode = 0;


    for (int i = PlayerData.size() ; i >= 0 ; i--){            
        if (PlayerData[i] == L'1'){
            if (NumberMode == 0 && Mode == 0){Height += 1;}
            if (NumberMode == 1 && Mode == 0){Height += 10;}
            if (NumberMode == 2 && Mode == 0){Height += 100;}

            if (NumberMode == 0 && Mode == 1){Width += 1;}
            if (NumberMode == 1 && Mode == 1){Width += 10;}
            if (NumberMode == 2 && Mode == 1){Width += 100;}

            NumberMode ++;
        }
        if (PlayerData[i] == L'2'){
            if (NumberMode == 0 && Mode == 0){Height += 2;}
            if (NumberMode == 1 && Mode == 0){Height += 20;}
            if (NumberMode == 2 && Mode == 0){Height += 200;}

            if (NumberMode == 0 && Mode == 1){Width += 2;}
            if (NumberMode == 1 && Mode == 1){Width += 20;}
            if (NumberMode == 2 && Mode == 1){Width += 200;}

            NumberMode ++;
        }
        if (PlayerData[i] == L'3'){
            if (NumberMode == 0 && Mode == 0){Height += 3;}
            if (NumberMode == 1 && Mode == 0){Height += 30;}
            if (NumberMode == 2 && Mode == 0){Height += 300;}

            if (NumberMode == 0 && Mode == 1){Width += 3;}
            if (NumberMode == 1 && Mode == 1){Width += 30;}
            if (NumberMode == 2 && Mode == 1){Width += 300;}

            NumberMode ++;
        }

        if (PlayerData[i] == L'4'){
            if (NumberMode == 0 && Mode == 0){Height += 4;}
            if (NumberMode == 1 && Mode == 0){Height += 40;}
            if (NumberMode == 2 && Mode == 0){Height += 400;}

            if (NumberMode == 0 && Mode == 1){Width += 4;}
            if (NumberMode == 1 && Mode == 1){Width += 40;}
            if (NumberMode == 2 && Mode == 1){Width += 400;}

            NumberMode ++;
        }

        if (PlayerData[i] == L'5'){
            if (NumberMode == 0 && Mode == 0){Height += 5;}
            if (NumberMode == 1 && Mode == 0){Height += 50;}
            if (NumberMode == 2 && Mode == 0){Height += 500;}

            if (NumberMode == 0 && Mode == 1){Width += 5;}
            if (NumberMode == 1 && Mode == 1){Width += 50;}
            if (NumberMode == 2 && Mode == 1){Width += 500;}

            NumberMode ++;
        }

        if (PlayerData[i] == L'6'){
            if (NumberMode == 0 && Mode == 0){Height += 6;}
            if (NumberMode == 1 && Mode == 0){Height += 60;}
            if (NumberMode == 2 && Mode == 0){Height += 600;}

            if (NumberMode == 0 && Mode == 1){Width += 6;}
            if (NumberMode == 1 && Mode == 1){Width += 60;}
            if (NumberMode == 2 && Mode == 1){Width += 600;}

            NumberMode ++;
        }

        if (PlayerData[i] == L'7'){
            if (NumberMode == 0 && Mode == 0){Height += 7;}
            if (NumberMode == 1 && Mode == 0){Height += 70;}
            if (NumberMode == 2 && Mode == 0){Height += 700;}

            if (NumberMode == 0 && Mode == 1){Width += 7;}
            if (NumberMode == 1 && Mode == 1){Width += 70;}
            if (NumberMode == 2 && Mode == 1){Width += 700;}

            NumberMode ++;
        }

        if (PlayerData[i] == L'8'){
            if (NumberMode == 0 && Mode == 0){Height += 8;}
            if (NumberMode == 1 && Mode == 0){Height += 80;}
            if (NumberMode == 2 && Mode == 0){Height += 800;}

            if (NumberMode == 0 && Mode == 1){Width += 8;}
            if (NumberMode == 1 && Mode == 1){Width += 80;}
            if (NumberMode == 2 && Mode == 1){Width += 800;}

            NumberMode ++;
        }

        if (PlayerData[i] == L'9'){
            if (NumberMode == 0 && Mode == 0){Height += 9;}
            if (NumberMode == 1 && Mode == 0){Height += 90;}
            if (NumberMode == 2 && Mode == 0){Height += 900;}

            if (NumberMode == 0 && Mode == 1){Width += 9;}
            if (NumberMode == 1 && Mode == 1){Width += 90;}
            if (NumberMode == 2 && Mode == 1){Width += 900;}

            NumberMode ++;
        }

        if (PlayerData[i] == L'0'){
            NumberMode ++;
        }

        if (PlayerData[i] == L'|'){
            NumberMode = 0;
            Mode = 1;
        }
    }

    MysticPlayer.Height = Height;
    MysticPlayer.Width = Width;
}


void ScanPlayerAnimationFrames(){

    // Falling

    MysticPlayer.AnimationFrame1 = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Falling/Frame1.png");
    MysticPlayer.AnimationFrame2 = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Falling/Frame2.png");
    MysticPlayer.AnimationFrame3 = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Falling/Frame3.png");
    MysticPlayer.AnimationFrame4 = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Falling/Frame4.png");
    MysticPlayer.AnimationFrame5 = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Falling/Frame5.png");

    //Jumping
    MysticPlayer.AnimationFrame6 = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Jumping/Frame1.png");
    MysticPlayer.AnimationFrame7 = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Jumping/Frame2.png");
    MysticPlayer.AnimationFrame8 = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Jumping/Frame3.png");
    MysticPlayer.AnimationFrame9 = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Jumping/Frame4.png");
    MysticPlayer.AnimationFrame10 = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Jumping/Frame5.png");

    //Left
    MysticPlayer.AnimationFrame11 = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Left/Frame1.png");
    MysticPlayer.AnimationFrame12 = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Left/Frame2.png");
    MysticPlayer.AnimationFrame13 = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Left/Frame3.png");
    MysticPlayer.AnimationFrame14 = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Left/Frame4.png");
    MysticPlayer.AnimationFrame15 = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Left/Frame5.png");

    //Right

    MysticPlayer.AnimationFrame16 = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Right/Frame1.png");
    MysticPlayer.AnimationFrame17 = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Right/Frame2.png");
    MysticPlayer.AnimationFrame18 = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Right/Frame3.png");
    MysticPlayer.AnimationFrame19 = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Right/Frame4.png");
    MysticPlayer.AnimationFrame20 = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Right/Frame5.png");

    //ETC

    MysticPlayer.ProjectileTexture = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Projectile/Frame1.png");
    MysticPlayer.ShadowTexture = LoadTexture("GameData/GameAssets/Player/AnimationFrames/Shadow/Shadow.png");

}

void LoadSoundEffects(){
    MysticPlayer.JumpSound = LoadMusicStream("GameData/GameAssets/Player/SoundEffects/Jump.mp3");
    MysticPlayer.DeathSound = LoadMusicStream("GameData/GameAssets/Player/SoundEffects/Death.mp3");
}

auto ReadTile(int X , int Y){
    return WorldData.Map[Y * WorldData.Width + X];
}


auto TransitionLevel(){
    wstring LevelName;
    wstring EndSign = L"*";

    WorldData.MapName[0] = '\0';

    char FileFormat[100];

    strcat( FileFormat ,".mpak2" ); 

    MysticEngine.LevelId ++;
    
    for (int i = 0 ; i < sizeof(MysticEngine.MapDataConfig) ; i++){
        if (!MysticEngine.GameEnd){
            if (i == MysticEngine.LevelId * 7){
                for (int w = 0 ; w < 6 ; w++){
                    LevelName += MysticEngine.MapDataConfig[i + w];   
                    if (LevelName == EndSign){
                        MysticEngine.GameEnd = true;
                    }                 
                }
            }
        }
    }

    if (!MysticEngine.GameEnd){
        char MapName[100];
        char MapPath[100];

        MapPath[0] = '\0';

        MapName[0] = '\0';

        strcat(MapPath,"GameData/");

        if (MysticEngine.LevelId == 0){
            for (int i = 0 ; i < 6 ; i++){
                if (LevelName[i] == L'A'){strcat(MapName,"A");}
                if (LevelName[i] == L'B'){strcat(MapName,"B");}
                if (LevelName[i] == L'C'){strcat(MapName,"C");}
                if (LevelName[i] == L'D'){strcat(MapName,"D");}
                if (LevelName[i] == L'E'){strcat(MapName,"E");}
                if (LevelName[i] == L'F'){strcat(MapName,"F");}
                if (LevelName[i] == L'G'){strcat(MapName,"G");}
                if (LevelName[i] == L'H'){strcat(MapName,"H");}
                if (LevelName[i] == L'I'){strcat(MapName,"I");}
                if (LevelName[i] == L'J'){strcat(MapName,"J");}
                if (LevelName[i] == L'K'){strcat(MapName,"K");}
                if (LevelName[i] == L'L'){strcat(MapName,"L");}
                if (LevelName[i] == L'M'){strcat(MapName,"M");}
                if (LevelName[i] == L'N'){strcat(MapName,"N");}
                if (LevelName[i] == L'O'){strcat(MapName,"O");}
                if (LevelName[i] == L'P'){strcat(MapName,"P");}
                if (LevelName[i] == L'Q'){strcat(MapName,"Q");}
                if (LevelName[i] == L'R'){strcat(MapName,"R");}
                if (LevelName[i] == L'S'){strcat(MapName,"S");}
                if (LevelName[i] == L'T'){strcat(MapName,"T");}
                if (LevelName[i] == L'U'){strcat(MapName,"U");}
                if (LevelName[i] == L'V'){strcat(MapName,"V");}
                if (LevelName[i] == L'W'){strcat(MapName,"W");}
                if (LevelName[i] == L'X'){strcat(MapName,"X");}
                if (LevelName[i] == L'Y'){strcat(MapName,"Y");}
                if (LevelName[i] == L'Z'){strcat(MapName,"Z");}

                if (LevelName[i] == L'a'){strcat(MapName,"a");}
                if (LevelName[i] == L'b'){strcat(MapName,"b");}
                if (LevelName[i] == L'c'){strcat(MapName,"c");}
                if (LevelName[i] == L'd'){strcat(MapName,"d");}
                if (LevelName[i] == L'e'){strcat(MapName,"e");}
                if (LevelName[i] == L'f'){strcat(MapName,"f");}
                if (LevelName[i] == L'g'){strcat(MapName,"g");}
                if (LevelName[i] == L'h'){strcat(MapName,"h");}
                if (LevelName[i] == L'i'){strcat(MapName,"i");}
                if (LevelName[i] == L'j'){strcat(MapName,"j");}
                if (LevelName[i] == L'k'){strcat(MapName,"k");}
                if (LevelName[i] == L'l'){strcat(MapName,"l");}
                if (LevelName[i] == L'm'){strcat(MapName,"m");}
                if (LevelName[i] == L'n'){strcat(MapName,"n");}
                if (LevelName[i] == L'o'){strcat(MapName,"o");}
                if (LevelName[i] == L'p'){strcat(MapName,"p");}
                if (LevelName[i] == L'q'){strcat(MapName,"q");}
                if (LevelName[i] == L'r'){strcat(MapName,"r");}
                if (LevelName[i] == L's'){strcat(MapName,"s");}
                if (LevelName[i] == L't'){strcat(MapName,"t");}
                if (LevelName[i] == L'u'){strcat(MapName,"u");}
                if (LevelName[i] == L'v'){strcat(MapName,"v");}
                if (LevelName[i] == L'w'){strcat(MapName,"w");}
                if (LevelName[i] == L'x'){strcat(MapName,"x");}
                if (LevelName[i] == L'y'){strcat(MapName,"y");}
                if (LevelName[i] == L'z'){strcat(MapName,"z");}

                if (LevelName[i] == L'1'){strcat(MapName,"1");}
                if (LevelName[i] == L'2'){strcat(MapName,"2");}
                if (LevelName[i] == L'3'){strcat(MapName,"3");}
                if (LevelName[i] == L'4'){strcat(MapName,"4");}
                if (LevelName[i] == L'5'){strcat(MapName,"5");}
                if (LevelName[i] == L'6'){strcat(MapName,"6");}
                if (LevelName[i] == L'7'){strcat(MapName,"7");}
                if (LevelName[i] == L'8'){strcat(MapName,"8");}
                if (LevelName[i] == L'9'){strcat(MapName,"9");}
                if (LevelName[i] == L'0'){strcat(MapName,"0");}

                if (LevelName[i] == L'!'){strcat(MapName,"!");}
                if (LevelName[i] == L'@'){strcat(MapName,"@");}
                if (LevelName[i] == L'#'){strcat(MapName,"#");}
                if (LevelName[i] == L'$'){strcat(MapName,"$");}
                if (LevelName[i] == L'%'){strcat(MapName,"%");}
                if (LevelName[i] == L'^'){strcat(MapName,"^");}
                if (LevelName[i] == L'&'){strcat(MapName,"&");}
                if (LevelName[i] == L'*'){strcat(MapName,"*");}
                if (LevelName[i] == L'('){strcat(MapName,"(");}
                if (LevelName[i] == L')'){strcat(MapName,")");}
            }
        }
        else {
            // Hacky Fix 
            strcat(MapName,FormatText("Level%i" , MysticEngine.LevelId));
        }

        strcat(MapPath,MapName);
        strcat(MapPath,"/");
        strcat(MapPath,MapName);
        strcat(MapPath,".mpak2");

        if (MysticEngine.ME1Compatable){
            for (int i = 0; i <= 512*10;i++){
                WorldData.Map += L'0';
            }
            WorldData.Map = LoadFile(MapPath);
        }
        else {
            WorldData.Map[0] = L'\0';
            WorldData.Map = LoadFile(MapPath);
        }

        ScanMapDimensions();

        WorldData.MapName[0] = '\0';

        strcat(WorldData.MapName,MapName);


        wcout << "MysticEngine: Loaded - " << LevelName << "\n";
        wcout << "MysticEngine: Level Width - " << WorldData.Width << "\n"; 
        wcout << "MysticEngine: Level Height - " << WorldData.Height << "\n"; 

        if (WorldData.Height == 0){
            wcout << "MysticEngine: Current Level Seems Broken :(" << "\n"; 
        }
    
    }
    else {
        wcout << "MysticEngine: Level Config End Reached" << "\n";
        wcout << "      MysticEngine" << "\n";
        wcout << "Software By PixelPhobicGames - 2021" << "\n";
        exit(0);
    }

    ScanPlayerSpawn();
    CustomLoadBehavior();
}

char WstringToChar(wchar_t Data){
    switch (Data){
        case L'a':
            return 'a';
            break;
        case L'b':
            return 'b';
            break;
        case L'c':
            return 'c';
            break;
        case L'd':
            return 'd';
            break;
        case L'e':
            return 'e';
            break;
        case L'f':
            return 'f';
            break;
        case L'g':
            return 'g';
            break;
        case L'h':
            return 'h';
            break;
        case L'i':
            return 'i';
            break;
        case L'j':
            return 'j';
            break;
        case L'k':
            return 'k';
            break;
        case L'l':
            return 'l';
            break;
        case L'm':
            return 'm';
            break;
        case L'n':
            return 'n';
            break;
        case L'o':
            return 'o';
            break;
        case L'p':
            return 'p';
            break;
        case L'q':
            return 'q';
            break;
        case L'r':
            return 'r';
            break;
        case L's':
            return 's';
            break;
        case L't':
            return 't';
            break;
        case L'u':
            return 'u';
            break;
        case L'v':
            return 'v';
            break;
        case L'w':
            return 'w';
            break;
        case L'x':
            return 'x';
            break;
        case L'y':
            return 'y';
            break;
        case L'z':
            return 'z';
            break;

        case L'A':
            return 'A';
            break;
        case L'B':
            return 'B';
            break;
        case L'C':
            return 'C';
            break;
        case L'D':
            return 'D';
            break;
        case L'E':
            return 'E';
            break;
        case L'F':
            return 'F';
            break;
        case L'G':
            return 'G';
            break;
        case L'H':
            return 'H';
            break;
        case L'I':
            return 'I';
            break;
        case L'J':
            return 'J';
            break;
        case L'K':
            return 'K';
            break;
        case L'L':
            return 'L';
            break;
        case L'M':
            return 'M';
            break;
        case L'N':
            return 'N';
            break;
        case L'O':
            return 'O';
            break;
        case L'P':
            return 'P';
            break;
        case L'Q':
            return 'Q';
            break;
        case L'R':
            return 'R';
            break;
        case L'S':
            return 'S';
            break;
        case L'T':
            return 'T';
            break;
        case L'U':
            return 'U';
            break;
        case L'V':
            return 'V';
            break;
        case L'W':
            return 'W';
            break;
        case L'X':
            return 'X';
            break;
        case L'Y':
            return 'Y';
            break;
        case L'Z':
            return 'Z';
            break;

        case L' ':
            return ' ';
            break;

            

        default:
            return ' ';
            break;
    }
}

void ScanFps(){
    wstring Data;
    Data = LoadFile("MysticEngine/Global/Config/Fps.mconf");

    int Fps = 0;
    int NumbPlace = 0;

    for (int i = Data.size() ; i >= 0 ; i--){     
        switch (Data[i])
        {
            case L'1':
                if(NumbPlace == 0){Fps += 1;} 
                if(NumbPlace == 1){Fps += 10;} 
                if(NumbPlace == 2){Fps += 100;} 
                NumbPlace ++;
                break;
            case L'2':
                if(NumbPlace == 0){Fps += 2;} 
                if(NumbPlace == 1){Fps += 20;} 
                if(NumbPlace == 2){Fps += 200;} 
                NumbPlace ++;
                break;
            case L'3':
                if(NumbPlace == 0){Fps += 3;} 
                if(NumbPlace == 1){Fps += 30;} 
                if(NumbPlace == 2){Fps += 300;} 
                NumbPlace ++;
                break;
            case L'4':
                if(NumbPlace == 0){Fps += 4;} 
                if(NumbPlace == 1){Fps += 40;} 
                if(NumbPlace == 2){Fps += 400;} 
                NumbPlace ++;
                break;
            case L'5':
                if(NumbPlace == 0){Fps += 5;} 
                if(NumbPlace == 1){Fps += 50;} 
                if(NumbPlace == 2){Fps += 500;}
                NumbPlace ++; 
                break;
            case L'6':
                if(NumbPlace == 0){Fps += 6;} 
                if(NumbPlace == 1){Fps += 60;} 
                if(NumbPlace == 2){Fps += 600;} 
                NumbPlace ++;
                break;
            case L'7':
                if(NumbPlace == 0){Fps += 7;} 
                if(NumbPlace == 1){Fps += 70;} 
                if(NumbPlace == 2){Fps += 700;} 
                NumbPlace ++;
                break;
            case L'8':
                if(NumbPlace == 0){Fps += 8;} 
                if(NumbPlace == 1){Fps += 80;} 
                if(NumbPlace == 2){Fps += 800;} 
                NumbPlace ++;
                break;
            case L'9':
                if(NumbPlace == 0){Fps += 9;} 
                if(NumbPlace == 1){Fps += 90;} 
                if(NumbPlace == 2){Fps += 900;} 
                NumbPlace ++;
                break;
            case L'0':
                NumbPlace ++;
                break;
            
            default:
                break;
        }
    }
    SetTargetFPS(Fps);
    MysticEngine.FpsScaler = Fps / 60;
}

static void MysticEngineInit(){

    MysticEngine.WindowScale = 1.0f;
    MysticEngine.MapDataConfig = LoadFile("GameData/Config/MasterLevelConfig.mconf");
    MysticEngine.LevelId = -1;
    MysticEngine.GameEnd = false;
    MysticEngine.EditMode = false;
    MysticEngine.EditCursorX = 80;
    MysticEngine.EditCursorY = 80;
    MysticEngineCamera.X = 0;
    MysticEngine.BackgroundXScroll = 0;
    MysticEngine.EditorTile = L'0';
    MysticPlayer.Width = 0;
    MysticPlayer.Height = 0;
    MysticPlayer.AnimationTicker = 0;
    MysticPlayer.Visable = true;
    MysticPlayer.MovementEnabled = true;
    MysticPlayer.ProjectileRotation = 0;
    MysticPlayer.ProjectileTrigger = false;
    MysticPlayer.ProjectileX = 0;
    MysticPlayer.ProjectileY = 0;
    MysticPlayer.ProjectileDirection = 1;

    MysticEngine.FirstLoad = true;

    wcout << MysticEngine.MapDataConfig << "\n";


    if (LoadConfigurationFile("MysticEngine/Global/Config/Compatability.mconf") == L'1'){
        MysticEngine.ME1Compatable = true;
    }
    else {
        MysticEngine.ME1Compatable = false;
    }

    if (LoadConfigurationFile("MysticEngine/Window/WindowStyle.mconf") == L'0'){
        SetWindowState(FLAG_WINDOW_UNDECORATED);
    }

    if (LoadConfigurationFile("MysticEngine/Global/Config/EditMode.mconf") == L'1'){
        MysticEngine.EditMode = true;
    }
    if (LoadConfigurationFile("MysticEngine/Global/Config/Debug.mconf") == L'1'){
        MysticEngine.Debug = true;
    }
    else {
        MysticEngine.Debug = false;
    }

    switch (LoadConfigurationFile("MysticEngine/Global/Config/Resolution.mconf")){
        case L'1':
            MysticEngine.XResolution = 300;
            MysticEngine.YResolution = 200;
            break;
        case L'2':
            MysticEngine.XResolution = 640;
            MysticEngine.YResolution = 480;
            break;
        case L'3':
            MysticEngine.XResolution = 500;
            MysticEngine.YResolution = 500;
            break;
        case L'4':
            MysticEngine.XResolution = 800;
            MysticEngine.YResolution = 600;
            break;
        case L'5':
            MysticEngine.XResolution = 660;
            MysticEngine.YResolution = 320;
            break;
        case L'6':
            MysticEngine.XResolution = 1280;
            MysticEngine.YResolution = 720;
            break;
        case L'7':
            MysticEngine.XResolution = 1380;
            MysticEngine.YResolution = 720;
            break;
        case L'8':
            MysticEngine.XResolution = 1920;
            MysticEngine.YResolution = 1080;
            break;
        case L'9':
            MysticEngine.XResolution = 3840;
            MysticEngine.YResolution = 2160;
            break;
        case L'%':
            MysticEngine.XResolution = 1024;
            MysticEngine.YResolution = 800;
            break;

    }

    MysticPlayer.JumpTrigger = false;
    MysticPlayer.JumpCounter = 20;
    
    TransitionLevel();      

    InitWindow(MysticEngine.XResolution * MysticEngine.WindowScale, MysticEngine.YResolution * MysticEngine.WindowScale, "Seedling Boy Needs A New Home! ( Demo )" );
    InitAudioDevice();

    Image Icon = LoadImage("MysticEngine/Icon/Icon.png");
    SetWindowIcon(Icon);   

    if (MysticEngine.ME1Compatable){
        SetWindowTitle("MysticEngine2: M1BWC (Classic) Mode ");   
    }

    GlobalFont = LoadFont("MysticEngine/Font/Font.ttf");

    ScanFps();
    ScanPlayerAnimationSpeed();
    ScanPlayerAnimationFrames();
    LoadTiles();
    ScanPlayerDimesions();
    ScanCameraSpeed();
    LoadSoundEffects();

    MysticPlayer.X = (MysticEngine.XResolution / 2) - 20;
    MysticPlayer.Y = (MysticEngine.YResolution / 2) + MysticPlayer.YOffset;

    if (MysticEngine.ME1Compatable){
        MysticEngine.XResolution = 640;
        MysticEngine.YResolution = 400;
        SetWindowSize(MysticEngine.XResolution , MysticEngine.YResolution);
    }
    PlayMusicStream(WorldData.Theme);

    PlayFadeEffect();
}

void SoundEffectsUpdate(){
    UpdateMusicStream(MysticPlayer.JumpSound);
    UpdateMusicStream(MysticPlayer.DeathSound);
}

void CoreUpdate(){
    SoundEffectsUpdate();

    if (MysticEngine.LevelType == 1){

        if (MysticPlayer.Visable){

            switch (MysticEngineCamera.Direction)
            {
                case 1:
                    if (MysticPlayer.AnimationTicker >= 0 && MysticPlayer.AnimationTicker <= 20){
                        DrawTextureEx(MysticPlayer.AnimationFrame6 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                    }
                    if (MysticPlayer.AnimationTicker >= 20 && MysticPlayer.AnimationTicker <= 40){
                        DrawTextureEx(MysticPlayer.AnimationFrame7 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                    }
                    if (MysticPlayer.AnimationTicker >= 40 && MysticPlayer.AnimationTicker <= 60){
                        DrawTextureEx(MysticPlayer.AnimationFrame8 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                    }
                    if (MysticPlayer.AnimationTicker >= 60 && MysticPlayer.AnimationTicker <= 80){
                        DrawTextureEx(MysticPlayer.AnimationFrame9 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                    }
                    if (MysticPlayer.AnimationTicker >= 80 && MysticPlayer.AnimationTicker <= 100){
                        DrawTextureEx(MysticPlayer.AnimationFrame10 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                    }
                    break;
                case 2:
                    if (IsKeyDown(KEY_RIGHT)){
                        if (MysticPlayer.AnimationTicker >= 0 && MysticPlayer.AnimationTicker <= 20){
                            DrawTextureEx(MysticPlayer.AnimationFrame16 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                        }
                        if (MysticPlayer.AnimationTicker >= 20 && MysticPlayer.AnimationTicker <= 40){
                            DrawTextureEx(MysticPlayer.AnimationFrame17 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                        }
                        if (MysticPlayer.AnimationTicker >= 40 && MysticPlayer.AnimationTicker <= 60){
                            DrawTextureEx(MysticPlayer.AnimationFrame18 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                        }
                        if (MysticPlayer.AnimationTicker >= 60 && MysticPlayer.AnimationTicker <= 80){
                            DrawTextureEx(MysticPlayer.AnimationFrame19 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                        }
                        if (MysticPlayer.AnimationTicker >= 80 && MysticPlayer.AnimationTicker <= 100){
                            DrawTextureEx(MysticPlayer.AnimationFrame20 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                        }
                    }
                    else {
                        DrawTextureEx(MysticPlayer.AnimationFrame16 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                    }
                    break;
                case 3:
                    if (MysticPlayer.AnimationTicker >= 0 && MysticPlayer.AnimationTicker <= 20){
                        DrawTextureEx(MysticPlayer.AnimationFrame1 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                    }
                    if (MysticPlayer.AnimationTicker >= 20 && MysticPlayer.AnimationTicker <= 40){
                        DrawTextureEx(MysticPlayer.AnimationFrame2 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                    }
                    if (MysticPlayer.AnimationTicker >= 40 && MysticPlayer.AnimationTicker <= 60){
                        DrawTextureEx(MysticPlayer.AnimationFrame3 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                    }
                    if (MysticPlayer.AnimationTicker >= 60 && MysticPlayer.AnimationTicker <= 80){
                        DrawTextureEx(MysticPlayer.AnimationFrame4 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                    }
                    if (MysticPlayer.AnimationTicker >= 80 && MysticPlayer.AnimationTicker <= 100){
                        DrawTextureEx(MysticPlayer.AnimationFrame5 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                    }
                    break;
                case 4:

                    if (IsKeyDown(KEY_LEFT)){
                        if (MysticPlayer.AnimationTicker >= 0 && MysticPlayer.AnimationTicker <= 20){
                            DrawTextureEx(MysticPlayer.AnimationFrame11 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                        }
                        if (MysticPlayer.AnimationTicker >= 20 && MysticPlayer.AnimationTicker <= 40){
                            DrawTextureEx(MysticPlayer.AnimationFrame12 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                        }
                        if (MysticPlayer.AnimationTicker >= 40 && MysticPlayer.AnimationTicker <= 60){
                            DrawTextureEx(MysticPlayer.AnimationFrame13 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                        }
                        if (MysticPlayer.AnimationTicker >= 60 && MysticPlayer.AnimationTicker <= 80){
                            DrawTextureEx(MysticPlayer.AnimationFrame14 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                        }
                        if (MysticPlayer.AnimationTicker >= 80 && MysticPlayer.AnimationTicker <= 100){
                            DrawTextureEx(MysticPlayer.AnimationFrame15 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                        }
                    }
                    else{
                        DrawTextureEx(MysticPlayer.AnimationFrame11 , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                    }
                    
                    break;
            }
        }

        if(MysticPlayer.IsGrounded){
            DrawTextureEx(MysticPlayer.ShadowTexture , {(MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
        }



        if (MysticPlayer.MovementEnabled){
            for(int x = 0; x <= MysticPlayer.Width / 20 ; x++){
                for(int y = 0; y <= MysticPlayer.Height / 20 ; y++){
                    if (ReadTile((MysticEngineCamera.X + MysticPlayer.X + x * 20) / 20, (MysticEngineCamera.Y + MysticPlayer.Y + y * 20) / 20) == L'%'){
                        PlayFadeEffect();
                        MysticPlayer.X = (MysticEngine.XResolution / 2) - 20;
                        MysticPlayer.Y = (MysticEngine.YResolution / 2) + MysticPlayer.YOffset;
                        MysticEngineCamera.X = 0;
                        MysticEngineCamera.Y = 0;
                        MysticEngine.BackgroundXScroll = 0;
                        StopMusicStream(WorldData.Theme);
                        TransitionLevel();      
                        LoadTiles();
                        PlayMusicStream(WorldData.Theme); 
                        
                    }
                }
            }

            if (MysticEngineCamera.Y % 2 == 1){
                MysticEngineCamera.Y --;
            }

            if (!MysticPlayer.JumpTrigger){
                if (ReadTile((MysticEngineCamera.X + MysticPlayer.X) / 20, (MysticEngineCamera.Y + MysticPlayer.Y + 20) / 20) != L'0'){
                    if (MysticEngineCamera.Y % 20 == 0){
                        MysticEngineCamera.Y --;
                    }
                }
            }
            if (MysticEngineCamera.Y % 2 == 1){
                MysticEngineCamera.Y --;
            }


            for (int i = 0 ; i <= WorldData.Height + 20 ; i += 20){
                if (MysticEngineCamera.Y == i + 2){
                    MysticEngineCamera.Y = i;
                }
            }

            if (IsKeyDown(KEY_LEFT) == false && IsKeyDown(KEY_RIGHT) == false && IsKeyDown(KEY_UP) == false && IsKeyDown(KEY_DOWN) == false){
                if (MysticEngineCamera.XAcceleration != 0){
                    MysticEngineCamera.XAcceleration --;
                }
            }
            else{
                if (MysticEngineCamera.XAcceleration != 30){
                    MysticEngineCamera.XAcceleration ++;
                }
            }

            if (MysticEngineCamera.X >= 0){
                if (IsKeyDown(KEY_LEFT)){
                    if (WorldData.BackgroundEnabled){
                        if (WorldData.BackgroundScrollEnabled){
                            MysticEngine.BackgroundXScroll += MysticEngine.BackgroundXScrollSpeed;
                        }
                    }
                    MysticEngineCamera.X -= MysticEngineCamera.Speed;
                    MysticEngineCamera.Direction = 4;
                }
                if (MysticEngineCamera.Direction == 4)MysticEngineCamera.X -= MysticEngineCamera.XAcceleration / 3;
            }
            else {
                MysticEngineCamera.X = 0;
            }
            if (MysticEngineCamera.X <= WorldData.Width * 20){
                if (IsKeyDown(KEY_RIGHT)){
                    if (WorldData.BackgroundEnabled){
                        if (WorldData.BackgroundScrollEnabled){
                            MysticEngine.BackgroundXScroll -= MysticEngine.BackgroundXScrollSpeed;
                        }
                    }
                    MysticEngineCamera.X += MysticEngineCamera.Speed;
                    MysticEngineCamera.Direction = 2;
                }
                if (MysticEngineCamera.Direction == 2)MysticEngineCamera.X += MysticEngineCamera.XAcceleration / 3;
            }

            if (MysticEngineCamera.Y >= 0){
                if (IsKeyDown(KEY_UP) && !MysticPlayer.JumpTrigger && MysticPlayer.IsGrounded){
                    MysticPlayer.JumpTrigger = true;
                    MysticPlayer.IsGrounded = false;

                    PlayMusicStream(MysticPlayer.JumpSound);
                }

                if (MysticPlayer.JumpTrigger){
                    MysticEngineCamera.Direction = 1;
                    if (MysticPlayer.JumpCounter >= -10) {

                        MysticEngineCamera.Y -= (MysticPlayer.JumpCounter * abs(MysticPlayer.JumpCounter)) * .05;

                        MysticPlayer.JumpCounter -= 1;
                    }
                    else {
                        MysticEngineCamera.Direction = 3;
                        MysticPlayer.JumpCounter = 20;
                        MysticPlayer.JumpTrigger = false;
                        StopMusicStream(MysticPlayer.JumpSound);
                    }
                }
            }
            else {
                MysticEngineCamera.Y = 0;
            }
            if (MysticEngineCamera.Y <= WorldData.Height * 20){
                if (MysticPlayer.JumpTrigger){
                    if (ReadTile((MysticEngineCamera.X + MysticPlayer.X) / 20, (MysticEngineCamera.Y + MysticPlayer.Y - (MysticPlayer.Height-20)) / 20) != L'0'){
                        MysticEngineCamera.Y += 4;
                        MysticEngineCamera.Y += (MysticPlayer.JumpCounter * abs(MysticPlayer.JumpCounter)) * .05;
                    }
                }
                if (MysticEngineCamera.Direction == 4){
                    if (ReadTile((MysticEngineCamera.X + MysticPlayer.X + 20) / 20, (MysticEngineCamera.Y + MysticPlayer.Y + 20) / 20) == L'0' ){
                        if(!MysticPlayer.JumpTrigger){
                            MysticEngineCamera.Y += 8;
                            MysticEngineCamera.Direction = 3;
                            
                        }
                    }
                    for (int i = 0 ; i <= MysticPlayer.Height / 20; i ++){
                        if (ReadTile((MysticEngineCamera.X + MysticPlayer.X + 10 - MysticPlayer.Width/2) / 20, (MysticEngineCamera.Y + MysticPlayer.Y - i * 20) / 20) != L'0' && ReadTile((MysticEngineCamera.X + MysticPlayer.X + 10 - MysticPlayer.Width/2) / 20, (MysticEngineCamera.Y + MysticPlayer.Y - i * 20) / 20) != L'%'){
                            MysticEngineCamera.X += MysticEngineCamera.Speed;
                            MysticEngineCamera.X += MysticEngineCamera.XAcceleration / 3;
                        }
                    }
                }
                else {

                    if (ReadTile((MysticEngineCamera.X + MysticPlayer.X) / 20, (MysticEngineCamera.Y + MysticPlayer.Y + 20) / 20) == L'0'){
                        if(!MysticPlayer.JumpTrigger){
                            MysticEngineCamera.Y += 8;
                            MysticEngineCamera.Direction = 3;
                            MysticPlayer.IsGrounded = false;
                        }
                    }
                    else {
                        MysticPlayer.IsGrounded = true;
                    }
        
                    if (MysticEngineCamera.Direction == 2){
                        for (int i = 0 ; i <= MysticPlayer.Height / 20; i ++){
                            if (ReadTile((MysticEngineCamera.X + MysticPlayer.X + 10 + MysticPlayer.Width/2) / 20, (MysticEngineCamera.Y + MysticPlayer.Y - i*20) / 20) != L'0' && ReadTile((MysticEngineCamera.X + MysticPlayer.X + 10 + MysticPlayer.Width/2) / 20, (MysticEngineCamera.Y + MysticPlayer.Y - i*20) / 20) != L'%' ){
                                MysticEngineCamera.X -= MysticEngineCamera.Speed;
                                MysticEngineCamera.X -= MysticEngineCamera.XAcceleration / 3;
                            }
                        }

                    }
                    
                }
                if (MysticEngineCamera.Y % 2 == 1){
                    MysticEngineCamera.Y --;
                }

                for (int i = 0 ; i <= WorldData.Height + 20 ; i += 20){
                    if (MysticEngineCamera.Y == i + 2){
                        MysticEngineCamera.Y = i;
                    }
                }
            }

            if (MysticEngine.Debug){
                DrawText("Debug Enabled" , 50 , MysticEngine.YResolution - 50 , 15 , GREEN);
                DrawText(FormatText("Camera X Position:%i", MysticEngineCamera.X) , 20 , 20 , 10, YELLOW);
                DrawText(FormatText("Camera Y Position:%i", MysticEngineCamera.Y) , 20 , 40 , 10, YELLOW);
                DrawText(FormatText("Camera Direction:%i", MysticEngineCamera.Direction) , 20 , 60 , 10, YELLOW);
                DrawText(FormatText("Camera X Acc:%i", MysticEngineCamera.XAcceleration) , 20 , 80 , 10, YELLOW);
                DrawText(FormatText("Camera Y Acc:%i", MysticEngineCamera.YAcceleration) , 20 , 100 , 10, YELLOW);
                DrawRectangle((MysticPlayer.X + 10 - MysticPlayer.Width/2)* MysticEngine.WindowScale, ((MysticPlayer.Y - (MysticPlayer.Height - 20) - 2) )* MysticEngine.WindowScale, MysticPlayer.Width * MysticEngine.WindowScale , MysticPlayer.Height * MysticEngine.WindowScale, PURPLE);
                DrawRectangle((MysticPlayer.X)* MysticEngine.WindowScale, (MysticPlayer.Y - 2 )* MysticEngine.WindowScale, 20 * MysticEngine.WindowScale , 20 * MysticEngine.WindowScale, RED);
            }
        }

        if (MysticEngine.BackgroundXScroll >= 0){
            MysticEngine.BackgroundXScroll = 0;
        }

        if (MysticPlayer.AnimationTicker <= 100){
            MysticPlayer.AnimationTicker += MysticPlayer.AnimationSpeed;
        }
        else{
            MysticPlayer.AnimationTicker = 0;
            
        }

        for(int x = 0; x <= MysticPlayer.Width / 20 ; x++){
            if (ReadTile((MysticEngineCamera.X + MysticPlayer.X + x * 20) / 20, (MysticEngineCamera.Y + MysticPlayer.Y + 20) / 20) == L'X'){

                PlayFadeEffect();

                MysticPlayer.X = (MysticEngine.XResolution / 2) - 20;
                MysticPlayer.Y = (MysticEngine.YResolution / 2) + MysticPlayer.YOffset;
                MysticEngineCamera.X = 0;
                MysticEngineCamera.Y = 0;

                MysticEngine.BackgroundXScroll = 0;

                ScanPlayerSpawn();    

            }
        }

    }

    if (MysticEngine.LevelType != 1){
        if (IsKeyPressed(KEY_SPACE)){
            MysticPlayer.X = (MysticEngine.XResolution / 2) - 20;
            MysticPlayer.Y = (MysticEngine.YResolution / 2) + MysticPlayer.YOffset;
            MysticEngineCamera.X = 0;
            MysticEngineCamera.Y = 0;
            StopMusicStream(WorldData.Theme);
            TransitionLevel();      
            LoadTiles();
            PlayMusicStream(WorldData.Theme);
        }
    }
}

void CustomLoadBehavior(){
    // All Custom Code Goes Here
    switch (MysticEngine.LevelId)
    {
        case 0:
            CustomVar1 = 0;
            break;

        case 1:
            MysticPlayer.Visable = false;
            MysticPlayer.MovementEnabled = false;

            CustomObjectFrame1 = LoadTexture("GameData/Level1/Custom/Frame1.png"); 
            CustomObjectFrame2 = LoadTexture("GameData/Level1/Custom/Frame2.png"); 
            CustomObjectFrame3 = LoadTexture("GameData/Level1/Custom/Frame3.png"); 

            CustomVar1 = 0;
            CustomVar2 = 0;

            break;

        case 12:
            MysticPlayer.Visable = false;
            MysticPlayer.MovementEnabled = false;

            CustomVar1 = 1;
            CustomVar2 = 0;
            break;

        default:
            break;
    }
}

void CustomLevelBehavior(){

    // All Custom Code Goes Here
    switch (MysticEngine.LevelId)
    {
        case 0:
            DrawTextEx(GlobalFont,"Options", {20* MysticEngine.WindowScale,580* MysticEngine.WindowScale}, 10* MysticEngine.WindowScale, 2, WHITE);

            DrawTextEx(GlobalFont,"Press Space", { GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"Press Space", 10* MysticEngine.WindowScale , 2).x / 2 , 580* MysticEngine.WindowScale}, 10* MysticEngine.WindowScale, 2, WHITE);

            if (GetCollision(20* MysticEngine.WindowScale,580* MysticEngine.WindowScale , 80* MysticEngine.WindowScale , 40* MysticEngine.WindowScale , GetMouseX(), GetMouseY() , 5* MysticEngine.WindowScale , 5* MysticEngine.WindowScale) && IsMouseButtonPressed(0)){
                CustomVar1 = 1;
            }

            if (CustomVar1 == 1){
                DrawRectangle(0 , 0 , GetScreenWidth() , GetScreenHeight() , ProGray);

                DrawTextEx(GlobalFont,"MysticEngine 2", { GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"MysticEngine 2", 20* MysticEngine.WindowScale , 2).x / 2 , 30* MysticEngine.WindowScale}, 20* MysticEngine.WindowScale, 2, WHITE);
                DrawTextEx(GlobalFont,"Options", { GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"Options", 10* MysticEngine.WindowScale , 2).x / 2 , 80* MysticEngine.WindowScale}, 10* MysticEngine.WindowScale, 2, WHITE);

                DrawTextEx(GlobalFont,"[ Increase Resolution ]", { GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"[ Increase Resolution ]", 10* MysticEngine.WindowScale , 2).x / 2 , 160* MysticEngine.WindowScale}, 10* MysticEngine.WindowScale, 2, BLUE);
                DrawTextEx(GlobalFont,"[ Decrease Resolution ]", { GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"[ Decrease Resolution ]", 10* MysticEngine.WindowScale , 2).x / 2 , 190* MysticEngine.WindowScale}, 10* MysticEngine.WindowScale, 2, BLUE);

                DrawTextEx(GlobalFont,"[ Mute Audio ]", { GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"[ Mute Audio ]", 10* MysticEngine.WindowScale , 2).x / 2 , 220* MysticEngine.WindowScale}, 10* MysticEngine.WindowScale, 2, GREEN);

                DrawTextEx(GlobalFont,"Code By Liquid", { GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"Code By Liquid", 10* MysticEngine.WindowScale , 2).x / 2 , 500* MysticEngine.WindowScale}, 10* MysticEngine.WindowScale, 2, GREEN);
                
                DrawTextEx(GlobalFont,"Back", {20* MysticEngine.WindowScale,50* MysticEngine.WindowScale}, 10* MysticEngine.WindowScale, 2, WHITE);

                if (GetCollision( GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"[ Increase Resolution ]", 10* MysticEngine.WindowScale , 2).x / 2 , 160* MysticEngine.WindowScale , 160* MysticEngine.WindowScale , 20* MysticEngine.WindowScale , GetMouseX(), GetMouseY() , 5* MysticEngine.WindowScale , 5* MysticEngine.WindowScale) && IsMouseButtonPressed(0)){
                    MysticEngine.WindowScale += .5f;
                    SetWindowSize(MysticEngine.XResolution * MysticEngine.WindowScale, MysticEngine.YResolution * MysticEngine.WindowScale);
                }

                if (GetCollision( GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"[ Decrease Resolution ]", 10* MysticEngine.WindowScale , 2).x / 2 , 190* MysticEngine.WindowScale , 160* MysticEngine.WindowScale , 20* MysticEngine.WindowScale , GetMouseX(), GetMouseY() , 5* MysticEngine.WindowScale , 5* MysticEngine.WindowScale) && IsMouseButtonPressed(0)){
                    MysticEngine.WindowScale -= .5f;
                    SetWindowSize(MysticEngine.XResolution * MysticEngine.WindowScale, MysticEngine.YResolution * MysticEngine.WindowScale);
                }

                if (GetCollision( GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"[ Mute Audio ]", 10* MysticEngine.WindowScale , 2).x / 2 , 220* MysticEngine.WindowScale , 160* MysticEngine.WindowScale , 20* MysticEngine.WindowScale , GetMouseX(), GetMouseY() , 5* MysticEngine.WindowScale , 5* MysticEngine.WindowScale) && IsMouseButtonPressed(0)){
                    SetMasterVolume(0.0);
                }


                if (GetCollision( GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"[ Increase Resolution ]", 10* MysticEngine.WindowScale , 2).x / 2 , 160* MysticEngine.WindowScale , 160* MysticEngine.WindowScale , 20* MysticEngine.WindowScale , GetMouseX(), GetMouseY() , 5* MysticEngine.WindowScale , 5* MysticEngine.WindowScale)){
                   DrawTextEx(GlobalFont,"[ Increase Resolution ]", { GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"[ Increase Resolution ]", 10* MysticEngine.WindowScale , 2).x / 2 , 160* MysticEngine.WindowScale}, 10* MysticEngine.WindowScale, 2, DARKBLUE);
                }

                if (GetCollision( GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"[ Decrease Resolution ]", 10* MysticEngine.WindowScale , 2).x / 2 , 190* MysticEngine.WindowScale , 160* MysticEngine.WindowScale , 20* MysticEngine.WindowScale , GetMouseX(), GetMouseY() , 5* MysticEngine.WindowScale , 5* MysticEngine.WindowScale)){
                     DrawTextEx(GlobalFont,"[ Decrease Resolution ]", { GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"[ Decrease Resolution ]", 10* MysticEngine.WindowScale , 2).x / 2 , 190* MysticEngine.WindowScale}, 10* MysticEngine.WindowScale, 2, DARKBLUE);
                }

                if (GetCollision( GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"[ Mute Audio ]", 10* MysticEngine.WindowScale , 2).x / 2 , 220* MysticEngine.WindowScale , 160* MysticEngine.WindowScale , 20* MysticEngine.WindowScale , GetMouseX(), GetMouseY() , 5* MysticEngine.WindowScale , 5* MysticEngine.WindowScale)){
                    DrawTextEx(GlobalFont,"[ Mute Audio ]", { GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"[ Mute Audio ]", 10* MysticEngine.WindowScale , 2).x / 2 , 220* MysticEngine.WindowScale}, 10* MysticEngine.WindowScale, 2, DARKGREEN);
                }



                if (GetCollision(20* MysticEngine.WindowScale,50* MysticEngine.WindowScale , 80* MysticEngine.WindowScale , 40* MysticEngine.WindowScale , GetMouseX(), GetMouseY() , 5* MysticEngine.WindowScale , 5* MysticEngine.WindowScale) && IsMouseButtonPressed(0)){
                    CustomVar1 = 0;
                }
            
            }


            break;

        case 1:
            if (!MysticPlayer.MovementEnabled){
                if (MysticPlayer.AnimationTicker >= 0 && MysticPlayer.AnimationTicker <= 33)DrawTextureEx(CustomObjectFrame1 , {350 * MysticEngine.WindowScale,446* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                if (MysticPlayer.AnimationTicker >= 33 && MysticPlayer.AnimationTicker <= 66)DrawTextureEx(CustomObjectFrame2 , {350* MysticEngine.WindowScale,446* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                if (MysticPlayer.AnimationTicker >= 66 && MysticPlayer.AnimationTicker <= 100)DrawTextureEx(CustomObjectFrame3 , {350* MysticEngine.WindowScale,446* MysticEngine.WindowScale} , 0 ,MysticEngine.WindowScale, WHITE);
                if (MysticPlayer.AnimationTicker >= 50 && CustomVar1 == 0)DrawTextEx(GlobalFont,"Press A to Wake Up", { GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"Press A to Wake Up", 10* MysticEngine.WindowScale , 2).x / 2 , 580* MysticEngine.WindowScale}, 10* MysticEngine.WindowScale, 2, WHITE);

                if (IsKeyPressed(KEY_A)){
                    CustomVar1 ++;
                    CustomVar2 = 0;
                }

                CustomVar2 ++;

                switch (CustomVar1)
                {
                    case 1:
                        DrawTextEx(GlobalFont,TextSubtext("Oh No!  How Long Was I Asleep For?", 0, CustomVar2/7), { GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"Oh No!  How Long Was I Asleep For?", 10* MysticEngine.WindowScale , 2).x / 2 , 580* MysticEngine.WindowScale}, 10* MysticEngine.WindowScale, 2, WHITE);
                        break;
                    case 2:
                        DrawTextEx(GlobalFont,TextSubtext("Why Is Everything Snowy Now?", 0, CustomVar2/7), { GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"Why Is Everything Snowy Now?", 10* MysticEngine.WindowScale , 2).x / 2 , 580* MysticEngine.WindowScale}, 10* MysticEngine.WindowScale, 2, WHITE);
                        break;
                    case 3:
                        DrawTextEx(GlobalFont,TextSubtext("If Its Too Cold That Means I Cant Plant Myself...", 0, CustomVar2/7), { GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"If Its Too Cold That Means I Cant Plant Myself...", 10* MysticEngine.WindowScale , 2).x / 2 , 580* MysticEngine.WindowScale}, 10* MysticEngine.WindowScale, 2, WHITE);
                        break;
                    case 4:
                        DrawTextEx(GlobalFont,TextSubtext("I Have To Find a Warmer Place So I Can Plant Myself!", 0, CustomVar2/7), { GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"I Have To Find a Warmer Place So I Can Plant Myself!", 10* MysticEngine.WindowScale , 2).x / 2 , 580* MysticEngine.WindowScale}, 10* MysticEngine.WindowScale, 2, WHITE);
                        break;
                    case 5:
                        MysticPlayer.Visable = true;
                        MysticPlayer.MovementEnabled = true;
                        break;
                    
                    default:
                        break;
                }
            }



            break;

            case 12:
                if (IsKeyPressed(KEY_A)){
                    CustomVar1 ++;
                    CustomVar2 = 0;
                }

                CustomVar2 ++;

                switch (CustomVar1)
                {
                    case 1:
                        DrawTextEx(GlobalFont,TextSubtext("Where Did the Seedling Boy Go?", 0, CustomVar2/7), { GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"Where Did the Seedling Boy Go?", 10* MysticEngine.WindowScale , 2).x / 2 , 300* MysticEngine.WindowScale}, 10* MysticEngine.WindowScale, 2, WHITE);
                        break;
                    case 2:
                        DrawTextEx(GlobalFont,TextSubtext("Did He Find a Warmer Place?", 0, CustomVar2/7), { GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"Did He Find a Warmer Place?", 10* MysticEngine.WindowScale , 2).x / 2 , 300* MysticEngine.WindowScale}, 10* MysticEngine.WindowScale, 2, WHITE);
                        break;
                    case 3:
                        DrawTextEx(GlobalFont,TextSubtext("To Be Continued..", 0, CustomVar2/7), { GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"To Be Continued..", 10* MysticEngine.WindowScale , 2).x / 2 , 300* MysticEngine.WindowScale}, 10* MysticEngine.WindowScale, 2, WHITE);
                        break;
                    case 4:
                        DrawTextEx(GlobalFont,TextSubtext("SeedlingBoy ~ PixelPhobicGames", 0, CustomVar2/7), { GetScreenWidth()/ 2 - MeasureTextEx(GlobalFont ,"SeedlingBoy ~ PixelPhobicGames", 10* MysticEngine.WindowScale , 2).x / 2 , 300* MysticEngine.WindowScale}, 10* MysticEngine.WindowScale, 2, GREEN);
                        break;
                    case 5:
                        MysticEngine.LevelId = -1;

                        MysticPlayer.X = (MysticEngine.XResolution / 2) - 20;
                        MysticPlayer.Y = (MysticEngine.YResolution / 2) + MysticPlayer.YOffset;
                        MysticEngineCamera.X = 0;
                        MysticEngineCamera.Y = 0;
                        StopMusicStream(WorldData.Theme);
                        TransitionLevel();      
                        LoadTiles();
                        PlayMusicStream(WorldData.Theme);
                        break;
                    
                    default:
                        break;
                }

                break;

        default:
            break;
    }
}
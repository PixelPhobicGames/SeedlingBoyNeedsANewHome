
#include "Player.hpp"

using namespace std;

#define DEBUG

#define ProGray  CLITERAL(Color){ 33, 33, 33, 255 } 

static Texture2D CustomObjectFrame1;
static Texture2D CustomObjectFrame2;
static Texture2D CustomObjectFrame3;

static int CustomVar1 = 0;
static int CustomVar2 = 0;
static int CustomVar3 = 0;
static int CustomVar4 = 0;
static int CustomVar5 = 0;



static int R = 0;
static int G = 0;
static int B = 0;

#define FadeColor CLITERAL(Color){ R, G, B, 255 }

static int FadeDirection = 0;

static Font GlobalFont;

typedef struct CoreData
{
    float WindowScale;
    int IntScale;
    int LevelId;
    wstring MapDataConfig;
    bool GameEnd;
    bool EditMode;
    int EditCursorX;
    int EditCursorY;
    int XResolution;
    int YResolution;
    int BackgroundXScroll;
    int BackgroundXScrollSpeed;
    wchar_t EditorTile;
    bool Debug;
    bool ME1Compatable;
    int LevelType;
    bool FirstLoad;
    int FpsScaler;
    char WindowCaption;

}CoreData;

static CoreData MysticEngine;

typedef struct MysticCamera{
    int X;
    int Y;
    int XAcceleration;
    int YAcceleration;
    int Direction;
    int Speed;

}MysticCamera;

static MysticCamera MysticEngineCamera;


typedef struct MpakData
{
    int Width;
    int Height;
    wstring Map;
    int BackgroundEnabled;
    int BackgroundScrollEnabled;
    Music Theme;


    char MapName[100];
    Texture2D Background;

    Texture2D Tile0;
    Texture2D Tile1;
    Texture2D Tile2;
    Texture2D Tile3;
    Texture2D Tile4;
    Texture2D Tile5;
    Texture2D Tile6;
    Texture2D Tile7;
    Texture2D Tile8;
    Texture2D Tile9;

}MpakData;

static MpakData WorldData;

wstring LoadFile(const char *Path){
    wstring Data;
    wifstream OutFile;
    OutFile.open(Path);
    OutFile >> Data;
    return Data;
}

wstring WriteFile(const char *Path , wstring Data){
    wofstream outfile;
    outfile.open(Path);
    outfile << Data << "\n";
}


wchar_t LoadConfigurationFile(const char *Path){
    wchar_t Data;
    wifstream outfile;
    outfile.open(Path);
    outfile >> Data;
    return Data;
}

bool GetCollision(int x, int y , int w, int h, int x2 , int y2 , int w2 , int h2){
    if( y+h <= y2 )
    {
        return false;
    }

    if( y >= y2+h2 )
    {
        return false;
    }

    if( x+w <= x2 )
    {
        return false;
    }

    if( x >= x2+w2 )
    {
        return false;
    }

    return true;

}

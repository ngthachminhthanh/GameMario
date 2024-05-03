#pragma once
#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <unordered_map>

class CSprite
{
    int id;                 // Sprite ID in the sprite database

    int left;
    int top;
    int right;
    int bottom;

    ID3D10ShaderResourceView* texture; 

public:
    CSprite(int id, int left, int top, int right, int bottom, ID3D10ShaderResourceView* tex);

    void Draw(float x, float y, int alpha = 255);
};

typedef CSprite* LPSPRITE;

/*
    Manage sprite database
*/
class CSprites
{
    static CSprites* __instance;

public:
    std::unordered_map<int, LPSPRITE> sprites;
    void Add(int id, int left, int top, int right, int bottom, ID3D10ShaderResourceView* tex); 
    LPSPRITE Get(int id);
    void Clear(); 

    static CSprites* GetInstance();
};

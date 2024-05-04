#pragma once

#include <unordered_map>
#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include "Camera.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include "Scene.h"

using namespace std;

#define KEYBOARD_BUFFER_SIZE 1024

class CGame
{
    static CGame* __instance;
    HWND hWnd;                                  // Window handle

    ID3D10Device* d3dDevice = NULL;            // Direct3D device object

    IDXGISwapChain* swapChain = NULL;
    ID3D10RenderTargetView* renderTargetView = NULL;

    ID3D10Texture2D* depthStencilBuffer = NULL;
    ID3D10DepthStencilView* depthStencilView = NULL;

    ID3DX10Sprite* spriteHandler = NULL;        // Help to draw 2D image on the screen 

    LPDIRECTINPUT8 di;        // The DirectInput object         
    LPDIRECTINPUTDEVICE8 didv;        // The keyboard device 

    BYTE  keyStates[256];            // DirectInput keyboard state buffer 
    DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];        // Buffered keyboard data

    LPKEYEVENTHANDLER keyHandler;

    Camera* cam;

    int screen_width;
    int screen_height;

    unordered_map<int, LPSCENE> scenes;
    int current_scene;
    int pre_scene = -1;

    void _ParseSection_SETTINGS(string line);
    void _ParseSection_SCENES(string line);

public:
    void InitKeyboard();
    void SetKeyHandler(LPKEYEVENTHANDLER handler) { keyHandler = handler; }
    void Init(HWND hWnd);
    void Draw(float x, float y, ID3D10ShaderResourceView* texture, RECT* sourceRect, D3DXVECTOR3* center, D3DXVECTOR3* position, D3DCOLOR color);

    int IsKeyDown(int KeyCode);
    void ProcessKeyboard();

    void Load(LPCWSTR gameFile);
    LPSCENE GetCurrentScene() { return scenes[current_scene]; }
    void SwitchScene(int scene_id);
    void SwitchBackScene(int scene_id, float start_x = 0, float start_y = 0);
    void SwitchExtraScene(int scene_id, float start_x = 0, float start_y = 0, bool pipeUp = false);

    int GetScreenWidth() { return screen_width; }
    int GetScreenHeight() { return screen_height; }

    static void SweptAABB(
        float ml,            // move left 
        float mt,            // move top
        float mr,            // move right 
        float mb,            // move bottom
        float dx,            // 
        float dy,            // 
        float sl,            // static left
        float st,
        float sr,
        float sb,
        float& t,
        float& nx,
        float& ny);

    ID3D10Device* GetDirect3DDevice() { return this->d3dDevice; }
    IDXGISwapChain* GetSwapChain() { return this->swapChain; }
    ID3D10RenderTargetView* GetRenderTargetView() { return this->renderTargetView; }
    ID3D10DepthStencilView* GetDepthStencilView() { return this->depthStencilView; }
    ID3D10Texture2D* GetDepthStencilBuffer() { return this->depthStencilBuffer; }
    ID3DX10Sprite* GetSpriteHandler() { return this->spriteHandler; }

    static CGame* GetInstance();

    ~CGame();
};

#include <windows.h>

#include <ddraw.h>
//#include <d3drm.h>
#include <d3drmwin.h>
#include <mmsystem.h>	//マルチメディア系の制御（timeGetTime()で必要）

#include <math.h>

#include "nav.h"		// プレーヤーの移動のためのルーチン

#include "sound.h"		// サウンド機能(MIDI)
#include "dsound.h"		// DirectSoundを使う関数(効果音)

#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "d3drm.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

#pragma comment(lib, "dsound.lib")

extern LPDIRECTDRAW lpDirectDraw;
extern LPDIRECTDRAWCLIPPER lpDDClipper;
extern LPDIRECTDRAWSURFACE lpPrimary;
extern LPDIRECTDRAWSURFACE lpBackbuffer;
extern LPDIRECTDRAWSURFACE lpZbuffer;

extern LPDIRECT3D lpDirect3D;
extern LPDIRECT3DDEVICE lpD3DDevice;

extern LPDIRECT3DRM lpDirect3DRM;
extern LPDIRECT3DRMDEVICE lpD3DRMDevice;
extern LPDIRECT3DRMVIEWPORT lpD3DRMView;
extern LPDIRECT3DRMFRAME lpD3DRMScene;
extern LPDIRECT3DRMFRAME lpD3DRMCamera;

// ドライバ検索処理関数
GUID* D3D_GuidSearch(HWND hwnd);

// DirectDraw デバイスの列挙と選定
BOOL CALLBACK DDEnumCallback(GUID FAR* lpGUID, LPSTR lpDriverDesc, LPSTR lpDriverName, LPVOID lpContext);

// メッシュなどを作りシーンを作成します
BOOL BuildScene(void);

void ReleaseAll(void);

#include <windows.h>

#include <ddraw.h>
//#include <d3drm.h>
#include <d3drmwin.h>
#include <mmsystem.h>	//�}���`���f�B�A�n�̐���itimeGetTime()�ŕK�v�j

#include <math.h>

#include "nav.h"		// �v���[���[�̈ړ��̂��߂̃��[�`��

#include "sound.h"		// �T�E���h�@�\(MIDI)
#include "dsound.h"		// DirectSound���g���֐�(���ʉ�)

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

// �h���C�o���������֐�
GUID* D3D_GuidSearch(HWND hwnd);

// DirectDraw �f�o�C�X�̗񋓂ƑI��
BOOL CALLBACK DDEnumCallback(GUID FAR* lpGUID, LPSTR lpDriverDesc, LPSTR lpDriverName, LPVOID lpContext);

// ���b�V���Ȃǂ����V�[�����쐬���܂�
BOOL BuildScene(void);

void ReleaseAll(void);

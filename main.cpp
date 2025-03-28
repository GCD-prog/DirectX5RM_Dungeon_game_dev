
/////////////////////////////////////////////////////////////////////////////////////////////////
// �ꕔ���p����(nav.h, nav.cpp, Scene.cpp, sound.h/cpp dsound.h/cpp ) �Q�l�v���O�������Ђ̃R�[�h
// DirectX5�Q�[���v���O���~���O����  �o�Ŏ�: �C���v���X (1998/3/1)
// �W�F�[�\�� �R���u (��), Jason Kolb (����), �A�N���o�C�g (�|��)
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "dx.h"
#include <stdio.h>

#define INITGUID

#define WAIT 25

LPDIRECTDRAWSURFACE lpScreen;

/*
LPDIRECTDRAW lpDirectDraw = NULL;
LPDIRECTDRAWCLIPPER lpDDClipper = NULL;
LPDIRECTDRAWSURFACE lpPrimary = NULL;
LPDIRECTDRAWSURFACE lpBackbuffer = NULL;
LPDIRECTDRAWSURFACE lpZbuffer = NULL;

//Direct3D �֘A
LPDIRECT3D lpDirect3D = NULL;
LPDIRECT3DDEVICE lpD3DDevice = NULL;

//Direct3D RM �֘A
LPDIRECT3DRM lpDirect3DRM = NULL;
LPDIRECT3DRMDEVICE lpD3DRMDevice = NULL;
LPDIRECT3DRMVIEWPORT lpD3DRMView = NULL;
LPDIRECT3DRMFRAME lpD3DRMScene = NULL;
LPDIRECT3DRMFRAME lpD3DRMCamera = NULL;
*/

char szDevice[128], szDDDeviceName[128] = "default";

int nScore = 0;			// ���_
int nPossible = 10;		// �\�ȍō��_

void FrameCnt(void)
{
	     static int cnt;
		 static DWORD Nowtime,Prevtime;
		 static char text0[10];
		 static char Data[256];

		 HDC hdc;
		 cnt++;
		 Nowtime = timeGetTime();
		 if((Nowtime - Prevtime) >= 1000){
			 Prevtime = Nowtime;
			 wsprintf(text0,"%d fps", cnt);
			 cnt = 0;
		 }
	
		 sprintf(Data, "%s , [%s]", szDevice, szDDDeviceName);

		 // �J�����̂ݕ\������
		 lpBackbuffer->GetDC(&hdc);
		 TextOut(hdc, 0, 0, text0, strlen(text0));
		 TextOut(hdc, 200, 100, Data, strlen(Data));
		 lpBackbuffer->ReleaseDC(hdc);
}

void KeyControl(void)
{
	//��������������

	//���̃v���O�����̓��������A�����̈ʒu�ł͎g��Ȃ��B
	// �v���[���[�̈ʒu�ɍ��킹�ăJ�����̈ʒu���X�V���܂�
	//lpD3DRMCamera->AddRotation(D3DRMCOMBINE_REPLACE, 0.0f, 1.0f, 0.0f,fGetAngle());
	//lpD3DRMCamera->SetPosition(lpD3DRMScene, fGetXPos(), 1.5f, fGetZPos());
	//���̍��W�ʒu�̕ϐ��̒l���Ƃ�Ă��Ȃ�����ړ����Ȃ��̂ł́H

	//������
	if( (GetAsyncKeyState(VK_LEFT)&0x8000) || (GetAsyncKeyState('Q')&0x8000) ){
			TurnLeft();
	}

	//�E����
	if( (GetAsyncKeyState(VK_RIGHT)&0x8000) || (GetAsyncKeyState('E')&0x8000) ){
			TurnRight();
	}

	//�O�i
	if(GetAsyncKeyState('W')&0x8000){
		if(GetKeyState(VK_SHIFT) & 0x8000){		// Shift�L�[�ō�����
			RunForward();
		}else{
			StepForward();
		}
	}

	//���
	if(GetAsyncKeyState('S')&0x8000){
		if(GetKeyState(VK_SHIFT) & 0x8000){		// Shift�L�[�ō�����
			RunBackward();
		}else{
			StepBackward();
		}
	}

	//��
	if(GetAsyncKeyState('A')&0x8000){
		if(GetKeyState(VK_SHIFT) & 0x8000){		// Shift�L�[�ō�����
			SwingLeft();
		}else{
			TurnLeft();
		}
	}

	//�E
	if(GetAsyncKeyState('D')&0x8000){
		if(GetKeyState(VK_SHIFT) & 0x8000){		// Shift�L�[�ō�����
			SwingRight();
		}else{
			TurnRight();
		}
	}

	// �v���[���[�̈ʒu�ɍ��킹�ăJ�����̈ʒu���X�V���܂� �����ɔz�u lpD3DRMCamare
	lpD3DRMCamera->AddRotation(D3DRMCOMBINE_REPLACE, 0.0f, 1.0f, 0.0f,fGetAngle());
	lpD3DRMCamera->SetPosition(lpD3DRMScene, fGetXPos(), 1.5f, fGetZPos());

}

BOOL RenderFrame(void)
{

	char lpt[20];  // midi ���s�[�g
	mciSendString("status bgm mode", lpt, sizeof(lpt), NULL);
	if(strcmp(lpt, "stopped") == 0){
		mciSendString("play bgm from 0", NULL, 0, NULL);
	}

	if ( lpPrimary->IsLost() == DDERR_SURFACELOST )		lpPrimary->Restore();

		RECT Scrrc={0, 0, 640, 480};   //��ʂ̃T�C�Y

		//�b�ԂU�O�t���[�����z���Ȃ��悤�ɂ���
		static DWORD nowTime, prevTime;
		nowTime = timeGetTime();
		if( (nowTime - prevTime) < 1000 / 60 ) return 0;
		prevTime = nowTime;

		//�L�[����
		KeyControl();

		//Direct3DRM �����_�����O����
		lpD3DRMScene->Move(D3DVAL(1.0)); 
		lpD3DRMView->Clear();

		// ���݂̃V�[�����o�b�N�o�b�t�@�ōĕ`�悵�܂��B����́A
		// ���݂̃T�[�t�F�C�X��GDI�T�[�t�F�C�X�łȂ��ꍇ�̏����ł�
		// ���̏ꍇ�A�������ăV�[�����ĕ`�悷��ƁA�X�R�A��\������O��
		// �V�[����1�t���[�������߂�̂�h���܂�
		lpD3DRMView->Render(lpD3DRMScene);  // �V�[���̃����_�����O
		lpD3DRMDevice->Update();              // �f�o�C�X�i�E�B���h�E�j�̍X�V

		//FPS�l�v��
		FrameCnt();

		// Flip�֐��͎g��Ȃ� ��ʂ������
		lpPrimary->Flip(NULL, DDFLIP_WAIT);

		return TRUE;
}

//-------------------------------------------
// �h���C�o���������֐�
//-------------------------------------------
GUID* D3D_GuidSearch(HWND hwnd)
{
	HRESULT d3dret;   //�_�C���N�g�R�c�n�֐��̖߂�l���i�[����ϐ�
	GUID*   Guid;
	LPDIRECT3D          lpD3D;
	LPDIRECTDRAW        lpDD;
	D3DFINDDEVICESEARCH S_DATA;
	D3DFINDDEVICERESULT R_DATA;
	char str[100];

	//GUID�擾�̏���
	memset(&S_DATA, 0, sizeof S_DATA);
	S_DATA.dwSize = sizeof S_DATA;
	S_DATA.dwFlags = D3DFDS_COLORMODEL;
	S_DATA.dcmColorModel = D3DCOLOR_RGB;
	memset(&R_DATA, 0, sizeof R_DATA);
	R_DATA.dwSize = sizeof R_DATA;

	//DIRECTDRAW�̐���
	d3dret = DirectDrawCreate(NULL, &lpDD, NULL);
	if (d3dret != DD_OK) {
		MessageBox( hwnd, "�_�C���N�g�h���[�I�u�W�F�N�g�̐����Ɏ��s���܂���", "������", MB_OK);
		lpDD->Release();
		return NULL;
	}

	//DIRECTD3D�̐���
	d3dret = lpDD->QueryInterface(IID_IDirect3D, (void**)&lpD3D);
	if (d3dret != D3D_OK) {
		MessageBox( hwnd, "�_�C���N�g�R�c�I�u�W�F�N�g�̐����Ɏ��s���܂���", "������", MB_OK);
		lpDD->Release();
		lpD3D->Release();
		return NULL;
	}
	//�f�o�C�X�̗�
	d3dret = lpD3D->FindDevice(&S_DATA, &R_DATA);
	if (d3dret != D3D_OK) {
		MessageBox( hwnd, "�f�o�C�X�̗񋓂Ɏ��s���܂���", "������", MB_OK);
		lpDD->Release();
		lpD3D->Release();
		return NULL;
	}

	//�K�C�h�̎擾
	Guid = &R_DATA.guid;
	//�s�v�ɂȂ����I�u�W�F�N�g�̃����[�X
	lpDD->Release();
	lpD3D->Release();
	//OutputDebugString(str);
	wsprintf(str, "%x", *Guid);
	return (Guid);
}

/*-------------------------------------------
// DirectDraw �f�o�C�X�̗񋓂ƑI��
--------------------------------------------*/
BOOL CALLBACK DDEnumCallback(GUID FAR* lpGUID, LPSTR lpDriverDesc, LPSTR lpDriverName, LPVOID lpContext)
{
	LPDIRECTDRAW lpDD;
	DDCAPS DriverCaps, HELCaps;

	// DirectDraw �I�u�W�F�N�g�������I�ɐ�������
	if(DirectDrawCreate(lpGUID, &lpDD, NULL) != DD_OK) {
		*(LPDIRECTDRAW*)lpContext = NULL;
		return DDENUMRET_OK;
	}

	// DirectDraw�̔\�͂��擾
	ZeroMemory(&DriverCaps, sizeof(DDCAPS));
	DriverCaps.dwSize = sizeof(DDCAPS);
	ZeroMemory(&HELCaps, sizeof(DDCAPS));
	HELCaps.dwSize = sizeof(DDCAPS);

	if(lpDD->GetCaps(&DriverCaps, &HELCaps) == DD_OK) {
	// �n�[�h�E�F�A3D�x�������҂ł���ꍇ�ŁD
	// �Ȃ����e�N�X�`�����g�p�ł���ꍇ������g��
		if ((DriverCaps.dwCaps & DDCAPS_3D) && (DriverCaps.ddsCaps.dwCaps & DDSCAPS_TEXTURE)) {
			*(LPDIRECTDRAW*)lpContext = lpDD;
			lstrcpy(szDDDeviceName, lpDriverDesc);
			return DDENUMRET_CANCEL;
		}
	}

	// ���̃h���C�o������
	*(LPDIRECTDRAW*)lpContext = NULL;
	lpDD->Release();

	return DDENUMRET_OK;
}

LRESULT APIENTRY WndFunc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch(msg){

	case WM_CREATE:

		break;

	case WM_KEYDOWN:

		// Esc�L�[�Ńv���O�������I�����܂�
		if(wParam == VK_ESCAPE){

			ShutdownDirectSound();
			StopBackgroundMusic();

			//��ʃ��[�h�����ɖ߂�
			lpDirectDraw->SetCooperativeLevel(hwnd, DDSCL_NORMAL);
			lpDirectDraw->RestoreDisplayMode();

			lpScreen->Release();

			ReleaseAll(); //�e�I�u�W�F�N�g��ReleaseAll()�ŉ������

			PostQuitMessage(0);

		}

		break;

	case WM_DESTROY:

			ShutdownDirectSound();
			StopBackgroundMusic();

			lpScreen->Release();

			ReleaseAll(); //�e�I�u�W�F�N�g��ReleaseAll()�ŉ������

			PostQuitMessage(0);

		break;

	// BGM����~����ƁA���̂��Ƃ��ʒm����܂�
	// "play"�R�}���h���Ď��s���܂�
	case MM_MCINOTIFY:
			if(wParam == MCI_NOTIFY_SUCCESSFUL)
				ReplayBackgroundMusic(hwnd);

		break;

	default:
		return (DefWindowProc(hwnd, msg, wParam, lParam));
	}
	return 0;
}

void LoadBMP(LPDIRECTDRAWSURFACE lpSurface, char *fname)
{
	     HBITMAP hBmp = NULL;
		 BITMAP bm;
		 HDC hdc, hMemdc;

		 hBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), fname, IMAGE_BITMAP, 0, 0,
			      LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		 GetObject(hBmp, sizeof(bm), &bm);

		 hMemdc = CreateCompatibleDC(NULL);
		 SelectObject(hMemdc, hBmp);

		 lpSurface->GetDC(&hdc);
		 BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hMemdc, 0, 0, SRCCOPY);
		 lpSurface->ReleaseDC(hdc);

		 DeleteDC(hMemdc);
		 DeleteObject(hBmp);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdParam, int nCmdShow)
{
		lpDirectDraw = NULL;
		lpDDClipper = NULL;
		lpPrimary = NULL;
		lpBackbuffer = NULL;
		lpZbuffer = NULL;
		lpDirect3DRM = NULL;
		lpD3DRMDevice = NULL;
		lpD3DRMView = NULL;
		lpD3DRMScene = NULL;

		MSG msg;
		HWND hwnd;

		DDSURFACEDESC Dds;
		DDSCAPS Ddscaps;

		WNDCLASS wc;
		char szAppName[] = "Generic Game SDK Window";
		
		wc.style = CS_DBLCLKS;
		wc.lpfnWndProc = WndFunc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInst;
		wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL,IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = szAppName;

		RegisterClass(&wc);

		hwnd=CreateWindowEx(
							WS_EX_TOPMOST,
							szAppName,
							"Direct X",
							WS_VISIBLE | WS_POPUP,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							640, 480,
							NULL, NULL, hInst,
							NULL);

		if(!hwnd) return FALSE;

		ShowWindow(hwnd, nCmdShow);
		UpdateWindow(hwnd);
		SetFocus(hwnd);

		ShowCursor(FALSE); //�J�[�\�����B��

		//Direct3DRM�̍\�z
		Direct3DRMCreate(&lpDirect3DRM);

		//DirectDrawClipper�̍\�z
		DirectDrawCreateClipper(0, &lpDDClipper, NULL);

		// DirectDraw�h���C�o��񋓂���
		DirectDrawEnumerate(DDEnumCallback, &lpDirectDraw);

		// �񋓂ɂ����DirectDraw�h���C�o�����߂�
		// ���肵�Ȃ������ꍇ�A���݃A�N�e�B�u�ȃh���C�o���g��
		if(!lpDirectDraw){
			lstrcpy(szDDDeviceName, "Active Driver");
			DirectDrawCreate(NULL, &lpDirectDraw, NULL);
		}

		lpDirectDraw->SetCooperativeLevel(hwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT);

		//�f�B�X�v���C���[�h�ύX
		lpDirectDraw->SetDisplayMode(640, 480, 16);

		//��{�T�[�t�F�X�ƃt�����g�o�b�t�@�̐��� (�P���쐬)
		ZeroMemory(&Dds, sizeof(DDSURFACEDESC));
		Dds.dwSize = sizeof(DDSURFACEDESC);
		Dds.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		Dds.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX | DDSCAPS_VIDEOMEMORY | DDSCAPS_3DDEVICE;
		Dds.dwBackBufferCount = 1;

		lpDirectDraw->CreateSurface(&Dds, &lpPrimary, NULL);

		//�o�b�N�o�b�t�@�̃|�C���^�擾
		Ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
		lpPrimary->GetAttachedSurface(&Ddscaps, &lpBackbuffer);

		// Z-Buffer�쐬
		//��{�T�[�t�F�X�ƃo�b�t�@�P���쐬
		ZeroMemory(&Dds, sizeof(DDSURFACEDESC));
		Dds.dwSize = sizeof(DDSURFACEDESC);
		Dds.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS | DDSD_ZBUFFERBITDEPTH;
		Dds.dwHeight = 640;
		Dds.dwWidth = 480;
		Dds.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_VIDEOMEMORY;
		Dds.dwZBufferBitDepth = 16;

		lpDirectDraw->CreateSurface(&Dds, &lpZbuffer, NULL);

		lpBackbuffer->AddAttachedSurface(lpZbuffer);

/*
		//DirectDraw�ł̃A�N�Z�X���ł���悤�ɁAClipper������
		struct _MYRGNDATA {
			RGNDATAHEADER rdh;
			RECT rc;
		}rgndata;
	
		rgndata.rdh.dwSize = sizeof(RGNDATAHEADER);
		rgndata.rdh.iType = RDH_RECTANGLES;
		rgndata.rdh.nCount = 1;
		rgndata.rdh.nRgnSize = sizeof(RECT)*1;
		rgndata.rdh.rcBound.left = 0;
		rgndata.rdh.rcBound.right = 640;
		rgndata.rdh.rcBound.top = 0;
		rgndata.rdh.rcBound.bottom = 480;

		rgndata.rc.top = 0;
		rgndata.rc.bottom = 480;
		rgndata.rc.left = 0;
		rgndata.rc.right = 640;

		lpDirectDraw->CreateClipper(0, &lpDDClipper, NULL);
		lpDDClipper->SetClipList((LPRGNDATA)&rgndata, NULL);
		lpBackbuffer->SetClipper(lpDDClipper);
*/

		DDCOLORKEY          ddck;

		//�w�i�T�[�t�F�X���쐬
		Dds.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
		Dds.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
		Dds.dwWidth = 640;
		Dds.dwHeight = 480;
		lpDirectDraw->CreateSurface(&Dds, &lpScreen, NULL);

		//�J���[�L�[�̎w�� ��:RGB(255, 255, 255)�@��:RGB(0, 0, 0)
		ddck.dwColorSpaceLowValue=RGB(0, 0, 0);
		ddck.dwColorSpaceHighValue=RGB(0, 0, 0);
		lpScreen->SetColorKey(DDCKEY_SRCBLT, &ddck);

		//�e�T�[�t�F�X�ɉ摜��ǂݍ���
		LoadBMP(lpScreen, "datafile\\back.BMP");  //�w�i

		DirectDrawCreateClipper(0, &lpDDClipper, NULL);

//Direct3DRM�̏����� ��������

//�f�o�C�X�̐��� �g�d�k���s RAMP ��掿 ���x�x��
//		Direct3DRMCreate(&lpDirect3DRM);
//		lpDirect3DRM->CreateDeviceFromSurface(NULL, lpDirectDraw, lpBackbuffer, &lpD3DRMDevice);
//

//�f�o�C�X�̐��� �g�`�k�Ŏ��s����

		HRESULT ddret;   //�_�C���N�g�R�c�n�֐��̖߂�l���i�[����ϐ�
		GUID*   Guid;

		Direct3DRMCreate(&lpDirect3DRM);

		Guid = D3D_GuidSearch(hwnd);
		// HAL
		ddret = lpDirect3DRM->CreateDeviceFromSurface(Guid, (IDirectDraw*)lpDirectDraw, lpBackbuffer, &lpD3DRMDevice);
			strcpy(szDevice,"D3D HAL");
		if (ddret != D3DRM_OK) {
			MessageBox( hwnd, "�f�o�C�X�̐����Ɏ��s�A�g�`�k�ł̎��s�͕s�\�ł�", "", MB_OK);
			//HAL�ł̎��s���s�\�Ȏ��AHEL�ł̎��s���s��
			ddret = lpDirect3DRM->CreateDeviceFromSurface(Guid, (IDirectDraw*)lpDirectDraw, lpBackbuffer, &lpD3DRMDevice);
			if (ddret != D3DRM_OK) {
				strcpy(szDevice,"HEL");
				MessageBox( hwnd, "�g�d�k�ł́A�f�o�C�X�̐����Ɏ��s�ADirect3D�̎g�p�͕s�\�ł�", "", MB_OK);
			}

			if(ddret != D3DRM_OK){
				//MMX
				ddret = lpDirect3DRM->CreateDeviceFromSurface(Guid, (IDirectDraw*)lpDirectDraw, lpBackbuffer, &lpD3DRMDevice);
				strcpy(szDevice,"D3D MMX Emulation");
			}

			if(ddret != D3DRM_OK){
				//RGB
				ddret = lpDirect3DRM->CreateDeviceFromSurface(Guid, (IDirectDraw*)lpDirectDraw, lpBackbuffer, &lpD3DRMDevice);
				strcpy(szDevice,"D3D RGB Emulation");
			}
		}
//

		lpD3DRMDevice->SetQuality(D3DRMLIGHT_ON | D3DRMFILL_SOLID | D3DRMSHADE_GOURAUD);

		lpDirect3DRM->CreateFrame(NULL, &lpD3DRMScene);

		//�J�������쐬
								// �e�t���[�� ,	�q�t���[��
		lpDirect3DRM->CreateFrame(lpD3DRMScene, &lpD3DRMCamera);

		lpD3DRMCamera->SetPosition(lpD3DRMScene, D3DVAL(0.0), D3DVAL(0.0), D3DVAL(0.0));

		//�f�o�C�X�ƃJ��������Direct3DRMViewPort���쐬
		lpDirect3DRM->CreateViewport(lpD3DRMDevice, lpD3DRMCamera, 0, 0, 640, 480, &lpD3DRMView);

		// �w�i�̉��s���A�v���[���[���_���W�������Ō��邱�Ƃ��ł���ő勗���ɐݒ肵�܂��B
		// ��������ƁA�_���W�����S�̂̎�����ז����邱�ƂȂ��A�����̃N���b�s���O�v���[�����ł��邾���߂��ɐݒ�ł��܂�
		lpD3DRMView->SetBack(D3DVAL(70.f));

		// �t�����g�N���b�s���O�v���[������ɋ߂��ɐݒ肵�܂�
		lpD3DRMView->SetFront(0.5f);

		// �i�r�Q�[�V�����V�X�e�������������܂�
		SetupNavigator();		

		// �V�[�����쐬���܂�
		BuildScene();

		// �V�[�����`�悳�ꂽ��ABGM���J�n���܂�
		StartBackgroundMusic(hwnd);

		while(1){

			if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
				{
					if(!GetMessage(&msg, NULL, 0, 0))
						return msg.wParam;
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}else{

							RenderFrame();

					}
		}
		return msg.wParam;

}

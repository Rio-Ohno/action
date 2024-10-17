//============================================================
//
//2D�A�N�V�����Q�[[main.cpp]
//Author:Rio Ohno
//
//============================================================

#include"main.h"
#include"input.h"
#include"fade.h"
#include"title.h"
#include"game.h"
#include"result.h"
#include"block.h"
#include<stdio.h>
#include<stdlib.h>
#include <crtdbg.h>

//�O���[�o���ϐ��錾
LPDIRECT3D9 g_pD3D = NULL;											 //DirectX3D�I�u�W�F�N�g�ւ̃|�C���^
LPD3DXFONT g_pfont = NULL;											 //�t�H���g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;								 //DirectX3D�f�o�C�X�ւ̃|�C���^
MODE g_mode = MODE_TITLE;											 //���݂̃��[�h
int g_nCountFPS = 0;												 //FPS�J�E���^

//=========================================================
//���C���֐�
//=========================================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);//���������[�N���m

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),											//WNDCLASSEX�̃������[�T�C�Y
		CS_CLASSDC,													//�E�B���h�E�̃X�^�C��
		WindowProc,													//�E�B���h�E�v���V�[�W��
		0,															//0�ɂ���i�ʏ�͂��Ȃ��j
		0,															//0�ɂ���i�ʏ�͂��Ȃ��j
		hInstance,													//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),								//�^�X�N�o�[�A�C�R��
		LoadCursor(NULL,IDC_ARROW),									//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW+1),									//�N���C�A���g�̈�̔w�i�F
		NULL,														//���j���[�o�[
		CLASS_NAME,													//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION),								//�t�@�C���̃A�C�R��
	};

	HWND hWnd;//�E�B���h�E�n���h��
	MSG msg;//���b�Z�[�W���i�[����

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };					//��ʃT�C�Y�̍\����

	DWORD dwCurrentTime;											//���ݎ���
	DWORD dwExecLastTime;											//�Ō�ɏ�����������
	DWORD dwFrameCount;												//�t���[���J�E���g
	DWORD dwFPSLastTime;											//�Ō�Ɍv����������

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐� 
	hWnd = CreateWindowEx
	   (0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right-rect.left),
		(rect.bottom-rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		//���������������s������
		return -1;
	}

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwFrameCount = 0;
	dwExecLastTime = timeGetTime();
	dwFPSLastTime = timeGetTime();
	
	//�E�B���h�E�̕\��
	ShowWindow(hWnd,nCmdShow);//�E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);       //�N���C�A���g�̈���X�V

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windows�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();								//���ݎ������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS�����Z
				g_nCountFPS = ((dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime));
				dwFPSLastTime = dwCurrentTime;							//FPS���v������������ۑ�

				dwFrameCount = 0;										//�t���[���J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime;							//�����J�n�̎���[���ݎ���]��ۑ�

				//�X�V����
				Update();

				//�`�揈��
				Draw();

				dwFrameCount++;											//�t���[���J�E���g�����Z
			}
		}
	}

	//�I������
	Uninit();

	//����]��߂�
	timeEndPeriod(1);

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================================================
//�E�B���h�E�v���V�[�W��
//=============================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch(uMsg)
	{
	case WM_DESTROY://�E�B���h�E�j���̃��b�Z�[�W

		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:

			DestroyWindow(hWnd);
			break;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================================================
//�f�o�C�X�̎擾
//=============================================================================================================
LPDIRECT3DDEVICE9 GetDevice()
{
	return g_pD3DDevice;
}

//=============================================================================================================
//����������
//=============================================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;             //�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;      //�v���[���e�[�V�����p�����[�^

	//DirectX3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));                               //�p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;                            //�Q�[����ʂ̃T�C�Y�i���j
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;                          //�Q�[����ʂ̃T�C�Y�i�����j
	d3dpp.BackBufferFormat = d3ddm.Format;                           //�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;                                       //�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                        //�_�u���o�b�t�@�̐؂�ւ��i�f���M���ɓ����j
	d3dpp.EnableAutoDepthStencil = TRUE;                             //�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                       //�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;                                        //�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//DirectX3D�f�o�C�X�̐����i�`�揈���ƒ��_�������n�[�h�E�F�A�s���j
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//DirectX3D�f�o�C�X�̐����i�`�揈���̓n�[�h�E�F�A�A���_������CPU�ōs���j
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}

		}

	}

	//�f�o�b�N�\���p�t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice,
		18, 0, 0, 0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal",
		&g_pfont);

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�W���C�p�b�h�̏���������
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	//���[�h�̐ݒ�
	SetMode(g_mode);

	//�t�F�[�h�̏���������
	InitFade(g_mode);

	return S_OK;
}

//=============================================================================================================
//�I������
//=============================================================================================================
void Uninit()
{	
	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	//�W���C�p�b�h�̏I������
	UninitJoypad();

	//�t�F�[�h�̏I������
	UninitFade();

	//�f�o�b�N�\���p�t�H���g�̔j��
	if (g_pfont != NULL)
	{
		g_pfont->Release();
		g_pfont = NULL;
	}

	//DirectX3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	//DirectX3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================================================================================
//�X�V����
//=============================================================================================================
void Update()
{
	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	//�W���C�p�b�h�̍X�V����
	UpdateJoypad();

	switch (g_mode)
	{
	case MODE_TITLE:

		UpdateTitle();
		break;

	case MODE_TUTORIAL:

		break;

	case MODE_GAME:

		UpdateGame();
		break;

	case MODE_RESULT://���U���g���
		UpdateResult();
		break;

	default:

		break;
	}

	//�t�F�[�h�̍X�V����
	UpdateFade();
}

//=============================================================================================================
//�`�揈��
//=============================================================================================================
void Draw()
{
	//��ʃN���A�i�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A�j
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
		case MODE_TITLE://�^�C�g�����
			DrawTitle();
			break;

		case MODE_TUTORIAL://�`���[�g���A�����
			break;

		case MODE_GAME://�Q�[�����
			DrawGame();
			break;

		case MODE_RESULT://���U���g���
			DrawResult();
			break;

		case MODE_RANKING://�����L���O
			//DrawRanking();
			break;
		}

		//�t�F�[�h�̕`�揈��
		DrawFade();

		#ifdef _DEBUG

			//FPS�̕\��
			DrawFPS();

			////�e���̕\��
			DrawNumBlock();

		#endif // _DEBUG


		//�`��I��
		g_pD3DDevice->EndScene();
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================================================
//FPS�̕\��(�f�o�b�N�p)
//=============================================================================================================
void DrawFPS()
{
	char a_Str[20];
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//������ɑ��
	wsprintf(&a_Str[0], "FPS:%d\n", g_nCountFPS);

	//�e�L�X�g�̕`��
	g_pfont->DrawText(NULL, &a_Str[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=============================================================================================================
//�e���̕\��(�f�o�b�N�p)
//=============================================================================================================
void DrawNumBlock()
{
	char a_Str1[20];
	RECT rect = { 0,15,SCREEN_WIDTH,SCREEN_HEIGHT };

	int nNumBullet = GetNumBlock();

	//������ɑ��
	wsprintf(&a_Str1[0], "�u���b�N��:%d\n", nNumBullet);

	//�e�L�X�g�̕`��
	g_pfont->DrawText(NULL, &a_Str1[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=============================================================================================================
//���[�h�̐ݒ�
//=============================================================================================================
void SetMode(MODE mode)
{
	//���݂̉�ʁi���[�h�j�̏I������
	switch (g_mode)
	{
	case MODE_TITLE://�^�C�g�����
		UninitTitle();
		break;

	case MODE_TUTORIAL://�`���[�g���A�����
		break;

	case MODE_GAME://�Q�[�����
		UninitGame();
		break;

	case MODE_RESULT://���U���g���
		UninitResult();
		break;

	case MODE_RANKING://�����L���O
		//UninitRanking();
		break;
	}

	//�V������ʁi���[�h�j�̏���������
	switch (mode)
	{
	case MODE_TITLE://�^�C�g�����
		InitTitle();
		break;

	case MODE_TUTORIAL://�`���[�g���A�����
		break;

	case MODE_GAME://�Q�[�����
		InitGame();
		break;

	case MODE_RESULT://���U���g���
		InitResult();
		break;

	case MODE_RANKING://�����L���O
		//InitRanking();
		break;
	}
	g_mode = mode;//���݂̉�ʁi���[�h�j��؂�ւ���
}

//=============================================================================================================
//���[�h�̎擾
//=============================================================================================================
MODE GetMode()
{
	return g_mode;
}
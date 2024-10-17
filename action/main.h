//============================================================
//
//2D�A�N�V�����Q�[[main.h]
//Author:Rio Ohno
//
//=============================================================

#ifndef _MAIN_H_
#define _MAIN_H_


#include<windows.h>
#include"d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)        //�r���h���Ex���E�Ep�}�N��
#include"dinput.h"                          //���E�E��?K�v
#include"Xinput.h"                          //�W���C�p�b�h�ɕK�v
#include"xaudio2.h"

//���C�u�����E����N 
#pragma comment(lib,"d3d9.lib")             //�`�E���EK�v
#pragma comment(lib,"d3dx9.lib")            //[d3d9.lib]�Eg�����C�u����
#pragma comment(lib,"dxguid.lib")           //DirectX�R���|�[�l���g�i���i�j�g�p�EK�v
#pragma comment(lib,"winmm.lib")            //�V�X�e���������E?K�v
#pragma comment(lib,"dinput8.lib")          //���E�E��?K�v
#pragma comment(lib,"xinput.lib")           //�W���C�p�b�h�����ɕK�v

//�}�N����`
#define CLASS_NAME "WindowClass"			//�E�B���h�E�N���X�E��O
#define WINDOW_NAME "action"				//�E�B���h�E�E��O�i�L���v�V�����E��O�j
#define SCREEN_WIDTH (1280)					//�E�B���h�E�E�E
#define SCREEN_HEIGHT (720)				    //�E�B���h�E�E���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define NUM_EIGHT (8)						//�W

//���_���[2D]�̍\����
typedef struct
{

	D3DXVECTOR3 pos;                        //���_���W
	float rhw;                              //���W�E��p�W���i1.0f�E?�j
	D3DCOLOR col;                           //���_�J���[
	D3DXVECTOR2 tex;                        //�e�N�X�`�����W

}VERTEX_2D;

//��ʃ��[�h�̎��
typedef enum
{
	MODE_TITLE=0,                           //�^�C�g�����
	MODE_TUTORIAL,							//�`���[�g���A�����
	MODE_GAME,                              //�Q�[�����
	MODE_RESULT,                            //���U���g���
	MODE_RANKING,							//�����L���O���
	MODE_MAX
}MODE;

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit();
void Update();
void Draw();
void DrawFPS();
void DrawNumBlock();
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode();

#endif // !_MAIN_H_
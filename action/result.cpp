//============================================================
//
//���U���g���[result.cpp]
//Author:Rio Ohno
//
//============================================================

#include"result.h"
#include"input.h"
#include"game.h"
#include"fade.h"

//�}�N����`
#define MAX_POLY_RESULT (3)

//�e�N�X�`��
static const char* RESULT_TEXTURE[RESULT_MAX] =
{
	"data\\TEXTURE\\GAMECLEAR000.png",
	"data\\TEXTURE\\GameOver000.png",
};

static const char* RESULTBG_TEXTURE[RESULT_MAX] =
{
	"data\\TEXTURE\\night000.png",
	"data\\TEXTURE\\Reslut000.png",
};

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureResult[MAX_POLY_RESULT] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult;
RESULT g_Result = RESULT_LOSE;
float g_Tex_y[3];

//=============================================================================================================
//�^�C�g����ʂ̏���������
//=============================================================================================================
void InitResult()
{
	LPDIRECT3DDEVICE9 pDevice;                                                  //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ�
	D3DXCreateTextureFromFile(pDevice,
		RESULTBG_TEXTURE[g_Result],
		&g_pTextureResult[0]);

	//�e�N�X�`���̎擾
	D3DXCreateTextureFromFile(pDevice,
		RESULT_TEXTURE[g_Result],
		&g_pTextureResult[1]);

	//�e�N�X�`���̎擾
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Coment000.png",
		&g_pTextureResult[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLY_RESULT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	for (int nCnt = 0; nCnt < MAX_POLY_RESULT; nCnt++)
	{
		g_Tex_y[nCnt] = 0;
	}

	g_Result = RESULT_LOSE;

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_POLY_RESULT; nCnt++)
	{
		if (nCnt == 0)
		{
			//���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
		}
		else if (nCnt == 1)
		{
			//���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(325.0f, 200.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(925.0f, 200.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(325.0f, 300.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(925.0f, 300.0f, 0.0f);
		}
		else if (nCnt == 2)
		{
			//���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(790.0f, 625.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1200.0f, 625.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(790.0f, 700.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1200.0f, 700.0f, 0.0f);
		}

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + g_Tex_y[nCnt]);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + g_Tex_y[nCnt]);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + g_Tex_y[nCnt]);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f + g_Tex_y[nCnt]);

		pVtx += 4;

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();
}

//=============================================================================================================
//�^�C�g����ʂ̏I������
//=============================================================================================================
void UninitResult()
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_POLY_RESULT; nCnt++)
	{
		if (g_pTextureResult[nCnt] != NULL)
		{
			g_pTextureResult[nCnt]->Release();
			g_pTextureResult[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//=============================================================================================================
//�^�C�g����ʂ̍X�V����
//=============================================================================================================
void UpdateResult()
{
	VERTEX_2D* pVtx{};

	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		//����L�[�iENTER�L�[�j�������ꂽ
		//���[�h�ݒ�i�Q�[����ʂɈڍs�j
		SetFade(MODE_TITLE);
	}
	else if (KeyboardTrigger(DIK_R) == true)
	{	
		//R�L�[�������ꂽ
		//�����L���O�Ɉڍs
		SetMode(MODE_RANKING);
		return;
	}

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_POLY_RESULT; nCnt++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + g_Tex_y[nCnt]);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + g_Tex_y[nCnt]);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + g_Tex_y[nCnt]);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f + g_Tex_y[nCnt]);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();

}

//=============================================================================================================
//�^�C�g����ʂ̕`�揈��
//=============================================================================================================
void DrawResult()
{
	LPDIRECT3DDEVICE9 pDevice;                                                  //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (int nCnt = 0; nCnt < MAX_POLY_RESULT; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResult[nCnt]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}

//=============================================================================================================
//���ʂ̎擾
//=============================================================================================================
void SetResult(RESULT result)
{
	g_Result=result;
}
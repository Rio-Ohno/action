//============================================================
//
//�w�i[backgraund.cpp]
//Author:Rio Ohno
//
//============================================================
#include "backgraund.h"

//�}�N����`
#define NUM_BG (1)                                                                //�w�i�̐�

//�e�N�X�`��
static const char* BG_TEXTURE[NUM_BG] =
{
	"data\\TEXTURE\\BG001.jpg",
};

LPDIRECT3DTEXTURE9 g_pTexturebackgraund[NUM_BG] = {};                             //�e�N�X�`��(�O����)�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffbackgraund = NULL;                              //���_�����i�[
float g_aPosTexU[NUM_BG];                                                         //�e�N�X�`�����W�̊J�n�ʒu�iU�l�j

//=============================================================================================================
//�w�i�̍X�V����
//=============================================================================================================
void Updatebackgraund()
{
	int nCntBG = 0;

	VERTEX_2D* pVtx2;															   //���_���ւ̃|�C���^

	//�e�N�X�`�����W�̊J�n�ʒu�iU�l�j�̏�����
	g_aPosTexU[0] = 0.000f;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffbackgraund->Lock(0, 0, (void**)&pVtx2, 0);

		pVtx2[0].tex = D3DXVECTOR2(0.0f,g_aPosTexU[nCntBG]);
		pVtx2[1].tex = D3DXVECTOR2(1.0f,g_aPosTexU[nCntBG]);
		pVtx2[2].tex = D3DXVECTOR2(0.0f,1.0f + g_aPosTexU[nCntBG]);
		pVtx2[3].tex = D3DXVECTOR2(1.0f,1.0f + g_aPosTexU[nCntBG]);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffbackgraund->Unlock();
}

//=============================================================================================================
//�w�i�̏���������
//=============================================================================================================
void Initbackgraund()
{
	LPDIRECT3DDEVICE9 pDevice;															//�f�o�C�X�ւ̃|�C���^
	int nCntBG = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	
		//�e�N�X�`���̓Ǎ�
		D3DXCreateTextureFromFile(pDevice,
			BG_TEXTURE[nCntBG],
			&g_pTexturebackgraund[nCntBG]);

		//�e�N�X�`�����W�̊J�n�ʒu�iU�l�j�̏�����
		g_aPosTexU[nCntBG] = 0.0f;

	//���_�o�b�t�@�̂̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffbackgraund,
		NULL);

	VERTEX_2D* pVtx2;																	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffbackgraund->Lock(0, 0, (void**)&pVtx2, 0);

		//���_���W�̐ݒ�
		pVtx2[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); 
		pVtx2[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx2[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx2[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx2[0].rhw = 1.0f;
		pVtx2[1].rhw = 1.0f;
		pVtx2[2].rhw = 1.0f;
		pVtx2[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx2[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f);
		pVtx2[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f);
		pVtx2[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f);
		pVtx2[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f);


		//�e�N�X�`�����W�̐ݒ�
		pVtx2[0].tex = D3DXVECTOR2(0.0f, g_aPosTexU[nCntBG]);
		pVtx2[1].tex = D3DXVECTOR2(1.0f, g_aPosTexU[nCntBG]);
		pVtx2[2].tex = D3DXVECTOR2(0.0f, 1.0f + g_aPosTexU[nCntBG]);
		pVtx2[3].tex = D3DXVECTOR2(1.0f, 1.0f + g_aPosTexU[nCntBG]);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffbackgraund->Unlock();

}

//=============================================================================================================
//�w�i�̕`�揈��
//=============================================================================================================
void Drawbackgraund()
{
	LPDIRECT3DDEVICE9 pDevice;															 //�f�o�C�X�ւ̃|�C���^
	int nCntBG = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffbackgraund, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, g_pTexturebackgraund[nCntBG]);

	//BG�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBG*4, 2);
}

//=============================================================================================================
//�w�i�̏I������
//=============================================================================================================
void Uninitbackgraund()
{
	int nCntBG = 0;

	//�e�N�X�`���̔j��
	if (g_pTexturebackgraund[nCntBG] != NULL)
	{
		g_pTexturebackgraund[nCntBG]->Release();
		g_pTexturebackgraund[nCntBG] = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffbackgraund != NULL)
	{
		g_pVtxBuffbackgraund->Release();
		g_pVtxBuffbackgraund= NULL;
	}
}
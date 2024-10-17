//============================================================
//
//�u���b�N[Block.cpp]
//Author:Rio Ohno
//
//============================================================

#include"block.h"
#include"player.h"

//�}�N����`
#define MAX_BLOCK (3)																				//�u���b�N�̍ő吔

//�v���C���[�̒e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;																				//�ʒu
	D3DXVECTOR3 move;																				//�ړ���
	D3DXVECTOR3 rot;																				//����
	BLOCKTYPE type;																					//���
	float fWidthBlock;																				//�|���S���̕�
	float fHeighBlock;																				//�|���S���̍���
	float fTex_x;																					//�e�N�X�`����x���W
	float fTex_y;																					//�e�N�X�`���̂����W
	bool bUse;																						//�g�p���Ă��邩�ǂ�
}Block;

//�e�N�X�`��
static const char* BLOCK_TEXTURE[BLOCK_MAX] =
{
	"data\\TEXTURE\\block000.jpg",
	"data\\TEXTURE\\toge000.png",
};

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBlock[BLOCK_MAX] = {};													//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;														//���_�o�b�t�@�ւ̃|�C���^
Block g_aBlock[MAX_BLOCK];																			//�u���b�N�̏��
int nNumBlock = 0;											

//=============================================================================================================
//�u���b�N�̏���������
//=============================================================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock = NULL;

	//�f�o�C�X�Ɏ擾
	pDevice = GetDevice();


	//�u���b�N�̏��̏�����
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//�ʒu�̏�����
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//�ړ��ʂ̏�����
		g_aBlock[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//�p�x�̏�����
		g_aBlock[nCntBlock].type = BLOCK_NULL;														//��ނ̏�����
		g_aBlock[nCntBlock].bUse = false;															//�g�p���Ă��Ȃ���Ԃɂ���

		//�e�N�X�`���̓Ǎ�
		D3DXCreateTextureFromFile(pDevice,
			BLOCK_TEXTURE[g_aBlock[nCntBlock].type],
			&g_pTextureBlock[g_aBlock[nCntBlock].type]);

	}


	nNumBlock = 0;																					//�e���̏�����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D * pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//���_���W�̐ݒ�
 		pVtx[0].pos.x = 0.0f;
		pVtx[0].pos.y = 0.0f;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = 0.0f;
		pVtx[1].pos.y = 0.0f;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = 0.0f;
		pVtx[2].pos.y = 0.0f;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = 0.0f;
		pVtx[3].pos.y = 0.0f;
		pVtx[3].pos.z = 0.0f;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================================================
//�u���b�N�̏I������
//=============================================================================================================
void UninitBlock()
{
	//�e�N�X�`���̔j��
	for (int nCntBlock = 0; nCntBlock < BLOCK_MAX; nCntBlock++)
	{
		if (g_pTextureBlock[nCntBlock] != NULL)
		{
			g_pTextureBlock[nCntBlock]->Release();
			g_pTextureBlock[nCntBlock] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//=============================================================================================================
//�u���b�N�̍X�V����
//=============================================================================================================
void UpdateBlock()
{

}

//=============================================================================================================
//�u���b�N�̕`�揈��
//=============================================================================================================
void DrawBlock()
{
	int nCntBlock;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//�u���b�N���g�p����Ă���

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].type]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntBlock*4,2);
		}
	}
}

//=============================================================================================================
//�u���b�N�̐ݒ菈��
//=============================================================================================================
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR2  tex, BLOCKTYPE type, float fWidthBlock, float fHeightBlock)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D* pVtx;

	int nCntBlock;

	//�f�o�C�X�Ɏ擾
	pDevice = GetDevice();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{
			//�u���b�N���g�p����Ă��Ȃ��Ƃ�
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].fWidthBlock = fWidthBlock;
			g_aBlock[nCntBlock].fHeighBlock = fHeightBlock;
			g_aBlock[nCntBlock].type = type;

			//�e�N�X�`���̓Ǎ�
			D3DXCreateTextureFromFile(pDevice,
				BLOCK_TEXTURE[g_aBlock[nCntBlock].type],
				&g_pTextureBlock[g_aBlock[nCntBlock].type]);


			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_aBlock[nCntBlock].pos.x - (g_aBlock[nCntBlock].fWidthBlock / 2.0f);
			pVtx[0].pos.y = g_aBlock[nCntBlock].pos.y - (g_aBlock[nCntBlock].fHeighBlock / 2.0f);
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWidthBlock / 2.0f);
			pVtx[1].pos.y = g_aBlock[nCntBlock].pos.y - (g_aBlock[nCntBlock].fHeighBlock / 2.0f);
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aBlock[nCntBlock].pos.x - (g_aBlock[nCntBlock].fWidthBlock / 2.0f);
			pVtx[2].pos.y = g_aBlock[nCntBlock].pos.y + (g_aBlock[nCntBlock].fHeighBlock / 2.0f);
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWidthBlock / 2.0f);
			pVtx[3].pos.y = g_aBlock[nCntBlock].pos.y + (g_aBlock[nCntBlock].fHeighBlock / 2.0f);
			pVtx[3].pos.z = 0.0f;

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(tex.x, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, tex.y);
			pVtx[3].tex = D3DXVECTOR2(tex.x, tex.y);

			g_aBlock[nCntBlock].move = move;														//�ړ��ʂ̐ݒ�
			g_aBlock[nCntBlock].bUse = true;														//�g�p���Ă��Ԃɂ���

			nNumBlock++;																			//�u���b�N�̐��J�E���g
			break;
		}
		pVtx += 4;
	}
	//�A�����b�N
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================================================
//�u���b�N�̐��̎擾
//=============================================================================================================
int GetNumBlock()
{
	return nNumBlock;
}

//=============================================================================================================
//�u���b�N�̓����蔻��
//=============================================================================================================
//�v���C���[��pos,�O��̃v���C���[��pos,�v���C���[�̈ړ���,�v���C���[�̕�,�v���C���[�̍���
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, bool* pDash,float fWidth, float fHeight)
{
	bool Landing = false;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		const float fAbove = g_aBlock[nCntBlock].pos.y - (g_aBlock[nCntBlock].fHeighBlock / 2.0f);	//��
		const float fBelow = g_aBlock[nCntBlock].pos.y + (g_aBlock[nCntBlock].fHeighBlock / 2.0f);	//��
		const float fLeft = g_aBlock[nCntBlock].pos.x - (g_aBlock[nCntBlock].fWidthBlock / 2.0f);	//��
		const float fRight = g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWidthBlock / 2.0f);	//�E

		if (g_aBlock[nCntBlock].bUse == true)
		{
			//�㉺�̓����蔻��
			if (pPos->x + (fWidth / 2.0f) > fLeft
				&& pPos->x - (fWidth / 2.0f) < fRight)
			{
				//�v���C���[���ォ�牺�ɂ߂荞��
				if (pPosOld->y <= fAbove
					&& pPos->y > fAbove)
				{
					pPos->y = fAbove;
					pMove->y = 0.0f;
					Landing = true;

					if (*pDash == true)
					{
						*pDash = false;
					}

					if (g_aBlock[nCntBlock].type == BLOCK_THORN)
					{
						HitPlayer(1.0f);
					}

				}
				//�v���C���[���������ɂ߂荞��
				else if ((pPosOld->y - fHeight) >= fBelow
					&& (pPos->y - fHeight) < fBelow)
				{
					pPos->y = fBelow + fHeight;
					pMove->y = 0.0f;
					Landing = true;
				}
			}

			//���̓����蔻��
			if (pPosOld->y > fAbove
				&& pPosOld->y - fHeight < fBelow)
			{
				//�v���C���[��������E�ɂ߂荞��
				if (pPosOld->x + (fWidth / 2.0f) <= fLeft
					&& pPos->x + (fWidth / 2.0f) > fLeft)
				{
					pPos->x = fLeft - (fWidth / 2.0f);
					pMove->x = 0.0f;
				}
				//�v���C���[���E���獶�ɂ߂荞��
				else if (pPosOld->x - (fWidth / 2.0f) >= fRight
					&& pPos->x - (fWidth / 2.0f) < fRight)
				{
					pPos->x = fRight + (fWidth / 2.0f);
					pMove->x = 0.0f;
				}
			}
		}
	}
	return Landing;
}


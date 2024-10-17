//============================================================
//
//�v���C���[[player.cpp]
//Author:Rio Ohno
//
//============================================================

#include"player.h"
#include"input.h"
#include"block.h"
#include"fade.h"

//�}�N����`
#define NUM_WIDTH (50)											                //�|���S���̕�
#define NUM_HEIGHT (50)												            //�|���S���̍���
#define PLAYERLIFE (1.0f)														//�v���C���[�̃��C�t
#define JUMP (18.0f)															//�v���C���[�̃W�����v��
#define G (0.8f)																//�d��
#define  DASH  (35.0f)															//�_�b�V��

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;                                     //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePlayerPos = NULL;                                  //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer=NULL;                                  //���_�����i�[
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerPos = NULL;                             //���_�����i�[
Player g_Player;

//=============================================================================================================
//�v���C���[�̏���������
//=============================================================================================================
void InitPlayer()
{

	LPDIRECT3DDEVICE9 pDevice;													//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ�
	D3DXCreateTextureFromFile(pDevice,
		NULL,
		&g_pTexturePlayer);

	g_Player.pos = D3DXVECTOR3(75.0f,187.5f,0);									//�ʒu������������
	g_Player.posOld = {};														//�O��̈ʒu������������
	g_Player.move = D3DXVECTOR3(0.0f,0.0f,0.0f);								//�ړ��ʂ�����������
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								//����������������
	g_Player.state = PLAYERSTATE_NORMAL;										//�G�̏�Ԃ̏�����
	g_Player.nCountState = 0;													//��ԊǗ��p�J�E���^�[�̏�����
	g_Player.nCntPlayer = 0;													//�c�@����������
	g_Player.nCntAime = 0;														//�A�j���[�V�����p�J�E���^�[�̏�����
	g_Player.Anime = 0;															//�A�j���[�V�����p�J�E���^�[�̏�����
	g_Player.Tex_v = 0;															//�e�N�X�`��Y���W�ۑ��p
	g_Player.fLife = PLAYERLIFE;												//�̗͂̏�����
	g_Player.bUse = true;														//���@���g�p��Ԃɂ���
	g_Player.bDisp = true;														//�\����Ԃɂ���
	g_Player.bJump = false;														//�W�����v���Ă��Ȃ���Ԃɂ���
	g_Player.bDash = false;														//�_�b�V�����Ă��Ȃ���Ԃɂ���

	//���_�o�b�t�@�̂̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,                               
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D* pVtx;															 //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_Player.pos.x - (NUM_WIDTH / 2.0f);
	pVtx[0].pos.y = g_Player.pos.y - NUM_HEIGHT;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Player.pos.x + (NUM_WIDTH / 2.0f);
	pVtx[1].pos.y = g_Player.pos.y - NUM_HEIGHT;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Player.pos.x - (NUM_WIDTH / 2.0f);
	pVtx[2].pos.y = g_Player.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Player.pos.x + (NUM_WIDTH / 2.0f);
	pVtx[3].pos.y = g_Player.pos.y;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//=============================================================================================================
//�v���C���[�̕`�揈��
//=============================================================================================================
void DrawPlayer()
{
	LPDIRECT3DDEVICE9 pDevice;														//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	if (g_Player.bDisp == true)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);

		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	}
}

//=============================================================================================================
//�v���C���[�̍X�V����
//=============================================================================================================
void UpdatePlayer()
{
	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	int nCntAnim=30;//�A�j���[�V�����̏�]�Z�̂Ƃ�
	
	switch (g_Player.state)
	{
	case PLAYERSTATE_NORMAL:

		break;

	case PLAYERSTATE_DAMAGE:

		g_Player.nCountState--;

		if (g_Player.nCountState <= 0)
		{
			g_Player.state = PLAYERSTATE_NORMAL;

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffPlayer->Unlock();
		}

		break;

	case PLAYERSTATE_APPEAR:

		g_Player.nCountState--;

		if (g_Player.nCountState <= 0)
		{
			if (g_Player.nCntPlayer > 0)
			{
				g_Player.nCntPlayer--;
				g_Player.fLife = PLAYERLIFE;
				g_Player.bUse = true;
				g_Player.bDisp = true;
				g_Player.state = PLAYERSTATE_NORMAL;
			}
		}

		break;

	case PLAYERSTATE_DEATH:

		g_Player.nCountState--;

		if (g_Player.nCountState <= 0)
		{
			if (g_Player.nCntPlayer <= 0)
			{
				//�v���C���[�̏�����
				InitPlayer();

				return;																//update���甲����
			}
		}

		break;

	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//---------------------------------------------------------------------------
	//�L�[���͊Ǘ�
	//---------------------------------------------------------------------------
	if (g_Player.bUse == true)
	{
		if (GetKeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT) == true)
		{//A�L�[||���i�Q�[���p�b�h�j����

			g_Player.nCntAime++;
			g_Player.Tex_v = 0.5f;
			g_Player.bLeftRight = true;

			g_Player.move.x -= 0.5f;

			if (g_Player.bJump == true)
			{
				g_Player.move.x -= 0.25f;
			}

			else
			{
				//�A�j���[�V����
				if ((g_Player.nCntAime % nCntAnim) == 0)
				{
					g_Player.Anime++;

					//�e�N�X�`��
					pVtx[0].tex = D3DXVECTOR2(0.00f + 0.25f * g_Player.Anime, g_Player.Tex_v);
					pVtx[1].tex = D3DXVECTOR2(0.25f + 0.25f * g_Player.Anime, g_Player.Tex_v);
					pVtx[2].tex = D3DXVECTOR2(0.00f + 0.25f * g_Player.Anime, g_Player.Tex_v + 0.5f);
					pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f * g_Player.Anime, g_Player.Tex_v + 0.5f);

					g_Player.nCntAime = 0;

					//�e�N�X�`���p�^�[���̏�����
					if (g_Player.Anime >= 4)
					{
						g_Player.Anime = 0;
					}
				}
			}
		}

		else if (GetKeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGHT) == true)
		{//D�L�[�������ꂽ

			g_Player.nCntAime++;
			g_Player.Tex_v = 0.0f;
			g_Player.bLeftRight = false;

			g_Player.move.x += 0.5f;

			if (g_Player.bJump == true)
			{
				g_Player.move.x += 0.25;
			}

			else
			{
				//�A�j���[�V����
				if ((g_Player.nCntAime % nCntAnim) == 0)
				{
					g_Player.Anime++;

					//�e�N�X�`��
					pVtx[0].tex = D3DXVECTOR2(0.00f + 0.25f * g_Player.Anime, g_Player.Tex_v);
					pVtx[1].tex = D3DXVECTOR2(0.25f + 0.25f * g_Player.Anime, g_Player.Tex_v);
					pVtx[2].tex = D3DXVECTOR2(0.00f + 0.25f * g_Player.Anime, g_Player.Tex_v + 0.5f);
					pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f * g_Player.Anime, g_Player.Tex_v + 0.5f);

					g_Player.nCntAime = 0;

					//�e�N�X�`���p�^�[���̏�����
					if (g_Player.Anime >= 4)
					{
						g_Player.Anime = 0;
					}
				}
			}
		}

		else//�~�܂��Ă�Ƃ�
		{
			pVtx[0].tex = D3DXVECTOR2(0.00f, g_Player.Tex_v);
			pVtx[1].tex = D3DXVECTOR2(0.25f, g_Player.Tex_v);
			pVtx[2].tex = D3DXVECTOR2(0.00f, g_Player.Tex_v + 0.5f);
			pVtx[3].tex = D3DXVECTOR2(0.25f, g_Player.Tex_v + 0.5f);
		}

		if (g_Player.bJump == false)
		{
			if (KeyboardTrigger(DIK_SPACE) == true)
			{//�X�y�[�X�L�[�������ꂽ�i�W�����v�j

				g_Player.move.y = (-JUMP);

				//�W�����v���Ă����Ԃɂ���
				g_Player.bJump = true;
			}
		}

		//�_�b�V��
		if (g_Player.bDash == false)
		{
			if (KeyboardTrigger(DIK_J) == true || KeyboardTrigger(DIK_LSHIFT) == true /*|| KeyboardTrigger(DIK_RSHIFT) == true*/)
			{
				int nData = 0;

				if (g_Player.bLeftRight == true)
				{
					nData = -1;
				}
				else if (g_Player.bLeftRight == false)
				{
					nData = 1;
				}

				g_Player.move.x += DASH * nData;
				g_Player.move.y -= G * 3.0f;
				g_Player.bDash = true;
			}
		}

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPlayer->Unlock();

		//�d��
		g_Player.move.y += G;

		//�O��̈ʒu��ۑ�
		g_Player.posOld = g_Player.pos;

		//�ʒu���X�V
		g_Player.pos.x += g_Player.move.x;
		g_Player.pos.y += g_Player.move.y;

		//�u���b�N�Ƃ̓����蔻��
		g_Player.bJump = !CollisionBlock(&g_Player.pos, &g_Player.posOld, &g_Player.move,&g_Player.bDash, NUM_WIDTH, NUM_HEIGHT);

		//�ړ��ʂ��X�V�i�����j
		g_Player.move.x += (0.0f - g_Player.move.x) * 0.11f;

		//��ʊO����
		if ((g_Player.pos.x + (NUM_WIDTH / 2.0f)) < 0.0f)							//��
		{
			g_Player.pos.x = SCREEN_WIDTH + (NUM_WIDTH / 2);
		}
		else if ((g_Player.pos.x - (NUM_WIDTH / 2.0f)) > SCREEN_WIDTH)				//�E
		{
			g_Player.pos.x = 0.0f - (NUM_WIDTH / 2);
		}

		if (g_Player.pos.y + NUM_HEIGHT/2 < 0.0f)									//��
		{
			g_Player.pos.y = NUM_HEIGHT / 2;
		}
		else if (g_Player.pos.y >= SCREEN_HEIGHT)									//��
		{
			g_Player.pos.y = SCREEN_HEIGHT;
			g_Player.move.y = 0.0f;

			//�W�����v���Ă��Ȃ���Ԃɂ���
			g_Player.bJump = false;

			//�_�b�V�����Ă��Ȃ���Ԃɂ���
			if (g_Player.bDash == true)
			{
				g_Player.bDash = false;
			}

		}

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_Player.pos.x - (NUM_WIDTH / 2.0f);
		pVtx[0].pos.y = g_Player.pos.y - NUM_HEIGHT;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Player.pos.x + (NUM_WIDTH / 2.0f);
		pVtx[1].pos.y = g_Player.pos.y - NUM_HEIGHT;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Player.pos.x - (NUM_WIDTH / 2.0f);
		pVtx[2].pos.y = g_Player.pos.y;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Player.pos.x + (NUM_WIDTH / 2.0f);
		pVtx[3].pos.y = g_Player.pos.y;
		pVtx[3].pos.z = 0.0f;

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPlayer->Unlock();
	}
}

//=============================================================================================================
//�v���C���[�̏I������
//=============================================================================================================
void UninitPlayer()
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//=============================================================================================================
//�v���C���[�̃_���[�W����
//=============================================================================================================
void HitPlayer(float fDamage)
{
	g_Player.fLife -= fDamage;

	if (g_Player.fLife <= 0)
	{
		if (g_Player.nCntPlayer <= 0)
		{
			g_Player.nCountState = 20;
			g_Player.bUse = false;
			g_Player.bDisp = false;
			g_Player.state = PLAYERSTATE_DEATH;
		}
		else if(g_Player.nCntPlayer > 0)
		{
			g_Player.nCountState = 20;
			g_Player.bUse = false;
			g_Player.bDisp = false;
			g_Player.state = PLAYERSTATE_APPEAR;
		}
	}

	else
	{
		g_Player.nCountState = 5;												//�_���[�W��Ԃ�ۂ��Ԃ�ݒ�
		g_Player.state = PLAYERSTATE_DAMAGE;

		VERTEX_2D* pVtx;

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPlayer->Unlock();

	}
}

//=============================================================================================================
//�v���C���[�̎擾
//=============================================================================================================
Player*GetPlayer()
{
	return &g_Player;
}
//============================================================
//
//�Q�[�����[game.cpp]
//Author:Rio Ohno
//
//============================================================

#include"game.h"
#include"player.h"
#include"block.h"
#include"input.h"
#include"main.h"
#include"fade.h"
#include"Time.h"
#include"backgraund.h"
//#include"pause.h"
#include"result.h"

//�O���[�o���ϐ�
GAMESTATE g_gameState = GAMESTATE_NONE;
int g_nCounterGameStat = 0;
bool g_bPause = false;
bool g_bParticle = false;

//=============================================================================================================
//�Q�[����ʂ̏���������
//=============================================================================================================
void InitGame()
{
	//�w�i�̏���������
	Initbackgraund();

	////�|�[�Y�̏���������
	////InitPause();

	//�v���C���[�̏���������
	InitPlayer();

	////�G�t�F�N�g�̏�����
	//InitEffect();

	//�u���b�N�̏�����
	InitBlock();

	//�u���b�N�̐ݒ�
	SetBlock(D3DXVECTOR3(75.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(12.0f, 0.5f), BLOCK_NULL, 150.0f, 25.0f);
	SetBlock(D3DXVECTOR3(640.0f, 600.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(8.0f, 1.0f), BLOCK_NULL, 380.0f, 100.0f);

	//��
	SetBlock(D3DXVECTOR3(400.0f, 705.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f), BLOCK_THORN, 30.0f, 30.0f);

	//�^�C���̏�����
	InitTime(TIME_CNTUP);

	////�E�F�[�u�̏�����
	//InitWave();

	g_gameState = GAMESTATE_NORMAL;
	g_bPause = false;
	g_nCounterGameStat = 0;

	////�Q�[���̓Ǎ�����
	//LoadWave();
}

//=============================================================================================================
//�Q�[����ʂ̏I������
//=============================================================================================================
void UninitGame()
{
	//�w�i�̏I������
	Uninitbackgraund();

	////�|�[�Y�̏I������
	//UninitPause();

	//�v���C���[�̏I������
	UninitPlayer();

	//�u���b�N�̏I������
	UninitBlock();

	//�^�C���̏I������
	UninitTime();
}

//=============================================================================================================
//�Q�[����ʂ̍X�V����
//=============================================================================================================
void UpdateGame()
{
	if (KeyboardTrigger(DIK_P) == true)
	{//�|�[�Y�iP�L�[�j�������ꂽ�Ƃ�
		g_bPause = g_bPause ? false : true;
	}

	//�|�[�Y��
	if (g_bPause == true)
	{
		////�|�[�Y�̍X�V����
		//UpdatePause();
	}
		//�w�i�̍X�V����
		Updatebackgraund();

		if (g_bPause == false)
		{
			//�v���C���[�̍X�V����
			UpdatePlayer();

			//�u���b�N�̍X�V����
			UpdateBlock();

			//�^�C���̍X�V����
			UpdateTime();

		}

	#ifdef  _DEBUG
	
		if (KeyboardTrigger(DIK_O) == true)
		{
			g_bParticle = g_bParticle ? false : true;
		}

		if (KeyboardTrigger(DIK_M)==true)//�Q�[���̏I������
		{
			g_gameState = GAMESTATE_END;
		}
	
	#endif //  _DEBUG

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:


		break;

	case GAMESTATE_END:

		g_nCounterGameStat++;

		if (g_nCounterGameStat >= 60)
		{
			g_nCounterGameStat = 0;
			g_gameState = GAMESTATE_NONE;

			//��ʂ̐ݒ�
			SetFade(MODE_RESULT);
		}
		break;
	}
}

//=============================================================================================================
//�Q�[����ʂ̕`�揈��
//=============================================================================================================
void DrawGame()
{
	//�w�i�̕`�揈��
	Drawbackgraund();

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//�u���b�N�̕`�揈��
	DrawBlock();

	//�^�C���̕`�揈��
	DrawTime();

	//�|�[�Y��
	if (g_bPause == true)
	{
		////�|�[�Y�̕`�揈��
		//DrawPause();
	}
}

//=============================================================================================================
//�Q�[���̏�Ԃ̐ݒ�
//=============================================================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
}

//=============================================================================================================
//�|�[�Y�̗L�������ݒ�ݒ�
//=============================================================================================================
void SetEnablePause(bool bPause) 
{
	g_bPause = bPause;
}

//=============================================================================================================
//�Q�[���̏�Ԃ̎擾
//=============================================================================================================
GAMESTATE GetGameState()
{
	return g_gameState;
}
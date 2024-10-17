//============================================================
//
//�V���[�e�B���O�Q�[[player.h]
//Author:Rio Ohno
//
//============================================================

#ifndef _Player_H_
#define _Player_H_

#include"main.h"

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_NORMAL = 0,								//�ʏ펞
	PLAYERSTATE_DAMAGE,									//�_���[�W���
	PLAYERSTATE_APPEAR,									//�������̖��G���
	PLAYERSTATE_DEATH,									//���S���
	PLAYERSTATE_MAX
}PLAYERSTATE;

//�v���C���[�̍\����`
typedef struct
{
	D3DXVECTOR3 pos;                                    //�ʒu
	D3DXVECTOR3 posOld;									//�O��̈ʒu
	D3DXVECTOR3 move;                                   //�ړ���
	D3DXVECTOR3 rot;                                    //����
	PLAYERSTATE state;                                  //�v���C���[�̏��
	int nCountState;                                    //��ԊǗ��J�E���^�[
	int nCntPlayer;										//�v���C���[�̎c�@��
	int nCntAime;										//�v���C���[�̃A�j���[�V�����p
	int Anime;											//�v���C���[�̃A�j���[�V�����p
	float Tex_v;										//�e�N�X�`����Y���W
	float fLength;                                      //�Ίp���̒���
	float fAngle;                                       //�Ίp���̊p�x
	float fLife;                                        //�̗�
	bool bUse;                                          //�g�p���Ă��邩�ǂ���
	bool bDisp;											//�`�悷�邩�ǂ���
	bool bJump;											//�W�����v���Ă��邩�ǂ���
	bool bDash;											//�_�b�V�����Ă��邩�ǂ���
	bool bLeftRight;									//[true]:��,[false]:�E
}Player;

//�v���g�^�C�v�錾
void InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();
void HitPlayer(float fDamage);
void StatePlayer();
Player* GetPlayer();

#endif // !_Player_H_

//============================================================
//
//�V���[�e�B���O�Q�[[BLOCK.h]
//Author:Rio Ohno
//
//============================================================

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

typedef enum
{
	BLOCK_NULL=0,
	BLOCK_THORN,					//��
	BLOCK_MAX
}BLOCKTYPE;

//�v���g�^�C�v�錾
void InitBlock();
void UninitBlock();
void UpdateBlock();
void DrawBlock();
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR2  tex, BLOCKTYPE type, float fWidthBlock, float fHeightBlock);
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove,bool*pDash, float fWidth, float fHeight);

//============================================================================================================================================
//�f�o�b�N�p
//============================================================================================================================================
int GetNumBlock();
#endif // !_BLOCK_H
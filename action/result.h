//============================================================
//
//�V���[�e�B���O�Q�[[result.h]
//Author:Rio Ohno
//
//============================================================

#ifndef _RESULT_H_
#define _RESULT_H_

#include"main.h"

//���ʕ���
typedef enum
{
	RESULT_WIN=0,
	RESULT_LOSE,
	RESULT_MAX
}RESULT;

//�v���g�^�C�v�錾
void InitResult();
void UninitResult();
void UpdateResult();
void DrawResult();
void SetResult(RESULT result);

#endif // !_RESULT_H_


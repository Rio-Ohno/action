//========================================================
// 
// �^�C�}�[����[Time.h]
// Author:Rio Ohno
// 
//========================================================

#ifndef _TIME_H_
#define _TIME_H_

#include"main.h"

typedef enum
{
	TIME_CNTUP=0,//�X�g�b�v�E�H�b�`
	TIME_CNTDOWN,//�^�C�}�[
	TIME_MAX
}TIMETYPE;

//�v���g�^�C�v�錾
void InitTime(TIMETYPE type);
void UninitTime();
void UpdateTime();
void SetTime();
void DrawTime();

#endif // !_TIME_H_
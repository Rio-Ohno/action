//============================================================
//
//シューティングゲー[result.h]
//Author:Rio Ohno
//
//============================================================

#ifndef _RESULT_H_
#define _RESULT_H_

#include"main.h"

//結果分け
typedef enum
{
	RESULT_WIN=0,
	RESULT_LOSE,
	RESULT_MAX
}RESULT;

//プロトタイプ宣言
void InitResult();
void UninitResult();
void UpdateResult();
void DrawResult();
void SetResult(RESULT result);

#endif // !_RESULT_H_


//=======================================================
// 
// アイテム処理[item.h]
// Author:Rio Ohno
// 
//=======================================================

#ifndef _ITEM_H_
#define _ITEM_H_

#include"main.h"

//マクロ定義
#define MAX_ITEM (2)

//アイテムの種類
typedef enum
{
	ITEMTYPE_ZERO=0,
	ITEMTYPE_ONE,
	ITEMTYPE_MAX
}ITEMTYPE;

//アイテム構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	ITEMTYPE type;
}Item;

//プロトタイプ宣言
void InitItem();
void UninitItem();
void UpdateItem();
void DrawItem();

#endif // !_ITEM_H_

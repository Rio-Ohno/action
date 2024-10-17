//=======================================================
// 
// �A�C�e������[item.h]
// Author:Rio Ohno
// 
//=======================================================

#ifndef _ITEM_H_
#define _ITEM_H_

#include"main.h"

//�}�N����`
#define MAX_ITEM (2)

//�A�C�e���̎��
typedef enum
{
	ITEMTYPE_ZERO=0,
	ITEMTYPE_ONE,
	ITEMTYPE_MAX
}ITEMTYPE;

//�A�C�e���\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	ITEMTYPE type;
}Item;

//�v���g�^�C�v�錾
void InitItem();
void UninitItem();
void UpdateItem();
void DrawItem();

#endif // !_ITEM_H_

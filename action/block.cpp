//============================================================
//
//ブロック[Block.cpp]
//Author:Rio Ohno
//
//============================================================

#include"block.h"
#include"player.h"

//マクロ定義
#define MAX_BLOCK (3)																				//ブロックの最大数

//プレイヤーの弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;																				//位置
	D3DXVECTOR3 move;																				//移動量
	D3DXVECTOR3 rot;																				//向き
	BLOCKTYPE type;																					//種類
	float fWidthBlock;																				//ポリゴンの幅
	float fHeighBlock;																				//ポリゴンの高さ
	float fTex_x;																					//テクスチャのx座標
	float fTex_y;																					//テクスチャのｙ座標
	bool bUse;																						//使用しているかどう
}Block;

//テクスチャ
static const char* BLOCK_TEXTURE[BLOCK_MAX] =
{
	"data\\TEXTURE\\block000.jpg",
	"data\\TEXTURE\\toge000.png",
};

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBlock[BLOCK_MAX] = {};													//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;														//頂点バッファへのポインタ
Block g_aBlock[MAX_BLOCK];																			//ブロックの情報
int nNumBlock = 0;											

//=============================================================================================================
//ブロックの初期化処理
//=============================================================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock = NULL;

	//デバイスに取得
	pDevice = GetDevice();


	//ブロックの情報の初期化
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//位置の初期化
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//移動量の初期化
		g_aBlock[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//角度の初期化
		g_aBlock[nCntBlock].type = BLOCK_NULL;														//種類の初期化
		g_aBlock[nCntBlock].bUse = false;															//使用していない状態にする

		//テクスチャの読込
		D3DXCreateTextureFromFile(pDevice,
			BLOCK_TEXTURE[g_aBlock[nCntBlock].type],
			&g_pTextureBlock[g_aBlock[nCntBlock].type]);

	}


	nNumBlock = 0;																					//弾数の初期化

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D * pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//頂点座標の設定
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

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

		pVtx += 4;//頂点データのポインタを4つ分進める
	}
	//頂点バッファのアンロック
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================================================
//ブロックの終了処理
//=============================================================================================================
void UninitBlock()
{
	//テクスチャの破棄
	for (int nCntBlock = 0; nCntBlock < BLOCK_MAX; nCntBlock++)
	{
		if (g_pTextureBlock[nCntBlock] != NULL)
		{
			g_pTextureBlock[nCntBlock]->Release();
			g_pTextureBlock[nCntBlock] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//=============================================================================================================
//ブロックの更新処理
//=============================================================================================================
void UpdateBlock()
{

}

//=============================================================================================================
//ブロックの描画処理
//=============================================================================================================
void DrawBlock()
{
	int nCntBlock;
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//ブロックが使用されている

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].type]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntBlock*4,2);
		}
	}
}

//=============================================================================================================
//ブロックの設定処理
//=============================================================================================================
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR2  tex, BLOCKTYPE type, float fWidthBlock, float fHeightBlock)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D* pVtx;

	int nCntBlock;

	//デバイスに取得
	pDevice = GetDevice();

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{
			//ブロックが使用されていないとき
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].fWidthBlock = fWidthBlock;
			g_aBlock[nCntBlock].fHeighBlock = fHeightBlock;
			g_aBlock[nCntBlock].type = type;

			//テクスチャの読込
			D3DXCreateTextureFromFile(pDevice,
				BLOCK_TEXTURE[g_aBlock[nCntBlock].type],
				&g_pTextureBlock[g_aBlock[nCntBlock].type]);


			//頂点座標の設定
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

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(tex.x, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, tex.y);
			pVtx[3].tex = D3DXVECTOR2(tex.x, tex.y);

			g_aBlock[nCntBlock].move = move;														//移動量の設定
			g_aBlock[nCntBlock].bUse = true;														//使用してる状態にする

			nNumBlock++;																			//ブロックの数カウント
			break;
		}
		pVtx += 4;
	}
	//アンロック
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================================================
//ブロックの数の取得
//=============================================================================================================
int GetNumBlock()
{
	return nNumBlock;
}

//=============================================================================================================
//ブロックの当たり判定
//=============================================================================================================
//プレイヤーのpos,前回のプレイヤーのpos,プレイヤーの移動量,プレイヤーの幅,プレイヤーの高さ
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, bool* pDash,float fWidth, float fHeight)
{
	bool Landing = false;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		const float fAbove = g_aBlock[nCntBlock].pos.y - (g_aBlock[nCntBlock].fHeighBlock / 2.0f);	//上
		const float fBelow = g_aBlock[nCntBlock].pos.y + (g_aBlock[nCntBlock].fHeighBlock / 2.0f);	//下
		const float fLeft = g_aBlock[nCntBlock].pos.x - (g_aBlock[nCntBlock].fWidthBlock / 2.0f);	//左
		const float fRight = g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWidthBlock / 2.0f);	//右

		if (g_aBlock[nCntBlock].bUse == true)
		{
			//上下の当たり判定
			if (pPos->x + (fWidth / 2.0f) > fLeft
				&& pPos->x - (fWidth / 2.0f) < fRight)
			{
				//プレイヤーが上から下にめり込んだ
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
				//プレイヤーが下から上にめり込んだ
				else if ((pPosOld->y - fHeight) >= fBelow
					&& (pPos->y - fHeight) < fBelow)
				{
					pPos->y = fBelow + fHeight;
					pMove->y = 0.0f;
					Landing = true;
				}
			}

			//横の当たり判定
			if (pPosOld->y > fAbove
				&& pPosOld->y - fHeight < fBelow)
			{
				//プレイヤーが左から右にめり込んだ
				if (pPosOld->x + (fWidth / 2.0f) <= fLeft
					&& pPos->x + (fWidth / 2.0f) > fLeft)
				{
					pPos->x = fLeft - (fWidth / 2.0f);
					pMove->x = 0.0f;
				}
				//プレイヤーが右から左にめり込んだ
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


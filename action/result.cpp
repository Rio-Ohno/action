//============================================================
//
//リザルト画面[result.cpp]
//Author:Rio Ohno
//
//============================================================

#include"result.h"
#include"input.h"
#include"game.h"
#include"fade.h"

//マクロ定義
#define MAX_POLY_RESULT (3)

//テクスチャ
static const char* RESULT_TEXTURE[RESULT_MAX] =
{
	"data\\TEXTURE\\GAMECLEAR000.png",
	"data\\TEXTURE\\GameOver000.png",
};

static const char* RESULTBG_TEXTURE[RESULT_MAX] =
{
	"data\\TEXTURE\\night000.png",
	"data\\TEXTURE\\Reslut000.png",
};

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureResult[MAX_POLY_RESULT] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult;
RESULT g_Result = RESULT_LOSE;
float g_Tex_y[3];

//=============================================================================================================
//タイトル画面の初期化処理
//=============================================================================================================
void InitResult()
{
	LPDIRECT3DDEVICE9 pDevice;                                                  //デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読込
	D3DXCreateTextureFromFile(pDevice,
		RESULTBG_TEXTURE[g_Result],
		&g_pTextureResult[0]);

	//テクスチャの取得
	D3DXCreateTextureFromFile(pDevice,
		RESULT_TEXTURE[g_Result],
		&g_pTextureResult[1]);

	//テクスチャの取得
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Coment000.png",
		&g_pTextureResult[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLY_RESULT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	for (int nCnt = 0; nCnt < MAX_POLY_RESULT; nCnt++)
	{
		g_Tex_y[nCnt] = 0;
	}

	g_Result = RESULT_LOSE;

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_POLY_RESULT; nCnt++)
	{
		if (nCnt == 0)
		{
			//頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
		}
		else if (nCnt == 1)
		{
			//頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(325.0f, 200.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(925.0f, 200.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(325.0f, 300.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(925.0f, 300.0f, 0.0f);
		}
		else if (nCnt == 2)
		{
			//頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(790.0f, 625.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1200.0f, 625.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(790.0f, 700.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1200.0f, 700.0f, 0.0f);
		}

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + g_Tex_y[nCnt]);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + g_Tex_y[nCnt]);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + g_Tex_y[nCnt]);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f + g_Tex_y[nCnt]);

		pVtx += 4;

	}
	//頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();
}

//=============================================================================================================
//タイトル画面の終了処理
//=============================================================================================================
void UninitResult()
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < MAX_POLY_RESULT; nCnt++)
	{
		if (g_pTextureResult[nCnt] != NULL)
		{
			g_pTextureResult[nCnt]->Release();
			g_pTextureResult[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//=============================================================================================================
//タイトル画面の更新処理
//=============================================================================================================
void UpdateResult()
{
	VERTEX_2D* pVtx{};

	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		//決定キー（ENTERキー）が押された
		//モード設定（ゲーム画面に移行）
		SetFade(MODE_TITLE);
	}
	else if (KeyboardTrigger(DIK_R) == true)
	{	
		//Rキーが押された
		//ランキングに移行
		SetMode(MODE_RANKING);
		return;
	}

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_POLY_RESULT; nCnt++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + g_Tex_y[nCnt]);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + g_Tex_y[nCnt]);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + g_Tex_y[nCnt]);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f + g_Tex_y[nCnt]);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();

}

//=============================================================================================================
//タイトル画面の描画処理
//=============================================================================================================
void DrawResult()
{
	LPDIRECT3DDEVICE9 pDevice;                                                  //デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (int nCnt = 0; nCnt < MAX_POLY_RESULT; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureResult[nCnt]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}

//=============================================================================================================
//結果の取得
//=============================================================================================================
void SetResult(RESULT result)
{
	g_Result=result;
}
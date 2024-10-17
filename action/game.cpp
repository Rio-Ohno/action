//============================================================
//
//ゲーム画面[game.cpp]
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

//グローバル変数
GAMESTATE g_gameState = GAMESTATE_NONE;
int g_nCounterGameStat = 0;
bool g_bPause = false;
bool g_bParticle = false;

//=============================================================================================================
//ゲーム画面の初期化処理
//=============================================================================================================
void InitGame()
{
	//背景の初期化処理
	Initbackgraund();

	////ポーズの初期化処理
	////InitPause();

	//プレイヤーの初期化処理
	InitPlayer();

	////エフェクトの初期化
	//InitEffect();

	//ブロックの初期化
	InitBlock();

	//ブロックの設定
	SetBlock(D3DXVECTOR3(75.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(12.0f, 0.5f), BLOCK_NULL, 150.0f, 25.0f);
	SetBlock(D3DXVECTOR3(640.0f, 600.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(8.0f, 1.0f), BLOCK_NULL, 380.0f, 100.0f);

	//棘
	SetBlock(D3DXVECTOR3(400.0f, 705.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f), BLOCK_THORN, 30.0f, 30.0f);

	//タイムの初期化
	InitTime(TIME_CNTUP);

	////ウェーブの初期化
	//InitWave();

	g_gameState = GAMESTATE_NORMAL;
	g_bPause = false;
	g_nCounterGameStat = 0;

	////ゲームの読込処理
	//LoadWave();
}

//=============================================================================================================
//ゲーム画面の終了処理
//=============================================================================================================
void UninitGame()
{
	//背景の終了処理
	Uninitbackgraund();

	////ポーズの終了処理
	//UninitPause();

	//プレイヤーの終了処理
	UninitPlayer();

	//ブロックの終了処理
	UninitBlock();

	//タイムの終了処理
	UninitTime();
}

//=============================================================================================================
//ゲーム画面の更新処理
//=============================================================================================================
void UpdateGame()
{
	if (KeyboardTrigger(DIK_P) == true)
	{//ポーズ（Pキー）が押されたとき
		g_bPause = g_bPause ? false : true;
	}

	//ポーズ中
	if (g_bPause == true)
	{
		////ポーズの更新処理
		//UpdatePause();
	}
		//背景の更新処理
		Updatebackgraund();

		if (g_bPause == false)
		{
			//プレイヤーの更新処理
			UpdatePlayer();

			//ブロックの更新処理
			UpdateBlock();

			//タイムの更新処理
			UpdateTime();

		}

	#ifdef  _DEBUG
	
		if (KeyboardTrigger(DIK_O) == true)
		{
			g_bParticle = g_bParticle ? false : true;
		}

		if (KeyboardTrigger(DIK_M)==true)//ゲームの終わる条件
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

			//画面の設定
			SetFade(MODE_RESULT);
		}
		break;
	}
}

//=============================================================================================================
//ゲーム画面の描画処理
//=============================================================================================================
void DrawGame()
{
	//背景の描画処理
	Drawbackgraund();

	//プレイヤーの描画処理
	DrawPlayer();

	//ブロックの描画処理
	DrawBlock();

	//タイムの描画処理
	DrawTime();

	//ポーズ中
	if (g_bPause == true)
	{
		////ポーズの描画処理
		//DrawPause();
	}
}

//=============================================================================================================
//ゲームの状態の設定
//=============================================================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
}

//=============================================================================================================
//ポーズの有効無効設定設定
//=============================================================================================================
void SetEnablePause(bool bPause) 
{
	g_bPause = bPause;
}

//=============================================================================================================
//ゲームの状態の取得
//=============================================================================================================
GAMESTATE GetGameState()
{
	return g_gameState;
}
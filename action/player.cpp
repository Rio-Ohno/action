//============================================================
//
//プレイヤー[player.cpp]
//Author:Rio Ohno
//
//============================================================

#include"player.h"
#include"input.h"
#include"block.h"
#include"fade.h"

//マクロ定義
#define NUM_WIDTH (50)											                //ポリゴンの幅
#define NUM_HEIGHT (50)												            //ポリゴンの高さ
#define PLAYERLIFE (1.0f)														//プレイヤーのライフ
#define JUMP (18.0f)															//プレイヤーのジャンプ力
#define G (0.8f)																//重力
#define  DASH  (35.0f)															//ダッシュ

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;                                     //テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePlayerPos = NULL;                                  //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer=NULL;                                  //頂点情報を格納
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerPos = NULL;                             //頂点情報を格納
Player g_Player;

//=============================================================================================================
//プレイヤーの初期化処理
//=============================================================================================================
void InitPlayer()
{

	LPDIRECT3DDEVICE9 pDevice;													//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読込
	D3DXCreateTextureFromFile(pDevice,
		NULL,
		&g_pTexturePlayer);

	g_Player.pos = D3DXVECTOR3(75.0f,187.5f,0);									//位置を初期化する
	g_Player.posOld = {};														//前回の位置を初期化する
	g_Player.move = D3DXVECTOR3(0.0f,0.0f,0.0f);								//移動量を初期化する
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								//向きを初期化する
	g_Player.state = PLAYERSTATE_NORMAL;										//敵の状態の初期化
	g_Player.nCountState = 0;													//状態管理用カウンターの初期化
	g_Player.nCntPlayer = 0;													//残機数を初期化
	g_Player.nCntAime = 0;														//アニメーション用カウンターの初期化
	g_Player.Anime = 0;															//アニメーション用カウンターの初期化
	g_Player.Tex_v = 0;															//テクスチャY座標保存用
	g_Player.fLife = PLAYERLIFE;												//体力の初期化
	g_Player.bUse = true;														//自機を使用状態にする
	g_Player.bDisp = true;														//表示状態にする
	g_Player.bJump = false;														//ジャンプしていない状態にする
	g_Player.bDash = false;														//ダッシュしていない状態にする

	//頂点バッファのの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,                               
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D* pVtx;															 //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = g_Player.pos.x - (NUM_WIDTH / 2.0f);
	pVtx[0].pos.y = g_Player.pos.y - NUM_HEIGHT;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Player.pos.x + (NUM_WIDTH / 2.0f);
	pVtx[1].pos.y = g_Player.pos.y - NUM_HEIGHT;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Player.pos.x - (NUM_WIDTH / 2.0f);
	pVtx[2].pos.y = g_Player.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Player.pos.x + (NUM_WIDTH / 2.0f);
	pVtx[3].pos.y = g_Player.pos.y;
	pVtx[3].pos.z = 0.0f;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//=============================================================================================================
//プレイヤーの描画処理
//=============================================================================================================
void DrawPlayer()
{
	LPDIRECT3DDEVICE9 pDevice;														//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	if (g_Player.bDisp == true)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer);

		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	}
}

//=============================================================================================================
//プレイヤーの更新処理
//=============================================================================================================
void UpdatePlayer()
{
	VERTEX_2D* pVtx;//頂点情報へのポインタ

	int nCntAnim=30;//アニメーションの剰余算のとこ
	
	switch (g_Player.state)
	{
	case PLAYERSTATE_NORMAL:

		break;

	case PLAYERSTATE_DAMAGE:

		g_Player.nCountState--;

		if (g_Player.nCountState <= 0)
		{
			g_Player.state = PLAYERSTATE_NORMAL;

			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

			//頂点バッファをアンロックする
			g_pVtxBuffPlayer->Unlock();
		}

		break;

	case PLAYERSTATE_APPEAR:

		g_Player.nCountState--;

		if (g_Player.nCountState <= 0)
		{
			if (g_Player.nCntPlayer > 0)
			{
				g_Player.nCntPlayer--;
				g_Player.fLife = PLAYERLIFE;
				g_Player.bUse = true;
				g_Player.bDisp = true;
				g_Player.state = PLAYERSTATE_NORMAL;
			}
		}

		break;

	case PLAYERSTATE_DEATH:

		g_Player.nCountState--;

		if (g_Player.nCountState <= 0)
		{
			if (g_Player.nCntPlayer <= 0)
			{
				//プレイヤーの初期化
				InitPlayer();

				return;																//updateから抜ける
			}
		}

		break;

	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//---------------------------------------------------------------------------
	//キー入力管理
	//---------------------------------------------------------------------------
	if (g_Player.bUse == true)
	{
		if (GetKeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT) == true)
		{//Aキー||左（ゲームパッド）だけ

			g_Player.nCntAime++;
			g_Player.Tex_v = 0.5f;
			g_Player.bLeftRight = true;

			g_Player.move.x -= 0.5f;

			if (g_Player.bJump == true)
			{
				g_Player.move.x -= 0.25f;
			}

			else
			{
				//アニメーション
				if ((g_Player.nCntAime % nCntAnim) == 0)
				{
					g_Player.Anime++;

					//テクスチャ
					pVtx[0].tex = D3DXVECTOR2(0.00f + 0.25f * g_Player.Anime, g_Player.Tex_v);
					pVtx[1].tex = D3DXVECTOR2(0.25f + 0.25f * g_Player.Anime, g_Player.Tex_v);
					pVtx[2].tex = D3DXVECTOR2(0.00f + 0.25f * g_Player.Anime, g_Player.Tex_v + 0.5f);
					pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f * g_Player.Anime, g_Player.Tex_v + 0.5f);

					g_Player.nCntAime = 0;

					//テクスチャパターンの初期化
					if (g_Player.Anime >= 4)
					{
						g_Player.Anime = 0;
					}
				}
			}
		}

		else if (GetKeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGHT) == true)
		{//Dキーが押された

			g_Player.nCntAime++;
			g_Player.Tex_v = 0.0f;
			g_Player.bLeftRight = false;

			g_Player.move.x += 0.5f;

			if (g_Player.bJump == true)
			{
				g_Player.move.x += 0.25;
			}

			else
			{
				//アニメーション
				if ((g_Player.nCntAime % nCntAnim) == 0)
				{
					g_Player.Anime++;

					//テクスチャ
					pVtx[0].tex = D3DXVECTOR2(0.00f + 0.25f * g_Player.Anime, g_Player.Tex_v);
					pVtx[1].tex = D3DXVECTOR2(0.25f + 0.25f * g_Player.Anime, g_Player.Tex_v);
					pVtx[2].tex = D3DXVECTOR2(0.00f + 0.25f * g_Player.Anime, g_Player.Tex_v + 0.5f);
					pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f * g_Player.Anime, g_Player.Tex_v + 0.5f);

					g_Player.nCntAime = 0;

					//テクスチャパターンの初期化
					if (g_Player.Anime >= 4)
					{
						g_Player.Anime = 0;
					}
				}
			}
		}

		else//止まってるとき
		{
			pVtx[0].tex = D3DXVECTOR2(0.00f, g_Player.Tex_v);
			pVtx[1].tex = D3DXVECTOR2(0.25f, g_Player.Tex_v);
			pVtx[2].tex = D3DXVECTOR2(0.00f, g_Player.Tex_v + 0.5f);
			pVtx[3].tex = D3DXVECTOR2(0.25f, g_Player.Tex_v + 0.5f);
		}

		if (g_Player.bJump == false)
		{
			if (KeyboardTrigger(DIK_SPACE) == true)
			{//スペースキーが押された（ジャンプ）

				g_Player.move.y = (-JUMP);

				//ジャンプしている状態にする
				g_Player.bJump = true;
			}
		}

		//ダッシュ
		if (g_Player.bDash == false)
		{
			if (KeyboardTrigger(DIK_J) == true || KeyboardTrigger(DIK_LSHIFT) == true /*|| KeyboardTrigger(DIK_RSHIFT) == true*/)
			{
				int nData = 0;

				if (g_Player.bLeftRight == true)
				{
					nData = -1;
				}
				else if (g_Player.bLeftRight == false)
				{
					nData = 1;
				}

				g_Player.move.x += DASH * nData;
				g_Player.move.y -= G * 3.0f;
				g_Player.bDash = true;
			}
		}

		//頂点バッファをアンロックする
		g_pVtxBuffPlayer->Unlock();

		//重力
		g_Player.move.y += G;

		//前回の位置を保存
		g_Player.posOld = g_Player.pos;

		//位置を更新
		g_Player.pos.x += g_Player.move.x;
		g_Player.pos.y += g_Player.move.y;

		//ブロックとの当たり判定
		g_Player.bJump = !CollisionBlock(&g_Player.pos, &g_Player.posOld, &g_Player.move,&g_Player.bDash, NUM_WIDTH, NUM_HEIGHT);

		//移動量を更新（減衰）
		g_Player.move.x += (0.0f - g_Player.move.x) * 0.11f;

		//画面外処理
		if ((g_Player.pos.x + (NUM_WIDTH / 2.0f)) < 0.0f)							//左
		{
			g_Player.pos.x = SCREEN_WIDTH + (NUM_WIDTH / 2);
		}
		else if ((g_Player.pos.x - (NUM_WIDTH / 2.0f)) > SCREEN_WIDTH)				//右
		{
			g_Player.pos.x = 0.0f - (NUM_WIDTH / 2);
		}

		if (g_Player.pos.y + NUM_HEIGHT/2 < 0.0f)									//上
		{
			g_Player.pos.y = NUM_HEIGHT / 2;
		}
		else if (g_Player.pos.y >= SCREEN_HEIGHT)									//下
		{
			g_Player.pos.y = SCREEN_HEIGHT;
			g_Player.move.y = 0.0f;

			//ジャンプしていない状態にする
			g_Player.bJump = false;

			//ダッシュしていない状態にする
			if (g_Player.bDash == true)
			{
				g_Player.bDash = false;
			}

		}

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos.x = g_Player.pos.x - (NUM_WIDTH / 2.0f);
		pVtx[0].pos.y = g_Player.pos.y - NUM_HEIGHT;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Player.pos.x + (NUM_WIDTH / 2.0f);
		pVtx[1].pos.y = g_Player.pos.y - NUM_HEIGHT;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Player.pos.x - (NUM_WIDTH / 2.0f);
		pVtx[2].pos.y = g_Player.pos.y;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Player.pos.x + (NUM_WIDTH / 2.0f);
		pVtx[3].pos.y = g_Player.pos.y;
		pVtx[3].pos.z = 0.0f;

		//頂点バッファをアンロックする
		g_pVtxBuffPlayer->Unlock();
	}
}

//=============================================================================================================
//プレイヤーの終了処理
//=============================================================================================================
void UninitPlayer()
{
	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//=============================================================================================================
//プレイヤーのダメージ処理
//=============================================================================================================
void HitPlayer(float fDamage)
{
	g_Player.fLife -= fDamage;

	if (g_Player.fLife <= 0)
	{
		if (g_Player.nCntPlayer <= 0)
		{
			g_Player.nCountState = 20;
			g_Player.bUse = false;
			g_Player.bDisp = false;
			g_Player.state = PLAYERSTATE_DEATH;
		}
		else if(g_Player.nCntPlayer > 0)
		{
			g_Player.nCountState = 20;
			g_Player.bUse = false;
			g_Player.bDisp = false;
			g_Player.state = PLAYERSTATE_APPEAR;
		}
	}

	else
	{
		g_Player.nCountState = 5;												//ダメージ状態を保つ時間を設定
		g_Player.state = PLAYERSTATE_DAMAGE;

		VERTEX_2D* pVtx;

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffPlayer->Unlock();

	}
}

//=============================================================================================================
//プレイヤーの取得
//=============================================================================================================
Player*GetPlayer()
{
	return &g_Player;
}
//============================================================
//
//2Dアクションゲー[main.cpp]
//Author:Rio Ohno
//
//============================================================

#include"main.h"
#include"input.h"
#include"fade.h"
#include"title.h"
#include"game.h"
#include"result.h"
#include"block.h"
#include<stdio.h>
#include<stdlib.h>
#include <crtdbg.h>

//グローバル変数宣言
LPDIRECT3D9 g_pD3D = NULL;											 //DirectX3Dオブジェクトへのポインタ
LPD3DXFONT g_pfont = NULL;											 //フォントへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;								 //DirectX3Dデバイスへのポインタ
MODE g_mode = MODE_TITLE;											 //現在のモード
int g_nCountFPS = 0;												 //FPSカウンタ

//=========================================================
//メイン関数
//=========================================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);//メモリリーク検知

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),											//WNDCLASSEXのメモリーサイズ
		CS_CLASSDC,													//ウィンドウのスタイル
		WindowProc,													//ウィンドウプロシージャ
		0,															//0にする（通常はしない）
		0,															//0にする（通常はしない）
		hInstance,													//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),								//タスクバーアイコン
		LoadCursor(NULL,IDC_ARROW),									//マウスカーソル
		(HBRUSH)(COLOR_WINDOW+1),									//クライアント領域の背景色
		NULL,														//メニューバー
		CLASS_NAME,													//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION),								//ファイルのアイコン
	};

	HWND hWnd;//ウィンドウハンドル
	MSG msg;//メッセージを格納する

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };					//画面サイズの構造体

	DWORD dwCurrentTime;											//現在時刻
	DWORD dwExecLastTime;											//最後に処理した時刻
	DWORD dwFrameCount;												//フレームカウント
	DWORD dwFPSLastTime;											//最後に計測した時刻

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成 
	hWnd = CreateWindowEx
	   (0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right-rect.left),
		(rect.bottom-rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		//初期化処理が失敗したら
		return -1;
	}

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwFrameCount = 0;
	dwExecLastTime = timeGetTime();
	dwFPSLastTime = timeGetTime();
	
	//ウィンドウの表示
	ShowWindow(hWnd,nCmdShow);//ウィンドウの表示状態を設定
	UpdateWindow(hWnd);       //クライアント領域を更新

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windowsの処理
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();								//現在時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				//FPSを加算
				g_nCountFPS = ((dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime));
				dwFPSLastTime = dwCurrentTime;							//FPSを計測した時刻を保存

				dwFrameCount = 0;										//フレームカウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60分の1秒経過
				dwExecLastTime = dwCurrentTime;							//処理開始の時刻[現在時刻]を保存

				//更新処理
				Update();

				//描画処理
				Draw();

				dwFrameCount++;											//フレームカウントを加算
			}
		}
	}

	//終了処理
	Uninit();

	//分解脳を戻す
	timeEndPeriod(1);

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================================================
//ウィンドウプロシージャ
//=============================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch(uMsg)
	{
	case WM_DESTROY://ウィンドウ破棄のメッセージ

		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:

			DestroyWindow(hWnd);
			break;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================================================
//デバイスの取得
//=============================================================================================================
LPDIRECT3DDEVICE9 GetDevice()
{
	return g_pD3DDevice;
}

//=============================================================================================================
//初期化処理
//=============================================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;             //ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;      //プレゼンテーションパラメータ

	//DirectX3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));                               //パラメータのゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;                            //ゲーム画面のサイズ（幅）
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;                          //ゲーム画面のサイズ（高さ）
	d3dpp.BackBufferFormat = d3ddm.Format;                           //バックバッファの形式
	d3dpp.BackBufferCount = 1;                                       //バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                        //ダブルバッファの切り替え（映像信号に同期）
	d3dpp.EnableAutoDepthStencil = TRUE;                             //デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                       //デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;                                        //ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//DirectX3Dデバイスの生成（描画処理と頂点処理をハードウェア行う）
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//DirectX3Dデバイスの生成（描画処理はハードウェア、頂点処理はCPUで行う）
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}

		}

	}

	//デバック表示用フォントの生成
	D3DXCreateFont(g_pD3DDevice,
		18, 0, 0, 0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal",
		&g_pfont);

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//ジョイパッドの初期化処理
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	//モードの設定
	SetMode(g_mode);

	//フェードの初期化処理
	InitFade(g_mode);

	return S_OK;
}

//=============================================================================================================
//終了処理
//=============================================================================================================
void Uninit()
{	
	//キーボードの終了処理
	UninitKeyboard();

	//ジョイパッドの終了処理
	UninitJoypad();

	//フェードの終了処理
	UninitFade();

	//デバック表示用フォントの破棄
	if (g_pfont != NULL)
	{
		g_pfont->Release();
		g_pfont = NULL;
	}

	//DirectX3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	//DirectX3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================================================================================
//更新処理
//=============================================================================================================
void Update()
{
	//キーボードの更新処理
	UpdateKeyboard();

	//ジョイパッドの更新処理
	UpdateJoypad();

	switch (g_mode)
	{
	case MODE_TITLE:

		UpdateTitle();
		break;

	case MODE_TUTORIAL:

		break;

	case MODE_GAME:

		UpdateGame();
		break;

	case MODE_RESULT://リザルト画面
		UpdateResult();
		break;

	default:

		break;
	}

	//フェードの更新処理
	UpdateFade();
}

//=============================================================================================================
//描画処理
//=============================================================================================================
void Draw()
{
	//画面クリア（バックバッファ＆Zバッファのクリア）
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
		case MODE_TITLE://タイトル画面
			DrawTitle();
			break;

		case MODE_TUTORIAL://チュートリアル画面
			break;

		case MODE_GAME://ゲーム画面
			DrawGame();
			break;

		case MODE_RESULT://リザルト画面
			DrawResult();
			break;

		case MODE_RANKING://ランキング
			//DrawRanking();
			break;
		}

		//フェードの描画処理
		DrawFade();

		#ifdef _DEBUG

			//FPSの表示
			DrawFPS();

			////弾数の表示
			DrawNumBlock();

		#endif // _DEBUG


		//描画終了
		g_pD3DDevice->EndScene();
	}
	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================================================
//FPSの表示(デバック用)
//=============================================================================================================
void DrawFPS()
{
	char a_Str[20];
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//文字列に代入
	wsprintf(&a_Str[0], "FPS:%d\n", g_nCountFPS);

	//テキストの描画
	g_pfont->DrawText(NULL, &a_Str[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=============================================================================================================
//弾数の表示(デバック用)
//=============================================================================================================
void DrawNumBlock()
{
	char a_Str1[20];
	RECT rect = { 0,15,SCREEN_WIDTH,SCREEN_HEIGHT };

	int nNumBullet = GetNumBlock();

	//文字列に代入
	wsprintf(&a_Str1[0], "ブロック数:%d\n", nNumBullet);

	//テキストの描画
	g_pfont->DrawText(NULL, &a_Str1[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=============================================================================================================
//モードの設定
//=============================================================================================================
void SetMode(MODE mode)
{
	//現在の画面（モード）の終了処理
	switch (g_mode)
	{
	case MODE_TITLE://タイトル画面
		UninitTitle();
		break;

	case MODE_TUTORIAL://チュートリアル画面
		break;

	case MODE_GAME://ゲーム画面
		UninitGame();
		break;

	case MODE_RESULT://リザルト画面
		UninitResult();
		break;

	case MODE_RANKING://ランキング
		//UninitRanking();
		break;
	}

	//新しい画面（モード）の初期化処理
	switch (mode)
	{
	case MODE_TITLE://タイトル画面
		InitTitle();
		break;

	case MODE_TUTORIAL://チュートリアル画面
		break;

	case MODE_GAME://ゲーム画面
		InitGame();
		break;

	case MODE_RESULT://リザルト画面
		InitResult();
		break;

	case MODE_RANKING://ランキング
		//InitRanking();
		break;
	}
	g_mode = mode;//現在の画面（モード）を切り替える
}

//=============================================================================================================
//モードの取得
//=============================================================================================================
MODE GetMode()
{
	return g_mode;
}
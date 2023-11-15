#include "WinAPP.h"

WinApp::~WinApp()
{
#ifdef _DEBUG
	debugController->Release();
#endif
	CloseWindow(hwnd);
}

void WinApp::Initialize()
{
	CreateGameWindow();

}

void WinApp::Update()
{
}

HWND WinApp::GetHWND() {
	return hwnd;
}

bool WinApp::ProcessMessage()
{

		MSG msg{}; // メッセージ

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) // メッセージがある？
		{
			TranslateMessage(&msg); // キー入力メッセージの処理
			DispatchMessage(&msg);  // ウィンドウプロシージャにメッセージを送る
		}

		if (msg.message == WM_QUIT) // 終了メッセージが来たらループを抜ける
		{
			return true;
		}

		return false;
}

LRESULT CALLBACK WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	// メッセージに応じてゲーム固有の処理を行う
	switch (msg) {
		// ウィンドウが破棄された
	case WM_DESTROY:
		// OSに対して、アプリ終了を伝える
		PostQuitMessage(0);
		return 0;
	}
	// 標準のメッセージ処理を行う
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void WinApp::CreateGameWindow()
{
	//ウィンドウプロージャー
	wc.lpfnWndProc = WindowProc;
	//ウィンドウクラス名(なんでもいい)
	wc.lpszClassName = L"CGWindowClass";
	//インスタンスハンドル
	wc.hInstance = GetModuleHandle(nullptr);
	//カーソル
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

	//ウィンドウクラスを登録する
	RegisterClass(&wc);

	//ウィンドウサイズを表す構造体にクライアント領域を入れる
	RECT wrc{ 0,0,kClientWidth,kClientHeight };

	//クライアント領域をもとに実際のサイズにwrcを変更してもらう
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//ウィンドウの生成
	 hwnd = CreateWindow(
		wc.lpszClassName,//利用するクラス名
		L"CG2",//タイトルバーの文字(なんでもいい)
		WS_OVERLAPPEDWINDOW,//よく見るウィンドウスタイル
		CW_USEDEFAULT,//表記X座標(Windowsに任せる)
		CW_USEDEFAULT,//表記Y座標(WindowsOSに任せる)
		wrc.right - wrc.left,//ウィンドウ横幅
		wrc.bottom - wrc.top,//ウィンドウ縦幅
		nullptr,//親ウィンドウハンドル
		nullptr,//メニューハンドル
		wc.hInstance,//インスタンスハンドル
		nullptr//オプション
	);
	//ウィンドウを表示する
	ShowWindow(hwnd, SW_SHOW);
#ifdef _DEBUG
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		// デバッグレイヤーを有効化する
		debugController->EnableDebugLayer();
		// さらにGPU側でもチェックを行うようにする
		debugController->SetEnableGPUBasedValidation(TRUE);
		//debugController->Release();
	}
#endif
}
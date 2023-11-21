#include<Windows.h>
#include<stdio.h>
#include"WinApp.h"
#include"Logger.h"
#include"DirectXCommon.h"
#include<dxgidebug.h>
#pragma comment(lib,"dxguid.lib")


// Windowsアプリでのエントリーポイント（main関数）
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WinApp* winApp_ = new WinApp;
	winApp_->Initialize();
	
	DirectXCommon* directXCommand_ = nullptr;
	directXCommand_->Initialize(winApp_);

	
	
	MSG msg{};
	//ウィンドウの×ボタンが押されるまでループ
	while (winApp_->ProcessMessage() == false) {
		directXCommand_->PreDraw();
		directXCommand_->PostDraw();
	}
	delete winApp_;
	delete directXCommand_;
	//出力ウィンドウへの文字出力
	OutputDebugStringA("Hello,DirectX!\n");


	//リソースチェック
	IDXGIDebug* debug;
	if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debug)))) {
		debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
		debug->ReportLiveObjects(DXGI_DEBUG_APP, DXGI_DEBUG_RLO_ALL);
		debug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_ALL);
		debug->Release();
	}

	return 0;
}

#include<Windows.h>
#include<stdio.h>
#include"WinApp.h"
#include"Logger.h"
#include"DirectXCommon.h"


// Windowsアプリでのエントリーポイント（main関数）
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WinApp* winApp_ = new WinApp;
	winApp_->Initialize();
	
	DirectXCommon* directXCommand_ = new DirectXCommon;
	directXCommand_->Initialize();

	//Log("asas");
	
	MSG msg{};
	//ウィンドウの×ボタンが押されるまでループ
	while (winApp_->ProcessMessage() == false) {
	
	}
	delete winApp_;
	//出力ウィンドウへの文字出力
	OutputDebugStringA("Hello,DirectX!\n");

	return 0;
}
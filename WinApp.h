#pragma once
#include<Windows.h>
#include<cstdint>

class WinApp
{
	public:
				
	/// <summary>
	/// デストラクタ
	/// </summary>
	~WinApp();
  /// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	void Draw();

	bool ProcessMessage();

	// クライアント領域のサイズ
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;

private:

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	void CreateGameWindow();
    WNDCLASS wc{};

	
};


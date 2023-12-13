#pragma once

#include"WinApp.h"
#include"MyMath.h"
#include<cassert>
#include <d3d12.h>
#include <dxgi1_6.h>
#include "Logger.h"
#include <format>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

class Triangle
{
public:
	Triangle();
	~Triangle();

	void Initialize(WinApp* winApp_);
	void Update();

	//描画前
	void PreDraw();
	//描画後
	void PostDraw();

private:
	//使用するアダプタ用の変数。最初にnullptrを入れておく
	IDXGIAdapter4* useAdapter = nullptr;
	//実際に頂点リソースを作る
	ID3D12Resource* vertexResource;
	//頂点バッファービューを作成する
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	ID3D12GraphicsCommandList* commandList;
	//ビューポート
	D3D12_VIEWPORT viewport{};
	//シザー短形
	D3D12_RECT scissorRect{};
	//コマンドアロケータを生成する
	ID3D12CommandAllocator* commandAllocator;
	HRESULT hr;
	ID3D12Device* device = nullptr;

public:
	/// <summary>
	/// D3D12Deviceの生成
	/// </summary>
	void SetUpD3D12Device();
	/// <summary>
	/// CommandListを生成する
	/// </summary>
	void SetUpCommandList();
	/// <summary>
	/// VertexResourceを生成する
	/// </summary>
	void SetUpVertexResource();

};


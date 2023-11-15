#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include "Logger.h"
#include <format>
#include"WinApp.h"

class DirectXCommon
{
public:
	~DirectXCommon();
	void Initialize(WinApp*winApp_);
	void Upadate();
	
	//描画前
	void PreDraw();
	//描画後
	void PostDraw();

private:
	//SwapChainからResourceを引っ張ってくる
	ID3D12Resource* swapChainResources[2] = { nullptr };
	IDXGISwapChain4* swapChain;
	ID3D12GraphicsCommandList* commandList;
	ID3D12CommandQueue* commandQueue;
	//RTVを2つ作るのでディスクリプタを2つ用意
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];
	//コマンドアロケータを生成する
	ID3D12CommandAllocator* commandAllocator;
	HRESULT hr;
	//DXGIファクトリーの生成
	IDXGIFactory7* dxgiFactory = nullptr;

	ID3D12Device* device = nullptr;
	//使用するアダプタ用の変数。最初にnullptrを入れておく
	IDXGIAdapter4* useAdapter = nullptr;
	//ディスクリプタヒープの生成
	ID3D12DescriptorHeap* rtvDescriptorHeap = nullptr;
	//TranaitionBarrie野設定
	D3D12_RESOURCE_BARRIER barrier{};

	//初期値0でFenceを作る
	ID3D12Fence* fence = nullptr;
	uint64_t fenceValue = 0;
	//FenceのSignalを待つためのイベントを作成する
	HANDLE fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	
private:
	/// <summary>
	/// DXGIFactoryの生成
	/// </summary>
	void SetUpDXGIFactory();
	/// <summary>
	/// D3D12Deviceの生成
	/// </summary>
	void SetUpD3D12Device();
	/// <summary>
	/// CommandQueueを生成する
	/// </summary>
	void SetUpCommandQueue();
	/// <summary>
	/// CommandListを生成する
	/// </summary>
	void SetUpCommandList();
	/// <summary>
	/// SwapChainを生成する
	/// </summary>
	void SetUpSwapChain(WinApp* winApp_);
	/// <summary>
	/// DescriptorHeapを生成する
	/// </summary>
	void SetUpDescriptorHeap();
	/// <summary>
	/// FenceとEventを生成する
	/// </summary>
	void SetUpFence();
};


#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include "Logger.h"
#include <format>
#include"WinApp.h"
#include<dxcapi.h>
#include"MyMath.h"
#include"Triangle.h"

#pragma comment(lib,"dxcompiler.lib")

class DirectXCommon
{
public:
	DirectXCommon();
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
	HANDLE fenceEvent =nullptr;
	
	IDxcUtils* dxcUtils = nullptr;
	IDxcIncludeHandler* includeHandler;
	// //hlslファイルを読む
	IDxcBlobEncoding* shaderSource = nullptr;
	//実際にShaderをコンパイルする
	IDxcResult* shaderResult = nullptr;
	//警告・エラーが出たらログに出して止める
	IDxcBlobUtf8* shaderError = nullptr;
	//コンパイル結果から実行用のバイナリ部分を取得
	IDxcBlob* shaderBlob = nullptr;
	//バイナリを基に作成
	ID3D12RootSignature* rootSignature = nullptr;
	//シリアライズしてバイナリにする
	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	//const std::wstring& filePath;
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};

	//BlendStateの設定
	D3D12_BLEND_DESC blendDesc{};
	//RasiterzerStateの設定
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	IDxcBlob* vertexShaderBlob;
	IDxcBlob* pixelShaderBlob;
	////実際に頂点リソースを作る
	ID3D12Resource* vertexResource;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
	ID3D12PipelineState* graphicsPipelineState = nullptr;
	//ビューポート
	D3D12_VIEWPORT viewport{};
	//シザー短形
	D3D12_RECT scissorRect{};
	//頂点バッファービューを作成する
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

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
	/// <summary>
	/// CompileShader関数
	/// </summary>
	IDxcBlob* SetUpCompileShader(
		//CompilerするShaderファイルへのパス
		const std::wstring& filePath,
		//Compilerに使用するProfile
		const wchar_t* profile,
		//初期化で生成したものを3つ
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler);
	/// <summary>
	/// RoorSignatureを生成する
	/// </summary>
	void SetUpRootSignature();
	/// <summary>
	/// PSOを生成する
	/// </summary>
	void SetUpPSO();
	/// <summary>
	/// VertexResourceを生成する
	///</summary>
	void SetUpVertexResource();
};


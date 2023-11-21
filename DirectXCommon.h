#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include <format>
#include<dxcapi.h>
#include"WinApp.h"
#include"MyMath.h"
#include"Triangle.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxcompiler.lib")


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

	ID3D12Resource* GetVertexResource() {
		return vertexResorce;
	};

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
	
	// //hlslファイルを読む
	IDxcBlobEncoding* shaderSource = nullptr;
	//実際にShaderをコンパイルする
	IDxcResult* shaderResult = nullptr;
	//警告・エラーが出たらログに出して止める
	IDxcBlobUtf8* shaderError = nullptr;
	//コンパイル結果から実行用のバイナリ部分を取得
	IDxcBlob* shaderBlob = nullptr;

	//InputLayout
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[1] = {};
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	//バイナリを基に生成
	ID3D12RootSignature* rootSignature = nullptr;
	//dxcCompilerを初期化
	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	const std::wstring& filePath;
		//Compilerに使用するProfile
	const wchar_t* profile;
		//初期化で生成したものを3つ
	IDxcIncludeHandler* includeHandler;
	//現時点でincludeはしないが、includeに対応するための設定を行っておく
	IDxcIncludeHandler* includeHandeler = nullptr;
		//Shaderをコンパイルする
	IDxcBlob* vertexShaderBlob = SetUpCompileShader(L"Object3D.VS.hlsl", L"vs_6_0,", dxcUtils, dxcCompiler, includeHandeler);
	IDxcBlob* pixelShaderBlob = SetUpCompileShader(L"Object3D.PS.hlsl", L"ps_6_0", dxcUtils, dxcCompiler, includeHandeler);
	//BlendStateの設定
	D3D12_BLEND_DESC blendDesc{};
	//RasisterzerStateの設定
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	//実際に頂点リソースを作る
	ID3D12Resource* vertexResorce = nullptr;
	//ビューポート
	D3D12_VIEWPORT viewport{};
	//シザー短径
	D3D12_RECT scissorRect{};
	//実際に生成
	ID3D12PipelineState* graphicsPipelineState = nullptr;
	Triangle* triangle_=nullptr;
	//シリアライズしてバイナリにする
	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorblod = nullptr;

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
	/// RootSignatureを生成する
	/// </summary>
	void SetUpRootSignature();
	/// <summary>
	/// PSOを生成する
	/// </summary>
	void SetUpPSO();
	//VertexResourceを生成する
	void SetUpVertexResource(WinApp* winApp_);

		
};


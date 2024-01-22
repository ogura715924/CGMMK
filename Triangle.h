#pragma once

#include"WinApp.h"
#include"MyMath.h"
#include<cassert>
#include <d3d12.h>
#include <dxgi1_6.h>
#include "Logger.h"
#include <format>
#include <dxcapi.h>
#include"DirectXCommon.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

class Triangle
{
public:
	//Triangle();
	~Triangle();

	void Initialize(WinApp* winApp_,DirectXCommon*directXCommon);
	void Update();

	//描画前
	void PreDraw();
	//描画後
	void PostDraw();

private:
	//使用するアダプタ用の変数。最初にnullptrを入れておく
	//IDXGIAdapter4* useAdapter = nullptr;
	//実際に頂点リソースを作る
	ID3D12Resource* vertexResource;
	//頂点バッファービューを作成する
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	//ビューポート
	D3D12_VIEWPORT viewport{};
	//シザー短形
	D3D12_RECT scissorRect{};
	//コマンドアロケータを生成する
	//ID3D12CommandAllocator* commandAllocator;
	//HRESULT hr;
	//RasiterzerStateの設定
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	//IDxcBlob* vertexShaderBlob;
	//IDxcBlob* pixelShaderBlob;
	// //hlslファイルを読む
	//IDxcBlobEncoding* shaderSource = nullptr;
	//IDxcUtils* dxcUtils = nullptr;
	//IDxcCompiler3* dxcCompiler = nullptr;
	//IDxcIncludeHandler* includeHandler;
	//実際にShaderをコンパイルする
	//IDxcResult* shaderResult = nullptr;
	////警告・エラーが出たらログに出して止める
	//IDxcBlobUtf8* shaderError = nullptr;
	////コンパイル結果から実行用のバイナリ部分を取得
	//IDxcBlob* shaderBlob = nullptr;
	//D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
	////バイナリを基に作成
	//ID3D12RootSignature* rootSignature = nullptr;
	

	DirectXCommon* directXCommon_;
public:
	/// <summary>
	/// D3D12Deviceの生成
	/// </summary>
	//void SetUpD3D12Device();
	/// <summary>
	/// CommandListを生成する
	/// </summary>
	//void SetUpCommandList();
	/// <summary>
	/// VertexResourceを生成する
	/// </summary>
	//void SetUpVertexResource();
	/// <summary>
/// CompileShader関数
/// </summary>
//	IDxcBlob* SetUpCompileShader(
//		//CompilerするShaderファイルへのパス
//		const std::wstring& filePath,
//		//Compilerに使用するProfile
//		const wchar_t* profile,
//		//初期化で生成したものを3つ
//		IDxcUtils* dxcUtils,
//		IDxcCompiler3* dxcCompiler,
//		IDxcIncludeHandler* includeHandler);
};


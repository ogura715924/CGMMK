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
class Shape
{
public:
	~Shape();

	void Initialize(WinApp* winApp_, DirectXCommon* directXCommon);
	void Update();

	//描画前
	void PreDraw();
	//描画後
	void PostDraw();


private:
	//実際に頂点リソースを作る
	ID3D12Resource* vertexResource;
	//頂点バッファービューを作成する
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	//ビューポート
	D3D12_VIEWPORT viewport{};
	//シザー短形
	D3D12_RECT scissorRect{};
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	const uint32_t kSubdivision = 16;//分割数
	const uint32_t kVertexCount = kSubdivision * kSubdivision * 6;//球体頂点数

	DirectXCommon* directXCommon_;
public:
};


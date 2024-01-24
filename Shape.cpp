#include "Shape.h"

Shape::~Shape()
{
	vertexResource->Release();
}

void Shape::Initialize(WinApp* winApp_, DirectXCommon* directXCommon)
{
	const uint32_t kSubdivision = 16;//分割数
	const uint32_t kVertexCount = kSubdivision * kSubdivision * 6;//球体頂点数

	

	assert(directXCommon);
	directXCommon_ = directXCommon;
	vertexResource = directXCommon->CreateBufferResorce(directXCommon->GetDevice(), sizeof(Vector4) * 3);
	//リソースの先頭のアドレスから使う
	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();

	//使用するリソースのサイズは頂点3つ分のサイズ
	vertexBufferView.SizeInBytes = sizeof(Vector4) * 3;
	//1頂点当たりのサイズ
	vertexBufferView.StrideInBytes = sizeof(Vector4);
	//三角形の中を塗りつぶす
	rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;

	//頂点リソースにデータを書き込む
	Vector4* vertexData = nullptr;
	//書き込むためのアドレスを取得
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	//左下
	vertexData[0] = { -0.5f,-0.5f,0.0f,1.0f };
	//上
	vertexData[1] = { 0.0f,0.5f,0.0f,1.0f };
	//右下
	vertexData[2] = { 0.5f,-0.5f,0.0f,1.0f };

	//ビューポート
	//クライアントの領域のサイズと一緒にして画面全体に表示
	viewport.Width = (float)winApp_->kClientWidth;
	viewport.Height = (float)winApp_->kClientHeight;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	//シザー短形
	//基本的にビューポートと同じ短径が構成されるようにする
	scissorRect.left = 0;
	scissorRect.right = winApp_->kClientWidth;
	scissorRect.top = 0;
	scissorRect.bottom = winApp_->kClientHeight;

	ID3D12Resource* vertexResorce = CreateBufferResorce(directXCommon_->GetDevice(), sizeof(vertexData) * kVertexCount);
	vertexBufferView.SizeInBytes = UINT(sizeof(vertexData) * kVertexCount) * kVertexCount);
}

void Shape::Update()
{
}
void Shape::PreDraw()
{

	directXCommon_->GetCommandlist()->RSSetViewports(1, &viewport);//Viewportを設定
	directXCommon_->GetCommandlist()->RSSetScissorRects(1, &scissorRect);//Scirssorを設定
	directXCommon_->GetCommandlist()->IASetVertexBuffers(0, 1, &vertexBufferView);//VBVを設定
	//形状を設定。PSOに設定しているものとはまた別。同じものを設定する考えておけばいい
	directXCommon_->GetCommandlist()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//描画!(DrawCall/ドローコール。3頂点で1つのインスタンス。インスタンスについては今後
	directXCommon_->GetCommandlist()->DrawInstanced(3, 1, 0, 0);
}

void Shape::PostDraw()
{
}

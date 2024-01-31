#include "Shape.h"
#include<numbers>

Shape::~Shape()
{
	vertexResource->Release();
}

void Shape::Initialize(WinApp* winApp_, DirectXCommon* directXCommon)
{
	assert(directXCommon);
	directXCommon_ = directXCommon;
	vertexResource = directXCommon_->CreateBufferResorce(directXCommon_->GetDevice(), sizeof(VertexData) * kVertexCount);
	//vertexResource = directXCommon->CreateBufferResorce(directXCommon->GetDevice(), sizeof(Vector4) * 3);
	//リソースの先頭のアドレスから使う
	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();

	//使用するリソースのサイズは頂点3つ分のサイズ
	vertexBufferView.SizeInBytes = sizeof(Vector4) * kVertexCount;
	//1頂点当たりのサイズ
	vertexBufferView.StrideInBytes = sizeof(Vector4);
	//三角形の中を塗りつぶす
	rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;

	VertexData* vertexData = nullptr;

	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	vertexBufferView.SizeInBytes = UINT(sizeof(VertexData) * kVertexCount);

	//球体用頂点
	// //頂点リソースにデータを書き込む
	const float kPi = std::numbers::pi_v<float>;
	const float kLonEvery = (2 * kPi) / float(kSubdivision);//経度分割1つ分の角度
	const float kLatEvery = kPi / float(kSubdivision);//緯度分割1つ分の角度
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -kPi / 2.0f + kLatEvery * latIndex;
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			uint32_t start = (latIndex * kSubdivision +lonIndex) * 6;
			float lon = (float)lonIndex * kLonEvery;
			//a
			vertexData[start].position.x = cos(lat) * cos(lon);
			vertexData[start].position.y = sin(lat);
			vertexData[start].position.z = cos(lat) * sin(lon);
			vertexData[start].position.w = 1.0f;
			vertexData[start].texcord.x  = float(lonIndex) / float(kSubdivision);
			vertexData[start].texcord.y  = 1.0f - float(latIndex) / float(kSubdivision);

			//b
			vertexData[start + 1].position.x = cos(lat + kLatEvery) * cos(lon);
			vertexData[start + 1].position.y = sin(lat + kLatEvery);
			vertexData[start + 1].position.z = cos(lat + kLatEvery) * sin(lon);
			vertexData[start + 1].position.w = 1.0f;
			vertexData[start + 1].texcord.x =  float(lonIndex) / float(kSubdivision);
			vertexData[start + 1].texcord.y =  1.0f - float(latIndex+1) / float(kSubdivision);

				//c
			vertexData[start + 2].position.x = cos(lat) * cos(lon + kLonEvery);
			vertexData[start + 2].position.y = sin(lat);
			vertexData[start + 2].position.z = cos(lat) * sin(lon + kLonEvery);
			vertexData[start + 2].position.w = 1.0f;
			vertexData[start + 2].texcord.x = float(lonIndex + 1) / float(kSubdivision);
			vertexData[start + 2].texcord.y = 1.0f - float(latIndex) / float(kSubdivision);

			//c
			vertexData[start + 3] = vertexData[start + 2];
			//b
			vertexData[start + 4] = vertexData[start + 1];
			//d
			vertexData[start + 5].position.x = cos(lat + kLatEvery) * cos(lon + kLonEvery);
			vertexData[start+5].position.y = sin(lat+kLatEvery);
			vertexData[start+5].position.z = cos(lat+kLatEvery) * sin(lon+kLonEvery);
			vertexData[start+5].position.w = 1.0f;
			vertexData[start+5].texcord.x = float(lonIndex+1) / float(kSubdivision);
			vertexData[start+5].texcord.y = 1.0f - float(latIndex+1) / float(kSubdivision);
		}
	}

	

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
	directXCommon_->GetCommandlist()->DrawInstanced(kVertexCount,1,0,0);
}

void Shape::PostDraw()
{
}

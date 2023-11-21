#include "Triangle.h"

Triangle::~Triangle()
{

}

void Triangle::Initialize()
{
	//リソースの先頭のアドレスから使う
	vertexBufferView.BufferLocation = directXCommon_->GetVertexResource()->GetGPUVirtualAddress();
	//使用するリソースのサイズは頂点3つ分のサイズ
	vertexBufferView.SizeInBytes = sizeof(Vector4) * 3;
	//1頂点当たりのサイズ
	vertexBufferView.StrideInBytes = sizeof(Vector4); 

}

void Triangle::Update()
{
}

void Triangle::Draw()
{

}

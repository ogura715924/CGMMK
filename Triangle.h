#pragma once
#include<d3d12.h>
#include"DirectXCommon.h"
#include"MyMath.h"

class Triangle
{
public:
	~Triangle();
	void Initialize();
	void Update();
	void Draw();

	D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView() {
		return vertexBufferView;
	};
	
private:
	DirectXCommon directXCommon_ ;
	//頂点バッファビューを作成する
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

};


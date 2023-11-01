#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include "Logger.h"
#include <format>

class DirectXCommon
{
public:
	void Initialize();
	void Upadate();
	void Draw();
};


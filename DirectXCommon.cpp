#include "DirectXCommon.h"
#include"Logger.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")


void DirectXCommon::Initialize()
{
	//DXGファクトリーの生成
	IDXGIFactory7* dxgiFactory = nullptr;
	//HRESULTはWindows系のエラーコードであり、
	// 関数が成功したかどうかをSUCCEEDEDマクロで判定できる
	HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	//初期化の根本的な部分でエラーが出た場合はプログラムが間違っているか、
	//どうにもできない場合が多いのでassertにしておく
	assert(SUCCEEDED(hr));
	//使用するアダプタ用の変数。最初にnullptrを入れておく
	IDXGIAdapter4* useAdapter = nullptr;
	//良い順にアダプタを頼む
	for (UINT i = 0; dxgiFactory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&useAdapter)) != DXGI_ERROR_NOT_FOUND; i++) {
		//アダプターの情報を取得する
		DXGI_ADAPTER_DESC3 adapterDesc{};
		hr = useAdapter->GetDesc3(&adapterDesc);
		assert(SUCCEEDED(hr));//取得できないのは一大事
		//ソフトウェアアダプタでなければ採用!
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
			//採用したアダプタの情報をログに出力。wstringの方なので注意
			Log(ConvertString(std::format(L"Use Adapater:{}\n", adapterDesc.Description)));
			
			break;
		}
		useAdapter = nullptr;//ソフトウェアアダプタの場合は見なかったことにする
}
	//適切なアダプタが見つからなかったので起動できない
	assert(useAdapter != nullptr);

	ID3D12Device* device = nullptr;
	//機能レベルとログ出力用の文字列
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_12_2,D3D_FEATURE_LEVEL_12_1,D3D_FEATURE_LEVEL_12_0
	};
	const char* featureLevelStrings[] = { "12.2","12.1","12.0" };
//高い順に生成できるか試していく
for (size_t i = 0; i < _countof(featureLevels); ++i) {
	//採用したアダプターでデバイス生成
	hr = D3D12CreateDevice(useAdapter, featureLevels[i], IID_PPV_ARGS(&device));
//指定した機能レベルでデバイスが生成できたかを確認
	if (SUCCEEDED(hr)) {
		//生成できたのでログ出力を行ってループを抜ける
		Log (std::format("FeatureLevel:{}\n", featureLevelStrings[i]));
		break;
	}
}
	//デバイスの生成がうまくいかなかったので起動できない
	assert(device != nullptr);
	Log("Complete create D3D!2Device!!!\n");//初期化完了のログを出す
	}


void DirectXCommon::Upadate()
{
}

void DirectXCommon::Draw()
{
}

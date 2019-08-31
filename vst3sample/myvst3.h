#pragma once

// VST3 SDKのヘッダファイル
// funknown.hはFUID用のヘッダ
#include "pluginterfaces\base\funknown.h"
// vstaudioeffect.hとivstparameterchanges.hはAudioEffectクラス関連のヘッダ
#include "public.sdk/source/vst/vstaudioeffect.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
// vsteditcontroller.hはEditControllerクラス関連のヘッダ
#include "public.sdk/source/vst/vsteditcontroller.h"


// VST3作成に必要なの名前空間を使用
namespace Steinberg{
namespace Vst {

// FUIDの生成
// 
static const FUID ProcessorUID(0x1E5620F0, 0xB0C54434, 0x93A6D2E6, 0x793DF84E);
static const FUID ControllerUID(0xDC821BA2, 0x3DCA437F, 0x85046563, 0x196B2BFD);


// ===================================================================================
// 音声信号を処理するProcessorクラス
// ===================================================================================
class MyVSTProcessor : public AudioEffect
{
public:
	// コンストラクタ
	MyVSTProcessor();

	// クラスを初期化する関数(必須)
	tresult PLUGIN_API initialize(FUnknown* context);

	// バス構成を設定する関数。
	tresult PLUGIN_API setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts);

	// 音声信号を処理する関数(必須)
	tresult PLUGIN_API process(ProcessData& data);

	// 自作VST Processorクラスのインスタンスを作成するための関数(必須)
	static FUnknown* createInstance(void*) { return (IAudioProcessor*)new MyVSTProcessor(); }
};


// ===================================================================================
// VSTのパラメーターを操作するためのControllerクラス
// ===================================================================================
class MyVSTController : public EditController
{
public:
	// クラスを初期化する関数(必須)
	tresult PLUGIN_API initialize(FUnknown* context);

	// 自作VST Controllerクラスのインスタンスを作成するための関数(必須)
	static FUnknown* createInstance(void*) { return (IEditController*)new MyVSTController(); }

};


} } // namespace SteinbergとVstの終わり
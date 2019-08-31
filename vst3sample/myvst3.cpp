// 自作VST用のインクルードファイル
#include "myvst3.h"

// VST3 SDKのインクルードファイル
#include "public.sdk/source/main/pluginfactory.h"

// ===================================================================================
// DLLファイルの初期化、終了処理関数
// ===================================================================================
// 基本的に何もする必要はない。
bool InitModule() { return true; }
bool DeinitModule() { return true; }

// ===================================================================================
// 自作VSTプラグインの生成
// ===================================================================================

#define MYVST_VENDOR   "C++ de VST"               // 製作者(製作会社)の名前。
#define MYVST_URL      "http://vstcpp.wpblog.jp/" // 製作者(製作会社)のWebサイトのURL。
#define MYVST_EMAIL    "mailto:xxxx@example.com"  // 製作者(製作会社)の連絡先メールアドレス。
#define MYVST_VSTNAME  "MyVST Name"               // 自作するVSTの名前。
#define MYVST_VERSION  "0"                        // 自作するVSTのバージョン。
#define MYVST_SUBCATEGORIES Vst::PlugType::kFx    // 自作するVSTのカテゴリ。

BEGIN_FACTORY_DEF(MYVST_VENDOR, MYVST_URL, MYVST_EMAIL)

	// MyVSTProcessorクラスの作成を行う
	DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::ProcessorUID),
	PClassInfo::kManyInstances,
	kVstAudioEffectClass,
	MYVST_VSTNAME,
	Vst::kDistributable,
	MYVST_SUBCATEGORIES,
	MYVST_VERSION,
	kVstVersionString,
	Steinberg::Vst::MyVSTProcessor::createInstance)

	// MyVSTControllerクラスの作成を行う
	DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::ControllerUID),
	PClassInfo::kManyInstances,
	kVstComponentControllerClass,
	MYVST_VSTNAME " Controller",// 自作VSTの名前に"Controller"を付与したもの。
	0,						    // 使わないので必ず0にする
	"",						    // 使わないので必ず""にする
	MYVST_VERSION,
	kVstVersionString,
	Steinberg::Vst::MyVSTController::createInstance)

END_FACTORY

// VST3作成に必要なの名前空間を使用
namespace Steinberg{
namespace Vst {

// ===================================================================================
// 音声信号を処理するProcessorクラス
// ===================================================================================
// コンストラクタ
MyVSTProcessor::MyVSTProcessor()
{
	// コントローラーのFUIDを設定する
	setControllerClass(ControllerUID);
}

// クラスを初期化する関数
tresult PLUGIN_API MyVSTProcessor::initialize(FUnknown* context)
{
	// まず継承元クラスの初期化を実施
	tresult result = AudioEffect::initialize(context);
	if (result == kResultTrue)
	{
		// 入力と出力を設定
		addAudioInput(STR16("AudioInput"), SpeakerArr::kStereo);
		addAudioOutput(STR16("AudioOutput"), SpeakerArr::kStereo);

		// 以下固有の初期化を実施。
	}


	// 初期化が成功すればkResultTrueを返す。
	return result;
}

tresult PLUGIN_API MyVSTProcessor::setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts)
{
	// inputとoutputのバスが1つずつで、かつinputとoutputの構成がステレオの場合
	if (numIns == 1 && numOuts == 1 && inputs[0] == SpeakerArr::kStereo && outputs[0] == SpeakerArr::kStereo)
	{
		return AudioEffect::setBusArrangements(inputs, numIns, outputs, numOuts);
	}

	// 対応していないバス構成の場合、kResultFalseを返す。
	return kResultFalse;
}

tresult PLUGIN_API MyVSTProcessor::process(ProcessData& data)
{
	// パラメーター変更の処理
	// 与えられたパラメーターがあるとき、dataのinputParameterChangesに
	// IParameterChangesクラスへのポインタのアドレスが入る
	if (data.inputParameterChanges != NULL)
	{
		// 与えられたパラメーターの数を取得
		int32 paramChangeCount = data.inputParameterChanges->getParameterCount();

		// 与えられたパラメーター分、処理を繰り返す。
		for (int32 i = 0; i < paramChangeCount; i++)
		{
			// パラメーター変更のキューを取得
			// (処理するサンプル内に複数のパラメーター変更情報がある可能性があるため、
			// キューという形になっている。)
			IParamValueQueue* queue = data.inputParameterChanges->getParameterData(i);
			if (queue != NULL)
			{
				// どのパラメーターが変更されたか知るため、パラメーターtagを取得
				int32 tag = queue->getParameterId();

				// 変更された回数を取得
				int32 valueChangeCount = queue->getPointCount();
				ParamValue value;
				int32 sampleOffset;

				// 最後に変更された値を取得
				if (queue->getPoint(valueChangeCount - 1, sampleOffset, value) == kResultTrue)
				{
					// tagに応じた処理を実施
				}
			}
		}
	}

	// 入力・出力バッファのポインタをわかりやすい変数に格納
	// inputs[]、outputs[]はAudioBusの数だけある(addAudioInput()、addAudioOutput()で追加した分だけ)
	// 今回はAudioBusは1つだけなので 0 のみとなる
	// channelBuffers32は32bit浮動小数点型のバッファで音声信号のチャンネル数分ある
	// モノラル(kMono)なら 0 のみで、ステレオ(kStereo)なら 0(Left) と 1(Right) となる
	Sample32* inL = data.inputs[0].channelBuffers32[0];
	Sample32* inR = data.inputs[0].channelBuffers32[1];
	Sample32* outL = data.outputs[0].channelBuffers32[0];
	Sample32* outR = data.outputs[0].channelBuffers32[1];

	// numSamplesで示されるサンプル分、音声を処理する
	for (int32 i = 0; i < data.numSamples; i++)
	{
		outL[i] = inL[i];
		outR[i] = inR[i];
	}

	// 問題なければkResultTrueを返す(おそらく必ずkResultTrueを返す)
	return kResultTrue;
}

// ===================================================================================
// VSTのパラメーターを操作するためのControllerクラス
// ===================================================================================

// クラスを初期化する関数(必須)
tresult PLUGIN_API MyVSTController::initialize(FUnknown* context)
{
	// まず継承元クラスの初期化を実施
	tresult result = EditController::initialize(context);
	if (result == kResultTrue)
	{
		// パラメーターを追加

		// 以下固有の初期化を実施。
		// 今回は何もしない
	}

	// 初期化が成功すればkResultTrueを返す。
	result = kResultTrue;
	return result;
}


} } // namespace SteinbergとVstの終わり
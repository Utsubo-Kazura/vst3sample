#pragma once

// VST3 SDK�̃w�b�_�t�@�C��
// funknown.h��FUID�p�̃w�b�_
#include "pluginterfaces\base\funknown.h"
// vstaudioeffect.h��ivstparameterchanges.h��AudioEffect�N���X�֘A�̃w�b�_
#include "public.sdk/source/vst/vstaudioeffect.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
// vsteditcontroller.h��EditController�N���X�֘A�̃w�b�_
#include "public.sdk/source/vst/vsteditcontroller.h"


// VST3�쐬�ɕK�v�Ȃ̖��O��Ԃ��g�p
namespace Steinberg{
namespace Vst {

// FUID�̐���
// 
static const FUID ProcessorUID(0x1E5620F0, 0xB0C54434, 0x93A6D2E6, 0x793DF84E);
static const FUID ControllerUID(0xDC821BA2, 0x3DCA437F, 0x85046563, 0x196B2BFD);


// ===================================================================================
// �����M������������Processor�N���X
// ===================================================================================
class MyVSTProcessor : public AudioEffect
{
public:
	// �R���X�g���N�^
	MyVSTProcessor();

	// �N���X������������֐�(�K�{)
	tresult PLUGIN_API initialize(FUnknown* context);

	// �o�X�\����ݒ肷��֐��B
	tresult PLUGIN_API setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts);

	// �����M������������֐�(�K�{)
	tresult PLUGIN_API process(ProcessData& data);

	// ����VST Processor�N���X�̃C���X�^���X���쐬���邽�߂̊֐�(�K�{)
	static FUnknown* createInstance(void*) { return (IAudioProcessor*)new MyVSTProcessor(); }
};


// ===================================================================================
// VST�̃p�����[�^�[�𑀍삷�邽�߂�Controller�N���X
// ===================================================================================
class MyVSTController : public EditController
{
public:
	// �N���X������������֐�(�K�{)
	tresult PLUGIN_API initialize(FUnknown* context);

	// ����VST Controller�N���X�̃C���X�^���X���쐬���邽�߂̊֐�(�K�{)
	static FUnknown* createInstance(void*) { return (IEditController*)new MyVSTController(); }

};


} } // namespace Steinberg��Vst�̏I���
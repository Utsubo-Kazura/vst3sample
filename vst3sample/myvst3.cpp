// ����VST�p�̃C���N���[�h�t�@�C��
#include "myvst3.h"

// VST3 SDK�̃C���N���[�h�t�@�C��
#include "public.sdk/source/main/pluginfactory.h"

// ===================================================================================
// DLL�t�@�C���̏������A�I�������֐�
// ===================================================================================
// ��{�I�ɉ�������K�v�͂Ȃ��B
bool InitModule() { return true; }
bool DeinitModule() { return true; }

// ===================================================================================
// ����VST�v���O�C���̐���
// ===================================================================================

#define MYVST_VENDOR   "C++ de VST"               // �����(������)�̖��O�B
#define MYVST_URL      "http://vstcpp.wpblog.jp/" // �����(������)��Web�T�C�g��URL�B
#define MYVST_EMAIL    "mailto:xxxx@example.com"  // �����(������)�̘A���惁�[���A�h���X�B
#define MYVST_VSTNAME  "MyVST Name"               // ���삷��VST�̖��O�B
#define MYVST_VERSION  "0"                        // ���삷��VST�̃o�[�W�����B
#define MYVST_SUBCATEGORIES Vst::PlugType::kFx    // ���삷��VST�̃J�e�S���B

BEGIN_FACTORY_DEF(MYVST_VENDOR, MYVST_URL, MYVST_EMAIL)

	// MyVSTProcessor�N���X�̍쐬���s��
	DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::ProcessorUID),
	PClassInfo::kManyInstances,
	kVstAudioEffectClass,
	MYVST_VSTNAME,
	Vst::kDistributable,
	MYVST_SUBCATEGORIES,
	MYVST_VERSION,
	kVstVersionString,
	Steinberg::Vst::MyVSTProcessor::createInstance)

	// MyVSTController�N���X�̍쐬���s��
	DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::ControllerUID),
	PClassInfo::kManyInstances,
	kVstComponentControllerClass,
	MYVST_VSTNAME " Controller",// ����VST�̖��O��"Controller"��t�^�������́B
	0,						    // �g��Ȃ��̂ŕK��0�ɂ���
	"",						    // �g��Ȃ��̂ŕK��""�ɂ���
	MYVST_VERSION,
	kVstVersionString,
	Steinberg::Vst::MyVSTController::createInstance)

END_FACTORY

// VST3�쐬�ɕK�v�Ȃ̖��O��Ԃ��g�p
namespace Steinberg{
namespace Vst {

// ===================================================================================
// �����M������������Processor�N���X
// ===================================================================================
// �R���X�g���N�^
MyVSTProcessor::MyVSTProcessor()
{
	// �R���g���[���[��FUID��ݒ肷��
	setControllerClass(ControllerUID);
}

// �N���X������������֐�
tresult PLUGIN_API MyVSTProcessor::initialize(FUnknown* context)
{
	// �܂��p�����N���X�̏����������{
	tresult result = AudioEffect::initialize(context);
	if (result == kResultTrue)
	{
		// ���͂Əo�͂�ݒ�
		addAudioInput(STR16("AudioInput"), SpeakerArr::kStereo);
		addAudioOutput(STR16("AudioOutput"), SpeakerArr::kStereo);

		// �ȉ��ŗL�̏����������{�B
	}


	// �����������������kResultTrue��Ԃ��B
	return result;
}

tresult PLUGIN_API MyVSTProcessor::setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts)
{
	// input��output�̃o�X��1���ŁA����input��output�̍\�����X�e���I�̏ꍇ
	if (numIns == 1 && numOuts == 1 && inputs[0] == SpeakerArr::kStereo && outputs[0] == SpeakerArr::kStereo)
	{
		return AudioEffect::setBusArrangements(inputs, numIns, outputs, numOuts);
	}

	// �Ή����Ă��Ȃ��o�X�\���̏ꍇ�AkResultFalse��Ԃ��B
	return kResultFalse;
}

tresult PLUGIN_API MyVSTProcessor::process(ProcessData& data)
{
	// �p�����[�^�[�ύX�̏���
	// �^����ꂽ�p�����[�^�[������Ƃ��Adata��inputParameterChanges��
	// IParameterChanges�N���X�ւ̃|�C���^�̃A�h���X������
	if (data.inputParameterChanges != NULL)
	{
		// �^����ꂽ�p�����[�^�[�̐����擾
		int32 paramChangeCount = data.inputParameterChanges->getParameterCount();

		// �^����ꂽ�p�����[�^�[���A�������J��Ԃ��B
		for (int32 i = 0; i < paramChangeCount; i++)
		{
			// �p�����[�^�[�ύX�̃L���[���擾
			// (��������T���v�����ɕ����̃p�����[�^�[�ύX��񂪂���\�������邽�߁A
			// �L���[�Ƃ����`�ɂȂ��Ă���B)
			IParamValueQueue* queue = data.inputParameterChanges->getParameterData(i);
			if (queue != NULL)
			{
				// �ǂ̃p�����[�^�[���ύX���ꂽ���m�邽�߁A�p�����[�^�[tag���擾
				int32 tag = queue->getParameterId();

				// �ύX���ꂽ�񐔂��擾
				int32 valueChangeCount = queue->getPointCount();
				ParamValue value;
				int32 sampleOffset;

				// �Ō�ɕύX���ꂽ�l���擾
				if (queue->getPoint(valueChangeCount - 1, sampleOffset, value) == kResultTrue)
				{
					// tag�ɉ��������������{
				}
			}
		}
	}

	// ���́E�o�̓o�b�t�@�̃|�C���^���킩��₷���ϐ��Ɋi�[
	// inputs[]�Aoutputs[]��AudioBus�̐���������(addAudioInput()�AaddAudioOutput()�Œǉ�����������)
	// �����AudioBus��1�����Ȃ̂� 0 �݂̂ƂȂ�
	// channelBuffers32��32bit���������_�^�̃o�b�t�@�ŉ����M���̃`�����l����������
	// ���m����(kMono)�Ȃ� 0 �݂̂ŁA�X�e���I(kStereo)�Ȃ� 0(Left) �� 1(Right) �ƂȂ�
	Sample32* inL = data.inputs[0].channelBuffers32[0];
	Sample32* inR = data.inputs[0].channelBuffers32[1];
	Sample32* outL = data.outputs[0].channelBuffers32[0];
	Sample32* outR = data.outputs[0].channelBuffers32[1];

	// numSamples�Ŏ������T���v�����A��������������
	for (int32 i = 0; i < data.numSamples; i++)
	{
		outL[i] = inL[i];
		outR[i] = inR[i];
	}

	// ���Ȃ����kResultTrue��Ԃ�(�����炭�K��kResultTrue��Ԃ�)
	return kResultTrue;
}

// ===================================================================================
// VST�̃p�����[�^�[�𑀍삷�邽�߂�Controller�N���X
// ===================================================================================

// �N���X������������֐�(�K�{)
tresult PLUGIN_API MyVSTController::initialize(FUnknown* context)
{
	// �܂��p�����N���X�̏����������{
	tresult result = EditController::initialize(context);
	if (result == kResultTrue)
	{
		// �p�����[�^�[��ǉ�

		// �ȉ��ŗL�̏����������{�B
		// ����͉������Ȃ�
	}

	// �����������������kResultTrue��Ԃ��B
	result = kResultTrue;
	return result;
}


} } // namespace Steinberg��Vst�̏I���
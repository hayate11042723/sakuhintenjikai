#include "DxLib.h"

int PlayerX, PlayerY;
float JumpPower;
int PlayerGraph;
int EnemyGraph;
int EnemyX, EnemyY;

XINPUT_STATE input;


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int Key;
	int phase = 0;

	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);

	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(1280, 720, 32);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);

	// ���̃t���[���̊J�n�������o���Ă���
	LONGLONG start = GetNowHiPerformanceCount();

	// �O���t�B�b�N�wplayer.png�x���������Ƀ��[�h
	PlayerGraph = LoadGraph("image/player.png");
	// �O���t�B�b�N�wplayer.png�x���������Ƀ��[�h
	EnemyGraph = LoadGraph("image/enemy.png");

	// �L�����N�^�[�̏����f�[�^���Z�b�g
	PlayerX = 60;
	PlayerY = 640;

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
			
		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();	
	
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �L�[���͎擾
		Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		// ��������
		PlayerY -= JumpPower;

		// ���������x�t��
		JumpPower -= 1;

		// �v���C���[����ʉ��[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
		if (PlayerY > 720 - 64) PlayerY = 720 - 64;
		// �v���C���[����ʓV�䂩��͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
		if (PlayerY < 0 + 64) PlayerY = 0 + 64;

		// �����n�ʂɂ��Ă�����~�܂�
		if (PlayerY > 640)
		{
			PlayerY = 640;
			JumpPower = 0;
		}

		// space�L�[����������W�����v����
		if ((Key & PAD_INPUT_A) && PlayerY == 640)JumpPower = 28;

		// �v���C���[��`�悷��
		DrawGraph(PlayerX, PlayerY, PlayerGraph, TRUE);
		DrawGraph(EnemyX, EnemyY, EnemyGraph, TRUE);



		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		// esc�L�[�ŃQ�[���I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60�ɌŒ肷��
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66�~���b(16667�}�C�N���b)�o�߂���܂ő҂�
		}
	}

		DxLib_End();				// �c�w���C�u�����g�p�̏I������

		return 0;				// �\�t�g�̏I�� 
}
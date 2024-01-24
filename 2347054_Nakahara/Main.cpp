#include "DxLib.h"
//#include "SceneMgr.h"
#define IMAGE_SIZE	50

int PlayerX, PlayerY;
float JumpPower;
int PlayerGraph;
int EnemyGraph;
int EnemyW, EnemyH;
int PlayerH, PlayerW;


VECTOR EnemyPos;

XINPUT_STATE input;

void BackScroll(const int t_areaX, const int tD_graph, const int t_winWidth, const int t_winHeight)
{
	DrawRectGraph(0, 0, t_areaX, 0, t_winWidth, t_winHeight, tD_graph, false);
	DrawRectGraph(t_winWidth - t_areaX, 0, 0, 0, t_areaX, t_winHeight, tD_graph, false);
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int Key;
	int phase = 0;
	int StartTime;
	int Time;
	int BackGraph = LoadGraph("image/back.png");
	int areaX = 0;
	int speed = 3;
	unsigned int Cr;

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
	// �O���t�B�b�N�wenemy.png�x���������Ƀ��[�h
	EnemyGraph = LoadGraph("image/enemy.png");
	// �O���t�B�b�N�w�w�i.png�x���������Ƀ��[�h
	BackGraph = LoadGraph("image/back.png");

	// �L�����N�^�[�̏����f�[�^���Z�b�g
	PlayerX = 60;
	PlayerY = 640;



	//SceneMgr_Initialize();

	//while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {//��ʍX�V & ���b�Z�[�W���� & ��ʏ���

	//	SceneMgr_Update();  //�X�V
	//	SceneMgr_Draw();    //�`��

	//}

	//SceneMgr_Finalize();

		// ���݌o�ߎ��Ԃ𓾂�
		StartTime = GetNowCount();
		int EnemyNum = 0;

	// �Q�[�����[�v
	while (GetNowCount() - StartTime < 25000)
	{
		
		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();	

		BackScroll(areaX, BackGraph, 1280, 720);

			areaX += speed;
			if (areaX > 1280)
			{
				areaX = 0;
			}
	
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();
		// ���̐F�R�[�h��ۑ�
		Cr = GetColor(255, 255, 255);
		Time = GetNowCount() - StartTime;

		DrawFormatString(1150, 10, Cr, "�o�ߎ���%d�b", Time/1000);

		// �G�l�~�[�̏o������
		if (EnemyNum == 0 && Time >= 0) {
			EnemyPos.x = 1280;
			EnemyPos.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 1 && Time >= 3000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 2 && Time >= 6000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 3 && Time >= 8000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 4 && Time >= 10000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 5 && Time >= 12000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 6 && Time >= 13000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 7 && Time >= 14000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 8 && Time >= 15000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 9 && Time >= 18000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 10 && Time >= 20000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 11 && Time >= 20000) {
			EnemyPos.x = 1280;
			EnemyPos.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 12 && Time >= 22000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 620;
			EnemyNum++;
		}


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

		EnemyPos.x -= 10;


		// �v���C���[��`�悷��
		DrawGraph(PlayerX, PlayerY, PlayerGraph, TRUE);
		// �G�l�~�[��`�悷��
		DrawGraph(EnemyPos.x, EnemyPos.y, EnemyGraph, TRUE);



		// �v���C���[�摜�ƓG�摜�œ����蔻��
		if (PlayerX + IMAGE_SIZE >= EnemyPos.x && PlayerX <= EnemyPos.x + IMAGE_SIZE) {
			if (PlayerY + IMAGE_SIZE >= EnemyPos.y && PlayerY <= EnemyPos.y + IMAGE_SIZE) {
				// ����������v���C���[���f���[�g
				DeleteGraph(PlayerGraph);
			}
		}

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
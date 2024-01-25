#include "DxLib.h"
#include <math.h>

//#include "SceneMgr.h"
#define IMAGE_SIZE	50

int PlayerX, PlayerY;
float JumpPower;
int PlayerGraph;
int EnemyGraph;
int BackGraph;
int TitleGraph;
int EnemyW, EnemyH;
int PlayerH, PlayerW;

constexpr int GAMEEND = 0;
constexpr int TITLESCENE = 1;
constexpr int GAMESCENE = 2;
constexpr int GAMEOVERSCENE = 3;
constexpr int GAMECLEARSCENE = 4;

bool isInputEnterHold = false;// InputEneter�p�̕ϐ�
bool isInputUpHold = false;// InputUp�p�̕ϐ�
bool isInputDownHold = false;// InputDown�p�̕ϐ�

int TitleScene();
int GameScene();
int GameOverScene();
int GameClearScene();
bool InputEnter();
bool InputUp();
bool InputDown();

// �G�l�~�[�\����
VECTOR EnemyPos;
VECTOR EnemyPos1;
VECTOR EnemyPos2;
VECTOR EnemyPos3;
VECTOR EnemyPos4;

XINPUT_STATE input;

void BackScroll(const int t_areaX, const int tD_graph, const int t_winWidth, const int t_winHeight)
{
	DrawRectGraph(0, 0, t_areaX, 0, t_winWidth, t_winHeight, tD_graph, false);
	DrawRectGraph(t_winWidth - t_areaX, 0, 0, 0, t_areaX, t_winHeight, tD_graph, false);
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	LONGLONG roopStartTime = 0;
	bool gameRoop = true;
	int nextScene = TITLESCENE;

	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);
	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(1280, 720, 32);
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);

	while (gameRoop) 
	{
		roopStartTime = GetNowHiPerformanceCount();
	
		ClearDrawScreen();

		if (nextScene == TITLESCENE)
		{
			nextScene = TitleScene();
		}
		else if (nextScene == GAMESCENE)
		{
			nextScene = GameScene();
		}
		else if (nextScene == GAMEOVERSCENE)
		{
			nextScene = GameOverScene();
		}
		else if (nextScene == GAMECLEARSCENE)
		{
			nextScene = GameClearScene();
		}
		else if (nextScene == GAMEEND)
		{
			break;
		}

		//����ʂ�\��
		ScreenFlip();

		//���t���b�V������(-1�Ȃ�G���[)
		if (ProcessMessage() < 0)
		{
			break;
		}

		// esc�L�[�ŃQ�[���I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60�ɌŒ肷��
		while (GetNowHiPerformanceCount() - roopStartTime < 16667)
		{
			// 16.66�~���b(16667�}�C�N���b)�o�߂���܂ő҂�
		}
	}

		DxLib_End();				// �c�w���C�u�����g�p�̏I������

		return 0;				// �\�t�g�̏I�� 
}

int TitleScene()
{
	/*�ϐ�*/
	bool gameRoop = true;
	int nextScene = TITLESCENE;
	int arrowPosY = 440;
	int countFrame = 0;

	/*�Q�[������*/
	while (gameRoop)
	{
		/*�v�Z����*/
		//Input Down.
		if (InputDown())
		{
			if (arrowPosY == 440)
			{
				arrowPosY = 480;
			}
			else
			{
				arrowPosY = 440;
			}
		}
		//Input Up.
		if (InputUp())
		{
			if (arrowPosY == 440)
			{
				arrowPosY = 480;
			}
			else
			{
				arrowPosY = 440;
			}
		}


		/*�^�C�}�X�V*/
		countFrame++;
		if (countFrame > 80000) { countFrame = 0; }//���ȏ㐔���������珉����(���͓K��)

		/*Draw����*/
		//����ʂ̏�����
		ClearDrawScreen();

		//�^�C�g�����S
		//SetFontSize(80);//�t�H���g�T�C�Y�ύX
		//DrawString(440, 240, "", GetColor(255, 255, 255));
		//SetFontSize(40);//�t�H���g�T�C�Y��
		//DrawString(460, 320, "-GameTemplate1-", GetColor(255, 255, 255));
		//SetFontSize(20);//�t�H���g�T�C�Y������
		//�Q�[���V�[���e�L�X�g
		DrawString(600, 440, "START", GetColor(255, 255, 255));
		//�Q�[���G���h�e�L�X�g
		DrawString(600, 480, "END", GetColor(255, 255, 255));
		//���\��(�_�ł�����)
		if ((countFrame % 60) < 32)
		{
			DrawString(560, arrowPosY, "->", GetColor(255, 255, 255));
		}

		// �O���t�B�b�N�wTitle.png�x���������Ƀ��[�h
		TitleGraph = LoadGraph("image/Title.png");

		/*DebugDraw����*/
		DrawString(0, 0, "TitleScene", GetColor(255, 255, 255));//�V�[�����\��

		//����ʂ�\��
		ScreenFlip();

		/*�V�[���J�ڏ���*/
		//�G���^�[�ŃV�[���ύX
		if (InputEnter())
		{
			if (arrowPosY == 440)
			{
				return GAMESCENE;
			}
			else
			{
				return GAMEEND;
			}

		}
	}

	//��O����
	return TITLESCENE;
}

int GameScene()
{
	bool gameRoop = true;
	int Key;
	int phase = 0;
	int StartTime;
	int Time;
	int areaX = 0;
	int speed = 3;
	unsigned int Cr;
	int nextScene = GAMESCENE;


	// �O���t�B�b�N�wplayer.png�x���������Ƀ��[�h
	PlayerGraph = LoadGraph("image/player.png");
	// �O���t�B�b�N�wenemy.png�x���������Ƀ��[�h
	EnemyGraph = LoadGraph("image/enemy.png");
	// �O���t�B�b�N�wback.png�x���������Ƀ��[�h
	BackGraph = LoadGraph("image/back.png");

	// �L�����N�^�[�̏����f�[�^���Z�b�g
	PlayerX = 60;
	PlayerY = 600;

	// ���݌o�ߎ��Ԃ𓾂�
	StartTime = GetNowCount();
	int EnemyNum = 0;

	// �Q�[�����[�v
	while (gameRoop)
	{

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		BackScroll(areaX, BackGraph, 1280, 720);

		areaX += speed;
		if (areaX > 1280)
		{
			areaX = 0;
		}

		// ���̐F�R�[�h��ۑ�
		Cr = GetColor(255, 255, 255);
		Time = GetNowCount() - StartTime;

		DrawFormatString(1150, 10, Cr, "�o�ߎ���%d�b", Time / 1000);

		// �G�l�~�[�̏o������
		if (EnemyNum == 0 && Time >= 0) {
			EnemyPos.x = 1280;
			EnemyPos.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 1 && Time >= 3000) {
			EnemyPos1.x = 1270;
			EnemyPos1.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 2 && Time >= 6000) {
			EnemyPos2.x = 1270;
			EnemyPos2.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 3 && Time >= 8000) {
			EnemyPos3.x = 1270;
			EnemyPos3.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 4 && Time >= 10000) {
			EnemyPos4.x = 1270;
			EnemyPos4.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 5 && Time >= 12000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 6 && Time >= 13000) {
			EnemyPos1.x = 1270;
			EnemyPos1.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 7 && Time >= 14000) {
			EnemyPos2.x = 1270;
			EnemyPos2.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 8 && Time >= 15000) {
			EnemyPos3.x = 1270;
			EnemyPos3.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 9 && Time >= 18000) {
			EnemyPos4.x = 1270;
			EnemyPos4.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 10 && Time >= 20000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 11 && Time >= 20000) {
			EnemyPos1.x = 1280;
			EnemyPos1.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 12 && Time >= 22000) {
			EnemyPos2.x = 1270;
			EnemyPos2.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 13 && Time >= 24000) {
			EnemyPos3.x = 1270;
			EnemyPos3.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 14 && Time >= 24000) {
			EnemyPos4.x = 1270;
			EnemyPos4.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 10 && Time >= 26000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 11 && Time >= 28000) {
			EnemyPos1.x = 1280;
			EnemyPos1.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 12 && Time >= 28000) {
			EnemyPos2.x = 1270;
			EnemyPos2.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 13 && Time >= 30000) {
			EnemyPos3.x = 1270;
			EnemyPos3.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 14 && Time >= 31000) {
			EnemyPos4.x = 1270;
			EnemyPos4.y = 310;
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
		if (PlayerY > 600)
		{
			PlayerY = 600;
			JumpPower = 0;
		}

		// Z�L�[����������W�����v����
		if ((Key & PAD_INPUT_A) && PlayerY == 600)JumpPower = 28;

		EnemyPos.x -= 10;
		EnemyPos1.x -= 10;
		EnemyPos2.x -= 10;
		EnemyPos3.x -= 10;
		EnemyPos4.x -= 10;


		// �v���C���[��`�悷��
		DrawGraph(PlayerX, PlayerY, PlayerGraph, TRUE);
		// �G�l�~�[��`�悷��
		DrawGraph(EnemyPos.x, EnemyPos.y, EnemyGraph, TRUE);
		DrawGraph(EnemyPos1.x, EnemyPos1.y, EnemyGraph, TRUE);
		DrawGraph(EnemyPos2.x, EnemyPos2.y, EnemyGraph, TRUE);
		DrawGraph(EnemyPos3.x, EnemyPos3.y, EnemyGraph, TRUE);
		DrawGraph(EnemyPos4.x, EnemyPos4.y, EnemyGraph, TRUE);



		// �v���C���[�摜�ƓG�摜�œ����蔻��
		if (PlayerX + IMAGE_SIZE >= EnemyPos.x && PlayerX <= EnemyPos.x + IMAGE_SIZE) {
			if (PlayerY + IMAGE_SIZE >= EnemyPos.y && PlayerY <= EnemyPos.y + IMAGE_SIZE) {
				// ����������v���C���[���f���[�g
				DeleteGraph(PlayerGraph);
				return GAMEOVERSCENE;
			}
		}
		if (PlayerX + IMAGE_SIZE >= EnemyPos1.x && PlayerX <= EnemyPos1.x + IMAGE_SIZE) {
			if (PlayerY + IMAGE_SIZE >= EnemyPos1.y && PlayerY <= EnemyPos1.y + IMAGE_SIZE) {
				// ����������v���C���[���f���[�g
				DeleteGraph(PlayerGraph);
				return GAMEOVERSCENE;
			}
		}
		if (PlayerX + IMAGE_SIZE >= EnemyPos2.x && PlayerX <= EnemyPos2.x + IMAGE_SIZE) {
			if (PlayerY + IMAGE_SIZE >= EnemyPos2.y && PlayerY <= EnemyPos2.y + IMAGE_SIZE) {
				// ����������v���C���[���f���[�g
				DeleteGraph(PlayerGraph);
				return GAMEOVERSCENE;
			}
		}
		if (PlayerX + IMAGE_SIZE >= EnemyPos3.x && PlayerX <= EnemyPos3.x + IMAGE_SIZE) {
			if (PlayerY + IMAGE_SIZE >= EnemyPos3.y && PlayerY <= EnemyPos3.y + IMAGE_SIZE) {
				// ����������v���C���[���f���[�g
				DeleteGraph(PlayerGraph);
				return GAMEOVERSCENE;
			}
		}
		if (PlayerX + IMAGE_SIZE >= EnemyPos4.x && PlayerX <= EnemyPos4.x + IMAGE_SIZE) {
			if (PlayerY + IMAGE_SIZE >= EnemyPos4.y && PlayerY <= EnemyPos4.y + IMAGE_SIZE) {
				// ����������v���C���[���f���[�g
				DeleteGraph(PlayerGraph);
				return GAMEOVERSCENE;
			}
		}

		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		/*�V�[���J�ڏ���*/
			//�G���^�[�ŃV�[���ύX
		if (InputEnter())
		{
			return TITLESCENE;
		}

	}

	//��O����
	return GAMECLEARSCENE;
}

int GameOverScene()
{
	int nextScene = GAMEOVERSCENE;
	int arrowPosY = 440;
	int countFrame = 0;
	bool gameRoop = true;



	while (gameRoop)
	{
		/*�v�Z����*/
	//Input Down.
		if (InputDown())
		{
			if (arrowPosY == 440)
			{
				arrowPosY = 480;
			}
			else
			{
				arrowPosY = 440;
			}
		}
		//Input Up.
		if (InputUp())
		{
			if (arrowPosY == 440)
			{
				arrowPosY = 480;
			}
			else
			{
				arrowPosY = 440;
			}
		}


		/*�^�C�}�X�V*/
		countFrame++;
		if (countFrame > 80000) { countFrame = 0; }//���ȏ㐔���������珉����(���͓K��)

		/*Draw����*/
		//����ʂ̏�����
		ClearDrawScreen();

		//�Q�[���V�[���e�L�X�g
		DrawString(600, 440, "RE START", GetColor(255, 255, 255));
		//�Q�[���G���h�e�L�X�g
		DrawString(600, 480, "TITLE", GetColor(255, 255, 255));
		//���\��(�_�ł�����)
		if ((countFrame % 60) < 32)
		{
			DrawString(560, arrowPosY, "->", GetColor(255, 255, 255));
		}

		DrawString(0, 0, "GameOverScene", GetColor(255, 255, 255));//�V�[�����\��

		ScreenFlip();

		/*�V�[���J�ڏ���*/
		//�G���^�[�ŃV�[���ύX
		if (InputEnter())
		{
			if (arrowPosY == 440)
			{
				return GAMESCENE;
			}
			else
			{
				return TITLESCENE;
			}

		}
	}
	
}

int GameClearScene()
{
	int nextScene = GAMECLEARSCENE;
	int arrowPosY = 440;
	int countFrame = 0;
	bool gameRoop = true;

	while (gameRoop)
	{
		/*�v�Z����*/
//Input Down.
		if (InputDown())
		{
			if (arrowPosY == 440)
			{
				arrowPosY = 480;
			}
			else
			{
				arrowPosY = 440;
			}
		}
		//Input Up.
		if (InputUp())
		{
			if (arrowPosY == 440)
			{
				arrowPosY = 480;
			}
			else
			{
				arrowPosY = 440;
			}
		}


		/*�^�C�}�X�V*/
		countFrame++;
		if (countFrame > 80000) { countFrame = 0; }//���ȏ㐔���������珉����(���͓K��)

		/*Draw����*/
		//����ʂ̏�����
		ClearDrawScreen();

		//�Q�[���V�[���e�L�X�g
		DrawString(600, 440, "RE START", GetColor(255, 255, 255));
		//�Q�[���G���h�e�L�X�g
		DrawString(600, 480, "TITLE", GetColor(255, 255, 255));
		//���\��(�_�ł�����)
		if ((countFrame % 60) < 32)
		{
			DrawString(560, arrowPosY, "->", GetColor(255, 255, 255));
		}

		DrawString(0, 0, "GameClearScene", GetColor(255, 255, 255));//�V�[�����\��

		ScreenFlip();

		/*�V�[���J�ڏ���*/
		//�G���^�[�ŃV�[���ύX
		if (InputEnter())
		{
			if (arrowPosY == 440)
			{
				return GAMESCENE;
			}
			else
			{
				return TITLESCENE;
			}

		}
	}

	
	return TITLESCENE;
}

bool InputEnter()
{
	//�w��t���[���ȏ㉟���Ă����牟��������
	if (CheckHitKey(KEY_INPUT_RETURN) && !isInputEnterHold)
	{
		isInputEnterHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_RETURN))
	{
		isInputEnterHold = false;
	}

	return false;
}
//Up�������ꂽ���ǂ����𔻒肷��֐�
//Up���������炸�C�P�ĂȂ��B���R�����蒼���Ă����܂��B
bool InputUp()
{
	//�w��t���[���ȏ㉟���Ă����牟��������
	if (CheckHitKey(KEY_INPUT_UP) && !isInputDownHold)
	{
		isInputDownHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_UP))
	{
		isInputDownHold = false;
	}

	return false;
}
//Down�������ꂽ���ǂ����𔻒肷��֐�
//Down���������炸�C�P�ĂȂ��B���R�����蒼���Ă����܂��B
bool InputDown()
{
	//�w��t���[���ȏ㉟���Ă����牟��������
	if (CheckHitKey(KEY_INPUT_DOWN) && !isInputUpHold)
	{
		isInputUpHold = true;
		return true;
	}
	else if (!CheckHitKey(KEY_INPUT_DOWN))
	{
		isInputUpHold = false;
	}

	return false;
}
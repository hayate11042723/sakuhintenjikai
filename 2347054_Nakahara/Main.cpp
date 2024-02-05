#include "DxLib.h"
#include <math.h>

//#include "SceneMgr.h"
#define IMAGE_SIZE	50
#define XINPUT_BUTTON_X


int Key;
int Key1;
int Key2;

int PlayerX, PlayerY;
int PlayerH, PlayerW;
int PlayerGraph;

int EnemyW, EnemyH;

int BackGraph;
int TitleGraph;
int TitleScrollGraph;
int ChangeSceenGraph;
int ChangeSceen2Graph;

int ManualGraph;

int GameOverGraph;
int GameOverTxtGraph;

int ClearGraph;
int GameClearTxtGraph;

int ArrowGraph;

int BgmHandle;
int SeHandle;
int GameOverHandle;

float JumpPower;
float JumpPower1;
float JumpPower2;

constexpr int GAMEEND = 0;
constexpr int TITLESCENE = 1;
constexpr int MANUALSCENE = 2;
constexpr int GAMESCENE = 3;
constexpr int GAMEOVERSCENE = 4;
constexpr int GAMECLEARSCENE = 5;


bool isInputEnterHold = false;// InputEneter用の変数
bool isInputUpHold = false;// InputUp用の変数
bool isInputDownHold = false;// InputDown用の変数
bool isInputJump1Hold = false;// InputJump1用の変数
bool isInputJump2Hold = false;// InputJump2用の変数

int TitleScene();
int ManualScene();
int GameScene();
int GameOverScene();
int GameClearScene();
bool InputEnter();
bool InputUp();
bool InputDown();
bool InputJump1();
bool InputJump2();

// エネミー構造体
VECTOR EnemyPos;
VECTOR EnemyPos1;
VECTOR EnemyPos2;
VECTOR EnemyPos3;
VECTOR EnemyPos4;
VECTOR EnemyPos5;
VECTOR EnemyPos6;
VECTOR EnemyPos7;
VECTOR EnemyPos8;
VECTOR EnemyPos9;

XINPUT_STATE input;

void BackScroll(const int t_areaX, const int tD_graph, const int t_winWidth, const int t_winHeight)
{
	DrawRectGraph(0, 0, t_areaX, 0, t_winWidth, t_winHeight, tD_graph, false);
	DrawRectGraph(t_winWidth - t_areaX, 0, 0, 0, t_areaX, t_winHeight, tD_graph, false);
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	LONGLONG roopStartTime = 0;
	bool gameRoop = true;
	int nextScene = TITLESCENE;

	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(true);
	SetWindowText("すらいむすとろぉく");

	//if (KEY_INPUT_ESCAPE) {
	//	ChangeWindowMode(false);
	//}
	// 画面モードの設定
	SetGraphMode(1280, 720, 32);
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);

	// BGM
	BgmHandle = LoadSoundMem("image/maou_game_village05.mp3");

	

	EnemyPos.x = 800;
	EnemyPos.y = 800;

	EnemyPos1.x = 800;
	EnemyPos1.y = 800;

	EnemyPos2.x = 800;
	EnemyPos2.y = 800;

	while (gameRoop) 
	{
		roopStartTime = GetNowHiPerformanceCount();

		ClearDrawScreen();

		if (nextScene == TITLESCENE)
		{
			nextScene = TitleScene();


			if (nextScene == GAMESCENE)
			{
				EnemyPos.x = 800;
				EnemyPos.y = 800;

				EnemyPos1.x = 800;
				EnemyPos1.y = 800;

				EnemyPos2.x = 800;
				EnemyPos2.y = 800;

				EnemyPos3.x = 800;
				EnemyPos3.y = 800;

				EnemyPos4.x = 800;
				EnemyPos4.y = 800;

				EnemyPos5.x = 800;
				EnemyPos5.y = 800;

				EnemyPos6.x = 800;
				EnemyPos6.y = 800;

				EnemyPos7.x = 800;
				EnemyPos7.y = 800;

				EnemyPos8.x = 800;
				EnemyPos8.y = 800;

				EnemyPos9.x = 800;
				EnemyPos9.y = 800;
			}
		}
		else if (nextScene == MANUALSCENE)
		{
			nextScene = ManualScene();

			if (nextScene == TITLESCENE)
			{
				EnemyPos.x = 800;
				EnemyPos.y = 800;

				EnemyPos1.x = 800;
				EnemyPos1.y = 800;

				EnemyPos2.x = 800;
				EnemyPos2.y = 800;

			}
		}
		else if (nextScene == GAMESCENE)
		{
			nextScene = GameScene();

			if (nextScene == GAMEOVERSCENE)
			{
				StopSoundMem(BgmHandle);
			}

			if (nextScene == TITLESCENE) 
			{
				EnemyPos.x = 800;
				EnemyPos.y = 800;

				EnemyPos1.x = 800;
				EnemyPos1.y = 800;

				EnemyPos2.x = 800;
				EnemyPos2.y = 800;

				StopSoundMem(BgmHandle);
			}
		}
		else if (nextScene == GAMEOVERSCENE)
		{
			nextScene = GameOverScene();

			if (nextScene == TITLESCENE) 
			{
				EnemyPos.x = 800;
				EnemyPos.y = 800;

				EnemyPos1.x = 800;
				EnemyPos1.y = 800;

				EnemyPos2.x = 800;
				EnemyPos2.y = 800;

				StopSoundMem(GameOverHandle);
			}

			if (nextScene == GAMESCENE)
			{
				EnemyPos.x = 800;
				EnemyPos.y = 800;

				EnemyPos1.x = 800;
				EnemyPos1.y = 800;
				
				EnemyPos2.x = 800;
				EnemyPos2.y = 800;	
				
				EnemyPos3.x = 800;
				EnemyPos3.y = 800;

				EnemyPos4.x = 800;
				EnemyPos4.y = 800;

				EnemyPos5.x = 800;
				EnemyPos5.y = 800;

				EnemyPos6.x = 800;
				EnemyPos6.y = 800;

				EnemyPos7.x = 800;
				EnemyPos7.y = 800;

				EnemyPos8.x = 800;
				EnemyPos8.y = 800;

				EnemyPos9.x = 800;
				EnemyPos9.y = 800;

				StopSoundMem(GameOverHandle);
				// BGMをメモリにロード
				PlaySoundMem(BgmHandle, DX_PLAYTYPE_LOOP);
			}
		}
		else if (nextScene == GAMECLEARSCENE)
		{
			nextScene = GameClearScene();

			if (nextScene == GAMESCENE)
			{
				EnemyPos.x = 800;
				EnemyPos.y = 800;

				EnemyPos1.x = 800;
				EnemyPos1.y = 800;

				EnemyPos2.x = 800;
				EnemyPos2.y = 800;

				EnemyPos3.x = 800;
				EnemyPos3.y = 800;

				EnemyPos4.x = 800;
				EnemyPos4.y = 800;

				EnemyPos5.x = 800;
				EnemyPos5.y = 800;

				EnemyPos6.x = 800;
				EnemyPos6.y = 800;

				EnemyPos7.x = 800;
				EnemyPos7.y = 800;

				EnemyPos8.x = 800;
				EnemyPos8.y = 800;

				EnemyPos9.x = 800;
				EnemyPos9.y = 800;

				// BGMをメモリにロード
				PlaySoundMem(BgmHandle, DX_PLAYTYPE_LOOP);
			}

			if (nextScene == TITLESCENE) 
			{
				EnemyPos.x = 800;
				EnemyPos.y = 800;

				EnemyPos1.x = 800;
				EnemyPos1.y = 800;

				EnemyPos2.x = 800;
				EnemyPos2.y = 800;
				// BGMをメモリにロード
				PlaySoundMem(BgmHandle, DX_PLAYTYPE_LOOP);
			}
		}
		else if (nextScene == GAMEEND)
		{
			break;
		}

		//裏画面を表へ
		ScreenFlip();

		//リフレッシュ処理(-1ならエラー)
		if (ProcessMessage() < 0)
		{
			break;
		}

		// escキーでゲーム終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60に固定する
		while (GetNowHiPerformanceCount() - roopStartTime < 16667)
		{
			// 16.66ミリ秒(16667マイクロ秒)経過するまで待つ
		}
	}

		DxLib_End();				// ＤＸライブラリ使用の終了処理

		return 0;				// ソフトの終了 
}

int TitleScene()
{
	/*変数*/
	bool gameRoop = true;
	int nextScene = TITLESCENE;
	int arrowPosY = 0;
	int countFrame = 0;
	int areaX = 0;
	int speed = 3;
	int EnemyGraph;

	// グラフィック『Title.png』をメモリにロード
	TitleScrollGraph = LoadGraph("image/title (2).png");
	TitleGraph = LoadGraph("image/Title.png");
	
	// シーン選択をメモリにロード
	ChangeSceenGraph = LoadGraph("image/ChangeSceen.png");
	ChangeSceen2Graph = LoadGraph("image/ChangeSceen(2).png");

	// グラフィック『arrow.png』をメモリにロード
	ArrowGraph = LoadGraph("image/arrow.png");
	
	// グラフィック『player.png』をメモリにロード
	PlayerGraph = LoadGraph("image/player.png");
	GetGraphSize(PlayerGraph, &PlayerW, &PlayerH);
	
	// グラフィック『enemy.png』をメモリにロード
	EnemyGraph = LoadGraph("image/enemy.png");
	GetGraphSize(EnemyGraph, &EnemyW, &EnemyH);
	
	// BGMをメモリにロード
	PlaySoundMem(BgmHandle, DX_PLAYTYPE_LOOP);


	// キャラクターの初期データをセット
	PlayerX = 60;
	PlayerY = 600;

	/*ゲーム処理*/
	while (gameRoop)
	{
		/*計算処理*/
		//Input Down.
		if (InputDown())
		{
			if (arrowPosY == 0)
			{
				arrowPosY = 40;
			}
			else if (arrowPosY == 40 , arrowPosY > 80)
			{
				arrowPosY = 0;
			}
			else
			{
				arrowPosY = 80;
			}
		}
		//Input Up.
		if (InputUp())
		{
			if (arrowPosY == 80)
			{
				arrowPosY = 40;
			}
			else if (arrowPosY == 40, arrowPosY < 80)
			{
				arrowPosY = 0;
			}
			else
			{
				arrowPosY = 80;
			}
		}


		/*タイマ更新*/
		countFrame++;
		if (countFrame > 380) { countFrame = 0; }//一定以上数が増えたら初期化(数は適当)

		/*Draw処理*/
		//裏画面の初期化
		ClearDrawScreen();

		if (countFrame == 120)
		{
			EnemyPos.x = 1280;
			EnemyPos.y = 600;
		}
		if (countFrame == 280) 
		{
			EnemyPos1.x = 1270;
			EnemyPos1.y = 460;
		}
		if (countFrame == 280) 
		{
			EnemyPos2.x = 1270;
			EnemyPos2.y = 600;
		}


		EnemyPos.x -= 10;
		EnemyPos1.x -= 10;
		EnemyPos2.x -= 10;


		// 背景スクロールの描画
		BackScroll(areaX, TitleScrollGraph, 1280, 720);
		const float SinSpeed = 0.1f;
		const float AnimationSize = 8.0f;
		static float AnimationHeight = 0.0f;	// プレイヤーが弾んでいるようにアニメーションしているよう見せるための高さ値
		static float SinCount = 0;
		SinCount += SinSpeed;
		AnimationHeight = sinf(SinCount) * AnimationSize;		// 決まった数値だけ高さを増やしてあげる
		// プレイヤーの描画
		DrawExtendGraph(PlayerX, PlayerY - AnimationHeight, PlayerX + PlayerW, PlayerY + PlayerH, PlayerGraph, TRUE);
		// エネミーの描画
		DrawExtendGraph(EnemyPos.x, EnemyPos.y - AnimationHeight, EnemyPos.x + EnemyW, EnemyPos.y + EnemyH, EnemyGraph, TRUE);
		DrawExtendGraph(EnemyPos1.x, EnemyPos1.y - AnimationHeight, EnemyPos1.x + EnemyW, EnemyPos1.y + EnemyH, EnemyGraph, TRUE);
		DrawExtendGraph(EnemyPos2.x, EnemyPos2.y - AnimationHeight, EnemyPos2.x + EnemyW, EnemyPos2.y + EnemyH, EnemyGraph, TRUE);
		// タイトルの描画
		DrawGraph(0, 0, TitleGraph, true);
		DrawGraph(0, 0, ChangeSceenGraph, true);
		DrawGraph(0, 0, ChangeSceen2Graph, true);


		areaX += speed;
		if (areaX > 1280)
		{
			areaX = 0;
		}

		// 落下処理
		PlayerY -= JumpPower;
		PlayerY -= JumpPower1;

		// 落下加速度付加
		JumpPower -= 0.5;
		JumpPower1 -= 0.5;

		// プレイヤーが画面下端からはみ出そうになっていたら画面内の座標に戻してあげる
		if (PlayerY > 720 - 64) PlayerY = 720 - 64;
		// プレイヤーが画面天井からはみ出そうになっていたら画面内の座標に戻してあげる
		if (PlayerY < 0 + 64) PlayerY = 0 + 64;

		// もし地面についていたら止まる
		if (PlayerY > 600)
		{
			PlayerY = 600;
			JumpPower = 0;
			JumpPower1 = 0;
		}
		if (countFrame == 220)JumpPower = 24;
		if (countFrame == 375)JumpPower1 = 29;


		//タイトルロゴ
		//SetFontSize(80);//フォントサイズ変更
		//DrawString(440, 240, "", GetColor(255, 255, 255));
		//SetFontSize(40);//フォントサイズ上
		//DrawString(460, 320, "-GameTemplate1-", GetColor(255, 255, 255));
		//SetFontSize(20);//フォントサイズ初期化
		//矢印表示(点滅させる)
		if ((countFrame % 60) < 32)
		{
			DrawGraph(0, arrowPosY, ArrowGraph, true);
		}

		//裏画面を表へ
		ScreenFlip();

		/*シーン遷移処理*/
		//エンターでシーン変更
		if (InputEnter())
		{
			if (arrowPosY == 0)
			{
				return GAMESCENE;
			}
			else if (arrowPosY == 40)
			{
				return MANUALSCENE;
			}
			else
			{
				return GAMEEND;
			}
		}

			//// 再生を止めます
			//StopSoundMem(BgmHandle);
	}

	DeleteSoundMem(BgmHandle);

	//例外処理
	return TITLESCENE;
}

int ManualScene()
{
	int GameRoop = true;
	int countFrame = 0;
	int nextScene = MANUALSCENE;
	int areaX = 0;
	int speed = 2;
	
	PlayerGraph = LoadGraph("image/player.png");
	GetGraphSize(PlayerGraph, &PlayerW, &PlayerH);
	BackGraph = LoadGraph("image/back.png");
	ManualGraph = LoadGraph("image/manual.png");

	// キャラクターの初期データをセット
	PlayerX = 60;
	PlayerY = 600;

	while (GameRoop)
	{
		/*タイマ更新*/
		countFrame++;
		if (countFrame > 120) { countFrame = 0; }//一定以上数が増えたら初期化(数は適当)

		/*Draw処理*/
		//裏画面の初期化
		ClearDrawScreen();

		BackScroll(areaX, BackGraph, 1280, 720);

		areaX += speed;
		if (areaX > 1280)
		{
			areaX = 0;
		}

		// 落下処理
		PlayerY -= JumpPower;

		// 落下加速度付加
		JumpPower -= 1;

		// プレイヤーが画面下端からはみ出そうになっていたら画面内の座標に戻してあげる
		if (PlayerY > 720 - 64) PlayerY = 720 - 64;
		// プレイヤーが画面天井からはみ出そうになっていたら画面内の座標に戻してあげる
		if (PlayerY < 0 + 64) PlayerY = 0 + 64;

		// もし地面についていたら止まる
		if (PlayerY > 600)
		{
			PlayerY = 600;
			JumpPower = 0;
		}
		if (countFrame == 120)JumpPower = 20;

		const float SinSpeed = 0.1f;
		const float AnimationSize = 5.0f;
		static float AnimationHeight = 0.0f;	// プレイヤーが弾んでいるようにアニメーションしているよう見せるための高さ値
		static float SinCount = 0;
		SinCount += SinSpeed;
		AnimationHeight = sinf(SinCount) * AnimationSize;		// 決まった数値だけ高さを増やしてあげる
		DrawExtendGraph(PlayerX, PlayerY - AnimationHeight, PlayerX + PlayerW, PlayerY + PlayerH, PlayerGraph, TRUE);

		DrawGraph(0, 0, ManualGraph, true);

		//裏画面を表へ
		ScreenFlip();
	
	
		/*シーン遷移処理*/
		//エンターでシーン変更
		if (InputEnter())
		{
			return TITLESCENE;
		}
	}
		return TITLESCENE;
}




int GameScene()
{
	int EnemyGraph;
	bool gameRoop = true;
	int phase = 0;
	int StartTime;
	int Time;
	int areaX = 0;
	int speed = 3;
	unsigned int Cr;
	int nextScene = GAMESCENE;

	// グラフィック『player.png』をメモリにロード
	PlayerGraph = LoadGraph("image/player.png");
	GetGraphSize(PlayerGraph, &PlayerW, &PlayerH);
	// グラフィック『enemy.png』をメモリにロード
	EnemyGraph = LoadGraph("image/enemy.png");
	GetGraphSize(EnemyGraph, &EnemyW, &EnemyH);
	// グラフィック『back.png』をメモリにロード
	BackGraph = LoadGraph("image/back.png");
	// 音源『SlimeSe.mp3』をメモリにロード
	SeHandle = LoadSoundMem("image/SlimeSe.mp3");

	// キャラクターの初期データをセット
	PlayerX = 60;
	PlayerY = 600;

	// 現在経過時間を得る
	StartTime = GetNowCount();

	int EnemyNum = 0;
	int JumpNum = 0;

	// ゲームループ
	while (GetNowCount() - StartTime < 60000)
	{

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		BackScroll(areaX, BackGraph, 1280, 720);

		areaX += speed;
		if (areaX > 1280)
		{
			areaX = 0;
		}

		// 白の色コードを保存
		Cr = GetColor(200, 100, 0);
		Time = GetNowCount() - StartTime;

		SetFontSize(30);

		DrawFormatString(1100, 10, Cr, "経過時間%d秒", Time / 1000);

		// エネミーの出現処理
		if (EnemyNum == 0 && Time >= 0) {
			EnemyPos.x = 1280;
			EnemyPos.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 1 && Time >= 3000) {
			EnemyPos1.x = 1270;
			EnemyPos1.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 2 && Time >= 6000) {
			EnemyPos2.x = 1270;
			EnemyPos2.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 3 && Time >= 8000) {
			EnemyPos3.x = 1270;
			EnemyPos3.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 4 && Time >= 10000) {
			EnemyPos4.x = 1270;
			EnemyPos4.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 5 && Time >= 12000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 6 && Time >= 12000) {
			EnemyPos1.x = 1270;
			EnemyPos1.y = 460;
			EnemyNum++;
		}
		if (EnemyNum == 7 && Time >= 14000) {
			EnemyPos2.x = 1270;
			EnemyPos2.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 8 && Time >= 14000) {
			EnemyPos3.x = 1270;
			EnemyPos3.y = 460;
			EnemyNum++;
		}
		if (EnemyNum == 9 && Time >= 16000) {
			EnemyPos4.x = 1270;
			EnemyPos4.y = 600;
			EnemyNum++;
		}	
		if (EnemyNum == 10 && Time >= 16000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 460;
			EnemyNum++;
		}
		if (EnemyNum == 11 && Time >= 18000) {
			EnemyPos1.x = 1270;
			EnemyPos1.y = 600;
			EnemyNum++;
		}	
		if (EnemyNum == 12 && Time >= 18000) {
			EnemyPos2.x = 1270;
			EnemyPos2.y = 460;
			EnemyNum++;
		}
		if (EnemyNum == 13 && Time >= 20000) {
			EnemyPos3.x = 1270;
			EnemyPos3.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 14 && Time >= 20000) {
			EnemyPos4.x = 1280;
			EnemyPos4.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 15 && Time >= 22000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 16 && Time >= 24000) {
			EnemyPos1.x = 1270;
			EnemyPos1.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 17 && Time >= 24000) {
			EnemyPos2.x = 1270;
			EnemyPos2.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 18 && Time >= 26000) {
			EnemyPos3.x = 1270;
			EnemyPos3.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 19 && Time >= 28000) {
			EnemyPos4.x = 1280;
			EnemyPos4.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 20 && Time >= 28000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 21 && Time >= 30000) {
			EnemyPos1.x = 1270;
			EnemyPos1.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 22 && Time >= 32000) {
			EnemyPos2.x = 1270;
			EnemyPos2.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 23 && Time >= 32000) {
			EnemyPos3.x = 1270;
			EnemyPos3.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 24 && Time >= 33000) {
			EnemyPos4.x = 1280;
			EnemyPos4.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 25 && Time >= 35000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 26 && Time >= 35000) {
			EnemyPos1.x = 1270;
			EnemyPos1.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 27 && Time >= 36000) {
			EnemyPos2.x = 1270;
			EnemyPos2.y = 600;
			EnemyNum++;
		}	
		if (EnemyNum == 28 && Time >= 38000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 29 && Time >= 38000) {
			EnemyPos1.x = 1280;
			EnemyPos1.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 30 && Time >= 39000) {
			EnemyPos2.x = 1270;
			EnemyPos2.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 31 && Time >= 41000) {
			EnemyPos3.x = 1270;
			EnemyPos3.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 32 && Time >= 41000) {
			EnemyPos4.x = 1270;
			EnemyPos4.y = 310;
			EnemyNum++;
		}		
		if (EnemyNum == 33 && Time >= 42000) {
			EnemyPos5.x = 1270;
			EnemyPos5.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 34 && Time >= 44000) {
			EnemyPos6.x = 1280;
			EnemyPos6.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 35 && Time >= 44000) {
			EnemyPos7.x = 1270;
			EnemyPos7.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 36 && Time >= 45000) {
			EnemyPos8.x = 1270;
			EnemyPos8.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 37 && Time >= 45000) {
			EnemyPos9.x = 1270;
			EnemyPos9.y = 310;
			EnemyNum++;
		}	
		if (EnemyNum == 38 && Time >= 46000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 39 && Time >= 46000) {
			EnemyPos1.x = 1280;
			EnemyPos1.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 40 && Time >= 47000) {
			EnemyPos2.x = 1270;
			EnemyPos2.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 41 && Time >= 47000) {
			EnemyPos3.x = 1270;
			EnemyPos3.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 42 && Time >= 48000) {
			EnemyPos4.x = 1270;
			EnemyPos4.y = 310;
			EnemyNum++;
		}		
		if (EnemyNum == 43 && Time >= 48000) {
			EnemyPos5.x = 1270;
			EnemyPos5.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 44 && Time >= 49000) {
			EnemyPos6.x = 1280;
			EnemyPos6.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 45 && Time >= 49000) {
			EnemyPos7.x = 1270;
			EnemyPos7.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 46 && Time >= 50000) {
			EnemyPos8.x = 1270;
			EnemyPos8.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 47 && Time >= 50000) {
			EnemyPos9.x = 1270;
			EnemyPos9.y = 310;
			EnemyNum++;
		}		
		if (EnemyNum == 48 && Time >= 50700) {
			EnemyPos.x = 1270;
			EnemyPos.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 49 && Time >= 50700) {
			EnemyPos1.x = 1280;
			EnemyPos1.y = 460;
			EnemyNum++;
		}
		if (EnemyNum == 50 && Time >= 51500) {
			EnemyPos2.x = 1270;
			EnemyPos2.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 51 && Time >= 52300) {
			EnemyPos3.x = 1270;
			EnemyPos3.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 52 && Time >= 52300) {
			EnemyPos4.x = 1270;
			EnemyPos4.y = 460;
			EnemyNum++;
		}		
		if (EnemyNum == 53 && Time >= 53150) {
			EnemyPos5.x = 1270;
			EnemyPos5.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 54 && Time >= 53150) {
			EnemyPos6.x = 1280;
			EnemyPos6.y = 460;
			EnemyNum++;
		}
		if (EnemyNum == 55 && Time >= 54000) {
			EnemyPos7.x = 1270;
			EnemyPos7.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 56 && Time >= 54000) {
			EnemyPos8.x = 1270;
			EnemyPos8.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 57 && Time >= 54850) {
			EnemyPos9.x = 1270;
			EnemyPos9.y = 460;
			EnemyNum++;
		}
		if (EnemyNum == 58 && Time >= 54850) {
			EnemyPos.x = 1270;
			EnemyPos.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 59 && Time >= 55700) {
			EnemyPos1.x = 1280;
			EnemyPos1.y = 460;
			EnemyNum++;
		}
		if (EnemyNum == 60 && Time >= 55700) {
			EnemyPos3.x = 1270;
			EnemyPos3.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 61 && Time >= 56550) {
			EnemyPos4.x = 1270;
			EnemyPos4.y = 460;
			EnemyNum++;
		}
		if (EnemyNum == 62 && Time >= 56550) {
			EnemyPos5.x = 1270;
			EnemyPos5.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 63 && Time >= 57400) {
			EnemyPos6.x = 1270;
			EnemyPos6.y = 460;
			EnemyNum++;
		}
		if (EnemyNum == 64 && Time >= 57400) {
			EnemyPos7.x = 1270;
			EnemyPos7.y = 600;
			EnemyNum++;
		}

		// 落下処理
		PlayerY -= JumpPower;
		PlayerY -= JumpPower1;
		//PlayerY -= JumpPower2;

		//落下加速度付加
		JumpPower -= 0.8f;
		JumpPower1 -= 0.8f;
	

		// プレイヤーが画面下端からはみ出そうになっていたら画面内の座標に戻してあげる
		if (PlayerY > 720 - 64) PlayerY = 720 - 64;
		// プレイヤーが画面天井からはみ出そうになっていたら画面内の座標に戻してあげる
		if (PlayerY < 0 + 64) PlayerY = 0 + 64;

		// もし地面についていたら止まる
		if (PlayerY > 600)
		{
			PlayerY = 600;
			JumpPower = 0;
			JumpPower1 = 0;
			JumpNum = 0;
		}

		if (InputJump1())
		{
			if (PlayerY == 600)
			{
				JumpPower = 24;
				JumpNum = 1;
				// 読みこんだ音をバックグラウンド再生します(『PlaySoundMem』関数使用)
				PlaySoundMem(SeHandle, DX_PLAYTYPE_BACK);
			}
		}
		if (InputJump2())
		{
			if (JumpNum == 1)
			{
				JumpPower1 = 15;
				JumpNum = 2;
				// 読みこんだ音をバックグラウンド再生します(『PlaySoundMem』関数使用)
				PlaySoundMem(SeHandle, DX_PLAYTYPE_BACK);
			}
		}

		// エネミーの移動処理
		{
			EnemyPos.x -= 10;
			EnemyPos1.x -= 10;
			EnemyPos2.x -= 10;
			EnemyPos3.x -= 10;
			EnemyPos4.x -= 10;
			EnemyPos5.x -= 10;
			EnemyPos6.x -= 10;
			EnemyPos7.x -= 10;
			EnemyPos8.x -= 10;
			EnemyPos9.x -= 10;
		}

		const float SinSpeed = 0.1f;
		const float AnimationSize = 8.0f;
		static float AnimationHeight = 0.0f;	// プレイヤーが弾んでいるようにアニメーションしているよう見せるための高さ値
		static float SinCount = 0;
		SinCount += SinSpeed;
		AnimationHeight = sinf(SinCount) * AnimationSize;		// 決まった数値だけ高さを増やしてあげる
		// プレイヤーを描画する
		{
			DrawExtendGraph(PlayerX, PlayerY - AnimationHeight, PlayerX + PlayerW, PlayerY + PlayerH, PlayerGraph, TRUE);
		}
		// エネミーを描画する
		{
			DrawExtendGraph(EnemyPos.x, EnemyPos.y - AnimationHeight, EnemyPos.x + EnemyW, EnemyPos.y + EnemyH, EnemyGraph, TRUE);
			DrawExtendGraph(EnemyPos1.x, EnemyPos1.y - AnimationHeight, EnemyPos1.x + EnemyW, EnemyPos1.y + EnemyH, EnemyGraph, TRUE);
			DrawExtendGraph(EnemyPos2.x, EnemyPos2.y - AnimationHeight, EnemyPos2.x + EnemyW, EnemyPos2.y + EnemyH, EnemyGraph, TRUE);
			DrawExtendGraph(EnemyPos3.x, EnemyPos3.y - AnimationHeight, EnemyPos3.x + EnemyW, EnemyPos3.y + EnemyH, EnemyGraph, TRUE);
			DrawExtendGraph(EnemyPos4.x, EnemyPos4.y - AnimationHeight, EnemyPos4.x + EnemyW, EnemyPos4.y + EnemyH, EnemyGraph, TRUE);
			DrawExtendGraph(EnemyPos5.x, EnemyPos5.y - AnimationHeight, EnemyPos5.x + EnemyW, EnemyPos5.y + EnemyH, EnemyGraph, TRUE);
			DrawExtendGraph(EnemyPos6.x, EnemyPos6.y - AnimationHeight, EnemyPos6.x + EnemyW, EnemyPos6.y + EnemyH, EnemyGraph, TRUE);
			DrawExtendGraph(EnemyPos7.x, EnemyPos7.y - AnimationHeight, EnemyPos7.x + EnemyW, EnemyPos7.y + EnemyH, EnemyGraph, TRUE);
			DrawExtendGraph(EnemyPos8.x, EnemyPos8.y - AnimationHeight, EnemyPos8.x + EnemyW, EnemyPos8.y + EnemyH, EnemyGraph, TRUE);
			DrawExtendGraph(EnemyPos9.x, EnemyPos9.y - AnimationHeight, EnemyPos9.x + EnemyW, EnemyPos9.y + EnemyH, EnemyGraph, TRUE);
		}
		// プレイヤー画像と敵画像で当たり判定
		{
			if (PlayerX + IMAGE_SIZE >= EnemyPos.x && PlayerX <= EnemyPos.x + IMAGE_SIZE) {
				if (PlayerY + IMAGE_SIZE >= EnemyPos.y && PlayerY <= EnemyPos.y + IMAGE_SIZE) {
					// 当たったらプレイヤーをデリート
					DeleteGraph(PlayerGraph);
					return GAMEOVERSCENE;
				}
			}
			if (PlayerX + IMAGE_SIZE >= EnemyPos1.x && PlayerX <= EnemyPos1.x + IMAGE_SIZE) {
				if (PlayerY + IMAGE_SIZE >= EnemyPos1.y && PlayerY <= EnemyPos1.y + IMAGE_SIZE) {
					// 当たったらプレイヤーをデリート
					DeleteGraph(PlayerGraph);
					return GAMEOVERSCENE;
				}
			}
			if (PlayerX + IMAGE_SIZE >= EnemyPos2.x && PlayerX <= EnemyPos2.x + IMAGE_SIZE) {
				if (PlayerY + IMAGE_SIZE >= EnemyPos2.y && PlayerY <= EnemyPos2.y + IMAGE_SIZE) {
					// 当たったらプレイヤーをデリート
					DeleteGraph(PlayerGraph);
					return GAMEOVERSCENE;
				}
			}
			if (PlayerX + IMAGE_SIZE >= EnemyPos3.x && PlayerX <= EnemyPos3.x + IMAGE_SIZE) {
				if (PlayerY + IMAGE_SIZE >= EnemyPos3.y && PlayerY <= EnemyPos3.y + IMAGE_SIZE) {
					// 当たったらプレイヤーをデリート
					DeleteGraph(PlayerGraph);
					return GAMEOVERSCENE;
				}
			}
			if (PlayerX + IMAGE_SIZE >= EnemyPos4.x && PlayerX <= EnemyPos4.x + IMAGE_SIZE) {
				if (PlayerY + IMAGE_SIZE >= EnemyPos4.y && PlayerY <= EnemyPos4.y + IMAGE_SIZE) {
					// 当たったらプレイヤーをデリート
					DeleteGraph(PlayerGraph);
					return GAMEOVERSCENE;
				}
			}if (PlayerX + IMAGE_SIZE >= EnemyPos5.x && PlayerX <= EnemyPos5.x + IMAGE_SIZE) {
				if (PlayerY + IMAGE_SIZE >= EnemyPos5.y && PlayerY <= EnemyPos5.y + IMAGE_SIZE) {
					// 当たったらプレイヤーをデリート
					DeleteGraph(PlayerGraph);
					return GAMEOVERSCENE;
				}
			}if (PlayerX + IMAGE_SIZE >= EnemyPos6.x && PlayerX <= EnemyPos6.x + IMAGE_SIZE) {
				if (PlayerY + IMAGE_SIZE >= EnemyPos6.y && PlayerY <= EnemyPos6.y + IMAGE_SIZE) {
					// 当たったらプレイヤーをデリート
					DeleteGraph(PlayerGraph);
					return GAMEOVERSCENE;
				}
			}if (PlayerX + IMAGE_SIZE >= EnemyPos7.x && PlayerX <= EnemyPos7.x + IMAGE_SIZE) {
				if (PlayerY + IMAGE_SIZE >= EnemyPos7.y && PlayerY <= EnemyPos7.y + IMAGE_SIZE) {
					// 当たったらプレイヤーをデリート
					DeleteGraph(PlayerGraph);
					return GAMEOVERSCENE;
				}
			}if (PlayerX + IMAGE_SIZE >= EnemyPos8.x && PlayerX <= EnemyPos8.x + IMAGE_SIZE) {
				if (PlayerY + IMAGE_SIZE >= EnemyPos8.y && PlayerY <= EnemyPos8.y + IMAGE_SIZE) {
					// 当たったらプレイヤーをデリート
					DeleteGraph(PlayerGraph);
					return GAMEOVERSCENE;
				}
			}if (PlayerX + IMAGE_SIZE >= EnemyPos9.x && PlayerX <= EnemyPos9.x + IMAGE_SIZE) {
				if (PlayerY + IMAGE_SIZE >= EnemyPos9.y && PlayerY <= EnemyPos9.y + IMAGE_SIZE) {
					// 当たったらプレイヤーをデリート
					DeleteGraph(PlayerGraph);
					return GAMEOVERSCENE;
				}
			}
		}
		// 画面が切り替わるのを待つ
		ScreenFlip();

		/*シーン遷移処理*/
			//エンターでシーン変更
		if (InputEnter())
		{
			return TITLESCENE;
		}

	}

	//例外処理
	return GAMECLEARSCENE;
}

int GameOverScene()
{
	int nextScene = GAMEOVERSCENE;
	int arrowPosY = 40;
	int countFrame = 0;
	bool gameRoop = true;

	GameOverGraph = LoadGraph("image/gameOver.png");
	GameOverTxtGraph = LoadGraph("image/GameOverTxt.png");
	ArrowGraph = LoadGraph("image/arrow.png");
	GameOverHandle = LoadSoundMem("image/GameOver.mp3");


	PlaySoundMem(GameOverHandle, DX_PLAYTYPE_LOOP);

	while (gameRoop)
	{
		/*計算処理*/
	//Input Down.
		if (InputDown())
		{
			if (arrowPosY == 40)
			{
				arrowPosY = 120;
			}
			else
			{
				arrowPosY = 40;
			}
		}
		//Input Up.
		if (InputUp())
		{
			if (arrowPosY == 120)
			{
				arrowPosY = 40;
			}
			else
			{
				arrowPosY = 120;
			}
		}


		/*タイマ更新*/
		countFrame++;
		if (countFrame > 80000) { countFrame = 0; }//一定以上数が増えたら初期化(数は適当)

		/*Draw処理*/
		//裏画面の初期化
		ClearDrawScreen();

		DrawGraph(0, 0, GameOverGraph, true);

		DrawGraph(0, 0, GameOverTxtGraph, true);

		if ((countFrame % 60) < 32)
		{
			DrawGraph(0, arrowPosY, ArrowGraph, true);
		}


		ScreenFlip();

		/*シーン遷移処理*/
		//エンターでシーン変更
		if (InputEnter())
		{
			if (arrowPosY == 40)
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
	int arrowPosY = -120;
	int countFrame = 0;
	bool gameRoop = true;

	ClearGraph = LoadGraph("image/clear.png");
	GameClearTxtGraph = LoadGraph("image/GameClearTxt.png");
	ArrowGraph = LoadGraph("image/arrow.png");

	while (gameRoop)
	{
		/*計算処理*/
//Input Down.
		if (InputDown())
		{
			if (arrowPosY == -120)
			{
				arrowPosY = -30;
			}
			else
			{
				arrowPosY = -120;
			}
		}
		//Input Up.
		if (InputUp())
		{
			if (arrowPosY == -30)
			{
				arrowPosY = -120;
			}
			else
			{
				arrowPosY = -30;
			}
		}


		/*タイマ更新*/
		countFrame++;
		if (countFrame > 80000) { countFrame = 0; }//一定以上数が増えたら初期化(数は適当)

		/*Draw処理*/
		//裏画面の初期化
		ClearDrawScreen();

		DrawGraph(0, 0, ClearGraph, true);

		DrawGraph(0, 0, GameClearTxtGraph, true);

		if ((countFrame % 60) < 32)
		{
			DrawGraph(0, arrowPosY, ArrowGraph, true);
		}

		ScreenFlip();

		/*シーン遷移処理*/
		//エンターでシーン変更
		if (InputEnter())
		{
			if (arrowPosY == -120)
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
	Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//指定フレーム以上押していたら押した判定
	if (Key == (PAD_INPUT_8) && !isInputEnterHold)
	{
		isInputEnterHold = true;
		return true;
	}
	else if (!Key)
	{
		isInputEnterHold = false;
	}

	return false;
}

//Upが押されたかどうかを判定する関数
bool InputUp()
{
	Key1 = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//指定フレーム以上押していたら押した判定
	if (Key1 == (PAD_INPUT_UP) && !isInputDownHold)
	{
		isInputDownHold = true;
		return true;
	}
	else if (!Key1)
	{
		isInputDownHold = false;
	}

	return false;
}

//Downが押されたかどうかを判定する関数
bool InputDown()
{
	Key2 = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//指定フレーム以上押していたら押した判定
	if (Key2 == (PAD_INPUT_DOWN) && !isInputUpHold)
	{
		isInputUpHold = true;
		return true;
	}
	else if (!Key2)
	{
		isInputUpHold = false;
	}

	return false;
}

//Jump1が押されたかどうかを判定する関数
bool InputJump1()
{
	Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//指定フレーム以上押していたら押した判定
	if (Key == (PAD_INPUT_1) && !isInputJump1Hold)
	{
		isInputJump1Hold = true;
		return true;
	}
	else if (!Key)
	{
		isInputJump1Hold = false;
	}

	return false;
}

//Jump2が押されたかどうかを判定する関数
bool InputJump2()
{
	Key1 = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//指定フレーム以上押していたら押した判定
	if (Key1 == (PAD_INPUT_3) && !isInputJump2Hold)
	{
		isInputJump2Hold = true;
		return true;
	}
	else if (!Key1)
	{
		isInputJump2Hold = false;
	}

	return false;
}


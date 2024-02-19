#include "DxLib.h"
#include <math.h>

//#include "SceneMgr.h"
#define IMAGE_SIZE	50
#define XINPUT_BUTTON_X

int Key;
int Key1;
int Key2;

int Cr1;
int Cr2;

int Time;

int PlayerX, PlayerY;
int PlayerH, PlayerW;
int PlayerGraph;

int EnemyW, EnemyH;

int Telop1Graph;
int Telop2Graph;

int BackGraph;
int TitleGraph;
int TitleScrollGraph;
int ChangeSceenGraph;
int ChangeSceen2Graph;

int BackGlassGraph;

int ManualGraph;
int Manual2Graph;

int GameOverGraph;
int GameOverTxtGraph;

int ClearGraph;
int GameClearTxtGraph;

int SkyGraph;
int MountainGraph;
int GraundGraph;

int SlimeAyeGraph;
int SlimeAye2Graph;

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
constexpr int STARTMANUALSCENE = 3;
constexpr int GAMESCENE = 4;
constexpr int GAMEOVERSCENE = 5;
constexpr int GAMECLEARSCENE = 6;


bool isInputEnterHold = false;// InputEneter用の変数
bool isInputUpHold = false;// InputUp用の変数
bool isInputDownHold = false;// InputDown用の変数
bool isInputJump1Hold = false;// InputJump1用の変数
bool isInputJump2Hold = false;// InputJump2用の変数
bool isInputJump3Hold = false;// InputJump3用の変数

int TitleScene();
int ManualScene();
int StartManualScene();
int GameScene();
int GameOverScene();
int GameClearScene();
bool InputEnter();
bool InputUp();
bool InputDown();
bool InputJump1();
bool InputJump2();
bool InputJump3();

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

VECTOR TelopPos1;
VECTOR TelopPos2;

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
	ChangeWindowMode(false);
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

				TelopPos1.x = 800;
				TelopPos1.y = 800;

				TelopPos2.x = 800;
				TelopPos2.y = 800;

				StopSoundMem(BgmHandle);
			}
		}	
		else if (nextScene == STARTMANUALSCENE)
		{
			nextScene = StartManualScene();

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

				TelopPos1.x = 800;
				TelopPos1.y = 800;

				TelopPos2.x = 800;
				TelopPos2.y = 800;
			}
		}
		else if (nextScene == GAMESCENE)
		{
			nextScene = GameScene();

			if (nextScene == GAMEOVERSCENE)
			{
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

				TelopPos1.x = 800;
				TelopPos1.y = 800;

				TelopPos2.x = 800;
				TelopPos2.y = 800;

				StopSoundMem(GameOverHandle);
				// BGMをメモリにロード
				PlaySoundMem(BgmHandle, DX_PLAYTYPE_LOOP);
			}
		}
		else if (nextScene == GAMECLEARSCENE)
		{
			nextScene = GameClearScene();
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
	ArrowGraph = LoadGraph("image/arrow2.png");
	
	// グラフィック『player.png』をメモリにロード
	PlayerGraph = LoadGraph("image/player.png");
	GetGraphSize(PlayerGraph, &PlayerW, &PlayerH);
	
	// グラフィック『enemy.png』をメモリにロード
	EnemyGraph = LoadGraph("image/enemy.png");
	GetGraphSize(EnemyGraph, &EnemyW, &EnemyH);

	// グラフィック『Telop1・2.png』をメモリにロード
	Telop1Graph = LoadGraph("image/Telop1.png");
	Telop2Graph = LoadGraph("image/Telop2.png");

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
				arrowPosY = 60;
			}
			else if (arrowPosY == 60 , arrowPosY > 120)
			{
				arrowPosY = 0;
			}
			else
			{
				arrowPosY = 120;
			}
		}
		//Input Up.
		if (InputUp())
		{
			if (arrowPosY == 120)
			{
				arrowPosY = 60;
			}
			else if (arrowPosY == 60, arrowPosY < 120)
			{
				arrowPosY = 0;
			}
			else
			{
				arrowPosY = 120;
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
				return STARTMANUALSCENE;
			}
			else if (arrowPosY == 60)
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

int StartManualScene()
{
	int GameRoop = true;
	int countFrame = 0;
	int nextScene = STARTMANUALSCENE;
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
			return GAMESCENE;
		}
	}
		return GAMESCENE;
}

int GameScene()
{
	int EnemyGraph;
	bool gameRoop = true;
	int phase = 0;
	int StartTime;
	Time = 0;
	int areaX = 0;
	int speed = 3;
	unsigned int Cr1;
	unsigned int Cr2;
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
	// グラフィック『TimeWindow.png』をメモリにロード
	BackGlassGraph = LoadGraph("image/TimeWindow.png");

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

		DrawGraph(15, -10, BackGlassGraph, true);

		// 白の色コードを保存
		Cr1 = GetColor(255 , 200, 20);
		Cr2 = GetColor(0, 0, 0);
		Time = GetNowCount() - StartTime;

		SetFontSize(34);
		
		ChangeFont("HG創英角ﾎﾟｯﾌﾟ体");

		ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);

		DrawFormatString(53, 23, Cr2, "経過時間");
		DrawFormatString(63, 63, Cr2, "%d秒", Time / 1000);
		DrawFormatString(50, 20, Cr1, "経過時間");
		DrawFormatString(60, 60, Cr1, "%d秒", Time / 1000);

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
			TelopPos1.x = 690;
			TelopPos1.y = 0;
			EnemyNum++;
		}
		if (EnemyNum == 22 && Time >= 32000) {
		
			EnemyNum++;
		}
		if (EnemyNum == 23 && Time >= 33000) {
			EnemyPos2.x = 1270;
			EnemyPos2.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 24 && Time >= 33000) {
			EnemyPos3.x = 1270;
			EnemyPos3.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 25 && Time >= 34000) {
			EnemyPos4.x = 1280;
			EnemyPos4.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 26 && Time >= 34000) {
			EnemyPos5.x = 1270;
			EnemyPos5.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 27 && Time >= 35000) {
			EnemyPos6.x = 1270;
			EnemyPos6.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 28 && Time >= 36000) {
			EnemyPos7.x = 1270;
			EnemyPos7.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 29 && Time >= 36000) {
			EnemyPos8.x = 1270;
			EnemyPos8.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 30 && Time >= 37000) {
			EnemyPos9.x = 1280;
			EnemyPos9.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 31 && Time >= 37000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 32 && Time >= 38000) {
			EnemyPos1.x = 1270;
			EnemyPos1.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 33 && Time >= 39000) {
			EnemyPos2.x = 1270;
			EnemyPos2.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 34 && Time >= 39000) {
			EnemyPos3.x = 1280;
			EnemyPos3.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 35 && Time >= 41000) {
			EnemyPos4.x = 1270;
			EnemyPos4.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 36 && Time >= 41000) {
			EnemyPos5.x = 1270;
			EnemyPos5.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 37 && Time >= 42000) {
			EnemyPos6.x = 1270;
			EnemyPos6.y = 600;
			EnemyNum++;
		}	
		if (EnemyNum == 38 && Time >= 42000) {
			EnemyPos7.x = 1270;
			EnemyPos7.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 39 && Time >= 43000) {
			EnemyPos8.x = 1280;
			EnemyPos8.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 40 && Time >= 43000) {
			EnemyPos9.x = 1280;
			EnemyPos9.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 41 && Time >= 44000) {
			EnemyNum++;
		}
		if (EnemyNum == 42 && Time >= 45000) {
			TelopPos2.x = 690;
			TelopPos2.y = 0;
			EnemyNum++;
		}		
		if (EnemyNum == 43 && Time >= 47000) {
			EnemyPos1.x = 1270;
			EnemyPos1.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 44 && Time >= 47000) {
			EnemyPos2.x = 1280;
			EnemyPos2.y = 460;
			EnemyNum++;
		}
		if (EnemyNum == 45 && Time >= 47850) {
			EnemyPos3.x = 1270;
			EnemyPos3.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 46 && Time >= 47850) {
			EnemyPos4.x = 1270;
			EnemyPos4.y = 460;
			EnemyNum++;
		}
		if (EnemyNum == 47 && Time >= 48700) {
			EnemyPos5.x = 1270;
			EnemyPos5.y = 600;
			EnemyNum++;
		}	
		if (EnemyNum == 48 && Time >= 49550) {
			EnemyPos6.x = 1270;
			EnemyPos6.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 49 && Time >= 49550) {
			EnemyPos7.x = 1280;
			EnemyPos7.y = 460;
			EnemyNum++;
		}
		if (EnemyNum == 50 && Time >= 50400) {
			EnemyPos8.x = 1270;
			EnemyPos8.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 51 && Time >= 50400) {
			EnemyPos9.x = 1270;
			EnemyPos9.y = 460;
			EnemyNum++;
		}
		if (EnemyNum == 52 && Time >= 51250) {
			EnemyPos.x = 1270;
			EnemyPos.y = 600;
			EnemyNum++;
		}		
		if (EnemyNum == 53 && Time >= 52100) {
			EnemyPos1.x = 1270;
			EnemyPos1.y = 460;
			EnemyNum++;
		}
		if (EnemyNum == 54 && Time >= 52100) {
			EnemyPos2.x = 1280;
			EnemyPos2.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 55 && Time >= 52950) {
			EnemyPos3.x = 1270;
			EnemyPos3.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 56 && Time >= 52950) {
			EnemyPos4.x = 1270;
			EnemyPos4.y = 460;
			EnemyNum++;
		}
		if (EnemyNum == 57 && Time >= 53800) {
			EnemyPos5.x = 1270;
			EnemyPos5.y = 600;
			EnemyNum++;
		}		
		if (EnemyNum == 58 && Time >= 54650) {
			EnemyPos6.x = 1270;
			EnemyPos6.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 59 && Time >= 54650) {
			EnemyPos7.x = 1280;
			EnemyPos7.y = 460;
			EnemyNum++;
		}
		if (EnemyNum == 60 && Time >= 55500) {
			EnemyPos8.x = 1270;
			EnemyPos8.y = 600;
			EnemyNum++;
		}
		if (EnemyNum == 61 && Time >= 55500) {
			EnemyPos9.x = 1270;
			EnemyPos9.y = 460;
			EnemyNum++;
		}
		if (EnemyNum == 62 && Time >= 56350) {
			EnemyPos1.x = 1270;
			EnemyPos1.y = 600;
			EnemyNum++;
		}		
		if (EnemyNum == 63 && Time >= 56350) {
			EnemyPos2.x = 1270;
			EnemyPos2.y = 460;
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

		if (PlayerY == 600)
		{
			if (InputJump1())
			{
				if (InputJump2())
				{
					JumpPower = 24;
					JumpPower1 = 15;
					JumpNum = 2;
					// 読みこんだ音をバックグラウンド再生します(『PlaySoundMem』関数使用)
					PlaySoundMem(SeHandle, DX_PLAYTYPE_BACK);
				}
				else
				{
					JumpPower = 24;
					JumpNum = 1;
					// 読みこんだ音をバックグラウンド再生します(『PlaySoundMem』関数使用)
					PlaySoundMem(SeHandle, DX_PLAYTYPE_BACK);
				}
			}
		}
		else if (InputJump2())
		{
			if (JumpNum == 1)
			{
				JumpPower1 = 15;
				JumpNum = 2;
				// 読みこんだ音をバックグラウンド再生します(『PlaySoundMem』関数使用)
				PlaySoundMem(SeHandle, DX_PLAYTYPE_BACK);
			}
		}

		TelopPos1.x -= 10;
		TelopPos2.x -= 10;

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
		DrawGraph(TelopPos1.x, TelopPos1.y, Telop1Graph, true);
		DrawGraph(TelopPos2.x, TelopPos2.y, Telop2Graph, true);
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
	}

	//例外処理
	return GAMECLEARSCENE;
}

int GameOverScene()
{
	int nextScene = GAMEOVERSCENE;
	int arrowPosY = 0;
	int countFrame = 0;
	bool gameRoop = true;

	GameOverGraph = LoadGraph("image/gameOver.png");
	GameOverTxtGraph = LoadGraph("image/GameOverTxt.png");
	ArrowGraph = LoadGraph("image/arrow3.png");
	GameOverHandle = LoadSoundMem("image/GameOver.mp3");

	PlaySoundMem(GameOverHandle, DX_PLAYTYPE_LOOP);

	while (gameRoop)
	{
		/*計算処理*/
		//Input Down.
		if (InputDown())
		{
			if (arrowPosY == 0)
			{
				arrowPosY = 80;
			}
			else
			{
				arrowPosY = 0;
			}
		}
		//Input Up.
		if (InputUp())
		{
			if (arrowPosY == 80)
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

		Cr1 = GetColor(255, 200, 20);
		Cr2 = GetColor(0, 0, 0);


		SetFontSize(68);

		ChangeFont("HG創英角ﾎﾟｯﾌﾟ体");

		ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);

		DrawFormatString(105, 305, Cr2, "経過時間");
		DrawFormatString(185, 385, Cr2, "%d秒", Time / 1000);
		DrawFormatString(100, 300, Cr1, "経過時間");
		DrawFormatString(180, 380, Cr1, "%d秒", Time / 1000);

		ScreenFlip();

		/*シーン遷移処理*/
		//エンターでシーン変更
		if (InputEnter())
		{
			if (arrowPosY == 0)
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
	int arrowPosY = 10;
	int countFrame = 0;
	bool gameRoop = true;
	int SlimeAyeW, SlimeAyeH;
	int areaX = 0;
	int speed = 1;

	ClearGraph = LoadGraph("image/clear.png");
	GameClearTxtGraph = LoadGraph("image/GameClearTxt.png");
	ArrowGraph = LoadGraph("image/arrow1.png");
	SlimeAyeGraph = LoadGraph("image/SlimeAye.png");
	SlimeAye2Graph = LoadGraph("image/SlimeAye2.png");
	SkyGraph = LoadGraph("image/Sky.png");
	MountainGraph = LoadGraph("image/mountain.png");
	GraundGraph = LoadGraph("image/Graund.png");

	while (gameRoop)
	{
		///*計算処理*/
		////Input Down.
		//if (InputDown())
		//{
		//	if (arrowPosY == -120)
		//	{
		//		arrowPosY = -30;
		//	}
		//	else
		//	{
		//		arrowPosY = -120;
		//	}
		//}
		////Input Up.
		//if (InputUp())
		//{
		//	if (arrowPosY == -30)
		//	{
		//		arrowPosY = -120;
		//	}
		//	else
		//	{
		//		arrowPosY = -30;
		//	}
		//}

		/*タイマ更新*/
		countFrame++;
		if (countFrame > 80000) { countFrame = 0; }//一定以上数が増えたら初期化(数は適当)

		/*Draw処理*/
		//裏画面の初期化
		ClearDrawScreen();

		BackScroll(areaX, SkyGraph, 1280, 720);

		areaX += speed;
		if (areaX > 1280)
		{
			areaX = 0;
		}
	
		DrawGraph(0, 0, MountainGraph, true);
		DrawGraph(0, 0, GraundGraph, true);

		DrawGraph(0, 0, ClearGraph, true);

		if ((countFrame % 100) < 97)
		{
			DrawGraph(0, 0, SlimeAyeGraph, true);
		}
		else
		{
			DrawGraph(0, 0, SlimeAye2Graph, true);
		}
		
		DrawGraph(0, 0, GameClearTxtGraph, true);

		if ((countFrame % 60) < 32)
		{
			DrawGraph(-10, arrowPosY, ArrowGraph, true);
		}
		


		ScreenFlip();

		/*シーン遷移処理*/
		//エンターでシーン変更
		if (InputEnter())
		{
			if (arrowPosY == 10)
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
	if (Key == (PAD_INPUT_1) && !isInputEnterHold)
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
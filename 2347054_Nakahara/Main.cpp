#include "DxLib.h"
#include <math.h>

#define IMAGE_SIZE	50

// 操作キーの定義
int Key;
int Key1;
int Key2;

// カラーの定義
int Cr1;
int Cr2;

// 座標関連
int GroundCoordinate = 600;
int EnemyStart = 1280;
int EnemyUp1 = 310;
int EnemyUp2 = 460;

// 時間
int Time;

// プレイヤー関連の定義
int PlayerX, PlayerY;
int PlayerH, PlayerW;
int PlayerGraph;

// エネミーサイズの定義
int EnemyW, EnemyH;

// テロップの定義
int Telop1Graph;
int Telop2Graph;

// 背景の定義
int BackGraph;
int TitleGraph;
int TitleScrollGraph;
int ChangeSceenGraph;
int ChangeSceen2Graph;
int BackGlassGraph;

// マニュアル画面の描画定義
int ManualGraph;
int Manual2Graph;

// ゲームオーバー画面の描画定義
int GameOverGraph;
int GameOverTxtGraph;

// クリア画面の描画定義
int ClearGraph;
int GameClearTxtGraph;

// 背景素材の描画定義
int SkyGraph;
int MountainGraph;
int GraundGraph;

// 瞬きの描画定義
int SlimeAyeGraph;
int SlimeAye2Graph;

// →の定義
int ArrowGraph;

// サウンドハンドルの定義
int BgmHandle;
int SeHandle;
int GameOverHandle;

// JumpPowerの定義
float JumpPower;
float JumpPower1;

// シーン
constexpr int GAMEEND = 0;
constexpr int TITLESCENE = 1;
constexpr int MANUALSCENE = 2;
constexpr int STARTMANUALSCENE = 3;
constexpr int GAMESCENE = 4;
constexpr int GAMEOVERSCENE = 5;
constexpr int GAMECLEARSCENE = 6;

int TitleScene();
int ManualScene();
int StartManualScene();
int GameScene();
int GameOverScene();
int GameClearScene();

bool IsInputEnterHold = false;// InputEneter用の変数
bool IsInputUpHold = false;// InputUp用の変数
bool IsInputDownHold = false;// InputDown用の変数
bool IsInputJump1Hold = false;// InputJump1用の変数
bool IsInputJump2Hold = false;// InputJump2用の変数
bool IsInputJump3Hold = false;// InputJump3用の変数

// キーやボタンの定義
bool ConfirmButton();
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

// テロップ構造体
VECTOR TelopPos1;
VECTOR TelopPos2;


XINPUT_STATE Input;

void BackScroll(const int t_areaX, const int tD_graph, const int t_winWidth, const int t_winHeight)
{
	DrawRectGraph(0, 0, t_areaX, 0, t_winWidth, t_winHeight, tD_graph, false);
	DrawRectGraph(t_winWidth - t_areaX, 0, 0, 0, t_areaX, t_winHeight, tD_graph, false);
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	LONGLONG RoopStartTime = 0;
	bool GameRoop = true;
	int NextScene = TITLESCENE;

	// 座標の初期化用
	float Initialization = 800;

	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(false);
	SetWindowText("すらいむすとろぉく");

	// 画面モードの設定
	SetGraphMode(1280, 720, 32);
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);

	// BGM
	BgmHandle = LoadSoundMem("image/maou_game_village05.mp3");

	// エネミーの初期化
	EnemyPos.x = Initialization;
	EnemyPos.y = Initialization;

	EnemyPos1.x = Initialization;
	EnemyPos1.y = Initialization;

	EnemyPos2.x = Initialization;
	EnemyPos2.y = Initialization;

	// メインループ
	while (GameRoop) 
	{
		RoopStartTime = GetNowHiPerformanceCount();

		ClearDrawScreen();

		if (NextScene == TITLESCENE)
		{
			NextScene = TitleScene();
		}
		else if (NextScene == MANUALSCENE)
		{
			NextScene = ManualScene();

			if (NextScene == TITLESCENE)
			{
				// エネミーの初期化
				EnemyPos.x = Initialization;
				EnemyPos.y = Initialization;

				EnemyPos1.x = Initialization;
				EnemyPos1.y = Initialization;

				EnemyPos2.x = Initialization;
				EnemyPos2.y = Initialization;

				// テロップの初期化
				TelopPos1.x = Initialization;
				TelopPos1.y = Initialization;

				TelopPos2.x = Initialization;
				TelopPos2.y = Initialization;

				StopSoundMem(BgmHandle);
			}
		}	
		else if (NextScene == STARTMANUALSCENE)
		{
			NextScene = StartManualScene();

			if (NextScene == GAMESCENE)
			{
				// エネミーの初期化
				EnemyPos.x = Initialization;
				EnemyPos.y = Initialization;

				EnemyPos1.x = Initialization;
				EnemyPos1.y = Initialization;

				EnemyPos2.x = Initialization;
				EnemyPos2.y = Initialization;

				EnemyPos3.x = Initialization;
				EnemyPos3.y = Initialization;

				EnemyPos4.x = Initialization;
				EnemyPos4.y = Initialization;

				EnemyPos5.x = Initialization;
				EnemyPos5.y = Initialization;

				EnemyPos6.x = Initialization;
				EnemyPos6.y = Initialization;

				EnemyPos7.x = Initialization;
				EnemyPos7.y = Initialization;

				EnemyPos8.x = Initialization;
				EnemyPos8.y = Initialization;

				EnemyPos9.x = Initialization;
				EnemyPos9.y = Initialization;

				// テロップの初期化
				TelopPos1.x = Initialization;
				TelopPos1.y = Initialization;

				TelopPos2.x = Initialization;
				TelopPos2.y = Initialization;
			}
		}
		else if (NextScene == GAMESCENE)
		{
			NextScene = GameScene();

			if (NextScene == GAMEOVERSCENE)
			{
				StopSoundMem(BgmHandle);
			}
		}
		else if (NextScene == GAMEOVERSCENE)
		{
			NextScene = GameOverScene();

			if (NextScene == TITLESCENE) 
			{
				// エネミーの初期化
				EnemyPos.x = Initialization;
				EnemyPos.y = Initialization;

				EnemyPos1.x = Initialization;
				EnemyPos1.y = Initialization;

				EnemyPos2.x = Initialization;
				EnemyPos2.y = Initialization;

				StopSoundMem(GameOverHandle);
			}

			if (NextScene == GAMESCENE)
			{
				// エネミーの初期化
				EnemyPos.x = Initialization;
				EnemyPos.y = Initialization;

				EnemyPos1.x = Initialization;
				EnemyPos1.y = Initialization;

				EnemyPos2.x = Initialization;
				EnemyPos2.y = Initialization;

				EnemyPos3.x = Initialization;
				EnemyPos3.y = Initialization;

				EnemyPos4.x = Initialization;
				EnemyPos4.y = Initialization;

				EnemyPos5.x = Initialization;
				EnemyPos5.y = Initialization;

				EnemyPos6.x = Initialization;
				EnemyPos6.y = Initialization;

				EnemyPos7.x = Initialization;
				EnemyPos7.y = Initialization;

				EnemyPos8.x = Initialization;
				EnemyPos8.y = Initialization;

				EnemyPos9.x = Initialization;
				EnemyPos9.y = Initialization;

				// テロップの初期化
				TelopPos1.x = Initialization;
				TelopPos1.y = Initialization;

				TelopPos2.x = Initialization;
				TelopPos2.y = Initialization;

				StopSoundMem(GameOverHandle);
				// BGMをメモリにロード
				PlaySoundMem(BgmHandle, DX_PLAYTYPE_LOOP);
			}
		}
		else if (NextScene == GAMECLEARSCENE)
		{
			NextScene = GameClearScene();
			if (NextScene == TITLESCENE) 
			{
				// エネミーの初期化
				EnemyPos.x = Initialization;
				EnemyPos.y = Initialization;

				EnemyPos1.x = Initialization;
				EnemyPos1.y = Initialization;

				EnemyPos2.x = Initialization;
				EnemyPos2.y = Initialization;

				StopSoundMem(BgmHandle);
			}
		}
		else if (NextScene == GAMEEND)
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
		while (GetNowHiPerformanceCount() - RoopStartTime < 16667)
		{
			// 16.66ミリ秒(16667マイクロ秒)経過するまで待つ
		}
	}

		DxLib_End();				// ＤＸライブラリ使用の終了処理

		return 0;				// ソフトの終了 
}

// タイトルシーン
int TitleScene()
{
	/*変数*/
	bool GameRoop = true;
	int NextScene = TITLESCENE;
	int ArrowPosY = 0;
	int CountFrame = 0;
	int AreaX = 0;
	int Speed = 3;
	int EnemyGraph;
	int MoovSpeed = 10;

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
	PlayerY = GroundCoordinate;

	/*ゲーム処理*/
	while (GameRoop)
	{
		/*計算処理*/
		//Input Down.
		if (InputDown())
		{
			if (ArrowPosY == 0)
			{
				ArrowPosY = 60;
			}
			else if (ArrowPosY == 60 && ArrowPosY > 120)
			{
				ArrowPosY = 0;
			}
			else
			{
				ArrowPosY = 120;
			}
		}
		//Input Up.
		if (InputUp())
		{
			if (ArrowPosY == 120)
			{
				ArrowPosY = 60;
			}
			else if (ArrowPosY == 60 && ArrowPosY < 120)
			{
				ArrowPosY = 0;
			}
			else
			{
				ArrowPosY = 120;
			}
		}

		/*タイマ更新*/
		CountFrame++;
		if (CountFrame > 380) { CountFrame = 0; }//一定以上数が増えたら初期化(数は適当)

		/*Draw処理*/
		//裏画面の初期化
		ClearDrawScreen();

		if (CountFrame == 120)
		{
			EnemyPos.x = EnemyStart;
			EnemyPos.y = 600;
		}
		if (CountFrame == 280) 
		{
			EnemyPos1.x = EnemyStart;
			EnemyPos1.y = EnemyUp2;
		}
		if (CountFrame == 280) 
		{
			EnemyPos2.x = EnemyStart;
			EnemyPos2.y = 600;
		}

		// エネミーの移動速度
		EnemyPos.x -= MoovSpeed;
		EnemyPos1.x -= MoovSpeed;
		EnemyPos2.x -= MoovSpeed;


		// 背景スクロールの描画
		BackScroll(AreaX, TitleScrollGraph, EnemyStart, 720);
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


		AreaX += Speed;
		if (AreaX > EnemyStart)
		{
			AreaX = 0;
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
		if (PlayerY > GroundCoordinate)
		{
			PlayerY = GroundCoordinate;
			JumpPower = 0;
			JumpPower1 = 0;
		}
		// タイトルデモのジャンプタイミング
		if (CountFrame == 220)JumpPower = 24;
		if (CountFrame == 375)JumpPower1 = 29;

		//矢印表示(点滅させる)
		if ((CountFrame % 60) < 32)
		{
			DrawGraph(0, ArrowPosY, ArrowGraph, true);
		}

		//裏画面を表へ
		ScreenFlip();

		/*シーン遷移処理*/
		//エンターでシーン変更
		if (ConfirmButton())
		{
			if (ArrowPosY == 0)
			{
				return STARTMANUALSCENE;
			}
			else if (ArrowPosY == 60)
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

// マニュアルシーン
int ManualScene()
{
	int GameRoop = true;
	int CountFrame = 0;
	int NextScene = MANUALSCENE;
	int AreaX = 0;
	int Speed = 2;
	
	// グラフィック『player.png』をメモリにロード
	PlayerGraph = LoadGraph("image/player.png");
	GetGraphSize(PlayerGraph, &PlayerW, &PlayerH);
	// グラフィック『back.png』をメモリにロード
	BackGraph = LoadGraph("image/back.png");
	// グラフィック『manual.png』をメモリにロード
	ManualGraph = LoadGraph("image/manual.png");

	// キャラクターの初期データをセット
	PlayerX = 60;
	PlayerY = GroundCoordinate;

	while (GameRoop)
	{
		/*タイマ更新*/
		CountFrame++;
		if (CountFrame > 120) { CountFrame = 0; }//一定以上数が増えたら初期化(数は適当)

		/*Draw処理*/
		//裏画面の初期化
		ClearDrawScreen();

		BackScroll(AreaX, BackGraph, EnemyStart, 720);

		AreaX += Speed;
		if (AreaX > EnemyStart)
		{
			AreaX = 0;
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
		if (PlayerY > GroundCoordinate)
		{
			PlayerY = GroundCoordinate;
			JumpPower = 0;
		}
		if (CountFrame == 120)JumpPower = 20;

		// スライムが弾んで見えるモーション実装
		const float SinSpeed = 0.1f;
		const float AnimationSize = 5.0f;
		static float AnimationHeight = 0.0f;	// スライムが弾んでいるようにアニメーションしているよう見せるための高さ値
		static float SinCount = 0;
		SinCount += SinSpeed;
		AnimationHeight = sinf(SinCount) * AnimationSize;		// 決まった数値だけ高さを増やしてあげる
		DrawExtendGraph(PlayerX, PlayerY - AnimationHeight, PlayerX + PlayerW, PlayerY + PlayerH, PlayerGraph, TRUE);

		DrawGraph(0, 0, ManualGraph, true);

		//裏画面を表へ
		ScreenFlip();
	
		/*シーン遷移処理*/
		//エンターでシーン変更
		if (ConfirmButton())
		{
			return TITLESCENE;
		}
	}
		return TITLESCENE;
}

// スタートマニュアルシーン
int StartManualScene()
{
	int GameRoop = true;
	int CountFrame = 0;
	int NextScene = STARTMANUALSCENE;
	int AreaX = 0;
	int Speed = 2;

	// グラフィック『player.png』をメモリにロード
	PlayerGraph = LoadGraph("image/player.png");
	GetGraphSize(PlayerGraph, &PlayerW, &PlayerH);
	// グラフィック『back.png』をメモリにロード
	BackGraph = LoadGraph("image/back.png");
	// グラフィック『manual.png』をメモリにロード
	ManualGraph = LoadGraph("image/manual.png");

	// キャラクターの初期データをセット
	PlayerX = 60;
	PlayerY = GroundCoordinate;

	while (GameRoop)
	{
		/*タイマ更新*/
		CountFrame++;
		if (CountFrame > 120) { CountFrame = 0; }//一定以上数が増えたら初期化(数は適当)

		/*Draw処理*/
		//裏画面の初期化
		ClearDrawScreen();

		BackScroll(AreaX, BackGraph, EnemyStart, 720);

		AreaX += Speed;
		if (AreaX > EnemyStart)
		{
			AreaX = 0;
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
		if (PlayerY > GroundCoordinate)
		{
			PlayerY = GroundCoordinate;
			JumpPower = 0;
		}
		if (CountFrame == 120)JumpPower = 20;

		// スライムが弾んで見えるモーション
		const float SinSpeed = 0.1f;
		const float AnimationSize = 5.0f;
		static float AnimationHeight = 0.0f;	// スライムが弾んでいるようにアニメーションしているよう見せるための高さ値
		static float SinCount = 0;
		SinCount += SinSpeed;
		AnimationHeight = sinf(SinCount) * AnimationSize;		// 決まった数値だけ高さを増やしてあげる
		DrawExtendGraph(PlayerX, PlayerY - AnimationHeight, PlayerX + PlayerW, PlayerY + PlayerH, PlayerGraph, TRUE);

		DrawGraph(0, 0, ManualGraph, true);

		//裏画面を表へ
		ScreenFlip();
	
		/*シーン遷移処理*/
		//エンターでシーン変更
		if (ConfirmButton())
		{
			return GAMESCENE;
		}
	}
		return GAMESCENE;
}

// ゲームシーン
int GameScene()
{
	int EnemyGraph;
	bool GameRoop = true;
	int Phase = 0;
	int StartTime;
	Time = 0;
	int AreaX = 0;
	int Speed = 3;
	unsigned int Cr1;
	unsigned int Cr2;
	int NextScene = GAMESCENE;

	int MoovSpeed = 10;
	int ClarTime = 60000;
	int JumpHeight = 24;
	int JumpHeight1 = 15;
	int CountFrame = 0;

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
	PlayerY = GroundCoordinate;

	// 現在経過時間を得る
	StartTime = GetNowCount();

	int EnemyNum = 0;
	int JumpNum = 0;

	// ゲームループ
	while (GetNowCount() - StartTime < ClarTime)
	{

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 背景スクロールの描画
		BackScroll(AreaX, BackGraph, EnemyStart, 720);

		AreaX += Speed;
		if (AreaX > EnemyStart)
		{
			AreaX = 0;
		}

		// 経過時間の小窓の描画
		DrawGraph(15, -10, BackGlassGraph, true);

		// 白の色コードを保存
		Cr1 = GetColor(255 , 200, 20);
		Cr2 = GetColor(0, 0, 0);
		Time = GetNowCount() - StartTime;

		SetFontSize(34);

		// 経過時間の描画
		ChangeFont("HG創英角ﾎﾟｯﾌﾟ体");
		ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);
		DrawFormatString(53, 23, Cr2, "経過時間");
		DrawFormatString(63, 63, Cr2, "%d秒", Time / 1000);
		DrawFormatString(50, 20, Cr1, "経過時間");
		DrawFormatString(60, 60, Cr1, "%d秒", Time / 1000);

		// エネミーの出現処理
		{
			if (EnemyNum == 0 && Time >= 0) {
				EnemyPos.x = EnemyStart;
				EnemyPos.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 1 && Time >= 3000) {
				EnemyPos1.x = EnemyStart;
				EnemyPos1.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 2 && Time >= 6000) {
				EnemyPos2.x = EnemyStart;
				EnemyPos2.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 3 && Time >= 8000) {
				EnemyPos3.x = EnemyStart;
				EnemyPos3.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 4 && Time >= 10000) {
				EnemyPos4.x = EnemyStart;
				EnemyPos4.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 5 && Time >= 12000) {
				EnemyPos.x = EnemyStart;
				EnemyPos.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 6 && Time >= 12000) {
				EnemyPos1.x = EnemyStart;
				EnemyPos1.y = EnemyUp2;
				EnemyNum++;
			}
			if (EnemyNum == 7 && Time >= 14000) {
				EnemyPos2.x = EnemyStart;
				EnemyPos2.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 8 && Time >= 14000) {
				EnemyPos3.x = EnemyStart;
				EnemyPos3.y = EnemyUp2;
				EnemyNum++;
			}
			if (EnemyNum == 9 && Time >= 16000) {
				EnemyPos4.x = EnemyStart;
				EnemyPos4.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 10 && Time >= 16000) {
				EnemyPos.x = EnemyStart;
				EnemyPos.y = EnemyUp2;
				EnemyNum++;
			}
			if (EnemyNum == 11 && Time >= 18000) {
				EnemyPos1.x = EnemyStart;
				EnemyPos1.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 12 && Time >= 18000) {
				EnemyPos2.x = EnemyStart;
				EnemyPos2.y = EnemyUp2;
				EnemyNum++;
			}
			if (EnemyNum == 13 && Time >= 20000) {
				EnemyPos3.x = EnemyStart;
				EnemyPos3.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 14 && Time >= 20000) {
				EnemyPos4.x = EnemyStart;
				EnemyPos4.y = EnemyUp1;
				EnemyNum++;
			}
			if (EnemyNum == 15 && Time >= 22000) {
				EnemyPos.x = EnemyStart;
				EnemyPos.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 16 && Time >= 24000) {
				EnemyPos1.x = EnemyStart;
				EnemyPos1.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 17 && Time >= 24000) {
				EnemyPos2.x = EnemyStart;
				EnemyPos2.y = EnemyUp1;
				EnemyNum++;
			}
			if (EnemyNum == 18 && Time >= 26000) {
				EnemyPos3.x = EnemyStart;
				EnemyPos3.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 19 && Time >= 28000) {
				EnemyPos4.x = EnemyStart;
				EnemyPos4.y = EnemyUp1;
				EnemyNum++;
			}
			if (EnemyNum == 20 && Time >= 28000) {
				EnemyPos.x = EnemyStart;
				EnemyPos.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 21 && Time >= 30000) {
				TelopPos1.x = 690;
				TelopPos1.y = 0;
				EnemyNum++;
			}
			if (EnemyNum == 22 && Time >= 33000) {
				EnemyPos2.x = EnemyStart;
				EnemyPos2.y = EnemyUp1;
				EnemyNum++;
			}
			if (EnemyNum == 23 && Time >= 33000) {
				EnemyPos2.x = EnemyStart;
				EnemyPos2.y = EnemyUp1;
				EnemyNum++;
			}
			if (EnemyNum == 24 && Time >= 33000) {
				EnemyPos3.x = EnemyStart;
				EnemyPos3.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 25 && Time >= 34000) {
				EnemyPos4.x = EnemyStart;
				EnemyPos4.y = EnemyUp1;
				EnemyNum++;
			}
			if (EnemyNum == 26 && Time >= 34000) {
				EnemyPos5.x = EnemyStart;
				EnemyPos5.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 27 && Time >= 35000) {
				EnemyPos6.x = EnemyStart;
				EnemyPos6.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 28 && Time >= 36000) {
				EnemyPos7.x = EnemyStart;
				EnemyPos7.y = EnemyUp1;
				EnemyNum++;
			}
			if (EnemyNum == 29 && Time >= 36000) {
				EnemyPos8.x = EnemyStart;
				EnemyPos8.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 30 && Time >= 37000) {
				EnemyPos9.x = EnemyStart;
				EnemyPos9.y = EnemyUp1;
				EnemyNum++;
			}
			if (EnemyNum == 31 && Time >= 37000) {
				EnemyPos.x = EnemyStart;
				EnemyPos.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 32 && Time >= 38000) {
				EnemyPos1.x = EnemyStart;
				EnemyPos1.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 33 && Time >= 39000) {
				EnemyPos2.x = EnemyStart;
				EnemyPos2.y = EnemyUp1;
				EnemyNum++;
			}
			if (EnemyNum == 34 && Time >= 39000) {
				EnemyPos3.x = EnemyStart;
				EnemyPos3.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 35 && Time >= 41000) {
				EnemyPos4.x = EnemyStart;
				EnemyPos4.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 36 && Time >= 41000) {
				EnemyPos5.x = EnemyStart;
				EnemyPos5.y = EnemyUp1;
				EnemyNum++;
			}
			if (EnemyNum == 37 && Time >= 42000) {
				EnemyPos6.x = EnemyStart;
				EnemyPos6.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 38 && Time >= 42000) {
				EnemyPos7.x = EnemyStart;
				EnemyPos7.y = EnemyUp1;
				EnemyNum++;
			}
			if (EnemyNum == 39 && Time >= 43000) {
				EnemyPos8.x = EnemyStart;
				EnemyPos8.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 40 && Time >= 43000) {
				EnemyPos9.x = EnemyStart;
				EnemyPos9.y = EnemyUp1;
				EnemyNum++;
			}
			if (EnemyNum == 41 && Time >= 45000) {
				TelopPos2.x = 690;
				TelopPos2.y = 0;
				EnemyNum++;
			}
			if (EnemyNum == 42 && Time >= 45000) {
				TelopPos2.x = 690;
				TelopPos2.y = 0;
				EnemyNum++;
			}
			if (EnemyNum == 43 && Time >= 47000) {
				EnemyPos1.x = EnemyStart;
				EnemyPos1.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 44 && Time >= 47000) {
				EnemyPos2.x = EnemyStart;
				EnemyPos2.y = EnemyUp2;
				EnemyNum++;
			}
			if (EnemyNum == 45 && Time >= 47850) {
				EnemyPos3.x = EnemyStart;
				EnemyPos3.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 46 && Time >= 47850) {
				EnemyPos4.x = EnemyStart;
				EnemyPos4.y = EnemyUp2;
				EnemyNum++;
			}
			if (EnemyNum == 47 && Time >= 48700) {
				EnemyPos5.x = EnemyStart;
				EnemyPos5.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 48 && Time >= 49550) {
				EnemyPos6.x = EnemyStart;
				EnemyPos6.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 49 && Time >= 49550) {
				EnemyPos7.x = EnemyStart;
				EnemyPos7.y = EnemyUp2;
				EnemyNum++;
			}
			if (EnemyNum == 50 && Time >= 50400) {
				EnemyPos8.x = EnemyStart;
				EnemyPos8.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 51 && Time >= 50400) {
				EnemyPos9.x = EnemyStart;
				EnemyPos9.y = EnemyUp2;
				EnemyNum++;
			}
			if (EnemyNum == 52 && Time >= 51250) {
				EnemyPos.x = EnemyStart;
				EnemyPos.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 53 && Time >= 52100) {
				EnemyPos1.x = EnemyStart;
				EnemyPos1.y = EnemyUp2;
				EnemyNum++;
			}
			if (EnemyNum == 54 && Time >= 52100) {
				EnemyPos2.x = EnemyStart;
				EnemyPos2.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 55 && Time >= 52950) {
				EnemyPos3.x = EnemyStart;
				EnemyPos3.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 56 && Time >= 52950) {
				EnemyPos4.x = EnemyStart;
				EnemyPos4.y = EnemyUp2;
				EnemyNum++;
			}
			if (EnemyNum == 57 && Time >= 53800) {
				EnemyPos5.x = EnemyStart;
				EnemyPos5.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 58 && Time >= 54650) {
				EnemyPos6.x = EnemyStart;
				EnemyPos6.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 59 && Time >= 54650) {
				EnemyPos7.x = EnemyStart;
				EnemyPos7.y = EnemyUp2;
				EnemyNum++;
			}
			if (EnemyNum == 60 && Time >= 55500) {
				EnemyPos8.x = EnemyStart;
				EnemyPos8.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 61 && Time >= 55500) {
				EnemyPos9.x = EnemyStart;
				EnemyPos9.y = EnemyUp2;
				EnemyNum++;
			}
			if (EnemyNum == 62 && Time >= 56350) {
				EnemyPos1.x = EnemyStart;
				EnemyPos1.y = GroundCoordinate;
				EnemyNum++;
			}
			if (EnemyNum == 63 && Time >= 56350) {
				EnemyPos2.x = EnemyStart;
				EnemyPos2.y = EnemyUp2;
				EnemyNum++;
			}
		}
		// 落下処理
		PlayerY -= JumpPower;
		PlayerY -= JumpPower1;
		//PlayerY -= JumpPower2;

		//落下加速度付加
		JumpPower -= 0.8f;
		JumpPower1 -= 0.9f;
	
		// プレイヤーが画面下端からはみ出そうになっていたら画面内の座標に戻してあげる
		if (PlayerY > 720 - 64) PlayerY = 720 - 64;
		// プレイヤーが画面天井からはみ出そうになっていたら画面内の座標に戻してあげる
		if (PlayerY < 0 + 64) PlayerY = 0 + 64;

		// もし地面についていたら止まる
		if (PlayerY > GroundCoordinate)
		{
			PlayerY = GroundCoordinate;
			JumpPower = 0;
			JumpPower1 = 0;
			JumpNum = 0;
			CountFrame = 0;
		}

		CountFrame++;
		
		// プレイヤーのジャンプ処理
		{
			if (PlayerY == GroundCoordinate)
			{
				if (InputJump1())
				{
					JumpPower = JumpHeight;
					JumpNum = 1;
					// 読みこんだ音をバックグラウンド再生します(『PlaySoundMem』関数使用)
					PlaySoundMem(SeHandle, DX_PLAYTYPE_BACK);
				}
			}

			if (InputJump2())
			{
				if (JumpNum == 1 && CountFrame >= 8)
				{
					JumpPower1 = JumpHeight1;
					JumpNum = 2;
					// 読みこんだ音をバックグラウンド再生します(『PlaySoundMem』関数使用)
					PlaySoundMem(SeHandle, DX_PLAYTYPE_BACK);
				}
			}
		}

		// テロップの移動処理
		{
			TelopPos1.x -= MoovSpeed;
			TelopPos2.x -= MoovSpeed;
		}

		// エネミーの移動処理
		{
			EnemyPos.x -= MoovSpeed;
			EnemyPos1.x -= MoovSpeed;
			EnemyPos2.x -= MoovSpeed;
			EnemyPos3.x -= MoovSpeed;
			EnemyPos4.x -= MoovSpeed;
			EnemyPos5.x -= MoovSpeed;
			EnemyPos6.x -= MoovSpeed;
			EnemyPos7.x -= MoovSpeed;
			EnemyPos8.x -= MoovSpeed;
			EnemyPos9.x -= MoovSpeed;
		}

		// テロップを描画する
		DrawGraph(TelopPos1.x, TelopPos1.y, Telop1Graph, true);
		DrawGraph(TelopPos2.x, TelopPos2.y, Telop2Graph, true);
		
		// スライムの弾んでるモーション
		const float SinSpeed = 0.1f;
		const float AnimationSize = 8.0f;
		static float AnimationHeight = 0.0f;	// スライムが弾んでいるようにアニメーションしているよう見せるための高さ値
		static float SinCount = 0;
		SinCount += SinSpeed;
		AnimationHeight = sinf(SinCount) * AnimationSize;		// 決まった数値だけ高さを増やしてあげる
		
		// プレイヤーを描画する
		DrawExtendGraph(PlayerX, PlayerY - AnimationHeight, PlayerX + PlayerW, PlayerY + PlayerH, PlayerGraph, TRUE);
		
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

// ゲームオーバーシーン
int GameOverScene()
{
	int NextScene = GAMEOVERSCENE;
	int ArrowPosY = 0;
	int CountFrame = 0;
	bool GameRoop = true;

	// グラフィック『gameOver.png』をメモリにロード
	GameOverGraph = LoadGraph("image/gameOver.png");
	// グラフィック『GameOverTxt.png』をメモリにロード
	GameOverTxtGraph = LoadGraph("image/GameOverTxt.png");
	// グラフィック『arrow3.png』をメモリにロード
	ArrowGraph = LoadGraph("image/arrow3.png");
	// グラフィック『GameOver.mp3』をメモリにロード
	GameOverHandle = LoadSoundMem("image/GameOver.mp3");
	
	PlaySoundMem(GameOverHandle, DX_PLAYTYPE_LOOP);

	while (GameRoop)
	{
		/*計算処理*/
		//Input Down.
		if (InputDown())
		{
			if (ArrowPosY == 0)
			{
				ArrowPosY = 80;
			}
			else
			{
				ArrowPosY = 0;
			}
		}
		//Input Up.
		if (InputUp())
		{
			if (ArrowPosY == 80)
			{
				ArrowPosY = 0;
			}
			else
			{
				ArrowPosY = 80;
			}
		}

		/*タイマ更新*/
		CountFrame++;
		if (CountFrame > 80000) { CountFrame = 0; }//一定以上数が増えたら初期化(数は適当)

		/*Draw処理*/
		//裏画面の初期化
		ClearDrawScreen();

		// ゲームオーバー画面の描画
		DrawGraph(0, 0, GameOverGraph, true);
		DrawGraph(0, 0, GameOverTxtGraph, true);

		// →の描画
		if ((CountFrame % 60) < 32)
		{
			DrawGraph(0, ArrowPosY, ArrowGraph, true);
		}

		// ゲームオーバー時の経過時間の表示
		{
			Cr1 = GetColor(255, 200, 20);
			Cr2 = GetColor(0, 0, 0);
			SetFontSize(68);
			ChangeFont("HG創英角ﾎﾟｯﾌﾟ体");
			ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);
			DrawFormatString(105, 305, Cr2, "経過時間");
			DrawFormatString(185, 385, Cr2, "%d秒", Time / 1000);
			DrawFormatString(100, 300, Cr1, "経過時間");
			DrawFormatString(180, 380, Cr1, "%d秒", Time / 1000);
		}

		ScreenFlip();

		/*シーン遷移処理*/
		//エンターでシーン変更
		if (ConfirmButton())
		{
			if (ArrowPosY == 0)
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

// ゲームクリアシーン
int GameClearScene()
{
	int NextScene = GAMECLEARSCENE;
	int ArrowPosY = 10;
	int CountFrame = 0;
	bool GameRoop = true;
	int AreaX = 0;
	int Speed = 1;

	// グラフィック『clear.png』をメモリにロード
	ClearGraph = LoadGraph("image/clear.png");
	// グラフィック『GameClearTxt.png』をメモリにロード
	GameClearTxtGraph = LoadGraph("image/GameClearTxt.png");
	// グラフィック『arrow1.png』をメモリにロード
	ArrowGraph = LoadGraph("image/arrow1.png");
	// グラフィック『SlimeAye.png』をメモリにロード
	SlimeAyeGraph = LoadGraph("image/SlimeAye.png");
	// グラフィック『SlimeAye2.png』をメモリにロード
	SlimeAye2Graph = LoadGraph("image/SlimeAye2.png");
	// グラフィック『Sky.png』をメモリにロード
	SkyGraph = LoadGraph("image/Sky.png");
	// グラフィック『mountain.png』をメモリにロード
	MountainGraph = LoadGraph("image/mountain.png");
	// グラフィック『Graund.png』をメモリにロード
	GraundGraph = LoadGraph("image/Graund.png");

	while (GameRoop)
	{
		/*タイマ更新*/
		CountFrame++;
		if (CountFrame > 80000) { CountFrame = 0; }//一定以上数が増えたら初期化(数は適当)

		/*Draw処理*/
		//裏画面の初期化
		ClearDrawScreen();

		// 背景の描画
		BackScroll(AreaX, SkyGraph, EnemyStart, 720);
		AreaX += Speed;
		if (AreaX > EnemyStart)
		{
			AreaX = 0;
		}
	
		// ゲームクリア画面の描画
		DrawGraph(0, 0, MountainGraph, true);
		DrawGraph(0, 0, GraundGraph, true);
		DrawGraph(0, 0, ClearGraph, true);

		// スライムの瞬きの描画
		if ((CountFrame % 100) < 97)
		{
			DrawGraph(0, 0, SlimeAyeGraph, true);
		}
		else
		{
			DrawGraph(0, 0, SlimeAye2Graph, true);
		}
		// クリア画面のテキスト描画
		DrawGraph(0, 0, GameClearTxtGraph, true);

		if ((CountFrame % 60) < 32)
		{
			DrawGraph(-10, ArrowPosY, ArrowGraph, true);
		}

		ScreenFlip();

		/*シーン遷移処理*/
		//エンターでシーン変更
		if (ConfirmButton())
		{
			if (ArrowPosY == 10)
			{
				return TITLESCENE;
			}
		}
	}
	
	return TITLESCENE;
}

// 確定ボタンが押されたかどうかを判定する関数
bool ConfirmButton()
{
	Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//指定フレーム以上押していたら押した判定
	if (Key == (PAD_INPUT_1) && !IsInputEnterHold)
	{
		IsInputEnterHold = true;
		return true;
	}
	else if (!Key)
	{
		IsInputEnterHold = false;
	}

	return false;
}

// 上が押されたかどうかを判定する関数
bool InputUp()
{
	Key1 = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//指定フレーム以上押していたら押した判定
	if (Key1 == (PAD_INPUT_UP) && !IsInputDownHold)
	{
		IsInputDownHold = true;
		return true;
	}
	else if (!Key1)
	{
		IsInputDownHold = false;
	}

	return false;
}

// 下が押されたかどうかを判定する関数
bool InputDown()
{
	Key2 = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//指定フレーム以上押していたら押した判定
	if (Key2 == (PAD_INPUT_DOWN) && !IsInputUpHold)
	{
		IsInputUpHold = true;
		return true;
	}
	else if (!Key2)
	{
		IsInputUpHold = false;
	}

	return false;
}

//Jump1が押されたかどうかを判定する関数
bool InputJump1()
{
	Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//指定フレーム以上押していたら押した判定
	if (Key == (PAD_INPUT_1) && !IsInputJump1Hold)
	{
		IsInputJump1Hold = true;
		return true;
	}
	else if (!Key)
	{
		IsInputJump1Hold = false;
	}

	return false;
}

//Jump2が押されたかどうかを判定する関数
bool InputJump2()
{
	Key1 = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//指定フレーム以上押していたら押した判定
	if (Key1 == (PAD_INPUT_1) && !IsInputJump2Hold)
	{
		IsInputJump2Hold = true;
		return true;
	}
	else if (!Key1)
	{
		IsInputJump2Hold = false;
	}

	return false;
}

bool InputJump3()
{
	return false;
}

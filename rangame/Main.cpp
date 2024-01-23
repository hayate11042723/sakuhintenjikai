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


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int Key;
	int phase = 0;
	int StartTime;
	int Time;
	unsigned int Cr;

	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(true);

	// 画面モードの設定
	SetGraphMode(1280, 720, 32);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	// このフレームの開始時刻を覚えておく
	LONGLONG start = GetNowHiPerformanceCount();

	// グラフィック『player.png』をメモリにロード
	PlayerGraph = LoadGraph("image/player.png");
	// グラフィック『player.png』をメモリにロード
	EnemyGraph = LoadGraph("image/enemy.png");

	// キャラクターの初期データをセット
	PlayerX = 60;
	PlayerY = 640;



	//SceneMgr_Initialize();

	//while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {//画面更新 & メッセージ処理 & 画面消去

	//	SceneMgr_Update();  //更新
	//	SceneMgr_Draw();    //描画

	//}

	//SceneMgr_Finalize();

		// 現在経過時間を得る
		StartTime = GetNowCount();
		int EnemyNum = 0;

	// ゲームループ
	while (GetNowCount() - StartTime < 25000)
	{
		
		// 描画を行う前に画面をクリアする
		ClearDrawScreen();	

	
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();
		// 白の色コードを保存
		Cr = GetColor(255, 255, 255);
		Time = GetNowCount() - StartTime;

		DrawFormatString(1150, 10, Cr, "経過時間%d秒", Time/1000);

		// エネミーの出現処理
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


		// キー入力取得
		Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		// 落下処理
		PlayerY -= JumpPower;

		// 落下加速度付加
		JumpPower -= 1;

		// プレイヤーが画面下端からはみ出そうになっていたら画面内の座標に戻してあげる
		if (PlayerY > 720 - 64) PlayerY = 720 - 64;
		// プレイヤーが画面天井からはみ出そうになっていたら画面内の座標に戻してあげる
		if (PlayerY < 0 + 64) PlayerY = 0 + 64;

		// もし地面についていたら止まる
		if (PlayerY > 640)
		{
			PlayerY = 640;
			JumpPower = 0;
		}

		// spaceキーを押したらジャンプする
		if ((Key & PAD_INPUT_A) && PlayerY == 640)JumpPower = 28;

		EnemyPos.x -= 10;


		// プレイヤーを描画する
		DrawGraph(PlayerX, PlayerY, PlayerGraph, TRUE);
		// エネミーを描画する
		DrawGraph(EnemyPos.x, EnemyPos.y, EnemyGraph, TRUE);



		// プレイヤー画像と敵画像で当たり判定
		if (PlayerX + IMAGE_SIZE >= EnemyPos.x && PlayerX <= EnemyPos.x + IMAGE_SIZE) {
			if (PlayerY + IMAGE_SIZE >= EnemyPos.y && PlayerY <= EnemyPos.y + IMAGE_SIZE) {
				// 当たったらプレイヤーをデリート
				DeleteGraph(PlayerGraph);
			}
		}

		// 画面が切り替わるのを待つ
		ScreenFlip();

		// escキーでゲーム終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60に固定する
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66ミリ秒(16667マイクロ秒)経過するまで待つ
		}
	}

		DxLib_End();				// ＤＸライブラリ使用の終了処理

		return 0;				// ソフトの終了 
}
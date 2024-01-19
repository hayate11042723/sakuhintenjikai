#include "DxLib.h"

int PlayerX, PlayerY;
float JumpPower;
int PlayerGraph;
int EnemyGraph;
int EnemyX, EnemyY;

XINPUT_STATE input;


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int Key;
	int phase = 0;

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

	// ゲームループ
	while (ProcessMessage() != -1)
	{
			
		// 描画を行う前に画面をクリアする
		ClearDrawScreen();	
	
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

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

		// プレイヤーを描画する
		DrawGraph(PlayerX, PlayerY, PlayerGraph, TRUE);
		DrawGraph(EnemyX, EnemyY, EnemyGraph, TRUE);



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
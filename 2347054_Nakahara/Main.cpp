#include "DxLib.h"
#include <math.h>

//#include "SceneMgr.h"
#define IMAGE_SIZE	50

int PlayerX, PlayerY;
float JumpPower;
int PlayerGraph;
int BackGraph;
int TitleGraph;
int TitleScrollGraph;
int EnemyW, EnemyH;
int PlayerH, PlayerW;

constexpr int GAMEEND = 0;
constexpr int TITLESCENE = 1;
constexpr int MANUALSCENE = 2;
constexpr int GAMESCENE = 3;
constexpr int GAMEOVERSCENE = 4;
constexpr int GAMECLEARSCENE = 5;


bool isInputEnterHold = false;// InputEneter用の変数
bool isInputUpHold = false;// InputUp用の変数
bool isInputDownHold = false;// InputDown用の変数

int TitleScene();
int ManualScene();
int GameScene();
int GameOverScene();
int GameClearScene();
bool InputEnter();
bool InputUp();
bool InputDown();

// エネミー構造体
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

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	LONGLONG roopStartTime = 0;
	bool gameRoop = true;
	int nextScene = TITLESCENE;

	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(true);
	// 画面モードの設定
	SetGraphMode(1280, 720, 32);
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);

	while (gameRoop) 
	{
		roopStartTime = GetNowHiPerformanceCount();
	
		ClearDrawScreen();

		if (nextScene == TITLESCENE)
		{
			nextScene = TitleScene();

			if (nextScene == GAMESCENE) {
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
			}
		}
		else if (nextScene == MANUALSCENE)
		{
			nextScene = ManualScene();
		}
		else if (nextScene == GAMESCENE)
		{
			nextScene = GameScene();
		}
		else if (nextScene == GAMEOVERSCENE)
		{
			nextScene = GameOverScene();

			if (nextScene == GAMESCENE) {
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
			}
		}
		else if (nextScene == GAMECLEARSCENE)
		{
			nextScene = GameClearScene();
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
	int arrowPosY = 440;
	int countFrame = 0;
	int areaX = 0;
	int speed = 3;

	// グラフィック『Title.png』をメモリにロード
	TitleScrollGraph = LoadGraph("image/title (2).png");
	TitleGraph = LoadGraph("image/Title.png");

	/*ゲーム処理*/
	while (gameRoop)
	{


		/*計算処理*/
		//Input Down.
		if (InputDown())
		{
			if (arrowPosY == 440)
			{
				arrowPosY = 460;
			}
			else if (arrowPosY == 460 , arrowPosY > 480)
			{
				arrowPosY = 440;
			}
			else
			{
				arrowPosY = 480;
			}
		}
		//Input Up.
		if (InputUp())
		{
			if (arrowPosY == 480)
			{
				arrowPosY = 460;
			}
			else if (arrowPosY == 460, arrowPosY < 480)
			{
				arrowPosY = 440;
			}
			else
			{
				arrowPosY = 480;
			}
		}


		/*タイマ更新*/
		countFrame++;
		if (countFrame > 80000) { countFrame = 0; }//一定以上数が増えたら初期化(数は適当)

		/*Draw処理*/
		//裏画面の初期化
		ClearDrawScreen();

		BackScroll(areaX, TitleScrollGraph, 1280, 720);
		DrawGraph(0, 0, TitleGraph, true);

		areaX += speed;
		if (areaX > 1280)
		{
			areaX = 0;
		}

		//タイトルロゴ
		//SetFontSize(80);//フォントサイズ変更
		//DrawString(440, 240, "", GetColor(255, 255, 255));
		//SetFontSize(40);//フォントサイズ上
		//DrawString(460, 320, "-GameTemplate1-", GetColor(255, 255, 255));
		//SetFontSize(20);//フォントサイズ初期化
		//ゲームシーンテキスト
		DrawString(600, 440, "START", GetColor(255, 255, 255));
		//ゲームの操作テキスト
		DrawString(600, 460, "MANUAL", GetColor(255, 255, 255));
		//ゲームエンドテキスト
		DrawString(600, 480, "END", GetColor(255, 255, 255));
		//矢印表示(点滅させる)
		if ((countFrame % 60) < 32)
		{
			DrawString(560, arrowPosY, "→", GetColor(255, 255, 255));
		}

		/*DebugDraw処理*/
		DrawString(0, 0, "TitleScene", GetColor(255, 255, 255));//シーン名表示

		//裏画面を表へ
		ScreenFlip();

		/*シーン遷移処理*/
		//エンターでシーン変更
		if (InputEnter())
		{
			if (arrowPosY == 440)
			{
				return GAMESCENE;
			}
			else if (arrowPosY == 460)
			{
				return MANUALSCENE;
			}
			else
			{
				return GAMEEND;
			}

		}
	}

	//例外処理
	return TITLESCENE;
}

int ManualScene()
{
	int GameRoop = true;
	int countFrame = 0;
	int nextScene = MANUALSCENE;


	while (GameRoop)
	{
		/*タイマ更新*/
		countFrame++;
		if (countFrame > 80000) { countFrame = 0; }//一定以上数が増えたら初期化(数は適当)

		/*Draw処理*/
		//裏画面の初期化
		ClearDrawScreen();

		//タイトルロゴ
		//SetFontSize(80);//フォントサイズ変更
		//DrawString(440, 240, "", GetColor(255, 255, 255));
		//SetFontSize(40);//フォントサイズ上
		//DrawString(460, 320, "-GameTemplate1-", GetColor(255, 255, 255));
		//SetFontSize(20);//フォントサイズ初期化
		DrawString(200, 350, "キー説明", GetColor(255, 255, 255));
		//ENTERキー説明
		DrawString(250, 400, "ENTERキー：タイトル画面に戻る ＆ 選択肢の決定ボタン", GetColor(255, 255, 255));
		//ジャンプボタン
		DrawString(250, 450, "Ｚキー：ジャンプ", GetColor(255, 255, 255));
		//ルール説明
		DrawString(200, 100, "クリア条件", GetColor(255, 255, 255));
		DrawString(250, 150, "一分間敵に当たらずに生存", GetColor(255, 255, 255));
				
		DrawString(200, 200, "ゲームオーバー条件", GetColor(255, 255, 255));
		DrawString(250, 250, "道中にいる敵に当たる", GetColor(255, 255, 255));
		
		/*DebugDraw処理*/
		DrawString(0, 0, "ManualScene", GetColor(255, 255, 255));//シーン名表示

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
	int Key;
	int phase = 0;
	int StartTime;
	int Time;
	int areaX = 0;
	int speed = 3;
	unsigned int Cr;
	int nextScene = GAMESCENE;


	// グラフィック『player.png』をメモリにロード
	PlayerGraph = LoadGraph("image/player.png");
	// グラフィック『enemy.png』をメモリにロード
	EnemyGraph = LoadGraph("image/enemy.png");
	// グラフィック『back.png』をメモリにロード
	BackGraph = LoadGraph("image/back.png");

	// キャラクターの初期データをセット
	PlayerX = 60;
	PlayerY = 600;

	// 現在経過時間を得る
	StartTime = GetNowCount();
	int EnemyNum = 0;

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
		Cr = GetColor(255, 255, 255);
		Time = GetNowCount() - StartTime;

		DrawFormatString(1150, 10, Cr, "経過時間%d秒", Time / 1000);

		// エネミーの出現処理
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
		if (EnemyNum == 15 && Time >= 26000) {
			EnemyPos.x = 1270;
			EnemyPos.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 16 && Time >= 28000) {
			EnemyPos1.x = 1280;
			EnemyPos1.y = 310;
			EnemyNum++;
		}
		if (EnemyNum == 17 && Time >= 28000) {
			EnemyPos2.x = 1270;
			EnemyPos2.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 18 && Time >= 30000) {
			EnemyPos3.x = 1270;
			EnemyPos3.y = 620;
			EnemyNum++;
		}
		if (EnemyNum == 19 && Time >= 31000) {
			EnemyPos4.x = 1270;
			EnemyPos4.y = 310;
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
		if (PlayerY > 600)
		{
			PlayerY = 600;
			JumpPower = 0;
		}

		// Zキーを押したらジャンプする
		if ((Key & PAD_INPUT_A) && PlayerY == 600)JumpPower = 28;

		EnemyPos.x -= 10;
		EnemyPos1.x -= 10;
		EnemyPos2.x -= 10;
		EnemyPos3.x -= 10;
		EnemyPos4.x -= 10;


		// プレイヤーを描画する
		DrawGraph(PlayerX, PlayerY, PlayerGraph, TRUE);
		// エネミーを描画する
		DrawGraph(EnemyPos.x, EnemyPos.y, EnemyGraph, TRUE);
		DrawGraph(EnemyPos1.x, EnemyPos1.y, EnemyGraph, TRUE);
		DrawGraph(EnemyPos2.x, EnemyPos2.y, EnemyGraph, TRUE);
		DrawGraph(EnemyPos3.x, EnemyPos3.y, EnemyGraph, TRUE);
		DrawGraph(EnemyPos4.x, EnemyPos4.y, EnemyGraph, TRUE);



		// プレイヤー画像と敵画像で当たり判定
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
	int arrowPosY = 440;
	int countFrame = 0;
	bool gameRoop = true;



	while (gameRoop)
	{
		/*計算処理*/
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


		/*タイマ更新*/
		countFrame++;
		if (countFrame > 80000) { countFrame = 0; }//一定以上数が増えたら初期化(数は適当)

		/*Draw処理*/
		//裏画面の初期化
		ClearDrawScreen();

		//ゲームシーンテキスト
		DrawString(600, 440, "RE START", GetColor(255, 255, 255));
		//ゲームエンドテキスト
		DrawString(600, 480, "TITLE", GetColor(255, 255, 255));
		//矢印表示(点滅させる)
		if ((countFrame % 60) < 32)
		{
			DrawString(560, arrowPosY, "→", GetColor(255, 255, 255));
		}

		DrawString(0, 0, "GameOverScene", GetColor(255, 255, 255));//シーン名表示

		ScreenFlip();

		/*シーン遷移処理*/
		//エンターでシーン変更
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
		/*計算処理*/
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


		/*タイマ更新*/
		countFrame++;
		if (countFrame > 80000) { countFrame = 0; }//一定以上数が増えたら初期化(数は適当)

		/*Draw処理*/
		//裏画面の初期化
		ClearDrawScreen();

		//ゲームシーンテキスト
		DrawString(600, 440, "RE START", GetColor(255, 255, 255));
		//ゲームエンドテキスト
		DrawString(600, 480, "TITLE", GetColor(255, 255, 255));
		//矢印表示(点滅させる)
		if ((countFrame % 60) < 32)
		{
			DrawString(560, arrowPosY, "→", GetColor(255, 255, 255));
		}

		DrawString(0, 0, "GameClearScene", GetColor(255, 255, 255));//シーン名表示

		ScreenFlip();

		/*シーン遷移処理*/
		//エンターでシーン変更
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
	//指定フレーム以上押していたら押した判定
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
//Upが押されたかどうかを判定する関数
bool InputUp()
{
	//指定フレーム以上押していたら押した判定
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
//Downが押されたかどうかを判定する関数
bool InputDown()
{
	//指定フレーム以上押していたら押した判定
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
#include <Novice.h>
#include "GameMain/header.file/GameManeger.h"

const char kWindowTitle[] = "GC2A_02_アリマ_ナオト";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	GameManeger* gameManeger = new GameManeger();

	gameManeger->Run();

	// ライブラリの終了
	Novice::Finalize();
	delete gameManeger;
	return 0;
}

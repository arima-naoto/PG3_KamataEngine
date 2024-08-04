#pragma once
#include "GameMain/header.file/scene/IScene.h"
#include "GameMain/header.file/other/InputHandler.h"
#include "GameMain/header.file/other/ICommand.h"
#include "GameMain/header.file/object/Particle.h"
#include "GameMain/header.file/object/Player.h"
#include "GameMain/header.file/object/Enemy.h"
#include "list"

enum class Phase {
	kPlay, //ゲームプレイ
	kDead  //デス
};

/// <summary>
/// Isceneクラスを継承したStageSceneクラスを宣言
/// </summary>
class StageScene : public IScene
{
public://メンバ関数

#pragma region オーバーライドしたメンバ関数の定義

	///初期化処理
	void Initialize() override;
	
	///更新処理
	void Update(char* keys, char* preKeys) override;

	///描画処理
	void Draw() override;

#pragma endregion


#pragma region 再帰関数を使用した各オブジェクトのインスタンス生成処理

	///指定された数のパーティクルを生成する
	void GenerateParticle(int32_t count);

	///指定された数の敵機を描画する
	void GenerateEnemy(int32_t count);

#pragma endregion


#pragma region 衝突判定メンバ関数の宣言

	///自機の複数弾と複数の敵機の衝突判定
	void EnemyCollision();

	///自機と敵機の弾の衝突判定
	void PlayerCollision();

	///衝突判定
	void CheckCollision();

#pragma endregion 

private://メンバ変数

	///インプットハンドルクラス
	InputHandler* inputHander_ = nullptr;
	
	///コマンドクラス
	ICommand* iCommand_ = nullptr;

	///パーティクルクラス
	std::list<Particle*> particles_;

	///エネミークラス
	std::list<Enemy*>enemys_;

	///プレイヤークラス
	Player* player_;

	///現在のフェーズ
	Phase phase_;

};


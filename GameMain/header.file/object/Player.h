#pragma once
#define SHOT_MAX 2
#include "GameMain/header.file/other/MyStruct.h"
#include "GameMain/header.file/object/BulletA.h"
#include "list"

/// <summary>
/// Playerクラスの作成
/// </summary>
class Player
{
public://メンバ関数

	///初期化処理
	void Initialize();

	///更新処理
	void Update();

	///描画処理
	void Draw();

	///指定された数の弾を生成する
	void GenerateBullets(int32_t count);

	//敵機の弾が自機に当たった時の処理
	void OnCollision();

#pragma region 移動処理メンバ関数

	///右移動処理
	void MoveRight();

	///左移動処理
	void MoveLeft();

	///上移動処理
	void MoveUp();

	///下移動処理
	void MoveDown();

#pragma endregion


#pragma region カプセル化とアクセッサ

	///座標getter
	Vector2 GetPos();

	///座標setter
	void SetPosition(Vector2 pos);

	///半径getter
	Vector2 GetRadius();

	///ヒットフラグgetter
	bool GetIsHit();

	///ヒットフラグsetter
	bool SetIsHit(bool isHit);

	///自機の体力getter
	int GetHp();

	///弾クラスgetter
	std::list<Bullet*>IsBullets();


#pragma endregion

private://メンバ変数

	///座標
	Vector2 pos_;

	///半径
	Vector2 radius_;

	///移動速度
	int speed_;

	///プレイヤーの色
	unsigned int color_;

	///弾クラスの包含
	std::list<Bullet*>bullets_;
	///弾の発射クールタイマー
	int shotCoolTimer_;

	///自機の体力
	int hp_;

	//ヒットフラグ
	int isHit_;


};


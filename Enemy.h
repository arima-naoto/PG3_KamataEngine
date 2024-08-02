#pragma once
#include "MyStruct.h"
#include "functional"
#include "BulletB.h"

/// <summary>
/// Enemyクラスの宣言
/// </summary>
class Enemy
{
public://メンバ関数

	///初期化処理
	void Initialize(Vector2 position);

	///更新処理
	void Update();
	
	///描画処理
	void Draw();

	///衝突したときの処理
	void OnCollision();

#pragma region カプセル化とアクセッサ

	///座標getter
	Vector2 GetPos();

	///座標setter
	void SetPosition(Vector2 pos);

	///半径getter
	Vector2 GetRadius();

	///移動速度setter
	void SetSpeed(int speed);

	///衝突getter
	bool GetIsAlive();

	///衝突setter
	bool SetIsAlive(bool isAlive);

	///敵の体力getter
	int GetHp();

	///敵の体力setter
	int SetHp(int hp);

	Bullet* IsBullet()const;

#pragma endregion

private://メンバ変数

	//Bulletクラスの包含
	Bullet *enemyBullet_;

	///座標
	Vector2 pos_;

	///半径
	Vector2 radius_;

	///移動速度
	int speed_;

	///敵機の色
	unsigned int color_;

	///衝突フラグ
	bool isAlive_;

	///復活タイマー
	int respawnTimer_;

	///敵の体力
	int hp_;

	/// 敵機の移動処理を保持するラムダ式
	std::function<void()>moveEnemy_;

	

	///弾を発射するタイマー
	int shotTimer_;

};


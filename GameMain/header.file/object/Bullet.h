#pragma once
#include "GameMain/header.file/other/MyStruct.h"
#include "functional"

/// <summary>
/// 基底クラスBulletを宣言
/// </summary>
class Bullet
{
public://メンバ関数

	///初期化処理
	virtual void Initialize();

	///更新処理
	virtual void Update();

	///描画処理
	virtual void Draw();

#pragma region カプセル化とアクセッサ

	///座標getter
	Vector2 GetPos();

	///座標setter
	void SetPosition(Vector2 pos);

	///半径getter
	Vector2 GetRadius();

	///発射フラグgetter
	bool GetIsShot();

	///発射フラグsetter
	bool SetIsShot(bool isShot);

#pragma endregion

protected:///メンバ変数

	///座標
	Vector2 pos_;

	///半径
	Vector2 radius_;
	
	///移動速度
	int speed_;
	
	///弾の色
	unsigned int color_;
	
	///発射フラグ
	bool isShot_;
	
	///弾の移動処理を保持するメンバ変数
	std::function<void()> bulletMove_;

};


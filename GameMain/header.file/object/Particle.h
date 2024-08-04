#pragma once
#include "GameMain/header.file/other/MyStruct.h"
#include "functional"

/// <summary>
/// Particleクラスを宣言
/// </summary>
class Particle
{
public://メンバ関数

	///初期化処理
	void Initialize();

	///更新処理
	void Update();
	///描画処理
	void Draw();

#pragma region カプセル化とアクセッサ

	///座標setter
	void SetPosition(Vector2 pos);

	///発射フラグgetter
	bool GetIsShot();

	///発射フラグsetter
	bool SetIsShot(bool isShot);

#pragma endregion 


private:///メンバ変数

	///座標
	Vector2 pos_;
	///半径
	int radius_;
	///移動速度
	int speed_;
	///パーティクルの色
	unsigned int color_;
	///ショットフラグ
	bool isShot_;

	std::function<void()> particleMove_;

};


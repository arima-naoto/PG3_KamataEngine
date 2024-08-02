#pragma once
#include "Bullet.h"

/// <summary>
/// 弾クラスの宣言(敵機用)
/// </summary>
class BulletB : public Bullet
{
public://メンバ関数

	///初期化処理
	void Initialize() override; 

	///更新処理
	void Update() override;

	///描画処理
	void Draw() override;

};


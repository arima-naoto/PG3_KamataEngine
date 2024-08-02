#pragma once
#include "Bullet.h"

class BulletA : public Bullet
{
public:

	///初期化処理
	void Initialize() override;

	///更新処理
	void Update() override;

	///描画処理
	void Draw() override;	

};


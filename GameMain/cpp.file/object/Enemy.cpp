#include "GameMain/header.file/object/Enemy.h"

/// <summary>
/// 初期化処理
/// </summary>
void Enemy::Initialize(Vector2 position) {

	///座標
	pos_ = position;

	///半径
	radius_ = { 32,32 };

	///移動速度
	speed_ = 5;

	///敵機の色
	color_ = WHITE;

	///生存フラグ
	isAlive_ = true;

	///復活タイマー
	respawnTimer_ = 0;

	///敵の体力
	hp_ = 2;

	//ラムダ式で敵機の移動処理を定義する
	moveEnemy_ = [this]() {

		//敵機が生きている状態であれば
		if (isAlive_) 
		{	
			//敵の座標を右方向に動かす
			pos_ += Vector2(speed_, 0);
			
			//もし敵の座標が特定の位置まで達したら
			if (pos_.x >= 1216 || pos_.x <= 0) 
			{
				//敵機の移動速度を反転させる
				speed_ *= -1;
			}

		}
	};

	shotTimer_ = 0;

	enemyBullet_ = new BulletB();
	enemyBullet_->Initialize();

}

/// 更新処理
void Enemy::Update() {

	//メンバ関数Initializeで定義したmoveEnemyを更新処理内で呼び出す
	moveEnemy_();

	///発射タイマーをインクリメントする
	shotTimer_++;

	///発射タイマーが140以上であれば
	if (shotTimer_ >= 140) 
	{
		///発射タイマーを0に戻し
		shotTimer_ = 0;
		
		///敵機の弾発射フラグがfalseであれば
		if (!enemyBullet_->GetIsShot()) {

			///発射フラグをtrueに設定し
			enemyBullet_->SetIsShot(true);

			///敵機が撃つ弾の座標を敵機の座標に合わせる
			enemyBullet_->SetPosition(Enemy::GetPos());
			
		}
	}

	///敵機の弾の更新処理
	enemyBullet_->Update();

}

/// 描画処理
void Enemy::Draw()
{
	//敵機の弾の描画処理
	enemyBullet_->Draw();

	///敵の残機画像を読み込む
	int enemyTextureHandle = Novice::LoadTexture("./Resources/enemy.png");
	int ExplosionHandle = Novice::LoadTexture("./Resources/enemyExplosion.png");

	if (isAlive_) {
		Novice::DrawSprite(pos_.x, pos_.y, enemyTextureHandle, 1.0f, 1.0f, 0.0f, color_);
	}
	else if (!isAlive_) {
		Novice::DrawBox(pos_.x - 50, pos_.y - 20, 120, 10, 0.0f, RED, kFillModeSolid);
		Novice::DrawBox(pos_.x - 50, pos_.y - 20, respawnTimer_, 10, 0.0f, GREEN, kFillModeSolid);	

		///敵の復活タイマーが0以上30以下であれば
		if (respawnTimer_ >= 0 && respawnTimer_ <= 30) {
			//爆発画像を呼び出す
	        Novice::DrawSprite(pos_.x + 8 , pos_.y, ExplosionHandle, 1, 1, 0, WHITE);
		}

	}
	
}

///衝突したときの処理
void Enemy::OnCollision() {

	if (!isAlive_) {

		respawnTimer_++;

		if (respawnTimer_ >= 120) {
			isAlive_ = true;
			respawnTimer_ = 0;
			hp_--;
		}
	}
	
}

#pragma region カプセル化とアクセッサの定義

///敵機座標getterの定義
Vector2 Enemy::GetPos() { return this->pos_; }

///敵機座標setterの定義
void Enemy::SetPosition(Vector2 pos) { this->pos_ = pos; }

///敵機半径getterの定義
Vector2 Enemy::GetRadius() { return this->radius_; }

///敵機移動速度setterの定義
void Enemy::SetSpeed(int speed) { this->speed_ = speed; }

///敵機生存フラグgetterの定義
bool Enemy::GetIsAlive() { return this->isAlive_; }

///敵機生存フラグsetterの定義
bool Enemy::SetIsAlive(bool isAlive) { return this->isAlive_ = isAlive; }

///敵機体力getterの定義
int Enemy::GetHp() { return this->hp_; }

///敵機体力setterの定義
int Enemy::SetHp(int hp) { return this->hp_ = hp; }

///敵機の弾getterを宣言
Bullet* Enemy::IsBullet()const { return enemyBullet_; }

#pragma endregion
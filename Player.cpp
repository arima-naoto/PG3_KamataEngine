#include "Player.h"

/// 初期化処理
void Player::Initialize() {

#pragma region メンバ変数の定義

	///座標
	pos_ = { 640,550 };

	///半径
	radius_ = { 32,32 };

	//移動速度
	speed_ = 7;

	//プレイヤーの色
	color_ = WHITE;

	///弾の発射クールタイマー
	shotCoolTimer_ = 10;

	///自機の体力
	hp_ = 50;

	///ヒットフラグ
	isHit_ = false;

#pragma endregion

	///指定された数の弾を生成するメンバ関数を呼び出す
	GenerateBullets(SHOT_MAX);

}

/// 更新処理
void Player::Update() {

	if (Novice::CheckHitKey(DIK_SPACE)) {

		if (shotCoolTimer_ > 0) {
			shotCoolTimer_--;
		}
		else {
			shotCoolTimer_ = 10;
		}
		if (shotCoolTimer_ <= 0) {
			for (auto* bullet : bullets_) {
				if (!bullet->GetIsShot()) {
					bullet->SetIsShot(true);
					bullet->SetPosition(Player::GetPos());
					break;
				}
			}
		}
	}

	for (auto* bullet : bullets_) {
		bullet->Update();
	}

}

/// 描画処理
void Player::Draw() {

	//for文を使用して、弾を描画する
	for (auto* bullet : bullets_) {
		bullet->Draw();
	}

	//自機画像を読み込む
	int playerTextureHandle = Novice::LoadTexture("./Resources/player.png");

	///DrawEllipse関数を使用して、座標変換済みの半径24の緑色の円を描画する
	Novice::DrawSprite(pos_.x, pos_.y, playerTextureHandle, 1.0f, 1.0f, 0.0f, color_);

	///自機の体力バーを表示
	Novice::DrawBox(pos_.x + 7 , pos_.y + 64 , 50, 10, 0.0f, RED, kFillModeSolid);
	Novice::DrawBox(pos_.x + 7 , pos_.y + 64, hp_, 10, 0.0f, GREEN, kFillModeSolid);

	///自機の体力を表示
	Novice::ScreenPrintf(0, 0, "player.hp = %d", Player::hp_);

}

///指定された数の弾を生成する
void Player::GenerateBullets(int32_t count) {

	///弾の生成が必要ない場合は終了
	if (count <= 0) {
		return;
	}

	////弾のインスタンスを生成,初期化
	Bullet* newBullet = new BulletA();
	newBullet->Initialize();

	////弾をリスト登録する
	bullets_.push_back(newBullet);

	////残りの弾の数を減らして再帰呼び出し
	GenerateBullets(count - 1);

}

///敵機の弾が自機に当たった時の処理
void Player::OnCollision() {


	if (isHit_) {
		hp_ -= 10;
	}
}

#pragma region 移動処理メンバ関数の定義

/// 右移動処理
void Player::MoveRight() {

	this->pos_ += Vector2(this->speed_,0);

	if (this->pos_.x >= 1216) {
		this->speed_ = 0;
	}
	else {
		this->speed_ = 7;
	}

}

/// 左移動処理
void Player::MoveLeft() {

	this->pos_ -= Vector2(this->speed_, 0);

	if (this->pos_.x <= 0) {
		this->speed_ = 0;
	}
	else {
		this->speed_ = 7;
	}
}

/// 上移動処理
void Player::MoveUp() 
{
	this->pos_ -= Vector2(0, this->speed_);
}

/// 下移動処理
void Player::MoveDown() {
	this->pos_ += Vector2(0, this->speed_);

	if (this->pos_.y >= 640) {
		this->speed_ = 0;
	}
	else {
		this->speed_ = 7;
	}

}

#pragma endregion

#pragma region カプセル化とアクセッサの定義 

/// 座標getterの定義
Vector2 Player::GetPos() { return this->pos_; }

/// 座標setterの定義
void Player::SetPosition(Vector2 pos) { this->pos_ = pos; }

/// 半径getterの定義
Vector2 Player::GetRadius() { return this->radius_; }

///ヒットフラグgetter
bool Player::GetIsHit() { return this->isHit_; }

///ヒットフラグsetter
bool Player::SetIsHit(bool isHit) { return this->isHit_ = isHit; }

///自機の体力getter
int Player::GetHp() { return this->hp_; }

/// 自機弾クラスgetterの定義
std::list<Bullet*>Player::IsBullets() { return bullets_; }

#pragma endregion 


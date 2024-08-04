#include "StageScene.h"
#define PARTICLE_MAX 150 //パーティクルを生成する最大数
#define ENEMY_MAX 10 //画面上に敵機を表示する最大数

#pragma region オーバーライドされたメンバ関数の定義

/// 初期化処理
void StageScene::Initialize() {

	// 敵とパーティクルのリストをクリアする
	enemys_.clear();
	particles_.clear();

	///InputHanderクラスのインスタンスを作成
	inputHander_ = new InputHandler();

	//InputHanderクラスからプレイヤーを各方向に移動させるメンバ関数を呼び出す
	inputHander_->AssignMoveRIghtCommand2PressKeyD();
	inputHander_->AssignMoveLeftCommand2PressKeyA();
	inputHander_->AssignMoveUpCommand2PressKeyW();
	inputHander_->AssignMoveDownCommand2PressKeyS();

	GenerateParticle(PARTICLE_MAX);

	GenerateEnemy(ENEMY_MAX);

	//Playerクラスのインスタンスを作成
	player_ = new Player();
	//Playerの初期化処理
	player_->Initialize();

	///最初のフェーズの初期化
	phase_ = Phase::kPlay;

}

/// 更新処理
void StageScene::Update(char *keys,char*preKeys) {


	if(phase_ == Phase::kPlay){

#pragma region フェーズゲームプレイの更新処理

		///入力ハンドルからコマンドを取得する
		iCommand_ = inputHander_->HandleInput();

		///取得したコマンドが有効であれば、実行する
		if (this->iCommand_) { iCommand_->Exec(*player_); }

		//パーティクルの発生処理
		for (auto* particle : particles_) {
			//発射フラグがfalseになっていれば
			if (!particle->GetIsShot())
			{
				//発射フラグを立て
				particle->SetIsShot(true);
				//出現させる座標を指定の範囲に設定する
				particle->SetPosition(
					{ .x{ rand() % 1240 + 20},
					 .y{ rand() % 720 - 60 } });
				break;
			}
		}

		//パーティクルの更新処理
		for (auto* particle : particles_) { 
			particle->Update(); 
		}

		//敵機の更新処理
		for (auto* enemy : enemys_) { 
			enemy->Update(); 
		}

		//自機の更新処理
		player_->Update();

		///衝突判定
		StageScene::CheckCollision();


#pragma endregion


	}
	else if (phase_ == Phase::kDead) {

#pragma region 

		///スペースキーを押したら
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
		{
			//シーンをタイトルに切り替える
			sceneNo = Scene::TITLE;
		}

		//リセットボタンが押されたら
		if (keys[DIK_R] && !preKeys[DIK_R])
		{
			//フェーズをゲームプレイに戻す
			phase_ = Phase::kPlay;

			///全ての処理をリセットするためInitialize関数を使用する
			StageScene::Initialize();
		}

#pragma endregion

	}

}

/// 描画処理
void StageScene::Draw() {
	
	if (phase_ == Phase::kPlay) {

#pragma region //フェーズゲームプレイの描画処理

		///1280x720の黒い四角形を背景用として描画する
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);

		//Particleの描画処理
		for (auto* particle : particles_) {
			particle->Draw();
		}

		//敵機の描画処理
		for (auto* enemy : enemys_) {
			enemy->Draw();
		}

		///自機の描画処理
		player_->Draw();

#pragma endregion

	}else if(phase_ == Phase::kDead){

		//画像の読み込み
		int DeathTextureHandle = Novice::LoadTexture("./Resources/Dead.png");

		///DrawSprite関数で画像を描画する
		Novice::DrawSprite(0, 0, DeathTextureHandle, 1, 1, 0, WHITE);
	}

}

#pragma endregion


#pragma region 再帰関数を使用した各オブジェクトのインスタンス生成処理

///指定された数のパーティクルを生成する
void StageScene::GenerateParticle(int32_t count) {

	//パーティクルの生成がない場合は終了
	if (count <= 0) {
		return;
	}

	///Particleクラスのインスタンスを作成,初期化
	Particle* newParticle = new Particle();
	newParticle->Initialize();

	///パーティクルのリストを登録する
	particles_.push_back(newParticle);

	///再帰関数呼び出し
	GenerateParticle(count - 1);

}

///指定された数の敵機を生成する
void StageScene::GenerateEnemy(int32_t count) {

	///敵機の生成が無い場合は終了
	if (count <= 0) {
		return;
	}

	///各敵機の初期座標を設定する
	Vector2 enemyPosition = { 1200 - (120 * count),120 - (10 * count) };

	///敵機のインスタンスを生成、初期化
	Enemy* newEnemy = new Enemy();
	newEnemy->Initialize(enemyPosition);
	//敵機のリストを登録する
	enemys_.push_back(newEnemy);
	//再帰関数呼び出し
	GenerateEnemy(count - 1);
}

#pragma endregion


#pragma region 衝突判定メンバ関数の定義

///自機の複数弾と複数の敵の衝突判定
void StageScene::EnemyCollision() {

	for (auto* playerBullet : player_->IsBullets())
	{
		for (auto* enemy : enemys_)
		{

			//敵の生存フラグと複数弾のフラグがtrueである場合
			if (enemy->GetIsAlive() && playerBullet->GetIsShot()) {
				//もし衝突していれば
				if (IsCollision(playerBullet->GetPos(), enemy->GetPos(), playerBullet->GetRadius(), enemy->GetRadius()))
				{
					//各敵機の生存フラグをfalseに設定する
					enemy->SetIsAlive(false);
					playerBullet->SetIsShot(false);
				}
			}
			//敵の生存フラグが折られている場合
			else if (!enemy->GetIsAlive()) {
				//弾を発射させない
				enemy->IsBullet()->SetIsShot(false);
			}
		}
	}

	enemys_.remove_if([](Enemy* enemy) {
		enemy->OnCollision();
		if (enemy->GetHp() == 0) {
			return true;
		}
		return false;
	});

	///画面上に敵が全ていなくなったら
	if (enemys_.empty()) {
		//シーンをクリアに切り替える
		sceneNo = Scene::CLEAR;
	}

}

///自機と敵機の弾の衝突判定
void StageScene::PlayerCollision() {

	for (auto* enemy : enemys_) {

		if (enemy->IsBullet()->GetIsShot()) {
			//もし衝突しているなら
			if (IsCollision(enemy->IsBullet()->GetPos(), player_->GetPos(), enemy->IsBullet()->GetRadius(), player_->GetRadius()))
			{
				//自機のヒットフラグをtrueにし
				player_->SetIsHit(true);

				//当たった時の処理を呼び出し
				player_->OnCollision();

				///敵機の玉発射フラグをfalseに設定する
				enemy->IsBullet()->SetIsShot(false);
			}
		}
	}

	if (player_->GetHp() == 0) {
		phase_ = Phase::kDead;
	}

}

/// 全ての衝突判定
void StageScene::CheckCollision() {

	///自機と複数弾と複数の敵の衝突判定
	EnemyCollision();

	///自機と敵機の弾の衝突判定
	PlayerCollision();
}

#pragma endregion




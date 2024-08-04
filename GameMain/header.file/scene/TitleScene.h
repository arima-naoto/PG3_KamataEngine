#pragma once
#include "GameMain/header.file/scene/IScene.h"

/// <summary>
/// ISceneクラスを継承したTitleSceneクラスを宣言
/// </summary>
class TitleScene : public IScene
{
public://メンバ関数

	///	初期化処理
	void Initialize() override;

	/// 更新処理
	void Update(char* keys, char* preKeys) override;

	/// 描画処理
	void Draw() override;

};


#pragma once
#include <memory>
#include "GameMain/header.file/scene/IScene.h"
#include "GameMain/header.file/scene/TitleScene.h"
#include "GameMain/header.file/scene/StageScene.h"
#include "GameMain/header.file/scene/ClearScene.h"

class GameManeger
{
private:

	std::unique_ptr<IScene> sceneArr_[3];

	int currentSceneNo_;
	int prevSceneNo_;

public:

	GameManeger();

	~GameManeger();

	int Run();

};


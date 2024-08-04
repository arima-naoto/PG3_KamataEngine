#pragma once
#include "Novice.h"

enum Scene { TITLE,STAGE,CLEAR };

class IScene
{
protected:

	static int sceneNo;

public:

	virtual void Initialize() = 0;

	virtual void Update(char *keys,char *preKeys) = 0;

	virtual void Draw() = 0;

	virtual ~IScene();

	int GetSceneNo();

};


#include "GameMain/header.file/other/MyStruct.h"

bool IsCollision(const Vector2& obj1, const Vector2& obj2, const Vector2& obj1Radius, const Vector2& obj2Radius) {

	if (obj1.x - obj1Radius.x <= obj2.x + obj2Radius.x && obj2.x - obj2Radius.x <= obj1.x + obj1Radius.x &&
		obj1.y - obj1Radius.y <= obj2.y + obj2Radius.y && obj2.y - obj2Radius.y <= obj1.y + obj1Radius.y) {
		return true;
	}

	return false;
}
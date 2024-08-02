#pragma once
#include <Novice.h>

/// <summary>
/// Vector2構造体を定義
/// </summary>
struct Vector2 {

	int x;
	int y;

	///複合加算演算子
	Vector2& operator+=(Vector2 num) {
		this->x += num.x;
		this->y += num.y;
		return *this;
	}

	///複合減算演算子
	Vector2& operator-=(Vector2 num) {
		this->x -= num.x;
		this->y -= num.y;
		return *this;
	}
};

///衝突判定(矩形の当たり判定)
bool IsCollision(const Vector2& obj1, const Vector2& obj2, const Vector2& obj1Radius, const Vector2& obj2Radius);
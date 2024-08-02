#include "Bullet.h"

void Bullet::Initialize() {}

void Bullet::Update() {}

void Bullet::Draw() {}

Vector2 Bullet::GetPos() { return this->pos_; }

void Bullet::SetPosition(Vector2 pos) { this->pos_ = pos; }

Vector2 Bullet::GetRadius() { return this->radius_; }

bool Bullet::GetIsShot() { return this->isShot_; }

bool Bullet::SetIsShot(bool isShot) { return this->isShot_ = isShot; }
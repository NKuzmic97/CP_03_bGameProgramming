#include "Paddle.h"

Paddle::Paddle(
	const Vec2 & pos_, 
	float halfWidth_, 
	float halfHeight_)
:
	pos(pos_),
	halfWidth(halfWidth_),
	halfHeight(halfHeight_)
{
	//
}

void Paddle::Draw(Graphics & gfx) const {
	RectF rect = GetRect();
	gfx.DrawRect(rect, wingColor);
	rect.left += wingWidth;
	rect.right -= wingWidth;
	gfx.DrawRect(rect, color);
}

bool Paddle::DoBallCollision(Ball & ball) {
	if (!isCooldown) {
		const RectF rect = GetRect();

		if (rect.IsOverlapingWith(ball.GetRect())) {
			const Vec2 ballPos = ball.GetPosition();

			if (std::signbit(ball.GetVelocity().x) == std::signbit((ballPos - pos).x)) {
				ball.ReboundY();
			}

			else if (ballPos.x >= rect.left && ballPos.x <= rect.right) {
				ball.ReboundY();
			}
			else {
				ball.ReboundX();
			}
			isCooldown = true;
			return true;
		}
	}
	return false;
}

void Paddle::DoWallCollision(const RectF & walls) {
	const RectF rect = GetRect();
	if (rect.left < walls.left) {
		pos.x += walls.left - rect.left;
	}
	else if (rect.right > walls.right) {
		pos.x -= rect.right - walls.right;
	}
}

RectF Paddle::GetRect() const {
	return RectF::FromCenter(pos,halfWidth,halfHeight);
}

void Paddle::ResetCooldown() {
	isCooldown = false;
}

void Paddle::Update(const Keyboard& kbd, float dt) {
	if (kbd.KeyIsPressed(VK_LEFT)) {
		pos.x -= speed * dt;
	}
	else if (kbd.KeyIsPressed(VK_RIGHT)) {
		pos.x += speed * dt;
	}
}

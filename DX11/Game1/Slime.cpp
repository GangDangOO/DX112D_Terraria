#include "stdafx.h"

Slime::Slime(ObTileMap* _tileMap)
{
	stat.atk = 6;
	stat.def = 0;
	stat.hp = 14;
	stat.knockBack = -0.2f;

	tileMap = _tileMap;

	bodySprite = new ObImage(L"NPC_1.png");
	bodySprite->scale = Vector2(32.0f, 23.0f);
	bodySprite->maxFrame = Int2(1, 2);
	col->scale = bodySprite->scale;
	bodySprite->SetParentRT(*col);
	bodySprite->pivot = col->pivot;

	bodySprite->ChangeAnim(ANISTATE::LOOP, 0.5f, false);

	move = Vector2(0.0f, 0.0f);
	atkTime = 0.5f;
}

Slime::~Slime()
{
	SafeDelete(bodySprite);
}

bool Slime::Fall()
{
	bool isFall = false;
	if (dirCheck.up && move.y > 0.0f) move.y = 0.0f;
	if (!dirCheck.down) isFall = true;
	if (isFall) {
		atkTime = 0.0f;
		move.y -= 300 * DELTA * GAMESIZE;
	}else if (move.y < 0.0f) move = Vector2(0.0f, 0.0f);
	return isFall;
}

bool Slime::Jump()
{
	bool isJump = false;
	float dist = (playerCol->GetWorldPos().x - col->GetWorldPos().x) * GAMESIZE;
	float maxDist = 100.0f * GAMESIZE;
	if (dist > maxDist) {
		dist = maxDist;
	}
	else if (dist < -maxDist) {
		dist = -maxDist;
	}
	float jumpPower = 200.0f * GAMESIZE;
	move = Vector2(dist, jumpPower);
	if (move.x > 0.0f && dirCheck.right) move.x *= -1.0f;
	if (move.x < 0.0f && dirCheck.left) move.x *= -1.0f;
	return isJump;
}

void Slime::Update()
{
	Character::Update();
	if (!isDead) {
		atkTime += DELTA;

		Fall();
		if (atkTime >= 3.0f) {
			atkTime = 0.0f;
			bodySprite->aniInterval = 0.5f;
			Jump();
		}
		else if (atkTime >= 2.7f)
			bodySprite->aniInterval = 0.05f;
		else
			bodySprite->aniInterval = 0.5f;
		col->MoveWorldPos(move * DELTA);

		col->Update();
		bodySprite->Update();
	}

}

void Slime::Render()
{
	Character::Render();
	if (!isDead) bodySprite->Render();
}

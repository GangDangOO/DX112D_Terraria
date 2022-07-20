#include "stdafx.h"

Zombie::Zombie(ObTileMap* _tileMap)
{
	tileMap = _tileMap;

	bodySprite = new ObImage(L"NPC_3.png");
	bodySprite->scale = Vector2(36.0f, 46.0f);
	bodySprite->maxFrame = Int2(1, 3);
	col->scale = bodySprite->scale;
	bodySprite->SetParentRT(*col);
	bodySprite->pivot = col->pivot;

	bodySprite->ChangeAnim(ANISTATE::LOOP, 0.2f, false);

	move = Vector2(0.0f, 0.0f);
	jumpTime = 0.0f;
}

Zombie::~Zombie()
{
	SafeDelete(bodySprite);
}

bool Zombie::Fall()
{
	bool isFall = false;
	if (dirCheck.up && move.y > 0.0f) move.y = 0.0f;
	if (!dirCheck.down) isFall = true;
	if (isFall) {
		move.y -= 300 * DELTA * GAMESIZE;
	}
	else if (jumpTime <= 0.0f) move.y = 0.0f;
	return isFall;
}

bool Zombie::Jump()
{
	bool isJump = false;
	isJump = true;
	jumpTime = 0.2f;
	move.y = 200.0f * GAMESIZE;
	return isJump;
}

bool Zombie::Move()
{
	bool isMove = false;
	float speed = 50.0f * GAMESIZE;
	if (col->GetWorldPos().x > playerCol->GetWorldPos().x) {
		bodySprite->reverseLR = false;
		move.x -= speed * DELTA;
		isMove = true;
	}
	else if (col->GetWorldPos().x < playerCol->GetWorldPos().x) {
		bodySprite->reverseLR = true;
		move.x += speed * DELTA;
		isMove = true;
	}
	if (move.x > speed) move.x = speed;
	else if (move.x < -speed) move.x = -speed;
	return isMove;
}

void Zombie::Update()
{
	bool isFall;
	Character::Update();
	jumpTime -= DELTA;
	Move();
	isFall = Fall();

	if (col->GetWorldPos().x - playerCol->GetWorldPos().x > -10.0f && col->GetWorldPos().x - playerCol->GetWorldPos().x < 10.0f) {
		if (col->GetWorldPos().y < playerCol->GetWorldPos().y && !isFall) Jump();
	}
	if (move.x > 0.0f && dirCheck.right){
		if (!isFall) Jump();
		move.x = 0.0f;
	}
	if (move.x < 0.0f && dirCheck.left) {
		if (!isFall) Jump();
		move.x = 0.0f;
	}
	col->MoveWorldPos(move * DELTA);
	col->Update();
	bodySprite->Update();
}

void Zombie::Render()
{
	Character::Render();
	bodySprite->Render();
}

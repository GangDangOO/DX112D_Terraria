#include "stdafx.h"

Boss::Boss(ObTileMap* _tileMap)
{
	stat.atk = 10;
	stat.def = 2;
	stat.hp = 800;
	stat.knockBack = 1.0f;

	maxStat = stat;

	tileMap = _tileMap;

	bodySprite = new ObImage(L"NPC_4.png");
	bodySprite->scale = Vector2(110.0f, 986.0f / 6);
	bodySprite->maxFrame = Int2(1, 6);
	col->scale = bodySprite->scale - Vector2(-40.0f, 20.0f);
	bodySprite->SetParentRT(*col);
	col->pivot = OFFSET_N;
	bodySprite->pivot = col->pivot;


	bodySprite->ChangeAnim(ANISTATE::LOOP, 0.5f, false);

	goreSprite[0] = new ObImage(L"Gore_8.png");
	goreSprite[0]->scale = Vector2(46.0f, 32.0f);
	goreSprite[0]->maxFrame = Int2(1, 1);
	goreSprite[0]->frame = Int2(0, 0);
	goreSprite[0]->pivot = col->pivot;

	goreSprite[1] = new ObImage(L"Gore_9.png");
	goreSprite[1]->scale = Vector2(48.0f, 52.0f);
	goreSprite[1]->maxFrame = Int2(1, 1);
	goreSprite[1]->frame = Int2(0, 0);
	goreSprite[1]->pivot = col->pivot;

	goreSprite[2] = new ObImage(L"Gore_10.png");
	goreSprite[2]->scale = Vector2(52.0f, 80.0f);
	goreSprite[2]->maxFrame = Int2(1, 1);
	goreSprite[2]->frame = Int2(0, 0);
	goreSprite[2]->pivot = col->pivot;

	isPhase = false;
	isAtk = false;
	dashTime = 0.0f;
	phaseTime = 0.0f;
	atkN = 0;
}

Boss::~Boss()
{
	SafeDelete(playerCol);
}

void Boss::Move()
{
	move = playerCol->GetWorldPos() - col->GetWorldPos();
	look = move;
	move.y += 75.0f;
	move.Normalize();
	if (!isPhase) {
		move *= 100;
	}
	else {
		move *= 180;
	}
	bodySprite->rotation = atan2(look.x, look.y * -1);
}

void Boss::Dash()
{
	move = playerCol->GetWorldPos() - col->GetWorldPos();
	look = move;
	move.Normalize();
	if (!isPhase) {
		move *= 220;
	}
	else {
		move *= 450;
	}
	bodySprite->rotation = atan2(look.x, look.y * -1);
}

void Boss::Update()
{
	if (!isDead) {
		if (!isPhase) {
			if (bodySprite->frame.y > 2) bodySprite->frame.y = 0;
		}
		else {
			if (bodySprite->frame.y == 0) bodySprite->frame.y = 3;
		}

		if (!isPhase && stat.hp < maxStat.hp * 0.3f) {
			bodySprite->frame.y = 3;
			isPhase = true;
		}
		else if (isPhase && stat.hp >= maxStat.hp * 0.3f) {
			isPhase = false;
		}

		if (atkN == 3) {
			dashTime = 0.0f;
			isAtk = false;
			atkN = 0;
		}

		if (dashTime > 15.0f) {
			phaseTime += DELTA;
			isAtk = true;
		}
		else {
			dashTime += DELTA;
		}

		if (phaseTime > 3.0f) {
			phaseTime = 0.0f;
			atkN++;
			Dash();
		}
		if (!isAtk) {
			Move();
		}
		col->MoveWorldPos(move * DELTA);
	}
	Character::Update();
}

void Boss::Render()
{
	Character::Render();
}
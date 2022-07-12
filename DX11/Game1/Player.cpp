#include "stdafx.h"

Player::Player(ObTileMap* _tileMap)
{
	tileMap = _tileMap;

	playerSprite = new ObImage(L"BestiaryGirl_Default.png");
	playerSprite->maxFrame = Int2(1, 23);
	playerSprite->scale = Vector2(42.0f, 1334.0f / 23);
	col->scale = playerSprite->scale - Vector2(16.0f, 6.0f);
	playerSprite->SetParentRT(*col);
	playerSprite->pivot = col->pivot;

	anim = ANIM::IDLE;

	playerMaxSpeed = 100.0f;
	playerBoostSpeed = 300.0f;
	move = Vector2(0.0f, 0.0f);
}

Player::~Player()
{
	SafeDelete(playerSprite);
}

void Player::Action()
{
	Run();
	if (!fall()) {
		if (move.x < DELTA && -DELTA < move.x)
			ChangeStat(ANIM::IDLE);
	}
	else {
		ChangeStat(ANIM::JUMP);
	}
}

void Player::ChangeStat(ANIM stat)
{
	if (anim != stat) {
		anim = stat;
		if (anim == ANIM::IDLE) {
			playerSprite->frame.y = 0;
			playerSprite->ChangeAnim(ANISTATE::STOP, 0.1f, false);
		}
		else if (anim == ANIM::MOVE) {
			playerSprite->frame.y = 2;
			playerSprite->ChangeAnim(ANISTATE::LOOP, 0.1f, false);
		}
		else if (anim == ANIM::JUMP) {
			playerSprite->frame.y = 2;
			playerSprite->ChangeAnim(ANISTATE::STOP, 0.1f, false);
		}
	}
}

bool Player::Run()
{
	bool isMove = false;
	Int2 temp;
	Int2 lCheckBlock[3], rCheckBlock[3];
	tileMap->WorldPosToTileIdx(col->GetWorldPos(), temp);
	// your now get check left and right phisics
	if (INPUT->KeyPress('A')) {
		ChangeStat(ANIM::MOVE);
		move.x -= playerBoostSpeed * DELTA;
		isMove = true;
		playerSprite->reverseLR = false;
	}
	else if (INPUT->KeyPress('D')) {
		ChangeStat(ANIM::MOVE);
		move.x += playerBoostSpeed * DELTA;
		isMove = true;
		playerSprite->reverseLR = true;
	}
	else {
		if (move.x > DELTA * playerBoostSpeed) move.x -= DELTA * playerBoostSpeed;
		else if (move.x < -DELTA * playerBoostSpeed) move.x += DELTA * playerBoostSpeed;
		else move.x = 0.0f;
	}
	if (move.x > playerMaxSpeed) move.x = playerMaxSpeed;
	else if (move.x < -playerMaxSpeed) move.x = -playerMaxSpeed;
	col->MoveWorldPos(move * DELTA);
	if (playerSprite->frame.y == 13) playerSprite->frame.y = 2;

	return isMove;
}

bool Player::fall()
{
	bool isFall = false;
	Int2 checkDown;
	tileMap->WorldPosToTileIdx(col->GetWorldPos(), checkDown);
	if (tileMap->GetTileState(checkDown) == 0 && tileMap->GetTileState(Int2(checkDown.x - 1, checkDown.y)) == 0) isFall = true;
	if (INPUT->KeyDown(VK_SPACE) && !isFall) {
		isJump = true;
		move.y = 100.0f;
	}
	if (isFall)move.y -= DELTA * 200;
	else if (move.y < DELTA)move.y = 0.0f;

	return isFall;
}

void Player::Update()
{
	Action();
	col->Update();
	playerSprite->Update();
}


void Player::Render()
{
	playerSprite->Render();
	// col->Render();
}


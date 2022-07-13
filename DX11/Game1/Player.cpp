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
	Int2 lCheckBlock, rCheckBlock;
	tileMap->WorldPosToTileIdx(col->GetWorldPos(), temp);
	lCheckBlock = Int2(temp.x - 1, temp.y + 1);
	rCheckBlock = Int2(temp.x + 1, temp.y + 1);
	cout << "L : " << tileMap->GetTileState(lCheckBlock) << '\t';
	cout << "R : " << tileMap->GetTileState(rCheckBlock) << '\n';
	// your now get check left and right phisics
	if (INPUT->KeyPress('A') &&
		tileMap->GetTileState(lCheckBlock) == 0 &&
		tileMap->GetTileState(Int2(lCheckBlock.x, lCheckBlock.y + 1)) == 0 &&
		tileMap->GetTileState(Int2(lCheckBlock.x, lCheckBlock.y + 2)) == 0) {
		ChangeStat(ANIM::MOVE);
		move.x -= playerBoostSpeed * DELTA;
		isMove = true;
		playerSprite->reverseLR = false;
	}
	else if (tileMap->GetTileState(lCheckBlock) == 1 && move.x < 0.0f) {
		move.x = 0.0f;
	}
	else if (INPUT->KeyPress('D') && 
		tileMap->GetTileState(rCheckBlock) == 0 &&
		tileMap->GetTileState(Int2(rCheckBlock.x, rCheckBlock.y + 1)) == 0 &&
		tileMap->GetTileState(Int2(rCheckBlock.x, rCheckBlock.y + 2)) == 0) {
		ChangeStat(ANIM::MOVE);
		move.x += playerBoostSpeed * DELTA;
		isMove = true;
		playerSprite->reverseLR = true;
	}
	else if (tileMap->GetTileState(rCheckBlock) == 1 && move.x > 0.0f) {
		move.x = 0.0f;
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
	Int2 checkTile;
	tileMap->WorldPosToTileIdx(col->GetWorldPos(), checkTile);
	if (tileMap->GetTileState(checkTile) == 0 && tileMap->GetTileState(Int2(checkTile.x - 1, checkTile.y)) == 0) isFall = true;
	if (INPUT->KeyDown(VK_SPACE) && !isFall) {
		isJump = true;
		move.y = 100.0f;
	}
	if (tileMap->GetTileState(Int2(checkTile.x, checkTile.y + 4)) == 1 ||
		tileMap->GetTileState(Int2(checkTile.x - 1, checkTile.y + 4)) == 1)
		move.y = 0.0f;
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


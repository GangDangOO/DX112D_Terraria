#include "stdafx.h"

Player::Player(ObTileMap* _tileMap)
{
	tileMap = _tileMap;

	bodySprite = new ObImage(L"BestiaryGirl_Default.png");
	bodySprite->maxFrame = Int2(1, 23);
	bodySprite->scale = Vector2(42.0f, 1334.0f / 23);
	col->scale = bodySprite->scale - Vector2(18.0f, 6.0f);
	bodySprite->SetParentRT(*col);
	bodySprite->MoveWorldPos(Vector2(0.0f, 0.0f));
	bodySprite->pivot = col->pivot;

	anim = ANIM::IDLE;

	playerMaxSpeed = 100.0f;
	playerBoostSpeed = 300.0f;
	move = Vector2(0.0f, 0.0f);
}

Player::~Player()
{
	SafeDelete(bodySprite);
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
			bodySprite->frame.y = 0;
			bodySprite->ChangeAnim(ANISTATE::STOP, 0.1f, false);
		}
		else if (anim == ANIM::MOVE) {
			bodySprite->frame.y = 2;
			bodySprite->ChangeAnim(ANISTATE::LOOP, 0.1f, false);
		}
		else if (anim == ANIM::JUMP) {
			bodySprite->frame.y = 2;
			bodySprite->ChangeAnim(ANISTATE::STOP, 0.1f, false);
		}
	}
}

bool Player::Run()
{
	bool isMove = false;
	// your now get check left and right phisics
	if (INPUT->KeyPress('A') && !dirCheck.left) {
		ChangeStat(ANIM::MOVE);
		move.x -= playerBoostSpeed * DELTA;
		isMove = true;
		bodySprite->reverseLR = false;
	}
	else if (move.x < 0.0f) {
		move.x = 0.0f;
	}
	else if (INPUT->KeyPress('D') && !dirCheck.right) {
		ChangeStat(ANIM::MOVE);
		move.x += playerBoostSpeed * DELTA;
		isMove = true;
		bodySprite->reverseLR = true;
	}
	else if (move.x > 0.0f) {
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
	if (bodySprite->frame.y == 13) bodySprite->frame.y = 2;

	return isMove;
}

bool Player::fall()
{
	bool isFall = false;
	if (!dirCheck.down) isFall = true;
	else move.y += DELTA * 200.0f;
	if (isFall) move.y -= DELTA * 200.0f;
	else if (INPUT->KeyDown(VK_SPACE)) {
		move.y = 200.0f;
	}
	return isFall;
}

void Player::Update()
{
	Character::Update();
	Action();
	col->Update();
	bodySprite->Update();
}


void Player::Render()
{
	bodySprite->Render();
	// col->Render();
}


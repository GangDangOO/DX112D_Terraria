#include "stdafx.h"

Player::Player()
{
	playerSprite = new ObImage(L"BestiaryGirl_Default.png");
	playerSprite->maxFrame = Int2(1, 23);
	playerSprite->scale = Vector2(42.0f, 1334.0f / 23);
	col->scale = playerSprite->scale - Vector2(16.0f, 6.0f);
	playerSprite->SetParentRT(*col);
	playerSprite->pivot = col->pivot;

	anim = ANIM::IDLE;
}

Player::~Player()
{
	SafeDelete(playerSprite);
}

void Player::Action()
{
	if (INPUT->KeyPress('A')) {
		anim = ANIM::MOVE;
	}
	else if (INPUT->KeyPress('D')) {
		anim = ANIM::MOVE;
	}
	else
		anim = ANIM::IDLE;

	if (anim == ANIM::IDLE) {
		playerSprite->frame.y = 0;
		playerSprite->ChangeAnim(ANISTATE::ONCE, 0.1f);
	}
	else if (anim == ANIM::MOVE) {
		playerSprite->frame.y = 1;
		playerSprite->ChangeAnim(ANISTATE::LOOP, 0.1f);
	}
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

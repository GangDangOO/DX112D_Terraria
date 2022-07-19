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
}

Zombie::~Zombie()
{
	SafeDelete(bodySprite);
}

void Zombie::Update()
{
	Character::Update();
	col->Update();
	bodySprite->Update();
}

void Zombie::Render()
{
	Character::Render();
	bodySprite->Render();
}

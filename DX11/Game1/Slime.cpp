#include "stdafx.h"

Slime::Slime(ObTileMap* _tileMap)
{
	tileMap = _tileMap;

	bodySprite = new ObImage(L"NPC_1.png");
	bodySprite->scale = Vector2(32.0f, 23.0f);
	bodySprite->maxFrame = Int2(1, 2);
	col->scale = bodySprite->scale;
	bodySprite->SetParentRT(*col);
	bodySprite->pivot = col->pivot;

	bodySprite->ChangeAnim(ANISTATE::LOOP, 0.5f, false);
}

Slime::~Slime()
{
	SafeDelete(bodySprite);
}

void Slime::Update()
{
	cout << col->GetWorldPos().x << '\n';
	Character::Update();
	bodySprite->Update();
}

void Slime::Render()
{
	Character::Render();
	bodySprite->Render();
}

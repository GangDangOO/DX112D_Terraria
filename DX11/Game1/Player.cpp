#include "stdafx.h"

Player::Player(ObTileMap* _tileMap)
{
	stat.atk = 0;
	stat.def = 0;
	stat.hp = 100;
	stat.knockBack = 0;

	tileMap = _tileMap;

	bodySprite = new ObImage(L"BestiaryGirl_Default.png");
	bodySprite->maxFrame = Int2(1, 23);
	bodySprite->scale = Vector2(42.0f, 1334.0f / 23);
	col->scale = bodySprite->scale - Vector2(18.0f, 6.0f);
	bodySprite->SetParentRT(*col);
	bodySprite->pivot = col->pivot;

	goreSprite[0] = new ObImage(L"Gore_1219.png");
	goreSprite[0]->maxFrame = Int2(1, 1);
	goreSprite[0]->scale = Vector2(24.0f, 26.0f);
	goreSprite[0]->pivot = col->pivot;

	goreSprite[1] = new ObImage(L"Gore_1220.png");
	goreSprite[1]->maxFrame = Int2(1, 1);
	goreSprite[1]->scale = Vector2(12.0f, 8.0f);
	goreSprite[1]->pivot = col->pivot;

	goreSprite[2] = new ObImage(L"Gore_1221.png");
	goreSprite[2]->maxFrame = Int2(1, 1);
	goreSprite[2]->scale = Vector2(16.0f, 10.0f);
	goreSprite[2]->pivot = col->pivot;

	goreSprite[3] = new ObImage(L"Gore_1222.png");
	goreSprite[3]->maxFrame = Int2(1, 1);
	goreSprite[3]->scale = Vector2(10.0f, 14.0f);
	goreSprite[3]->pivot = col->pivot;

	pick = new ObImage(L"Item_1.png");
	pick->scale = Vector2(32.0f, 32.0f);
	pick->SetParentRT(*col);
	pick->visible = false;

	dirt = new ObImage(L"Item_2.png");
	dirt->scale = Vector2(16.0f, 16.0f);
	dirt->visible = false;
	dirt->SetParentRT(*col);

	rock = new ObImage(L"Item_3.png");
	rock->scale = Vector2(16.0f, 16.0f);
	rock->visible = false;
	rock->SetParentRT(*col);

	sword = new ObImage(L"Item_4.png");
	sword->scale = Vector2(32.0f, 32.0f);
	sword->visible = false;
	sword->SetParentRT(*col);
	sword->MoveWorldPos(Vector2(0.0f, bodySprite->scale.y * 0.4f));

	colSword = new ObRect();
	colSword->scale = sword->scale;
	colSword->visible = false;
	colSword->SetParentRT(*sword);
	colSword->SetWorldPos(Vector2(0.0f, 0.0f));

	touch = new ObImage(L"Item_8.png");
	touch->scale = Vector2(14.0f, 16.0f);
	touch->visible = false;
	touch->SetParentRT(*col);

	bow = new ObImage(L"Item_99.png");
	bow->scale = Vector2(16.0f, 32.0f);
	bow->visible = false;
	bow->SetParentRT(*col);
	bow->MoveWorldPos(Vector2(0.0f, bodySprite->scale.y * 0.4f));

	boss_Spawner = new ObImage(L"Item_43.png");
	boss_Spawner->scale = Vector2(30.0f, 20.0f);
	boss_Spawner->visible = false;
	boss_Spawner->SetParentRT(*col);

	for (int i = 0; i < 10; i++) {
		arrow[i] = new ObImage(L"Item_40.png");
		arrow[i]->scale = Vector2(14.0f, 32.0f);
		arrow[i]->SetParentRT(*col);
		arrow[i]->visible = false;
	}

	anim = ANIM::IDLE;

	playerMaxSpeed = 100.0f * GAMESIZE;
	playerBoostSpeed = 300.0f * GAMESIZE;
	move = Vector2(0.0f, 0.0f);

	jumpTime = 0.0f;
	atkTime = 0.0f;
	blockMiningTime = 0.0f;
}

Player::~Player()
{
	SafeDelete(bodySprite);
	SafeDelete(colSword);
}

void Player::Action()
{
	atkTime -= DELTA;
	ChangeSlot();
	UseItem();
	Run();
	if (!fall()) {
		if (move.x < DELTA && -DELTA < move.x && anim != ANIM::ITEM)
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
		else if (anim == ANIM::ITEM) {
			blockMiningTime = 0.0f;
			bodySprite->frame.y = 20;
			bodySprite->ChangeAnim(ANISTATE::LOOP, 0.1f, false);
		}
	}
}

bool Player::Run()
{
	bool isMove = false;
	if (INPUT->KeyPress('A') && !dirCheck.left) {
		ChangeStat(ANIM::MOVE);
		move.x -= playerBoostSpeed * DELTA;
		isMove = true;

		if (atkTime < 0.0f) {
			bodySprite->reverseLR = false;
			bow->reverseLR = true;
			sword->reverseLR = true;
		}
	}
	else if (move.x < 0.0f && invincibilityTime <= 0.1f) {
		move.x = 0.0f;
	}
	else if (INPUT->KeyPress('D') && !dirCheck.right) {
		ChangeStat(ANIM::MOVE);
		move.x += playerBoostSpeed * DELTA;
		isMove = true;

		if (atkTime < 0.0f) {
			bodySprite->reverseLR = true;
			bow->reverseLR = false;
			sword->reverseLR = false;
		}
	}
	else if (move.x > 0.0f && invincibilityTime <= 0.1f) {
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

	jumpTime -= DELTA;
	if (dirCheck.up && move.y > 0.0f) move.y = 0.0f;
	if (!dirCheck.down) isFall = true;
	else if (jumpTime <= 0.0f && invincibilityTime <= 0.4f) {
		move.y = 0.0f;
	}
	if (isFall) {
		move.y -= DELTA * 300.0f * GAMESIZE;
	}
	else if (INPUT->KeyDown(VK_SPACE)) {
		jumpTime = 0.2f;
		move.y = 200.0f * GAMESIZE;
	}
	return isFall;
}

bool Player::UseItem()
{
	ImGui::Text("%d", itemSlot);
	bool isUse = false;
	Int2 tileMousePos;
	if (INPUT->KeyPress(VK_LBUTTON) && itemSlot != ITEM::NOT) {
		isUse = true;
		ChangeStat(ANIM::ITEM);
		tileMap->WorldPosToTileIdx(INPUT->GetMouseWorldPos(), tileMousePos);
		switch (itemSlot)
		{
		case ITEM::NOT:
			break;
		case ITEM::BLOCK:
			if (tileMousePos.x > 0 && tileMousePos.x < tileMap->GetTileSize().x &&
				tileMousePos.y > 0 && tileMousePos.y < tileMap->GetTileSize().y) {
				if (tileMap->GetTileState(tileMousePos) == TILE_NONE) {
					Tilebuild tb;
					tb.TileAdd(*tileMap, tileMousePos, *map, DIRT, mapLight->lightPower);
					for (int i = tileMousePos.y - 10; i < tileMousePos.y + 10; i++) {
						for (int j = tileMousePos.x - 10; j < tileMousePos.x + 10; j++) {
							mapLight->RemoveLight(Int2(j, i), shadow);
						}
					}
					for (int i = tileMousePos.y - 11; i < tileMousePos.y + 11; i++) {
						for (int j = tileMousePos.x - 11; j < tileMousePos.x + 11; j++) {
							mapLight->SpreadLight(Int2(j, i), tileMap, shadow);
						}
					}
					tileMap->UpdateSub();
					shadow->UpdateSub();
				}
			}
			break;
		case ITEM::TOUCH:
			if (tileMousePos.x > 0 && tileMousePos.x < tileMap->GetTileSize().x &&
				tileMousePos.y > 0 && tileMousePos.y < tileMap->GetTileSize().y) {
				if (tileMap->GetTileState(tileMousePos) == TILE_NONE) {
					Tilebuild tb;
					tb.TileAdd(*tileMap, tileMousePos, *map, TOUCH, mapLight->lightPower);
					for (int i = tileMousePos.y - 10; i < tileMousePos.y + 10; i++) {
						for (int j = tileMousePos.x - 10; j < tileMousePos.x + 10; j++) {
							mapLight->RemoveLight(Int2(j, i), shadow);
						}
					}
					for (int i = tileMousePos.y - 11; i < tileMousePos.y + 11; i++) {
						for (int j = tileMousePos.x - 11; j < tileMousePos.x + 11; j++) {
							mapLight->SpreadLight(Int2(j, i), tileMap, shadow);
						}
					}
					tileMap->UpdateSub();
					shadow->UpdateSub();
				}
			}
			break;
		case ITEM::PICK:
			if (tileMousePos.x > 0 && tileMousePos.x < tileMap->GetTileSize().x &&
				tileMousePos.y > 0 && tileMousePos.y < tileMap->GetTileSize().y) {
				if (tileMap->GetTileState(tileMousePos) == TILE_WALL || map->GetType(tileMousePos) == TOUCH || map->GetType(tileMousePos) == FLOWER) {
					blockMiningTime += DELTA;
					if (blockMiningTime >= 0.5f) {
						blockMiningTime = 0.0f;
						if (map->MiningBlock(tileMousePos)) {
							Tilebuild tb;
							tb.TileRemove(*tileMap, tileMousePos, *map,mapLight->lightPower, isWall);
							for (int i = tileMousePos.y - 10; i < tileMousePos.y + 10; i++) {
								for (int j = tileMousePos.x - 10; j < tileMousePos.x + 10; j++) {
									mapLight->RemoveLight(Int2(j, i), shadow);
								}
							}
							for (int i = tileMousePos.y - 11; i < tileMousePos.y + 11; i++) {
								for (int j = tileMousePos.x - 11; j < tileMousePos.x + 11; j++) {
									mapLight->SpreadLight(Int2(j, i), tileMap, shadow);
								}
							}
							tileMap->UpdateSub();
							shadow->UpdateSub();
						}
					}
				}
			}
			break;
		case ITEM::SWORD:
			if (atkTime < 0.0f) {
				atkTime = 1.0f;
				if (bodySprite->reverseLR) sword->SetWorldPos(col->GetWorldPos() + Vector2(20.0, bodySprite->scale.y * 0.6f));
				else sword->SetWorldPos(col->GetWorldPos() + Vector2(-20.0, bodySprite->scale.y * 0.6f));
				sword->visible = true;
				stat.atk = 8;
			}
			break;
		case ITEM::BOW:
			if (atkTime < 0.0f) {
				atkTime = 1.0f;
				bodySprite->ChangeAnim(ANISTATE::STOP, 0.1f, false);
				bodySprite->frame.y = 21;
				bow->visible = true;
				stat.atk = 5;
			}
			break;
		case ITEM::MAGIC:
			if (atkTime < 0.0f) {
				atkTime = 1.0f;
			}
			break;
		default:
			break;
		}
	}
	else if (anim != ANIM::MOVE){
		ChangeStat(ANIM::IDLE);
	}
	if (bow->visible) {
		if (!bow->reverseLR) {
			bow->SetWorldPosX(col->GetWorldPos().x + 10);
		}
		else {
			bow->SetWorldPosX(col->GetWorldPos().x - 10);
		}
	}
	if (sword->visible) {
		if (!sword->reverseLR) {
			sword->MoveWorldPos(Vector2(10 * DELTA, -20 * DELTA));
		}
		else {
			sword->MoveWorldPos(Vector2(-10 * DELTA, -20 * DELTA));
		}
	}
	if (atkTime < 0.0f) {
		if (bow->visible) bow->visible = false;
		if (sword->visible) sword->visible = false;
	}

	if (isUse && bodySprite->frame.y == 0) bodySprite->frame.y = 20;
	return isUse;
}

void Player::ChangeSlot()
{
	if (INPUT->KeyDown('1')) itemSlot = ITEM::BLOCK;
	if (INPUT->KeyDown('2')) itemSlot = ITEM::PICK;
	if (INPUT->KeyDown('3')) itemSlot = ITEM::TOUCH;
	if (INPUT->KeyDown('4')) itemSlot = ITEM::SWORD;
	if (INPUT->KeyDown('5')) itemSlot = ITEM::BOW;
	if (INPUT->KeyDown('6')) itemSlot = ITEM::MAGIC;
	if (INPUT->KeyDown('0')) itemSlot = ITEM::NOT;
}

void Player::Update()
{
	Character::Update();
	if (!isDead) {
		Action();
		col->Update();
		bodySprite->Update();
		bow->Update();
		sword->Update();
		colSword->Update();
		for (int i = 0; i < 10; i++) {
			arrow[i]->Update();
		}
	}
}


void Player::Render()
{
	Character::Render();
	if (!isDead) {
		bodySprite->Render();
		bow->Render();
		sword->Render();
		for (int i = 0; i < 10; i++) {
			arrow[i]->Render();
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			goreSprite[i]->Render();
		}
	}
	/*col->Render();*/
}


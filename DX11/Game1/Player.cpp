#include "stdafx.h"

Player::Player(ObTileMap* _tileMap)
{
	tileMap = _tileMap;

	bodySprite = new ObImage(L"BestiaryGirl_Default.png");
	bodySprite->maxFrame = Int2(1, 23);
	bodySprite->scale = Vector2(42.0f, 1334.0f / 23);
	col->scale = bodySprite->scale - Vector2(18.0f, 6.0f);
	bodySprite->SetParentRT(*col);
	bodySprite->pivot = col->pivot;

	anim = ANIM::IDLE;

	playerMaxSpeed = 100.0f * GAMESIZE;
	playerBoostSpeed = 300.0f * GAMESIZE;
	move = Vector2(0.0f, 0.0f);

	jumpTime = 0.0f;
	blockMiningTime = 0.0f;
}

Player::~Player()
{
	SafeDelete(bodySprite);
}

void Player::Action()
{
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

	jumpTime -= DELTA;
	if (dirCheck.up && move.y > 0.0f) move.y = 0.0f;
	if (!dirCheck.down) isFall = true;
	else if (jumpTime <= 0.0f) {
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
				}
			}
			tileMap->UpdateSub();
			shadow->UpdateSub();
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
				}
			}
			tileMap->UpdateSub();
			shadow->UpdateSub();
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
						}
					}
				}
			}
			tileMap->UpdateSub();
			shadow->UpdateSub();
			break;
		case ITEM::SWORD:
			break;
		case ITEM::BOW:
			break;
		case ITEM::MAGIC:
			break;
		default:
			break;
		}
	}
	else if (anim != ANIM::MOVE) ChangeStat(ANIM::IDLE);

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
	Action();
	col->Update();
	bodySprite->Update();
}


void Player::Render()
{
	Character::Render();
	bodySprite->Render();
	/*col->Render();*/
}


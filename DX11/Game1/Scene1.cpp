#include "stdafx.h"

Scene1::Scene1()
{
	
}

Scene1::~Scene1()
{
	
}

void Scene1::Init()
{
	//mapSize = Int2(App.GetWidth() * 0.2, App.GetHeight() * 0.2);
	mapSize = Int2(1000, 400);
	unsigned int seed = RANDOM->Int(200, 350);
	map = new Map(mapSize, seed);
	mapLight = new MapLight(mapSize);
	block = new ObTileMap();
	map->tileMap = block;
	wall = new ObTileMap();
	shadow = new ObTileMap();
	mapWall = new MapWall(mapSize);
	block->scale = Vector2(16.0f, 16.0f) * GAMESIZE;
	wall->scale = Vector2(16.0f, 16.0f) * GAMESIZE;
	shadow->scale = Vector2(16.0f, 16.0f) * GAMESIZE;
	bg = new BackGround(Vector2(mapSize.x * block->scale.x, mapSize.y * block->scale.y));
	block->SetWorldPos(Vector2(-(mapSize.x * block->scale.x) * 0.5, -(mapSize.y * block->scale.y) * 0.5));
	block->ResizeTile(mapSize);
	wall->SetWorldPos(Vector2(-(mapSize.x * wall->scale.x) * 0.5, -(mapSize.y * wall->scale.y) * 0.5));
	wall->ResizeTile(mapSize);
	shadow->SetWorldPos(Vector2(-(mapSize.x * wall->scale.x) * 0.5, -(mapSize.y * wall->scale.y) * 0.5));
	shadow->ResizeTile(mapSize);
	//// 배치
	for (int y = 0; y < mapSize.y; y++) {
		for (int x = 0; x < mapSize.x; x++) {
			switch (map->GetType(Int2(x, y)))
			{
			case AIR:
				block->SetTile(Int2(x, y), Int2(1, 1), AIR, TILE_NONE);
				break;
			case DIRT:
				block->SetTile(Int2(x, y), Int2(1, 1), DIRT, TILE_WALL);
				break;
			case ROCK:
				block->SetTile(Int2(x, y), Int2(1, 1), ROCK, TILE_WALL);
				break;
			default:
				break;
			}
			if (mapWall->isWall[y][x] == true) {
				wall->SetTile(Int2(x, y), Int2(1, 1), DIRT, TILE_NONE);
			}
			else {
				wall->SetTile(Int2(x, y), Int2(1, 1), AIR, TILE_WALL);
			}
			shadow->SetTile(Int2(x, y), Int2(1, 1), 6);
		}
	}
	mapLight->CalcLight(map, mapWall->isWall);
	// 블럭 디테일
	for (int y = 0; y < mapSize.y; y++) {
		for (int x = 0; x < mapSize.x; x++) {
			tb.TileArrangement(*block, Int2(x, y), map->GetType(Int2(x, y)), *map, mapLight->lightPower);
			if (y > mapSize.y * 0.64 && map->GetType(Int2(x, y)) == DIRT) {
				tb.DirtToGrass(*block, Int2(x, y));
			}
			// 그림자 계산
			if (mapLight->lightPower[y][x] == 0)
				mapLight->SpreadLight(Int2(x, y), block, shadow);
		}
	}
	block->UpdateSub();
	wall->UpdateSub();
	shadow->UpdateSub();

	block->Update();
	// 플레이어 배치
	player = new Player(block);
	player->map = map;
	player->mapLight = mapLight;
	player->shadow = shadow;
	player->isWall = mapWall->isWall;
	player->bodySprite->scale *= GAMESIZE;
	player->col->scale *= GAMESIZE;
	player->Spawn();

	player->col->Update();

	for (int i = 0; i < 5; i++) {
		slime[i] = new Slime(block);
		slime[i]->playerCol = player->col;
		slime[i]->bodySprite->scale *= GAMESIZE;
		slime[i]->col->scale *= GAMESIZE;
		slime[i]->Spawn(player->col->GetWorldPos() + Vector2(i * 20, 0.0f));

		zombie[i] = new Zombie(block);
		zombie[i]->playerCol = player->col;
		zombie[i]->bodySprite->scale *= GAMESIZE;
		zombie[i]->col->scale *= GAMESIZE;
		zombie[i]->Spawn(player->col->GetWorldPos() + Vector2(i * 20, 0.0f));
	}
	boss = new Boss(block);
	boss->playerCol = player->col;
	boss->bodySprite->scale *= GAMESIZE;
	boss->col->scale *= GAMESIZE;
	boss->isDead = true;

	CAM->position = player->col->GetWorldPos();

	shadowMod = false;
	player->camMod = &camMod;
}

void Scene1::Release()
{
	map->Release();
	SafeDelete(mapLight);
	SafeDelete(block);
	SafeDelete(wall);
	SafeDelete(shadow);
	SafeDelete(player);
	for (int i = 0; i < 5; i++) {
		SafeDelete(slime[i]);
		SafeDelete(zombie[i]);
	}
	SafeDelete(boss);
}

void Scene1::Update()
{
	// ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());

	if (INPUT->KeyDown('V')) shadowMod = !shadowMod;
	// 카메라 움직임
	if (INPUT->KeyDown('C')) camMod = !camMod;
	if (camMod) {
		Vector2 move = Vector2(0.0, 0.0);
		if (INPUT->KeyPress('W'))
			move.y += 1;
		if (INPUT->KeyPress('A'))
			move.x -= 1;
		if (INPUT->KeyPress('S'))
			move.y -= 1;
		if (INPUT->KeyPress('D'))
			move.x += 1;
		move.Normalize();
		CAM->position += move * DELTA * 500;
	}
	else {
		CAM->position = player->col->GetWorldPos();
	}
	// Hit Player
	for (int i = 0; i < 5; i++) {
		if (!slime[i]->isDead && slime[i]->col->Intersect(player->col)) {
			player->Hit(slime[i]->stat, slime[i]->col->GetWorldPos());
		}
		if (!zombie[i]->isDead && zombie[i]->col->Intersect(player->col)) {
			player->Hit(zombie[i]->stat, zombie[i]->col->GetWorldPos());
		}
		// Hit Enemy
		if (!slime[i]->isDead && player->isAtk && player->colSword->Intersect(slime[i]->col)) {
			slime[i]->Hit(player->stat, player->col->GetWorldPos());
		}
		if (!zombie[i]->isDead && player->isAtk && player->colSword->Intersect(zombie[i]->col)) {
			zombie[i]->Hit(player->stat, player->col->GetWorldPos());
		}
	}
	if (!boss->isDead && boss->col->Intersect(player->col)) {
		player->Hit(boss->stat, boss->col->GetWorldPos());
	}
	if (!boss->isDead && player->isAtk && player->colSword->Intersect(boss->col)) {
		boss->Hit(player->stat, player->col->GetWorldPos());
	}
	for (int i = 0; i < 10; i++) {
		if (player->arrow[i]->visible) {
			if (!boss->isDead && player->colArrow[i]->Intersect(boss->col)) {
				boss->Hit(player->stat, player->colArrow[i]->GetWorldPos());
				player->arrow[i]->visible = false;
				player->arrowPos[i] = Vector2(0.0f, 0.0f);
			}
			for (int j = 0; j < 5; j++) {
				if (!slime[j]->isDead && player->colArrow[i]->Intersect(slime[j]->col)) {
					slime[j]->Hit(player->stat, player->colArrow[i]->GetWorldPos());
					player->arrow[i]->visible = false;
					player->arrowPos[i] = Vector2(0.0f, 0.0f);
				}
				if (!zombie[j]->isDead && player->colArrow[i]->Intersect(zombie[j]->col)) {
					zombie[j]->Hit(player->stat, player->colArrow[i]->GetWorldPos());
					player->arrow[i]->visible = false;
					player->arrowPos[i] = Vector2(0.0f, 0.0f);
				}
			}
		}
	}

	if (player->itemSlot == ITEM::BOSS_CALL && INPUT->KeyDown(VK_LBUTTON) && boss->isDead) {
		boss->Spawn(player->col->GetWorldPos());
	}

	bg->Update();
	wall->Update();
	block->Update();
	map->Update();
	player->Update();
	for (int i = 0; i < 5; i++) {
		slime[i]->Update();
		zombie[i]->Update();
	}
	boss->Update();
	shadow->Update();
}

void Scene1::LateUpdate()
{
	
}

void Scene1::Render()
{
	bg->Render();
	if (!shadowMod) wall->Render();
	block->Render();
	map->Render();
	player->Render();
	for (int i = 0; i < 5; i++) {
		slime[i]->Render();
		zombie[i]->Render();
	}
	boss->Render();
	if(!shadowMod) shadow->Render();
}

void Scene1::ResizeScreen()
{
}

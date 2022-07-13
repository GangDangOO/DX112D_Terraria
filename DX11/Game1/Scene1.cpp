#include "stdafx.h"

#define size 1;

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
	wall = new ObTileMap();
	mapWall = new MapWall(mapSize);
	block->scale = Vector2(16.0f, 16.0f) * size;
	wall->scale = Vector2(16.0f, 16.0f) * size;
	bg = new BackGround(Vector2(mapSize.x * block->scale.x, mapSize.y * block->scale.y));
	block->SetWorldPos(Vector2(-(mapSize.x * block->scale.x) * 0.5, -(mapSize.y * block->scale.y) * 0.5));
	block->ResizeTile(mapSize);
	wall->SetWorldPos(Vector2(-(mapSize.x * wall->scale.x) * 0.5, -(mapSize.y * wall->scale.y) * 0.5));
	wall->ResizeTile(mapSize);
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
		}
	}
	mapLight->CalcLight(map, mapWall->isWall, block, wall);
	// 블럭 디테일
	for (int y = 0; y < mapSize.y; y++) {
		for (int x = 0; x < mapSize.x; x++) {
			tb.TileArrangement(*block, Int2(x, y), map->GetType(Int2(x, y)), *map, mapLight->lightPower);
			wall->SetLight(Int2(x, y), mapLight->lightPower[y][x]);
			if (y > mapSize.y * 0.64 && map->GetType(Int2(x, y)) == DIRT) {
				tb.DirtToGrass(*block, Int2(x, y), mapLight->lightPower);
			}
		}
	}
	block->UpdateSub();
	wall->UpdateSub();
	addBlockType = DIRT;
	block->Update();
	// 플레이어 배치
	player = new Player(block);
	player->playerSprite->scale *= size;
	player->col->scale *= size;
	{
		Vector2 pos = Vector2(0.0f, 1350.0f);
		Int2 intpos;
		block->WorldPosToTileIdx(pos, intpos);
		while (true) {
			intpos.y--;
			if (block->GetTileState(intpos) == TILE_WALL) {
				intpos = Int2(block->tileSize.x * 0.5 - intpos.x, block->tileSize.y * 0.5 - intpos.y);
				pos = Vector2(intpos.x * block->scale.x, intpos.y * block->scale.y);
				pos *= -1;
				pos += Vector2(block->scale.x * 0.5, block->scale.y);
				player->col->SetWorldPos(pos);
				break;
			}
		}
	}

	CAM->position = player->col->GetWorldPos();
}

void Scene1::Release()
{
	map->Release();
	SafeDelete(mapLight);
	SafeDelete(block);
	SafeDelete(wall);
	SafeDelete(player);
}

void Scene1::Update()
{
	// ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());

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


	// 설치블럭변경
	if (INPUT->KeyPress('1')) {
		addBlockType = DIRT;
	}
	if (INPUT->KeyPress('2')) {
		addBlockType = ROCK;
	}
	if (INPUT->KeyPress('3')) {
		addBlockType = TOUCH;
	}
	
	Int2 tileMousePos;
	if (INPUT->KeyPress(VK_LBUTTON)) {
		block->WorldPosToTileIdx(INPUT->GetMouseWorldPos(), tileMousePos);
		if (tileMousePos.x > 0 && tileMousePos.x < mapSize.x &&
			tileMousePos.y > 0 && tileMousePos.y < mapSize.y) {
			if (block->GetTileState(tileMousePos) == TILE_NONE) {
				float light = mapLight->GetLightPower(Int2(tileMousePos.x, tileMousePos.y));
				tb.TileAdd(*block, tileMousePos, *map, addBlockType, mapLight->lightPower);
				if (map->GetType(tileMousePos) == TOUCH) {
					mapLight->SpreadLight(tileMousePos, block, wall);

				}
				else {
					for (int i = tileMousePos.y - 10; i < tileMousePos.y + 10; i++) {
						for (int j = tileMousePos.x - 10; j < tileMousePos.x + 10; j++) {
							mapLight->RemoveLight(Int2(j, i), block, wall);
						}
					}
					for (int i = tileMousePos.y - 11; i < tileMousePos.y + 11; i++) {
						for (int j = tileMousePos.x - 11; j < tileMousePos.x + 11; j++) {
							mapLight->SpreadLight(Int2(j, i), block, wall);
						}
					}
				}
				block->UpdateSub();
				wall->UpdateSub();
			}
		}
	}
	if (INPUT->KeyPress(VK_RBUTTON)) {
		block->WorldPosToTileIdx(INPUT->GetMouseWorldPos(), tileMousePos);
		if (tileMousePos.x > 0 && tileMousePos.x < mapSize.x &&
			tileMousePos.y > 0 && tileMousePos.y < mapSize.y) {
			if (map->GetType(tileMousePos) == TOUCH) {
				float light = 0;
				tb.TileRemove(*block, tileMousePos, *map, mapLight->lightPower, mapWall->isWall);
				for (int i = tileMousePos.y - 10; i < tileMousePos.y + 10; i++) {
					for (int j = tileMousePos.x - 10; j < tileMousePos.x + 10; j++) {
						mapLight->RemoveLight(Int2(j, i), block, wall);
					}
				}
				for (int i = tileMousePos.y - 11; i < tileMousePos.y + 11; i++) {
					for (int j = tileMousePos.x - 11; j < tileMousePos.x + 11; j++) {
						if (mapLight->lightPower[i][j] != 0)
							mapLight->SpreadLight(Int2(j, i), block, wall);
					}
				}
				block->UpdateSub();
				wall->UpdateSub();
			}
			else if (block->GetTileState(tileMousePos) == TILE_WALL) {
				float light = mapLight->GetLightPower(Int2(tileMousePos.x, tileMousePos.y));
				tb.TileRemove(*block, tileMousePos, *map, mapLight->lightPower, mapWall->isWall);
				for (int i = tileMousePos.y - 10; i < tileMousePos.y + 10; i++) {
					for (int j = tileMousePos.x - 10; j < tileMousePos.x + 10; j++) {
						if (mapLight->lightPower[i][j] != 0)
							mapLight->SpreadLight(Int2(j, i), block, wall);
					}
				}
				block->UpdateSub();
				wall->UpdateSub();
			}
		}
	}

	bg->Update();
	wall->Update();
	block->Update();
	if (!camMod) player->Update();
}

void Scene1::LateUpdate()
{
	
}

void Scene1::Render()
{
	bg->Render();
	wall->Render();
	block->Render();
	player->Render();
}

void Scene1::ResizeScreen()
{
}

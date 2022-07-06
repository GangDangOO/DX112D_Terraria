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
	wall = new ObTileMap();
	mapWall = new MapWall(mapSize);
	block->scale = Vector2(16.0f, 16.0f);
	wall->scale = Vector2(16.0f, 16.0f);
	bg = new BackGround(Vector2(mapSize.x * block->scale.x, mapSize.y * block->scale.y));
	block->SetWorldPos(Vector2(-(mapSize.x * block->scale.x) * 0.5, -(mapSize.y * block->scale.y) * 0.5));
	block->ResizeTile(mapSize);
	wall->SetWorldPos(Vector2(-(mapSize.x * wall->scale.x) * 0.5, -(mapSize.y * wall->scale.y) * 0.5));
	wall->ResizeTile(mapSize);
	mapLight->CalcLight(map, mapWall->isWall, block, wall);
	//// ��ġ
	for (int y = 0; y < mapSize.y; y++) {
		for (int x = 0; x < mapSize.x; x++) {
			float light = mapLight->GetLightPower(Int2(x, y)) * 0.05f;
			switch (map->GetType(Int2(x, y)))
			{
			case AIR:
				block->SetTile(Int2(x, y), Int2(1, 1), AIR, TILE_NONE, Color(light, light, light));
				break;
			case DIRT:
				block->SetTile(Int2(x, y), Int2(1, 1), DIRT, TILE_WALL, Color(light, light, light));
				break;
			case ROCK:
				block->SetTile(Int2(x, y), Int2(1, 1), ROCK, TILE_WALL, Color(light, light, light));
				break;
			default:
				break;
			}
			if (mapWall->isWall[y][x] == true) {
				wall->SetTile(Int2(x, y), Int2(1, 1), DIRT, TILE_NONE, Color(light, light, light));
			}
			else {
				wall->SetTile(Int2(x, y), Int2(1, 1), AIR, TILE_NONE, Color(light, light, light));
			}
		}
	}
	// �� ������
	for (int y = 0; y < mapSize.y; y++) {
		for (int x = 0; x < mapSize.x; x++) {
			float light = mapLight->GetLightPower(Int2(x, y)) * 0.05f;
			tb.TileArrangement(*block, Int2(x, y), map->GetType(Int2(x, y)), *map, mapLight->lightPower);
			if (y > mapSize.y * 0.64 && map->GetType(Int2(x, y)) == DIRT) {
				tb.DirtToGrass(*block, Int2(x, y), mapLight->lightPower);
			}
		}
	}
	block->UpdateSub();
	wall->UpdateSub();
	addBlockType = DIRT;
}

void Scene1::Release()
{
	map->Release();
	SafeDelete(mapLight);
	SafeDelete(block);
	SafeDelete(wall);
}

void Scene1::Update()
{
	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	
	// ī�޶� ������
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
	
	// ��ġ������
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
			// cout << tileMousePos.x << " : " << tileMousePos.y << endl;
			if (block->GetTileState(tileMousePos) == TILE_NONE) {
				float light = mapLight->GetLightPower(Int2(tileMousePos.x, tileMousePos.y)) * 0.05f;
				tb.TileAdd(*block, tileMousePos, *map, addBlockType, mapLight->lightPower);
				mapLight->SpreadLight(tileMousePos, block, wall);
				block->UpdateSub();
				wall->UpdateSub();
			}
		}
	}
	if (INPUT->KeyPress(VK_RBUTTON)) {
		block->WorldPosToTileIdx(INPUT->GetMouseWorldPos(), tileMousePos);
		if (tileMousePos.x > 0 && tileMousePos.x < mapSize.x &&
			tileMousePos.y > 0 && tileMousePos.y < mapSize.y) {
			cout << tileMousePos.x << " : " << tileMousePos.y << endl;
			if (block->GetTileState(tileMousePos) == TILE_WALL) {
				float light = mapLight->GetLightPower(Int2(tileMousePos.x, tileMousePos.y)) * 0.05f;
				tb.TileRemove(*block, tileMousePos, *map, mapLight->lightPower);
				block->UpdateSub();
				wall->UpdateSub();
			}
		}
	}

	bg->Update();
	wall->Update();
	block->Update();
}

void Scene1::LateUpdate()
{
	
}

void Scene1::Render()
{
	bg->Render();
	wall->Render();
	block->Render();
}

void Scene1::ResizeScreen()
{
}

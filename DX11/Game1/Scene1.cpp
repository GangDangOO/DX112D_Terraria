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
	block = new ObTileMap();
	block->scale = Vector2(16.0f, 16.0f);
	bg = new BackGround(Vector2(mapSize.x * block->scale.x, mapSize.y * block->scale.y));
	block->SetWorldPos(Vector2(-(mapSize.x * block->scale.x) * 0.5, -(mapSize.y * block->scale.y) * 0.5));
	block->ResizeTile(mapSize);
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
			
		}
	}
	// 흙 디테일
	for (int y = 1; y < mapSize.y - 1; y++) {
		for (int x = 1; x < mapSize.x - 1; x++) {
			tb.TileArrangement(*block, Int2(x, y), map->GetType(Int2(x, y)));
		}
	}
	block->UpdateSub();
}

void Scene1::Release()
{
	map->Release();
	SafeDelete(block);
}

void Scene1::Update()
{
	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());

	// if(INPUT->KeyDown())

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
	
	
	Int2 tileMousePos;
	if (INPUT->KeyPress(VK_LBUTTON)) {
		block->WorldPosToTileIdx(INPUT->GetMouseWorldPos(), tileMousePos);
		cout << tileMousePos.x << " : " << tileMousePos.y << endl;
		if (block->GetTileState(tileMousePos) == TILE_NONE) {
			tb.TileAdd(*block, tileMousePos, *map);
			block->UpdateSub();
		}
	}
	if (INPUT->KeyPress(VK_RBUTTON)) {
		block->WorldPosToTileIdx(INPUT->GetMouseWorldPos(), tileMousePos);
		cout << tileMousePos.x << " : " << tileMousePos.y << endl;
		if (block->GetTileState(tileMousePos) == TILE_WALL) {
			tb.TileRemove(*block, tileMousePos, *map);
			block->UpdateSub();
		}
	}

	bg->Update();
	block->Update();
	map->Update();
}

void Scene1::LateUpdate()
{
	
}

void Scene1::Render()
{
	bg->Render();
	block->Render();
	map->Render();
}

void Scene1::ResizeScreen()
{
}

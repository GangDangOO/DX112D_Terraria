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
	mapSize = Int2(200, 100);
	unsigned int seed = RANDOM->Int(200, 350);
	map = new Map(mapSize, seed);
	block = new ObTileMap();
	block->scale = Vector2(16.0f, 16.0f) * 2;
	block->SetWorldPos(Vector2(-(mapSize.x * block->scale.x) * 0.5, -(mapSize.y * block->scale.y) * 0.5));
	block->ResizeTile(mapSize);
	// 배치
	for (int y = 0; y < mapSize.y; y++) {
		for (int x = 0; x < mapSize.x; x++) {
			if (!map->IsThisWall(Int2(x, y))) {
				block->SetTile(Int2(x, y), Int2(1, 1), 1, TILE_NONE);
			}
			else {
				block->SetTile(Int2(x, y), Int2(1, 1), 0, TILE_WALL);
			}
		}
	}
	// 흙 디테일
	for (int y = 1; y < mapSize.y - 1; y++) {
		for (int x = 1; x < mapSize.x - 1; x++) {
			if (block->GetTileState(Int2(x, y)) == TileState::TILE_WALL) {
				bool l = false, r = false, u = false, d = false;
				int n = 0;
				if (block->GetTileState(Int2(x - 1, y)) == TileState::TILE_NONE) l = true;
				if (block->GetTileState(Int2(x + 1, y)) == TileState::TILE_NONE) r = true;
				if (block->GetTileState(Int2(x, y - 1)) == TileState::TILE_NONE) d = true;
				if (block->GetTileState(Int2(x, y + 1)) == TileState::TILE_NONE) u = true;
				if (l) n = 4;
				if (r) n = 6;
				if (u) n = 8;
				if (d) n = 2;
				if (l && u) n = 7;
				if (u && r) n = 9;
				if (r && d) n = 3;
				if (d && l) n = 1;
				if (l && u && r) n = 18;
				if (u && r && d) n = 16;
				if (r && d && l) n = 12;
				if (d && l && u) n = 14;
				if (l && r && u && d) n = 5;
				if (!l && !r && !u && !d) n = 0;
				switch (n)
				{
				case 0:
					block->SetTile(Int2(x, y), Int2(1, 1), 0, TILE_WALL);
					break;
				case 1:
					block->SetTile(Int2(x, y), Int2(0, 4), 0, TILE_WALL);
					break;
				case 2:
					block->SetTile(Int2(x, y), Int2(2, 2), 0, TILE_WALL);
					break;
				case 3:
					block->SetTile(Int2(x, y), Int2(1, 4), 0, TILE_WALL);
					break;
				case 4:
					block->SetTile(Int2(x, y), Int2(0, 1), 0, TILE_WALL);
					break;
				case 5:
					block->SetTile(Int2(x, y), Int2(9, 3), 0, TILE_WALL);
					break;
				case 6:
					block->SetTile(Int2(x, y), Int2(4, 1), 0, TILE_WALL);
					break;
				case 7:
					block->SetTile(Int2(x, y), Int2(0, 3), 0, TILE_WALL);
					break;
				case 8:
					block->SetTile(Int2(x, y), Int2(2, 0), 0, TILE_WALL);
					break;
				case 9:
					block->SetTile(Int2(x, y), Int2(1, 3), 0, TILE_WALL);
					break;
				case 18:
					block->SetTile(Int2(x, y), Int2(6, 0), 0, TILE_WALL);
					break;
				case 16:
					block->SetTile(Int2(x, y), Int2(12, 0), 0, TILE_WALL);
					break;
				case 12:
					block->SetTile(Int2(x, y), Int2(6, 3), 0, TILE_WALL);
					break;
				case 14:
					block->SetTile(Int2(x, y), Int2(9, 0), 0, TILE_WALL);
					break;
				default:
					break;
				}
			}
		}
	}
}

void Scene1::Release()
{
	map->Release();
	SafeDelete(block);
}

void Scene1::Update()
{
	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
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
	CAM->position += move * DELTA * 200;

	block->Update();
	map->Update();
}

void Scene1::LateUpdate()
{
	
}

void Scene1::Render()
{
	block->Render();
	map->Render();
}

void Scene1::ResizeScreen()
{
}

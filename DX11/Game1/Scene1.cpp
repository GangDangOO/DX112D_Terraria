#include "stdafx.h"

Scene1::Scene1()
{
	
}

Scene1::~Scene1()
{
	
}

void Scene1::Init()
{
	map = new Map(Int2(App.GetWidth() / 5, App.GetHeight() / 5), 230);
}

void Scene1::Release()
{
	map->Release();
}

void Scene1::Update()
{
	map->Update();
}

void Scene1::LateUpdate()
{
	
}

void Scene1::Render()
{
	map->Render();
}

void Scene1::ResizeScreen()
{
}

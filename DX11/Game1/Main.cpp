#include "stdafx.h"
#include "Main.h"
void Main::Init()
{
	{
		Scene1 * temp = new Scene1();
		SCENE->AddScene("SC0", temp);
	}
	SCENE->ChangeScene("SC0");
}

void Main::Release()
{
	
}


void Main::Update()
{
	SCENE->Update();
}

void Main::LateUpdate()
{
	SCENE->LateUpdate();

}

void Main::Render()
{
	SCENE->Render();
}

void Main::ResizeScreen()
{

}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	App.SetAppName(L"Game1");
	App.SetInstance(instance);
	App.InitWidthHeight(1400.0f, 700.0f);
	Main * main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}
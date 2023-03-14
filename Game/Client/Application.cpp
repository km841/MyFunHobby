#include "pch.h"
#include "Application.h"
#include "Engine.h"
#include "Scenes.h"

void Application::Init(const WindowInfo& wInfo)
{
	g_pEngine->Init(wInfo);
}

void Application::Awake()
{
}

void Application::Update()
{
	g_pEngine->Update();
	g_pEngine->Render();
}

void Application::Destroy()
{
	g_pEngine->Destroy();
}



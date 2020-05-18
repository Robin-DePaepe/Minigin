#include "TestScene2.h"

TestScene2::TestScene2(const std::wstring& name)
	:Scene{ name }
{
}

void TestScene2::Initialize()
{
	ShowFpsCounter(true);
}

void TestScene2::Update()
{
	ShowFpsCounter(true);
}

void TestScene2::Render() const
{
}



void TestScene2::SceneActivated()
{
}

void TestScene2::SceneDeactivated()
{
}

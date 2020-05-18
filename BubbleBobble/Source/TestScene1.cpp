#include "TestScene1.h"

TestScene1::TestScene1(const std::wstring& name)
	:Scene{name}
	,m_Test{"Source/Resources/Sounds/arena_champ.wav"}
	,m_stream{"Source/Resources/Sounds/happy.mp3"}
{
}

void TestScene1::Initialize()
{

}

void TestScene1::Update()
{
}

void TestScene1::Render() const
{
}



void TestScene1::SceneActivated()
{
	m_stream.Play(true);
	m_Test.Play(2);
}

void TestScene1::SceneDeactivated()
{
}

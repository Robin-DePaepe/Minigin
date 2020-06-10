#include "TestScene2.h"
#include "TextLocalizer.h"
#include <iostream>

TestScene2::TestScene2(const std::wstring& name)
	:Scene{ name }
	, localizer{ new TextLocalizer() }
{
}

void TestScene2::Initialize()
{
	ShowFpsCounter(true);
	// Load the file with Dutch translations, 
	localizer->Load("Resources/loca.csv", "nl-be");
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
		TestLoca(localizer);
}

void TestScene2::SceneDeactivated()
{
	// Load the British translations
	localizer->Load("Resources/gloca.csv", "en-uk");

	// test it
	TestLoca(localizer);
}

void TestScene2::TestLoca(ITextLocalizer* localizer)
{
	std::cout << localizer->Get("start") << std::endl;

	std::cout << localizer->Get("askforname") << std::endl;

	std::string name;
	std::getline(std::cin, name);

	std::cout << localizer->GetFormat("sayhello", name.c_str()) << std::endl;

	std::cout << localizer->Get("gameover") << std::endl;
}

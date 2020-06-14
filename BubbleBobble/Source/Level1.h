#pragma once
#include "Scene.h"
//#include "Command.h"
//#include <vector>
//#pragma warning(push)
//#pragma warning (disable:4201)
//#include <glm/vec2.hpp>
//#pragma warning(pop)


class Level1 final : public minigin::Scene
{
public:
	//rule of 5
	Level1(const wstring& name);
	~Level1() = default;

	Level1(const Level1& other) = delete;
	Level1(Level1&& other) = delete;
	Level1& operator=(const Level1& other) = delete;
	Level1& operator=(Level1&& other) = delete;

private:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() const override;

	virtual void SceneActivated() override;
	virtual void SceneDeactivated() override;

	//variables
};


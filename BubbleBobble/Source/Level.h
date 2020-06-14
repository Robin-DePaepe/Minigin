#pragma once
#include "Scene.h"
#include "Player.h"
#include "LevelParser.h"


class Level final : public minigin::Scene
{
public:
	//rule of 5
	Level(const wstring& name);
	~Level() = default;

	Level(const Level& other) = delete;
	Level(Level&& other) = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) = delete;

	static void SetTwoPlayersSelected(bool value);
private:
	//functions
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() const override;

	virtual void SceneActivated() override;
	virtual void SceneDeactivated() override;

	void LoadLevel();
	//variables
	shared_ptr<Player> m_spPlayer1, m_spPlayer2;
	shared_ptr<minigin::GameObject> m_spPlayerGameObject1, m_spPlayerGameObject2;

	static bool m_TwoPlayersSelected;
	static unsigned int m_LevelNumber;

	std::vector<LevelBlocks> m_Levels;
};


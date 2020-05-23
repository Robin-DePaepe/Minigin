#include "TestStatesManager.h"
#include "StateExample.h"
void TestStatesManager::SlapAss()
{
	static_cast<StateExample*>(m_pActiveState.second)->SlapAss();
}


#pragma once
#include "State.h"
#include "TestStatesManager.h"

class StateExample : public State<TestStates>
{
public:
	virtual TestStates Update() =0;
	virtual void Render() const =0;

	virtual void StartAction() =0;
	virtual void EndAction() = 0;

	virtual void SlapAss() =0;

protected:
	bool m_AssSlapped = false;
};


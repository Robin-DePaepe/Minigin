#pragma once
#include "StateExample.h"
class JumpingState : public StateExample
{
	virtual TestStates Update() override;
	virtual void Render() const override;

	virtual void StartAction() override;
	virtual void EndAction() override;

	virtual void SlapAss() override;

private :
	int counter = 180;
};

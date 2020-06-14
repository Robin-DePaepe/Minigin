#include "MiniginPCH.h"
#include "SceneObject.h"

minigin::SceneObject::SceneObject()
	:m_Delete{false}
	,m_Visible {true}
{
}

void minigin::SceneObject::DestroyObject()
{
	m_Delete = true;
}

void minigin::SceneObject::SetVisibility(bool value)
{
	m_Visible = value;
}

#include "MiniginPCH.h"
#include "SceneObject.h"

minigin::SceneObject::SceneObject()
	:m_Delete{false}
{
}

void minigin::SceneObject::DestroyObject()
{
	m_Delete = true;
}

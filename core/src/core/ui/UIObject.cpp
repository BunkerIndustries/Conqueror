#include "_Core.h"
#include "UIObject.h"

#include "utils/Core.h"

namespace core
{
	UIObject::UIObject(std::string name, const Transform& transform)
		: Object(name, transform) { }

	UIObject::~UIObject() { }

	void UIObject::RenderObject()
	{
		buttonID != 0 ? Render(buttonID) : Render(coreID);
	}

	void UIObject::AddChildObject(UIObject* uiObject)
	{
		if (!uiObject->buttonID)
			uiObject->buttonID = buttonID;
		uiObject->parent = this;
		childOjects.push_back(uiObject);
	}

	UIObject* UIObject::GetParentObject() const
	{
		return parent;
	}

	std::vector<UIObject*>& UIObject::GetChildObjects()
	{
		return childOjects;
	}

	void UIObject::CalculateGlobalCoords()
	{
		if (!parent) return;
		globalPos = parent->globalPos + transform.position * parent->transform.scale * glm::vec2(0.5f);
	}
}

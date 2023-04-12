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

	void UIObject::RemoveChildObject()
	{
		childOjects.clear();
	}

	void UIObject::RemoveChildObject(uint32_t index)
	{
		if (index >= childOjects.size())
		{
			LOG_CORE_ERROR("Index '{0}' out of range in 'RemoveChildObject' in Object '{0}'", index, this->GetName());
			return;
		}
		childOjects.erase(childOjects.begin() + index);
	}

	void UIObject::RemoveChildObject(UIObject* object)
	{
		std::vector<UIObject*>::iterator it = std::find(childOjects.begin(), childOjects.end(), object);
		if (it == childOjects.end())
		{
			LOG_CORE_ERROR("UIObject '{0}' not registered in 'RemoveChildObject' in Object '{0}'", (uint8_t)object, this->GetName());
			return;
		}
		childOjects.erase(it);
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

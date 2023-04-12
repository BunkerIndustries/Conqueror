#pragma once
#include "_Core.h"

#include "generic/Object.h"
#include "utils/DataPool.h"

namespace core
{
	enum class Type
	{
		Rectangle,
		Triangle
	};

	class UIObject : public Object
	{
		friend class Layer;
	public:
		

		UIObject(std::string name, const Transform& transform);
		virtual ~UIObject() override;


		void RenderObject();

		void AddChildObject(UIObject* uiObject);

		UIObject* GetParentObject() const;
		std::vector<UIObject*>& GetChildObjects();
		
	protected:

		glm::vec2 globalPos;
		ProjectionMode mode;

		UIObject* parent = nullptr;
		std::vector<UIObject*> childOjects;

		core_id buttonID = 0;

		virtual void Render(core_id idToRender) = 0;
	private:

		void CalculateGlobalCoords();
	};
}



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
		

		UIObject(std::string name, const Transform& transform, glm::vec4 color);
		virtual ~UIObject() override;


		void RenderObject();

		void AddChildObject(UIObject* uiObject);

		void RemoveChildObject();
		void RemoveChildObject(uint32_t index);
		void RemoveChildObject(UIObject* object);

		UIObject* GetParentObject() const;
		std::vector<UIObject*>& GetChildObjects();

		glm::vec4 GetColor() const;
		void SetColor(glm::vec4 color);
		
	protected:

		glm::vec2 globalPos;
		glm::vec2 globalScale;
		ProjectionMode mode;

		glm::vec4 color;

		UIObject* parent = nullptr;
		std::vector<UIObject*> childOjects;

		core_id buttonID = 0;

		virtual void Render(core_id idToRender) = 0;
	private:

		void CalculateGlobalCoords();
	};
}



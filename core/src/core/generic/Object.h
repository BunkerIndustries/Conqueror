#pragma once
#include "_Core.h"
#include "Transform.h"

namespace core
{
	class Object
	{
	public:
		Object(std::string name, const Transform& transform);
		virtual ~Object();

		void SetName(std::string name);

		std::string GetName();
		core_id GetCoreID() const;

		Transform transform;

	protected:
		std::string name;
		core_id coreID;
	};
}


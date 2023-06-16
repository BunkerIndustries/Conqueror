#include "_Core.h"
#include "Object.h"
#include "utils/Core.h"

namespace core
{
	Object::Object(std::string name, const Transform& transform)
		: transform(transform), name(name)
	{
		coreID = Core::RequestID(this);
	}

	Object::~Object()
	{
		Core::AddToDelete(coreID);
	}

	void Object::SetName(const std::string name)
	{
		this->name = name;
	}

	std::string Object::GetName()
	{
		return name;
	}

	core_id Object::GetCoreID() const
	{
		return coreID;
	}
}

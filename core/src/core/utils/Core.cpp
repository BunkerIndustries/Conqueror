#include "_Core.h"

#include "Core.h"

namespace core
{
	void Core::Init()
	{
		CORE_ASSERT(!initialized, "Core already initialized");
		IDinUse[0] = nullptr;
		leastIDavailable = 1;
		initialized = true;
	}

	core_id Core::RequestID(Object* object)
	{
		CORE_ASSERT(initialized, "Core not initialized");
		uint32_t id = leastIDavailable;
		IDinUse[leastIDavailable] = object;
		leastIDavailable = IDinUse.size();
		return id;
	}

	void Core::DeleteID(core_id id)
	{
		CORE_ASSERT(initialized, "Core not initialized");
		std::unordered_map<core_id, Object*>::iterator it = IDinUse.find(id);
		if (it == IDinUse.end())
		{
			CORE_ASSERT(false, "ID does not exist");
			return;
		}
		IDinUse.erase(it);
		if (id < leastIDavailable) leastIDavailable = id;
	}

	bool Core::IsDeleted(core_id id)
	{
		return std::find(deletedIDs.begin(), deletedIDs.end(), id) != deletedIDs.end();
	}

	void Core::AddToDelete(core_id id)
	{
		deletedIDs.push_back(id);
	}

	//TODO: ERROR HERE
	Object* Core::GetObjectByID(core_id id)
	{
		CORE_ASSERT(id > 0, "invalid ID");
		if (IDinUse.find(id) != IDinUse.end()) {
			return IDinUse.at(id);
		}
		CORE_ASSERT(false, "invalid ID");
		return nullptr;
	}
}

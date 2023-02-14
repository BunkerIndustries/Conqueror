#include "_Core.h"

#include "Core.h"

namespace core
{
	void Core::Init()
	{
		CORE_ASSERT(!initialized, "Core already initialized");
		IDinUse.emplace_back(0);
		leastIDavailable = 1;
		initialized = true;
	}

	core_id Core::RequestID()
	{
		CORE_ASSERT(initialized, "Core not initialized");
		uint32_t id = leastIDavailable;
		IDinUse.emplace_back(leastIDavailable);
		leastIDavailable = IDinUse.size();
		return id;
	}

	void Core::DeleteID(core_id id)
	{
		CORE_ASSERT(initialized, "Core not initialized");
		std::vector<uint32_t>::iterator it = std::find(IDinUse.begin(), IDinUse.end(), id);
		if (it == IDinUse.end())
		{
			CORE_ASSERT(false, "ID does not exist");
			return;
		}
		IDinUse.erase(it);
		if (id < leastIDavailable) leastIDavailable = id;
	}


}

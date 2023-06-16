#pragma once
#include "_Core.h"
#include "utility.h"
#include "generic/Object.h"

namespace core
{
	class Core
	{
	public:
		static void Init();

		static core_id RequestID(Object* object);
		static void DeleteID(core_id id);

		static bool IsDeleted(core_id id);
		static void AddToDelete(core_id id);

		static Object* GetObjectByID(core_id id);
	private:
		inline static std::unordered_map<core_id, Object*> IDinUse;
		inline static std::vector<core_id> deletedIDs;
		inline static core_id leastIDavailable;
		inline static bool initialized = false;
	};
}

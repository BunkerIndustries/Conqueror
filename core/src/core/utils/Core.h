#pragma once
#include "_Core.h"
#include "utility.h"

namespace core
{
	class Core
	{
	public:
		static void Init();

		static core_id RequestID();
		static void DeleteID(core_id id);
	private:
		inline static std::vector<core_id> IDinUse;
		inline static core_id leastIDavailable;
		inline static bool initialized = false;
	};
}

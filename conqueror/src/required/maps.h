#pragma once
#include "_Game.h"
#include "stands.h"
#include "constants.h"

inline float tr_wi = trench_node_size.x;
inline glm::vec2 mid_tr_start = glm::vec2(-4.0f * tr_wi, -4.0f);
inline glm::vec2 mid_tr_end = glm::vec2(4.0f * tr_wi, -4.0f);

inline std::vector<std::pair<std::vector<glm::vec2>, Stand>> standard_map =

{
	{
		{
			glm::vec2(-6.0f, -12.0f),
			glm::vec2(-5.0f, -12.0f),
			glm::vec2(-4.0f, -12.0f),
			glm::vec2(-6.0f, -11.0f),
			glm::vec2(-5.0f, -11.0f),
			glm::vec2(-4.0f, -11.0f)
		}
		,waiting_stand
	},
	{
		{
			glm::vec2(-9.0f, -4.5f),
			glm::vec2(-9.6f, -5.0f),
			glm::vec2(-10.2f, -5.5f),
			glm::vec2(-10.8f, -6.0f),
			glm::vec2(-11.4f, -6.5f),
			glm::vec2(-12.0f, -7.0f),
			glm::vec2(-12.6f, -7.5f),

			glm::vec2(-4.0f * tr_wi, -4.0f),
			glm::vec2(-3.0f * tr_wi, -4.0f),
			glm::vec2(-2.0f * tr_wi, -4.0f),
			glm::vec2(-tr_wi, -4.0f),
			glm::vec2(0.0f, -4.0f),
			glm::vec2(tr_wi, -4.0f),
			glm::vec2(2.0f * tr_wi, -4.0f),
			glm::vec2(3.0f * tr_wi, -4.0f),
			glm::vec2(4.0f * tr_wi, -4.0f),

			glm::vec2(9.0f, -4.5f),
			glm::vec2(9.6f, -5.0f),
			glm::vec2(10.2f, -5.5f),
			glm::vec2(10.8f, -6.0f),
			glm::vec2(11.4f, -6.5f),
			glm::vec2(12.0f, -7.0f),
			glm::vec2(12.6f, -7.5f)
		}
		,trench_stand
	},
	{
		{
			glm::vec2(-3.0f, -5.5f),
			glm::vec2(-1.0f, -5.5f),
			glm::vec2(1.0f, -5.5f),
			glm::vec2(3.0f, -5.5f)
		}
		,front_stand
	},
	{
		{
			// implement bunker_node size
			glm::vec2(mid_tr_start.x - 2.5f, -3.5f),
			glm::vec2(mid_tr_start.x - 2.5f, -4.5f),
			glm::vec2(mid_tr_start.x - 1.5f, -4.5f),
			glm::vec2(mid_tr_start.x - 1.5f, -3.5f),

			glm::vec2(mid_tr_end.x + 2.5f, -3.5f),
			glm::vec2(mid_tr_end.x + 2.5f, -4.5f),
			glm::vec2(mid_tr_end.x + 1.5f, -4.5f),
			glm::vec2(mid_tr_end.x + 1.5f, -3.5f)
		}
		,bunker_stand
	},
	{
		{
			glm::vec2(-3.5f, -7.75f),
			glm::vec2(-8.0f, -8.5f),
			glm::vec2(8.0f, -8.5f),
			glm::vec2(3.5f, -7.75f),
			glm::vec2(0.0f, -8.5f)
		}
		,hiding_stand
	}
};

inline std::vector<std::pair<std::vector<Transform>, std::string>> standard_map_sprites =
{
	{
		{
			
		}
		,
	}
};
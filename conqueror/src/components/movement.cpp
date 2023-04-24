﻿#include "_Game.h"
#include "movement.h"

#include <corecrt_math_defines.h>

#include "required/functions.h"
#include "required/constants.h"

static bool CoordRoundVec2(glm::vec2 targetPos, glm::vec2 pos, float speed)
{
	glm::vec2 diff = { targetPos.x - pos.x, targetPos.y - pos.y };
	if (abs(diff.x) < speed / 100 && abs(diff.y) < speed / 100) return true;
	return false;
}



Movement::Movement(float movement_speed)
	: tracking_position(nullptr), target_position(glm::vec2()), move(false), isArrived(false), movement_speed(movement_speed) { }

Movement::Movement(float movement_speed, glm::vec2 pos)
	: tracking_position(nullptr), target_position(pos), move(true), isArrived(false), movement_speed(movement_speed) { }

void Movement::OnUpdate() {

	
  	if (tracking_position != nullptr)
	{
		target_position = *tracking_position;
		move = true;
	}

	if (CoordRoundVec2(target_position, gameObject->transform.position, movement_speed))
	{
		gameObject->transform.position = target_position;
		move = false;
		isArrived = true;

		//when bullet then delete if arrived
		if (gameObject->HasTag("bullet"))
		{
			delete gameObject;
			move = false;
			return;
		}
	}

	if (move)
		MoveTo(target_position, movement_speed);
}

void Movement::SetTrackingPos(glm::vec2* pos)
{
	tracking_position = pos;
}

void Movement::SetTargetPos(glm::vec2 pos)
{
	target_position = pos;
	tracking_position = nullptr;
	move = true;
}

void Movement::MoveTo(glm::vec2 target_pos, float speed) {

	glm::vec2 dir = target_pos - gameObject->transform.position;	// calculate direction (pos2 - pos1)
	//if (dir == glm::vec2(0.0f, 0.0f)) return;
	
	RoundVec2(dir);	  // round direction vector
	dir = glm::normalize(dir);
	//dir = glm::vec2(std::sqrtf(-(dir.x * dir.x)), -std::sqrtf(-(dir.y * dir.y)));	  // does not work
	
	
	gameObject->transform.position += dir * speed * Application::GetDT();

	RoundVec2(gameObject->transform.position);

	//orient bullet in moving direction
	if (gameObject->HasTag("bullet"))
	{
		
		gameObject->transform.rotation = Util::VectorAngle(dir.y, dir.x);
	}
	
}

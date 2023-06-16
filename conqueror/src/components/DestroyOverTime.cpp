#include "_Game.h"
#include "DestroyOverTime.h"
#include "required/constants.h"

DestroyOverTime::DestroyOverTime(float time)
	:time(time) {

}

void DestroyOverTime::OnStart() {
	time *= game_time_factor;
}

void DestroyOverTime::OnUpdate() {
	dt_counter += Application::GetDT();

	if (dt_counter < time) return;

	delete gameObject;
}

void DestroyOverTime::OnStop() {

}
#pragma once

#ifdef CORE_PLATFORM_WINDOWS
#ifdef INCLUDE_MAIN

extern core::Application* core::CreateApplication();

int main(int argc, char ** argv) 
{
	auto app = core::CreateApplication();
	app->Run();
	delete app;
}

#endif
#endif
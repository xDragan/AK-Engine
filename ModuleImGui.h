#ifndef __MODULEIMGUI_H__
#define __MODULEIMGUI_H__

#pragma once
#include "Module.h"
#include "Globals.h"
#include "imgui-1.51\imgui.h"
#include <string>
#include <vector>

class ModuleImGui : public Module
{
public:
	ModuleImGui(Application* app, bool start_enabled = true);
	~ModuleImGui();

	bool Start();
	update_status Update(float dt);
	update_status PreUpdate(float dt);
	bool CleanUp();

private:
	//ImGui Menu Active Booleans
	bool testWindowActive = false;
	bool menuActive = false;
	bool consoleActive = false;
	bool closeApp = false;
	std::vector<std::string> consoleText;

//ImGui
public:
	IMGUI_API void ShowMenuWindow(bool* p_open = NULL);
	IMGUI_API void ShowDebugWindow(bool* p_open = NULL);
	IMGUI_API void ShowConsoleWindow(bool* p_open = NULL);
	void AddLogToWindow(std::string toAdd);
};

#endif // __MODULEIMGUI_H__
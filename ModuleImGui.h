#ifndef __ModuleImGui_H__
#define __ModuleImGui_H__

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
	bool CleanUp(Configuration data);

	void Draw() const;

private:
	//ImGui Menu Active Booleans
	bool consoleActive;
	bool configurationActive;
	bool aboutActive;
	bool editorActive;

	bool closeApp = false;

	std::vector<std::string> consoleText;

//ImGui
public:
	IMGUI_API void ShowDebugWindow(bool* p_open = NULL);
	IMGUI_API void ShowConsoleWindow(bool* p_open = NULL);
	IMGUI_API void ShowConfigurationWindow(bool* p_open = NULL);
	IMGUI_API void ShowAboutWindow(bool* p_open = NULL);
	IMGUI_API void ShowEditorWindow(bool* p_open = NULL);
	IMGUI_API void ShowGuiWindow(bool* p_open = NULL);
	void AddLogToWindow(std::string toAdd);
	void ProcessEvent(SDL_Event* event);

private:
	//Booleans for ImGui Checkbox buttons
	bool openConsoleWindow;
	bool openConfigurationWindow;
	bool openAboutWindow;
	bool openEditorWindow;
	bool openUI;
};

#endif // __ModuleImGui_H__
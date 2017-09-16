#ifndef __MODULEIMGUI_H__
#define __MODULEIMGUI_H__

#include "Module.h"
#include <vector>


class ModuleImGui : public Module
{
public:
	ModuleImGui(Application* app, bool start_enabled = true);
	~ModuleImGui();

	bool Init();
	bool CleanUp();

	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;

	bool show_test_window;
	bool show_another_window;

	SDL_Window *windowUI = nullptr;
};

#endif // __MODULEIMGUI_H__
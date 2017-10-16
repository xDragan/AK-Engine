#ifndef __ModuleHardware_H__
#define __ModuleHardware_H__

#include "Globals.h"
#include "Module.h"

class ModuleHardware : public Module
{
public:
	ModuleHardware(Application* app, bool start_enabled = true);
	~ModuleHardware();

	bool CleanUp(JSON_Object* data = nullptr);

	void OnConfiguration()override;
};

#endif

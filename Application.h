#pragma once

#include "p2List.h"
#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleImGui.h"
#include "ModuleSceneEditor.h"
#include "ModuleImporter.h"
#include "ModuleTextures.h"
#include "ModuleHardware.h"

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleImGui* imGui;
	ModuleSceneEditor* sceneEditor;
	ModuleImporter* importer;
	ModuleTextures* textures;
	ModuleHardware* hardware;

private:
	Timer	ms_timer;
	float	dt;
	float startTime;
	float lastFPS = 0;
	float lastMs = 0;

	bool debug;

	std::vector<float> FPSData;
	std::vector<float> MsData;
	std::list<Module*> listModules;

public:
	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	void OnConfiguration();

	float GetFPS();
	float GetMs();
	void CycleFPSAndMsData(float fps, float ms);
	
	bool GetDebug() const;

private:
	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

// Give App pointer access everywhere
extern Application* App;
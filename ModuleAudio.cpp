#include "Globals.h"
#include "Application.h"
#include "Brofiler-1.1.2/Brofiler.h"
#include "ModuleAudio.h"
#include "ModuleImGui.h"

#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleAudio::ModuleAudio(Application* app, bool start_enabled) : Module(app, start_enabled), music(NULL)
{
	name = "audio";
}

// Destructor
ModuleAudio::~ModuleAudio()
{}

// Called before render is available
bool ModuleAudio::Init(Configuration data)
{
	BROFILER_CATEGORY("Module Audio Init", Profiler::Color::AliceBlue);

	LOG("Loading Audio Mixer");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	// load support for the OGG format
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		ret = true;
	}

	//Initialize SDL_mixer
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		ret = true;
	}

	volume = 100;

	pausedMusic = true;

	return ret;
}

// Called before quitting
bool ModuleAudio::CleanUp(Configuration data)
{
	LOG("Freeing sound FX, closing Mixer and Audio subsystem.");

	if(music != NULL)
	{
		Mix_FreeMusic(music);
	}

	std::list<Mix_Chunk*>::iterator item;

	for (item = fx.begin(); item != fx.end(); item++)
	{
		Mix_FreeChunk(item._Ptr->_Myval);
	}

	fx.clear();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	return true;
}

void ModuleAudio::OnConfiguration()
{
	if ((ImGui::CollapsingHeader("Audio")))
	{
		if (ImGui::Button("Resume music"))
		{
			ResumeMusic();
		}
		ImGui::SameLine();
		if (ImGui::Button("Pause music"))
		{
			PauseMusic();
		}
		if (ImGui::SliderInt("Master Volume", &volume, 0, 100))
		{
			//TODO: Add more sound options
			Mix_VolumeMusic(volume);
		}
	}
}

// Play a music file
bool ModuleAudio::PlayMusic(const char* path, float fade_time)
{
	bool ret = true;
	
	if(music != NULL)
	{
		if(fade_time > 0.0f)
		{
			Mix_FadeOutMusic((int) (fade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		// this call blocks until fade out is done
		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if(music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if(fade_time > 0.0f)
		{
			if(Mix_FadeInMusic(music, -1, (int) (fade_time * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if(Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	pausedMusic = false;
	LOG("Successfully playing %s", path);
	return ret;
}

// Load WAV
unsigned int ModuleAudio::LoadFx(const char* path)
{
	unsigned int ret = 0;

	Mix_Chunk* chunk = Mix_LoadWAV(path);

	if(chunk == NULL)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		fx.push_back(chunk);
		ret = fx.size();
	}

	return ret;
}

// Play WAV
bool ModuleAudio::PlayFx(unsigned int id, int repeat)
{
	bool ret = false;

	if (id > 0 && id <= fx.size())
	{
		std::list<Mix_Chunk*>::iterator item = fx.begin();
		advance(item, id - 1);
		Mix_PlayChannel(-1, (*item), repeat);
		ret = true;
	}

	return ret;
}

void ModuleAudio::PauseMusic()
{
	if (!pausedMusic)
	{
		Mix_PauseMusic();
		pausedMusic = true;
	}
}

void ModuleAudio::ResumeMusic()
{
	if (pausedMusic)
	{
		Mix_ResumeMusic();
		pausedMusic = false;
	}
}
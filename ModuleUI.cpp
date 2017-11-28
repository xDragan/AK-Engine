#include "ModuleUI.h"


/*
ModuleUI::ModuleUI(Application* app, bool start_enabled): Module(app,start_enabled) 
{
	name = "UI";
}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Start()
{
	return true;
}

void ModuleUI::ReceiveInput()
{

}

bool ModuleUI::CleanUp()
{
	return true;
}

bool ModuleUI::Blit (SDL_Texture* texture, int x, int y, const SDL_Rect* section, float speed, bool resize, double angle, int pivot_x, int pivot_y, float posX , float posY ) const
{
	bool ret = true;
	uint scale = App->window->GetScale();
	
	SDL_Rect rect;
	if (posX != -999)
	{
		rect.x = (int)(camera.x * speed) + posX * scale;
		rect.y = (int)(camera.y * speed) + posY * scale;
	}
	else
	{
		rect.x = (int)(camera.x * speed) + x * scale;
		rect.y = (int)(camera.y * speed) + y * scale;
	}

	if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}
	if (resize == true) {
		rect.w *= scale;
		rect.h *= scale;
	}

	SDL_Point* p = NULL;
	SDL_Point pivot;

	if (pivot_x != INT_MAX && pivot_y != INT_MAX)
	{
		pivot.x = pivot_x;
		pivot.y = pivot_y;
		p = &pivot;
	}

	if (SDL_RenderCopyEx(renderer, texture, section, &rect, angle, p, SDL_FLIP_NONE) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

*/
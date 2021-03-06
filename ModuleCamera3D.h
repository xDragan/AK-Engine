#ifndef __ModuleCamera3D_H__
#define __ModuleCamera3D_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "MathGeo/Geometry/LineSegment.h"

class GameObject;
class ComponentCamera;

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	bool CleanUp(Configuration data);

	update_status Update(float dt);

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);
	void ZoomIn();
	void ZoomOut();
	void CenterToGO(const AABB& box);
	void SetMainCamera(ComponentCamera* camera);
	void RecalcAspectRatio(int width, int height);

	bool UsingSceneCamera()const;
	ComponentCamera* GetEditorCamera()const;
	ComponentCamera* GetMainCamera()const;

	const float* GetViewMatrix() const;

private:
	void CalculateViewMatrix();

public:
	vec3 X, Y, Z, Position, Reference;
	LineSegment lastPick;

private:
	mat4x4 ViewMatrix, ViewMatrixInverse;
	ComponentCamera* editorCamera = nullptr;
	ComponentCamera* mainCamera = nullptr;
};

#endif //__ModuleCamera3D_H__
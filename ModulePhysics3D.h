#ifndef __ModulePhysics_H__
#define __ModulePhysics_H__

#include "Module.h"
#include "Globals.h"
#include "p2List.h"
#include "Primitive.h"

#include "Bullet/include/btBulletDynamicsCommon.h"

// Recommended scale is 1.0f == 1 meter, no less than 0.2 objects
#define GRAVITY btVector3(0.0f, -20.0f, 0.0f) 

class DebugDrawer;
struct PhysBody3D;
struct PhysVehicle3D;
struct VehicleInfo;


class ModulePhysics3D : public Module
{
public:
	ModulePhysics3D(Application* app, bool start_enabled = true);
	~ModulePhysics3D();

	bool Init(JSON_Object* data = nullptr);
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp(JSON_Object* data = nullptr);

	PhysBody3D* AddBody(const pSphere& sphere, float mass = 1.0f);
	PhysBody3D* AddBody(const Cube& cube, float mass = 1.0f);
	PhysBody3D* AddBody(const Cube1& cube, float mass = 1.0f);
	PhysBody3D* AddBody(const Cube2& cube, float mass = 1.0f);
	PhysBody3D* AddBody(const pCylinder& cylinder, float mass = 1.0f);

	void AddConstraintP2P(PhysBody3D& bodyA, PhysBody3D& bodyB, const vec3& anchorA, const vec3& anchorB);
	void AddConstraintHinge(PhysBody3D& bodyA, PhysBody3D& bodyB, const vec3& anchorA, const vec3& anchorB, const vec3& axisS, const vec3& axisB, bool disable_collision = false);

	bool debug;

private:

	

	btDefaultCollisionConfiguration*	collision_conf;
	btCollisionDispatcher*				dispatcher;
	btBroadphaseInterface*				broad_phase;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld*			world;
	btDefaultVehicleRaycaster*			vehicle_raycaster;
	DebugDrawer*						debug_draw;

	p2List<btCollisionShape*> shapes;
	p2List<PhysBody3D*> bodies;
	p2List<btDefaultMotionState*> motions;
	p2List<btTypedConstraint*> constraints;
	p2List<PhysVehicle3D*> vehicles;
};

class DebugDrawer : public btIDebugDraw
{
public:
	DebugDrawer() : line(0,0,0)
	{}

	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
	void reportErrorWarning(const char* warningString);
	void draw3dText(const btVector3& location, const char* textString);
	void setDebugMode(int debugMode);
	int	 getDebugMode() const;

	DebugDrawModes mode;
	pLine line;
	Primitive point;
};

#endif //__ModulePhysics_H__
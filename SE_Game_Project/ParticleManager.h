#pragma once
#include <glm/glm.hpp>
#include"ColorRGBA32.h"
#include"CollisionManager.h"

#define MAX_PARTICLE_COUNT 100

struct Particle
{
	glm::vec3 position, direction;
	glm::vec2 size = glm::vec2(5.0, 5.0);
	glm::vec3 speed;
	glm::vec4 color;
	//glm::vec4 r,g,b,a;
	float lifeTime = 100.0f;
	float angle;
	bool isActive;
	ColorRGBA32 m_color;

	Particle()
		: position(0.0f), direction(0.0f), color(1.0f), lifeTime(0.0f) {}
};

class ParticleManager
{
private:
	int m_active_particles = 0;
	
public:
	CollisionManager* m_collisionManager = nullptr;

	ParticleManager();
	Particle m_particles[MAX_PARTICLE_COUNT];
	void update_particle(float health, bool isActive);	// Purely update all particles
	void update_AddParticle(glm::vec3 pos, glm::vec3 dir);
	void particle_init(CollisionManager& collisionManager);
	~ParticleManager();

};
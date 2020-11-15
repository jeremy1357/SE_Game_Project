#pragma once
#include <glm/glm.hpp>
#include"ColorRGBA32.h"
#include"CollisionManager.h"

#define MAX_PARTICLE_COUNT 100

struct Particle
{
	glm::vec2 position, direction;
	glm::vec2 size = glm::vec2(5.0, 5.0);
	glm::vec2 speed = glm::vec2(0.5, 0.50);
	//glm::vec4 r,g,b,a;
	float health = 100.0f;
	bool isActive;
	ColorRGBA32 m_color;

	Particle()
		: position(0.0f), direction(0.0f), /*color(1.0f),*/ health (0.0f) {}
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
	void update_AddParticle(glm::vec2 pos, glm::vec2 dir, ColorRGBA32 color);
	void particle_init(CollisionManager& collisionManager);
	~ParticleManager();

};
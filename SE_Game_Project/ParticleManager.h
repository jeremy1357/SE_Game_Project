#pragma once
#include <glm/glm.hpp>

#define MAX_PARTICLE_COUNT 500
struct Particle
{
	glm::vec2 position;
	float angle;
	glm::vec2 direction;
	float lifeTime = 100.0f;
	bool isActive;
	//ColorRGBA32 color;
};

class ParticleManager
{
public:
	ParticleManager();
	Particle m_particles[MAX_PARTICLE_COUNT];
	void update_particle(float health, bool isActive);	// Purely update all particles
	int AddParticle(glm::vec2 pos, glm::vec2 dir);
	~ParticleManager();

};
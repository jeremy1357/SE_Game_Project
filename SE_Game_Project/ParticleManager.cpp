#include"ParticleManager.h"

ParticleManager::ParticleManager()
{
	;
}

void ParticleManager::update_particle(float health, bool isActive)
{
	for (int i = 0; i < MAX_PARTICLE_COUNT; i++) {
		if (m_particles[i].lifeTime > 0.0) {
			m_particles[i].isActive = true;
			//m_particles[i].position += m_particles[i].direction * speed; //need to calculate the speed and then be able to implement it
			m_particles[i].lifeTime -= 1.0f; // This value might change
		}
		else {
			m_particles[i].isActive = false;
		}
	}
}

int ParticleManager::AddParticle(glm::vec2 pos, glm::vec2 dir)
{
	// Find an inactive particle within the array
	for (int i = 0; i < MAX_PARTICLE_COUNT; i++) {
		if (m_particles[i].isActive == false) {
			m_particles[i].isActive = true;
			m_particles[i].position = dir;
			m_particles[i].lifeTime -= 1.0f; // This value might change
		}
		else
		{

		}
	}
	return 0;
}

ParticleManager::~ParticleManager()
{
	;
}
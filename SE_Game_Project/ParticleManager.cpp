#include"ParticleManager.h"
#include"CollisionManager.h"


ParticleManager::ParticleManager()
{
	;
}

void ParticleManager::particle_init(CollisionManager& collisionManager)
{
	m_collisionManager = &collisionManager;
}

void ParticleManager::update_particle(float health, bool isActive)
{

	for (int i = 0; i < MAX_PARTICLE_COUNT; i++) {
		if (m_particles[i].lifeTime > 0.0) {
			m_particles[i].isActive = true;
			m_particles[i].position += m_particles[i].direction * m_particles[i].speed;
			m_particles[i].lifeTime -= 1.0f;

			bool check = m_collisionManager->is_square_on_restricted_tile(m_particles[i].position, m_particles[i].size);
			if (check == true)
			{
				m_particles[i].lifeTime = 0.0f;
				for (i = i; i < m_active_particles; i++)
				{
					m_particles[i] = m_particles[i + 1];
				}
				m_active_particles--;
			}					
		}
		else {
			m_particles[i].isActive = false;
		}
	}
}

void ParticleManager::update_AddParticle(glm::vec3 pos, glm::vec3 dir)
{
	// Find an inactive particle within the array
	for (int i = 0; i < MAX_PARTICLE_COUNT; i++) {
		if (m_particles[i].isActive == false) {
			m_particles[i].isActive = true;
			m_particles[i].position = dir;
			m_particles[i].lifeTime -= 1.0f; // This value might change
			m_active_particles++;
		}
	}
}

ParticleManager::~ParticleManager()
{
	;
}
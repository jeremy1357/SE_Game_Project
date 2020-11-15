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
		if (m_particles[i].health > 0.0) {
			m_particles[i].isActive = true;
			m_particles[i].position += m_particles[i].direction * m_particles[i].speed;
			m_particles[i].health-= 1.0f;

			bool check = m_collisionManager->is_square_on_restricted_tile(m_particles[i].position, m_particles[i].size);
			if (check == true)
			{
				m_particles[i].isActive = false;
				m_particles[i].health = 0.0f;
				m_active_particles--;
			}					
		}
		else {
			m_particles[i].isActive = false;
		}
	}
}

void ParticleManager::update_AddParticle(glm::vec2 pos, glm::vec2 dir, ColorRGBA32 color)
{
	// Find an inactive particle within the array
	for (int i = 0; i < MAX_PARTICLE_COUNT; i++) 
	{
		if (m_particles[i].isActive == false) 
		{
			m_particles[i].isActive = true;
			m_particles[i].position = pos;
			m_particles[i].direction = dir;
			m_particles[i].size = glm::vec2(5.0, 5.0);
			m_particles[i].speed = glm::vec2(0.5, 0.5);
			m_particles[i].health = 100.0f;
			m_particles[i].m_color = color;
			m_active_particles++;
		}
	}
}

ParticleManager::~ParticleManager()
{
	;
}
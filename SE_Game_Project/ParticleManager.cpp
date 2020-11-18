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

void ParticleManager::update_particle()
{

	for (i = i; i < MAX_PARTICLE_COUNT; i++) {
		if (m_particles[i].health > 0.0) {
			m_particles[i].isActive = true;
			m_particles[i].health -= 0.05f;

			glm::vec2 dirVector(cos(m_particles[i].angle * 3.14157 / 180), sin(m_particles[i].angle * 3.14157 / 180));
			m_particles[i].position +=  dirVector * m_particles[i].speed;

			bool check = m_collisionManager->is_point_on_restricted_tile(m_particles[i].position);
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
		if (i == MAX_PARTICLE_COUNT)
			i = 0;
	}
}

void ParticleManager::update_AddParticle(glm::vec2 pos, float angle, ColorRGBA32 color)
{
	// Find an inactive particle within the array
	for (int i = 0; i < MAX_PARTICLE_COUNT; i++) 
	{
		if (m_particles[i].isActive == false) {
			m_particles[i].isActive = true;
			m_particles[i].position = pos;
			m_particles[i].angle = angle;
			m_particles[i].size = glm::vec2(6.0);
			m_particles[i].speed = glm::vec2(7.0f);
			m_particles[i].health = 100.0f;
			m_particles[i].m_color = color;
			m_active_particles++;
			break;
		}
	}
}

ParticleManager::~ParticleManager()
{
	;
}
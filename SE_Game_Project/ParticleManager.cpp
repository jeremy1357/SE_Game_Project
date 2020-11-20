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
	for (int i = 0; i < MAX_PARTICLE_COUNT; i++) {
		if (m_particles[i].health > 0.0) {
			m_particles[i].isActive = true;
			m_particles[i].health -= 0.05f;

			glm::vec2 dirVector(cos(m_particles[i].angle * 3.14157 / 180), sin(m_particles[i].angle * 3.14157 / 180));
			m_particles[i].position += dirVector * m_particles[i].speed;

			bool check = m_collisionManager->is_point_on_restricted_tile(m_particles[i].position);
			if (check == true)
			{
				m_particles[i].isActive = false;
				m_particles[i].health = 0.0f;
			}
		}
		else if (m_particles[i].health <= 0.0f) {
			m_particles[i].isActive = false;
		}
	}
}

void ParticleManager::update_AddParticle(glm::vec2 pos, float angle, ColorRGBA32 color)
{
	// Find an inactive particle within the array
	for (int i = lastUsedParticle; i < MAX_PARTICLE_COUNT; i++) 
	{
		if (m_particles[i].isActive == false) {
			m_particles[i].isActive = true;
			m_particles[i].position = pos;
			m_particles[i].angle = angle;
			m_particles[i].size = glm::vec2(5.0);
			m_particles[i].speed = glm::vec2(7.0f);
			m_particles[i].health = 100.0f;
			m_particles[i].m_color = color;
			lastUsedParticle = i;
			break;
		}
		if (i == MAX_PARTICLE_COUNT)
			lastUsedParticle = 0;
	}
}

void ParticleManager::blood_particle(glm::vec2 pos, float angle)
{
	for (int i = 0; i < 10; i++)
	{
		blood_particles[i].isActive = true;
		blood_particles[i].position = pos; //position is location of the zombie
		blood_particles[i].angle = angle * (-1*rand()); //reverse the particle direction from impact. with some variation
		blood_particles[i].m_color = ColorRGBA32 (145, 0, 45, 1); //gives the color a dark red color
		//blood_particles[i].m_color = ColorRGBA32 (226, 0, 45, 1); //gives the color a bright red color
		blood_particles[i].size = glm::vec2(3.0);
		blood_particles[i].speed = glm::vec2(7.0f);
		blood_particles[i].health = 1.0f;
	}
}

ParticleManager::~ParticleManager()
{
	;
}
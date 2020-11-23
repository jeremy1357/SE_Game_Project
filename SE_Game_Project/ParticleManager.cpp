#include"ParticleManager.h"
#include"CollisionManager.h"

ParticleManager::ParticleManager()
{
	// Empty
}

void ParticleManager::reset() {
	for (auto& it : m_particles) {
		it.health = 0.0f;
		it.isActive = false;
	}
}

void ParticleManager::particle_init(CollisionManager& collisionManager)
{
	m_collisionManager = &collisionManager;
}

void ParticleManager::update_particle()
{
	for (int i = 0; i < MAX_PARTICLE_COUNT; i++) {
		if (m_particles[i].health > 0.0 && m_particles[i].m_color.a > 0) {
			if (m_particles[i].m_color.r != 0) {
				m_particles[i].m_color.a -= 3;
				m_particles[i].speed -= 0.025f;
				if (m_particles[i].speed.x < 0.0f) {
					m_particles[i].speed = glm::vec2(0.0f);
				}
			}
			else {
				m_particles[i].health -= 0.5f;

			}
			m_particles[i].isActive = true;

				glm::vec2 dirVector(cos(m_particles[i].angle * 3.14157 / 180), sin(m_particles[i].angle * 3.14157 / 180));
			m_particles[i].position += dirVector * m_particles[i].speed;

			bool check = m_collisionManager->is_point_on_restricted_tile(m_particles[i].position);
			if (check == true)
			{
				m_particles[i].isActive = false;
				m_particles[i].health = 0.0f;
			}
		}
		else if (m_particles[i].health <= 0.0f || m_particles[i].m_color.a <= 0) {
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
			m_particles[i].speed = glm::vec2(10.0f);
			m_particles[i].health = 100.0f;
			m_particles[i].m_color = color;
			lastUsedParticle = i;
			return;
		}
	}
	for (int i = 0; i < lastUsedParticle; i++)
	{
		if (m_particles[i].isActive == false) {
			m_particles[i].isActive = true;
			m_particles[i].position = pos;
			m_particles[i].angle = angle;
			m_particles[i].size = glm::vec2(5.0);
			m_particles[i].speed = glm::vec2(10.0f);
			m_particles[i].health = 100.0f;
			m_particles[i].m_color = color;
			lastUsedParticle = i;
			return;
		}
	}

}

void ParticleManager::blood_particle(glm::vec2 pos, float angle)
{
	for (int n = 0; n < 3; n++)
	{
		for (int i = lastUsedParticle; i < MAX_PARTICLE_COUNT; i++)
		{
			if (m_particles[i].isActive == false) {
				m_particles[i].isActive = true;
				m_particles[i].position = pos;
				m_particles[i].angle = angle * (-1 * rand());
				m_particles[i].size = glm::vec2(5.0f);
				m_particles[i].speed = glm::vec2(1.7f);
				m_particles[i].health = 25.0f;
				m_particles[i].m_color = ColorRGBA32(226, 0, 45, 255);
				lastUsedParticle = i;
				break;
			}
		}
		for (int i = 0; i < lastUsedParticle; i++)
		{
			if (m_particles[i].isActive == false) {
				m_particles[i].isActive = true;
				m_particles[i].position = pos;
				m_particles[i].angle = angle * (-1 * rand());
				m_particles[i].size = glm::vec2(5.0f);
				m_particles[i].speed = glm::vec2(1.7f);
				m_particles[i].health = 25.0f;
				m_particles[i].m_color = ColorRGBA32(226, 0, 45, 255);
				lastUsedParticle = i;
				break;
			}
		}
	}
}


ParticleManager::~ParticleManager()
{
	;
}
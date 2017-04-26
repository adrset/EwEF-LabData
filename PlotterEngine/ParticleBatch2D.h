#pragma once
#include <glm/glm.hpp>
#include <functional>
#include "SpriteBatch.h"
#include "vertex.h"
#include "glTexture.h"
namespace PlotterEngine {


	class Particle2D {
	public:
		glm::vec2 position = glm::vec2(0.0f);
		glm::vec2 velocity = glm::vec2(0.0f);
		ColorRGBA8 color;
		float life = 0.0f;
		float width = 0.0f;
	};

	inline void defaultUpdate(Particle2D& particle, float deltaTime) {
			particle.position += particle.velocity * deltaTime;
	}

	class ParticleBatch2D {
	public:
		ParticleBatch2D();
		~ParticleBatch2D();
		void init(int maxParticles, float decayRate, GLTexture texture, std::function<void(Particle2D&, float)> updateFunc = defaultUpdate);
		void addParticle(const glm::vec2& position,
						 const glm::vec2& velocity,
						 const ColorRGBA8& color,
						 float width);
		void update(float deltaTime);
		void draw(SpriteBatch* spriteBatch);

	private:
		std::function<void(Particle2D&, float)> m_updateFunc;
		int findFreeParticle();
		float m_decayRate = 0.1f;
		Particle2D* m_particles = nullptr;
		int m_maxParticles = 0;
		GLTexture m_texture;
		int m_lastFreeParticle = 0;
	};

}
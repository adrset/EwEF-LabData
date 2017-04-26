#pragma once
#include <vector>

namespace PlotterEngine {
	class ParticleBatch2D;
	class SpriteBatch;
	class ParticleEngine2D {
	public:
		ParticleEngine2D();
		~ParticleEngine2D();
		//after adding a particle batch, the particleengine2d becomes resp. for deallocation
		void addParticleBatch(ParticleBatch2D* particleBatch);

		void update(float deltaTime);

		void draw(SpriteBatch* spriteBatch);

	private:
		std::vector<ParticleBatch2D*> m_batches;
	};


}
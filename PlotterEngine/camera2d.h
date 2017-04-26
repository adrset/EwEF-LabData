#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace PlotterEngine {

	class camera2d
	{
	public:
		camera2d();
		~camera2d();

		void init(int screenWidth, int screenHeight);
		void update();

		glm::vec2 convertScreenToWorld(glm::vec2 screenCords);

		void setPosition(const glm::vec2& newPosition) { _position = newPosition; _needsUpdate = true; }
		void setScale(float newScale) { _scale = newScale; _needsUpdate = true; }

		glm::vec2 getPosition() { return _position; }
		float getScale() { return _scale; }
		glm::mat4 getCameraMatrix() { return _cameraMatrix; }

		bool isBoxInView(const glm::vec2& position, const glm::vec2& dimensions);


	private:
		int _screenWidth, _screenHeight;
		bool _needsUpdate;
		float _scale;
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
	};

}
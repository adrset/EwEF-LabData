#include "camera2d.h"
#include <iostream>
namespace PlotterEngine {

	camera2d::camera2d() : _position(0, 0),
		_scale(1.0f),
		_needsUpdate(true),
		_screenHeight(500),
		_screenWidth(500),
		_cameraMatrix(1.0f),
		_orthoMatrix(1.0f)
	{
	}

	glm::vec2 camera2d::convertScreenToWorld(glm::vec2 screenCords) {

		screenCords.y = _screenHeight - screenCords.y;
		//0 is center
		screenCords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
		//scale coordinates
		screenCords /= _scale;
		//translate with cam position
		screenCords += _position;
		return screenCords;

	}

	bool camera2d::isBoxInView(const glm::vec2& position, const glm::vec2& dimensions)
	{

		glm::vec2 scaledScreenDimensions = glm::vec2(_screenWidth, _screenHeight) / _scale ;
		//std::cout << scaledScreenDimensions.x << " " << scaledScreenDimensions.y << std::endl;
		
		const float MIN_DISTANCE_X = dimensions.x/2.0f + scaledScreenDimensions.x/2.0f;
		const float MIN_DISTANCE_Y = dimensions.y/2.0f + scaledScreenDimensions.y/2.0f;
		//std::cout << MIN_DISTANCE_X << " " << MIN_DISTANCE_Y << std::endl;
		glm::vec2 centerPos = position + dimensions / 2.0f;
		glm::vec2 centerCameraPos = _position;
		glm::vec2 distVec = centerPos - centerCameraPos;
		float xDepth = MIN_DISTANCE_X - abs(distVec.x);
		float yDepth = MIN_DISTANCE_Y - abs(distVec.y);
		

		if (xDepth > 0 && yDepth > 0) { // COLLISION
			return true;
		}
		return false;
	}
	

	camera2d::~camera2d()
	{
	}

	void camera2d::init(int screenWidth, int screenHeight) {
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
	}

	void camera2d::update() {

		if (_needsUpdate) {
			glm::vec3 translate(-_position.x + _screenWidth/2, -_position.y + _screenHeight/2 , 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);
			glm::vec3 scale(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;
			_needsUpdate = false;
		}
	}


}
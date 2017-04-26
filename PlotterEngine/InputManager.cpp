#include "InputManager.h"

namespace PlotterEngine {

	InputManager::InputManager():_mouseCoords(0) {

	}

	InputManager::~InputManager() {

	}
	void InputManager::update() {

		for (auto& it : _keyMap) {
			_previousKeyMap[it.first] = it.second;
		}
	}
	void InputManager::pressKey(unsigned int keyID) {
		_keyMap[keyID] = true; // same as _keyMap.insert();
	}
	void InputManager::releaseKey(unsigned int keyID) {
		_keyMap[keyID] = false;
	}

	void InputManager::setMouseCoords(float x, float y) {
		_mouseCoords.x = x;
		_mouseCoords.y = y;
	}
	bool InputManager::isKeyDown(unsigned int keyID) {
		auto it = _keyMap.find(keyID);
		if (it != _keyMap.end()) {
			return it->second;//ret val (it's bool)
		}
		else {
			return false;
		}
	}

	bool InputManager::isKeyPressed(unsigned int keyID)
	{
		bool isPressed = false;
		if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false) {
			return true;
		}
		return false;
	}

	bool InputManager::wasKeyDown(unsigned int keyID)
	{
		auto it = _previousKeyMap.find(keyID);
		if (it != _previousKeyMap.end()) {
			return it->second; //ret val (it's bool)
		}
		else {
			return false;
		}
	}

}
#pragma once

#include <SFML/Graphics.hpp>

class CameraManager {
	public:
		CameraManager();

		void setCamera(float x, float y);
		sf::View getCamera();

	private:
		sf::View camera;
		float camera_x, camera_y;
};
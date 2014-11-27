#pragma once

#include <SFML/Graphics.hpp>

class CameraManager {
	public:
		CameraManager();

		void SetCamera(float x, float y);
		sf::View GetCamera();

	private:
		sf::View camera;
		float camera_x, camera_y;
};
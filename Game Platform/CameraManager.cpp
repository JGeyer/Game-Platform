#include "CameraManager.h"

CameraManager::CameraManager() {
	camera_x = 0.0f;
	camera_y = 0.0f;
}

void CameraManager::SetCamera(float x, float y) {
	camera_x = x;
	camera_y = y;
	camera = sf::View(sf::FloatRect(camera_x, camera_y, 800, 600));
}

sf::View CameraManager::GetCamera() {
	return camera;
}
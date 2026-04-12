#ifndef GAME_PHYSICS_H
#define GAME_PHYSICS_H

struct VerticalPhysics {
	float velocityY = 0.0f;
	bool on_ground = false;
};

bool UpdateVerticalPhysics(float &posY, VerticalPhysics &vp, float deltaT, float gravity, float groundY);

#endif
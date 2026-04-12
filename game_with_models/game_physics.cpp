#include "raylib.h"
#include "raymath.h"
#include "iostream"
#include "string"
#include "game_physics.h"
using namespace std;

bool UpdateVerticalPhysics(float &posY, VerticalPhysics &vp, float deltaT, float gravity, float groundY) // apply gravity upon jumping
{
    bool justLanded = false; // did i land in this frame. gonna use for one time effects on landing.
    // apply the accelaration from gravity
    vp.velocityY += gravity * deltaT;
    // integrate the position 
    posY += vp.velocityY * deltaT; // players y position changes by velocitY of the player * time_per_frame. makes the gravity agnostic to fps by multiplying by time per frame

    // ensure ground collision
    if (posY >= groundY)
    {
        if (!vp.on_ground) // if player is on ground
        {
            justLanded = true;
        }
        posY = groundY;
        vp.velocityY = 0.0f;
        vp.on_ground = true;
    }
    return justLanded;
}

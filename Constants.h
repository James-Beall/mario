#pragma once

//Screen Dimensions
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 416

#define MAP_HEIGHT 13
#define MAP_WIDTH 16
#define TILE_WIDTH 32
#define TILE_HEIGHT 32

#define GRAVITY 96.0f
 
const float movementSpeed = 10.0f;
const float gravity = 1.0f;

const float JUMP_FORCE_DECREMENT = 400.0f;
const float INITIAL_JUMP_FORCE = 350.0f;
const float INITIAL_JUMP_FORCE_SMALL = 200.0f;
const float SCREENSHAKE_DURATION = 0.25f;

const float INJURED_TIME = 2.5f;
const float KOOPA_SPEED = 96.0f;
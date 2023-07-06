#include "types.h"
#include "math.h"
#include "vector2.h"

#include "macros.h"

#pragma once

// ---------- SCREEN ---------

const u16 WND_WIDTH = 800;
const u16 WND_HEIGHT = 600;

const u32 PIXEL_COUNT = WND_WIDTH * WND_HEIGHT;

const u16 WND_WIDTH_HALF = WND_WIDTH / 2;
const u16 WND_HEIGHT_HALF = WND_HEIGHT / 2;

// ---------- PLAYER ---------

const v2 DEFAULT_PLAYER_POS(6.0, 5.0);
const f32 DEFAULT_PLAYER_ANGLE = 0.0f;
const f32 PLAYER_SPEED = 35.0f;
const f32 PLATER_ROTATION_SPEED = PI/.80;

const f32 PLAYER_RADIUS = 0.3f; // on minimap


// --------- RAYCASTING --------

const f32 FOV = PI / 3;
const f32 HALF_FOV = FOV / 2;

const u16 NUM_RAYS = WND_WIDTH / 2;
const f32 DELTA_ANGLE = FOV / NUM_RAYS;
const f32 MAX_DEPH = 20.0f;

const f32 SCREEN_DIST = WND_WIDTH_HALF / tan(HALF_FOV);
const u8 PROJECTION_SCALE = WND_WIDTH / NUM_RAYS;


// ---------- MINIMAP ----------
const u8 MINIMAP_SCALE = 5;

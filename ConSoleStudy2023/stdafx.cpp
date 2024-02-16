#include "stdafx.h"

Vec2 MapSize::CURRENT_MAP_SIZE{};

bool PointInBox(Vec2 boxPos1, Vec2 boxPos2, Vec2 point)
{
	return boxPos1.x <= point.x && boxPos1.y <= point.y &&
		point.x <= boxPos2.x && point.y <= boxPos2.y;
}

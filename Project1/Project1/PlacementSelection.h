#pragma once
struct PlacementSelection
{
	struct Size
	{
		int lenght_x;
		int width_y;
		int height_z;
	} size;
	struct Coordination
	{
		int x;
		int y;
		int z;
	} coordination;

	int index = 0;
	int containerIndex = 0;
};
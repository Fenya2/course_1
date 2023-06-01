#include "Coord.h"

coord::coord(){x=y=-1;}

coord::coord(int x, int y)
{
	this->x=x;
	this->y=y;
}

bool coord::operator==(const coord& c) const
{return x==c.x && y==c.y;}

bool coord::operator!=(const coord& c) const
{return x!=c.x || y!=c.y;}

bool coord::valid()
{
	if(x<0||x>8||y<0||y>8)
		return false;
	return true;
}

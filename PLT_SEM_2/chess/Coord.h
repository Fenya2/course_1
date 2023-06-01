#ifndef COORD_H
#define COORD_H
struct coord
{
	int x;
	int y;
	coord();
	coord(int, int);
	bool operator==(const coord&) const;
	bool operator!=(const coord&) const;
	bool valid();
};
#endif

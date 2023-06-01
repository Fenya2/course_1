#ifndef EDGE_H
#define EDGE_H
#include<string>
struct Edge
{
	double C;
	double Z;
	double D;
	Edge();
	Edge(double,double,double);
	void summurize(Edge);
	double specificGravity(std::string);
	std::string to_string();
	~Edge();
};
#endif

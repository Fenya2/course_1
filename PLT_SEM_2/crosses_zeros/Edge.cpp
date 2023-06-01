#include "Edge.h"

Edge::Edge(double C,double Z,double D)
{
	this->C=C;
	this->Z=Z;
	this->D=D;
}

Edge::Edge() {C=Z=D=0;}

void Edge::summurize(Edge edge)
{
	C+=edge.C;
	Z+=edge.Z;
	D+=edge.D;
}

double Edge::specificGravity(std::string outcome)
{
	if(outcome=="C")
			return C/(C+Z+D);
	if(outcome=="Z")
			return Z/(C+Z+D);
	if(outcome=="D")
			return D/(C+Z+D);
	throw "Error";
}

std::string Edge::to_string()
{return std::to_string(C)+" "+std::to_string(Z)+" "+std::to_string(D);}

Edge::~Edge(){}

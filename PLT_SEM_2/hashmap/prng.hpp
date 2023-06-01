#ifndef PRNG
#define PRNG

double generatePseudoRandonShare(double r)
{
	double x = 0.2;
	if(r <= 0 || r >= 1)
		return -1;
	r=3.58+r*(4-3.8); // r * (max - min) + min; max=4, min=1
	for(int i = 0; i < 3000; ++i)
		x = r*x*(1-x);
	return x;
}

#endif

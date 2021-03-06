#include "Lookup.h"
#include <cmath>
#include <cassert>

namespace ImageCube
{

Lookup Lookup::instance;

Lookup::Lookup()
:num(5001)
,xMin(0.0)
,xMax(50.0)
,dx((xMax - xMin)/(num-1))
,one_over_dx(1.0/dx)
,_exp(num)
{
	for(int i=0; i<num; i++)
		_exp[i] = exp(-i*dx);
}

double Lookup::evaluate(double x)
{
	int i = static_cast<int>(x*instance.one_over_dx);
    double frac = (x - i*instance.dx)*instance.one_over_dx;

	if(i < 0 || i >= (instance.num-1))
		return 0.0;
	return frac*instance._exp[i+1] + (1.0 - frac)*instance._exp[i];
}

} // namespace ImageCube


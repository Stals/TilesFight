#include "MathUtils.h"


double MathUtils::linear_interpolation(double Kstart, double Kend, double Vstart, double Vend, double K)
{
	if (K <= Kstart)
		return Vstart;
	else if (K >= Kend)
		return Vend;
	else
		return Vstart + ((K - Kstart) / (Kend - Kstart)) * (Vend - Vstart);
}


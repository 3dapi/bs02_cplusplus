

#include <stdio.h>

#include "Vector3.h"

void main()
{
	CVector3 p1(1,2,3), p2(5,6,7);

	CVector3 p3 = p1 + p2;

	printf("%f %f %f\n", p3.x, p3.y, p3.z);
}


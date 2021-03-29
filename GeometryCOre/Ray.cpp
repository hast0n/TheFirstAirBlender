#include "Ray.h"

#include "Vector3f.h"

Ray::Ray(Vector3f origin, Vector3f dest): Destination(dest), Origin(origin)
{
	Direction = (Destination - Origin).normalize();
}
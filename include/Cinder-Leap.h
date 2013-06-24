#pragma once

#include "cinder/Matrix.h"
#include "cinder/Vector.h"

#include "Leap.h"

namespace mndl { namespace leap {

inline ci::Vec3f fromLeap( const Leap::Vector &v )
{
	return ci::Vec3f( v.x, v.y, v.z );
}

inline Leap::Vector toLeap( const ci::Vec3f &v )
{
	return Leap::Vector( v.x, v.y, v.z );
}

} } // mndl::leap

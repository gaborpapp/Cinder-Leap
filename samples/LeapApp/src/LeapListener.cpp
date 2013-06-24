#include "cinder/app/App.h"

#include "LeapListener.h"

using namespace ci;

namespace mndl { namespace leap {

void LeapListener::onFrame( const Leap::Controller &controller )
{
	std::lock_guard< std::mutex > lock( mMutex );
	const Leap::Frame frame = controller.frame();
	mHandList = frame.hands();
}

const Leap::HandList & LeapListener::getHands() const
{
	std::lock_guard< std::mutex > lock( mMutex );
	return mHandList;
}

} } // mndl::leap


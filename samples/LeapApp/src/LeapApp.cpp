/*
 Copyright (C) 2013 Gabor Papp

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "cinder/Cinder.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"

#include "LeapListener.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LeapApp : public AppBasic
{
	public:
		void prepareSettings( Settings *settings );
		void setup();

		void keyDown( KeyEvent event );

		void update();
		void draw();

	private:
		params::InterfaceGl mParams;

		float mFps;
		bool mVerticalSyncEnabled = false;

		Leap::Controller mLeapController;
		mndl::leap::LeapListener mLeapListener;
};

void LeapApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 800, 600 );
}

void LeapApp::setup()
{
	mParams = params::InterfaceGl( "Parameters", Vec2i( 200, 300 ) );
	mParams.addParam( "Fps", &mFps, "", true );
	mParams.addParam( "Vertical sync", &mVerticalSyncEnabled );

	mLeapController.addListener( mLeapListener );
}

void LeapApp::update()
{
	mFps = getAverageFps();

	if ( mVerticalSyncEnabled != gl::isVerticalSyncEnabled() )
		gl::enableVerticalSync( mVerticalSyncEnabled );
}

void LeapApp::draw()
{
	gl::clear( Color::black() );

	const Leap::HandList hands = mLeapListener.getHands();

	if ( !hands.isEmpty() )
	{
		// Get the first hand
		const Leap::Hand hand = hands[ 0 ];

		// Check if the hand has any fingers
		const Leap::FingerList fingers = hand.fingers();
		console() << "Hand has " << fingers.count() << endl;

		// Get the hand's sphere radius and palm position
		console() << "Hand sphere radius: " << hand.sphereRadius() << " mm, palm position: " << hand.palmPosition() << std::endl;

		// Get the hand's normal vector and direction
		Vec3f normal = mndl::leap::fromLeap( hand.palmNormal() );
		Vec3f direction = mndl::leap::fromLeap( hand.direction() );

		// Calculate the hand's pitch, roll, and yaw angles
		console() << "normal: " << normal << " dir: " << direction << endl;

/*
		std::cout << "Hand pitch: " << direction.pitch() * RAD_TO_DEG << " degrees, "
			<< "roll: " << normal.roll() * RAD_TO_DEG << " degrees, "
			<< "yaw: " << direction.yaw() * RAD_TO_DEG << " degrees" << std::endl;
*/
	}


	mParams.draw();
}

void LeapApp::keyDown( KeyEvent event )
{
	switch ( event.getCode() )
	{
		case KeyEvent::KEY_f:
			if ( !isFullScreen() )
			{
				setFullScreen( true );
				if ( mParams.isVisible() )
					showCursor();
				else
					hideCursor();
			}
			else
			{
				setFullScreen( false );
				showCursor();
			}
			break;

		case KeyEvent::KEY_s:
			mParams.show( !mParams.isVisible() );
			if ( isFullScreen() )
			{
				if ( mParams.isVisible() )
					showCursor();
				else
					hideCursor();
			}
			break;

		case KeyEvent::KEY_v:
			 mVerticalSyncEnabled = !mVerticalSyncEnabled;
			 break;

		case KeyEvent::KEY_ESCAPE:
			quit();
			break;

		default:
			break;
	}
}

CINDER_APP_BASIC( LeapApp, RendererGl )


#include "ofMain.h"
#include "ofApp.h"
#include "../TestMatrix3.h"
#include "../TestMatrix4.h"
#include "../TestQuaternion.h"

//========================================================================
int main( ){

	// Tests Matrix3, Matrix4 and Quaternion
	TestMatrix3 testMatrix3;
	testMatrix3.runTestMatrix3();
	TestMatrix4 testMatrix4;
	testMatrix4.runTestMatrix4();
	TestQuaternion testQuaternion;
	testQuaternion.runTests();

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setSize(1536, 1152);
	settings.windowMode = OF_FULLSCREEN; //can also be OF_WINDOW

	auto window = ofCreateWindow(settings);

	ofRunApp(window, make_shared<ofApp>());
	ofRunMainLoop();

}

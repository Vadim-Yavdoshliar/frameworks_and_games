
#include "_conditions.h"

#ifndef _gAPP_test_

#include "windowSystem.h"
#include <iostream>
#include <exception>


// ---------------------------------------*****
// [T E S T]                              *****
// Function for multiple window procedure *****
//                                        *****
// ---------------------------------------*****

#ifdef _TEST_
WindowProcedureFunction(cwndproc_1) {

	static std::chrono::time_point<std::chrono::system_clock> start =
		std::chrono::system_clock::now();
	static std::chrono::duration<double> duration;
	static std::chrono::duration<double> durationPrev;
	durationPrev = duration;
	duration = std::chrono::system_clock::now() - start;

	if (duration.count() > durationPrev.count()+0.01) {
		win.setTitle(std::to_string(duration.count()).c_str());
#ifdef _DEBUG_INFO_
		OutputDebugStringA((std::to_string(duration.count()) + "\n").c_str());
#endif
	}
	
}
#endif



int WINAPI WinMain(HINSTANCE handler, HINSTANCE someTrashMaybe, LPSTR cmdParams, int wndStatus) {
	

	base_window a("newWin", 500, 500, -1, -1);

#ifdef _TEST_
	base_window b("newWin2", 300, 300, 100, 100, cwndproc_1);
	base_window c("newWin3", 300, 400, 100, 500);

	b.setPosition(2000, 1000);
	c.setSize(1000, 1000);
#endif

#ifdef _DEBUG_INFO_
	try {

		base_window::processWindows();
	}
	catch (std::exception& ex) { OutputDebugStringA(ex.what()); }
	base_window::clearWindowList();
#else
	base_window::processWindows();
	base_window::clearWindowList();
#endif
	return 0;
}


#endif // !_gAPP_test_

#ifdef _gAPP_test_

//#define _STREAMING_TEST_

#include "gApp.h"
#include <string>

class MyGame : public gAPP {

	Sprite* s;
	Sprite* s1;
	Sprite* s2;
	int counter = 0;
	float a = 0;
	void initFrameworkResources() override{
	
	}
	void init() override {
		 s = createSprite("Sprites\\Screenshot_2.png");
		 s1 = createSprite("Sprites\\chest_with_tongue_pixels.png");
		 s2 = createSprite("Sprites\\spaceShip.png");
	}
	void tick() override {
		
		drawSprite(s, 0, 0);
		drawSprite(s1, 300, 100);
		drawSprite(s2, a, 0);
		if (a < 500) a += 3;
	}
	void gKeyPressed(gKey k) override { 

	}
	void mouseKeyPressed(mouseKey) override {
	
	}
	void gKeyReleased(gKey k) override {

	}
	void mouseKeyReleased(mouseKey) override {
	}
	void mousePosition(int x,int y) override {
	}
	void charInput(char symbol) {

	}
	~MyGame() {
		delete s;
		delete s1;
	}
};

_MAIN_DECL_{

	
	return runApp(new MyGame);
	
}

#endif // _gAPP_test_







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

	Sprite* s = nullptr;
	Sprite* s1 = nullptr;
	//Sprite* s2=nullptr;
	//Sprite* s3;

	float a = 200, b = 200;
	int angle = 1;
	void initFrameworkResources() override{
	
	}
	void init() override {
		s1 = createSprite("Sprites\\Ball.png");
		//s1 = createSprite("Sprites\\chest_with_tongue_pixels.png");
		s = createSprite("Sprites\\Wood.png");
		
		//s3 = getSpriteCopy(s1);

		// int v1, v2;
		 //getSpriteSize(s2, v1, v2);
		 //setSpriteSize(s2, v1 / 4, v2 / 4);
		 //getSpriteSize(s1, v1, v2);
		 //setSpriteSize(s1, v1 / 2, v2/2);
		// setSpriteSize(s, v1 / 2, v2 / 2);
		// setSpritePosition(s1, 400, 100);

		 //setSpritePosition(s1,100, 100);
		 //rotateSpriteZ(s1, angle);
		 setSpritePosition(s, 150, 150);
		 rotateSpriteX(s, angle);

		// makeSpriteVisible(s3, true);
		// makeSpriteVisible(s2,true);
		// makeSpriteVisible(s1,true);
		 //makeSpriteVisible(s1,true);
		 makeSpriteVisible(s, true);
	}
	void tick() override {
		angle=(angle+1)%360;
		int aY = angle % 80;
		//rotateSpriteZ(s1, -angle);
		//rotateSpriteZ(s, angle);
		rotateSpriteX(s, angle);
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
		//delete s2;
		//delete s3;
	}
};

_MAIN_DECL_{

	
	return runApp(new MyGame);
	
}

#endif // _gAPP_test_






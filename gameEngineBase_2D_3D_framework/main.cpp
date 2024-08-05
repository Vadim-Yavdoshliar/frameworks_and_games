
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

#include "gApp.h"

class MyGame : public gAPP {

	void init() override {}
	void tick() override {}
	void gKeyPressed(gKey) override {}
	void mouseKeyPressed(mouseKey) override {}
	void gKeyReleased(gKey) override {}
	void mouseKeyReleased(mouseKey) override {}
	void gKeyHeld(gKey) override {}
	void mouseKeyHeld(mouseKey) override {}
};

_MAIN_DECL_{

	
	return runApp(new MyGame);
	
}

#endif // _gAPP_test_






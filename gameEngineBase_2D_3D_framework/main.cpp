
#include "windowSystem.h"

void cwndproc_1(base_window& win ,UINT& msg, WPARAM wp, LPARAM lp) {
	static clock_t start = clock();
	clock_t end = clock();
	if ((end - start) / CLOCKS_PER_SEC == 5) win.show();

}

int WINAPI WinMain(HINSTANCE handler, HINSTANCE someTrashMaybe, LPSTR cmdParams, int wndStatus) {
	

	base_window a("newWin", 500, 500, -1, -1, cwndproc_1);

	base_window b("newWin2", 300, 300, 100, 100);

	base_window c("newWin3", 200, 400, 100, 500);

	a.hide();

	base_window::processWindows();

	base_window::clearWindowList();

	return 0;
}
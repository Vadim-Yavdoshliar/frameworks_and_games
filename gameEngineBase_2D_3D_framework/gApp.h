

#ifndef _gAPP_

#define _gAPP_

#define runApp(gAppInst) gAPP::run(gAppInst);

#define _MAIN_DECL_ int WINAPI WinMain(HINSTANCE handler, HINSTANCE someTrashMaybe, LPSTR cmdParams, int wndStatus)

#include <string>

class Sprite;

Sprite* createSprite(const char*);
void getSpriteSize(int& x, int& y);
void drawSprite(Sprite*);
void resizeSprite(Sprite*,int width,int heith);
void rotateSprite(Sprite*);
void replaceSprite(Sprite*);

class gAPP {

protected:

	const char* gName = "My new game";
	int width = 500, height = 500;

public:

	enum gKey {
		ForwardKey,
		BackwardKey,
		LeftKey,
		RightKey,
		SpaceKey,
		ShiftKey,
		CtrlKey,
		TabKey,
		EscKey,
		BackspaceKey,
		EnterKey
	};

	enum mouseKey {
		LPressed,
		LReleased,
		RPressed,
		RReleased,
		MPressed,
		MReleased,
		SidePressed,
		SideReleased,
		WheelUp,
		WheelDown,
		none
	};

public:
	virtual void initFrameworkResources() = 0;
	// Initialisation of all objects you need
	virtual void init() = 0;

	// Actions which must be handled every tick
	virtual void tick() = 0;
	

	// User's input processing functions

	virtual void gKeyPressed(gKey) = 0;
	virtual void mouseKeyPressed(mouseKey) = 0;

	virtual void gKeyReleased(gKey) = 0;
	virtual void mouseKeyReleased(mouseKey) = 0;

	virtual void mousePosition(int x, int y) = 0;

	static int run(gAPP*);

	void openTextStream();
	std::string closeTextStream();
	virtual void charInput(char) = 0;

};

#endif // !_gAPP_


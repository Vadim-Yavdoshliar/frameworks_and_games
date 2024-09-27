

#ifndef _gAPP_

#define _gAPP_

#define runApp(gAppInst) gAPP::run(gAppInst);

#define _MAIN_DECL_ int WINAPI WinMain(HINSTANCE handler, HINSTANCE someTrashMaybe, LPSTR cmdParams, int wndStatus)

#include <string>

class Sprite;

Sprite* createSprite(const char*);
Sprite* getSpriteCopy(Sprite*);

void makeSpriteVisible(Sprite*, bool OnOff);
void getSpriteSize(Sprite*,int& width, int& height);
void setSpriteSize(Sprite*,int width,int height);
void getSptitePosition(Sprite*,int& x,int& y);
void rotateSprite(Sprite*);
void setSpritePosition(Sprite*, int x, int y);


class gAPP {

protected:

	const char* gName = "My new game";
	int width = 800, height = 700;

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


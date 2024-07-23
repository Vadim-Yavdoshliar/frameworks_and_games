

#ifndef _gAPP_

#define _gAPP_

class gAPP {

protected:

	enum gKey {
		ForwardKey,
		BackwardKey,
		LeftKey,
		RightKey,
		SpaceKey,
		ShiftKey,
		CtrlKey,
		TabKey
	};

	enum menuKey {
		EscKey,
		BackspaceKey,
		EnterKey
	};

	enum mouseKey {
		Left,
		Right
	};

public:

	virtual void tick() = 0;
	virtual void init() = 0;
	virtual void gKeyPressed() = 0;
	virtual void menuKeyPressed() = 0;
	virtual void mouseKeyPressed() = 0;

	static int run(gAPP*);

};

#endif // !_gAPP_


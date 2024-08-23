
#ifndef _SPRITE_
#define _SPRITE_

#include "gApp.h"
#include "windowSystem.h"

COM::ComPtr<ID3D11Texture2D> getPictureTexture(const char* filePath);



class Sprite
{

public:
	
<<<<<<< HEAD
=======
	vecXY pos;
	vecXY UV;
};

corner spriteRectangle[4];



public:

	static void initShaders();
	static void initLayout();
	static void initBlend();

	virtual void draw();
>>>>>>> ed13ef4 (Sprite transparency)
	
	Sprite(const char*);

	~Sprite();

};





#endif
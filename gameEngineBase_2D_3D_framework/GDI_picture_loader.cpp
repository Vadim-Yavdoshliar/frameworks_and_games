#include "GDIPlusController.h"



COM::ComPtr<ID3D11Texture2D> getPictureTexture(const char* filePath)
{
    initGDIPlus();
    std::wstring wideFilePath(filePath, filePath + strlen(filePath));
    Gdiplus::Bitmap image(wideFilePath.c_str());
    if (image.GetLastStatus() != Ok) {
        return nullptr;
    }

    UINT width = image.GetWidth();
    UINT height = image.GetHeight();
    std::vector<BYTE> pixels(height * width*4);

    for (UINT y = 0; y < height; y++) {
        for (UINT x = 0; x < width; x++) {
            Color color;
            image.GetPixel(x, y, &color);
            pixels[(x + y * width) * 4 + 0] = color.GetB();
            pixels[(x + y * width) * 4 + 1] = color.GetB();
            pixels[(x + y * width) * 4 + 2] = color.GetB();
            pixels[(x + y * width) * 4 + 3] = color.GetB();
        }
    }

    auto desc = D3D11_TEXTURE2D_DESC();
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    D3D11_SUBRESOURCE_DATA imData = {0};
    imData.pSysMem = pixels.data();
    imData.SysMemPitch = width * 4;

    COM::ComPtr<ID3D11Texture2D> texture;
    HRESULT hr = base_window::gameWindow->graphicsStation->getDevice()->CreateTexture2D(&desc,&imData, &texture);
    if (FAILED(hr)) {
        return nullptr;
    }
	return texture;
}



void drawTextureTest() {
    
  
}

// additional functions
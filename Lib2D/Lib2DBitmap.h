#pragma once
#include "lib2dshape.h"
#include <string>
#include <atlbase.h>
using namespace std;
class Lib2DBitmap :
	public Lib2DShape
{
public:
	Lib2DBitmap(void);
	~Lib2DBitmap(void);
	void LoadBitmapFromFile(string uri, UINT width, UINT height);
private:
	CComPtr<IWICImagingFactory> m_wicFactory;
};


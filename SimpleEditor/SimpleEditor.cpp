// SimpleEditor.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SimpleEditor.h"
#include <WinLib.h>
#include <Windows.h>
#include <CommCtrl.h>
#include <d2d1_1.h>
#include <d2d1_1helper.h>
#include <Lib2DDevice.h>
#include <Lib2DFactory.h>
#include <Lib2DBitmap.h>
#include <Lib2DBitmapBrush.h>
#include <Lib2DFactory.h>
#include <Lib2DRect.h>
#include <Lib2DLinearAnimation.h>
#include <vector>
#include <Lib2DAnimatedShape.h>
#include <Lib2DLinearAnimation.h>
//#pragma comment(lib,"Lib3D.lib")
#pragma comment(lib,"Comctl32.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "winmm.lib")
#include <d2d1helper.h>
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    INITCOMMONCONTROLSEX icex;
    icex.dwICC = ICC_STANDARD_CLASSES;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    InitCommonControlsEx(&icex);

    LIBSTRING name(L"test");
    Window mywin(name);
    mywin.X=0;
    mywin.Y=0;
    mywin.Width=640;
    mywin.Height=480;
    mywin.ExStyle = WS_EX_CLIENTEDGE;
    mywin.WndStyle = WS_OVERLAPPEDWINDOW;
    mywin.initWindow(SW_SHOWNORMAL);
    mywin.onDestroy = [](){PostQuitMessage(0);};
    /*
    Device device(mywin.Hwnd);
    
    float color[4];
    color[0]=255.0f;
    color[1]=0.0f;
    color[2]=0.0f;
    color[3]=1.0f;
    
    device.d3dDeviceContext->ClearRenderTargetView(device.pRenderTargetView,color);
    device.swapChain->Present(0,0);
    */
    

    Lib2DFactory factory(mywin.Hwnd);
    Lib2DDevice device = *factory.createLib2DDevice();
    Lib2DDeviceContext context = *device.getContext();
    Lib2DLinearAnimation anim(0.0,0.0);
    context.setTarget(factory.getBackBuffer());
    Lib2DBitmap bmp;
    bmp.LoadBitmapFromFile("testBitmap.bmp");
    bmp.BindToRenderTarget(context.getDeviceContext());
    Lib2DBitmapBrush bmpBrush(bmp.getBitmap(),context.getDeviceContext());
    std::vector<ILib2DShape*> commands;
    Lib2DRect rect(D2D1::RectF(100.0,100.0,bmp.getBitmap()->GetSize().height,bmp.getBitmap()->GetSize().width),bmpBrush.getBrush(), true);
    Lib2DAnimatedShape animShape(&anim, &rect);
    commands.push_back(&rect);
    DWORD initialTime = GetTickCount();
    DWORD dt = 0;
    mywin.onKeyDown = [&dt, &anim, &rect](WCHAR key){
        switch (key)
        {
        case VK_LEFT:
            anim = Lib2DLinearAnimation(-50,0,dt,dt+10000);
            break;
        case VK_RIGHT:
            anim = Lib2DLinearAnimation(50,0,dt,dt+10000);
            break;
        case VK_UP:
            anim = Lib2DLinearAnimation(0,-50,dt,dt+10000);
            break;
        case VK_DOWN:
            anim = Lib2DLinearAnimation(0,50,dt,dt+10000);
            break;
        default:
            break;
        }
    };
    
    mywin.onNoMessage = [&animShape, &initialTime, &dt, &context, &commands, &factory](){
        
        animShape.update(dt);
        context.Clear();
        context.DrawShapes(commands);
        factory.getSwapChain()->Present(1,0);
        dt = GetTickCount() - dt;
    };
    //context.DrawShapes(commands);
    //factory.getSwapChain()->Present(1,0);
    mywin.libStartWindow();
    

    
    
}
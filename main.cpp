#include "app.h"

using namespace std;

LRESULT CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

const char *progName = "Igrek Chords Studio";

App *app = new App(220,430,"2.1.6",31);

LRESULT CALLBACK wndproc_new(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	return app->subclass_wndproc_new(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK HookProcKb(int nCode, WPARAM wParam, LPARAM lParam){
	if(nCode<0) return CallNextHookEx(app->hHookkb, nCode, wParam, lParam);
	if(app->keyboard_hook(wParam,lParam)==1) return 1;
	return CallNextHookEx(app->hHookkb, nCode, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	app->setInstance(&hInstance);
	app->hpkb = HOOKPROC(HookProcKb);
	app->windowProc = windowProc;
	app->wndproc_new = wndproc_new;
	app->clear_file("log.txt");
	app->log("Hello World...");
	app->get_argv(lpCmdLine);
	WNDCLASS windowClass;
	windowClass.lpfnWndProc = windowProc;
	windowClass.style       = CS_HREDRAW | CS_VREDRAW;
	windowClass.hInstance   = hInstance;
	windowClass.hCursor     = LoadCursor(NULL, IDC_ARROW);
	windowClass.hIcon       = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hbrBackground=(HBRUSH)COLOR_BTNSHADOW;
	windowClass.cbClsExtra  = 0;
	windowClass.cbWndExtra  = 0;
	windowClass.lpszClassName = progName;
	windowClass.lpszMenuName  = NULL;
	if(!RegisterClass(&windowClass)){
		app->log("! RegisterClass failed");
		return 0;
	}
	HWND window = CreateWindowEx(0,progName,progName,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,app->window_w+16,app->window_h+38,NULL,NULL,hInstance,NULL);
	if(!window){
		app->log("! window NULL pointer");
		return 0;
	}
	ShowWindow(window,nCmdShow);
	UpdateWindow(window);
	MSG message;
	while(GetMessage(&message, NULL, 0, 0)){
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return message.wParam;
}

LRESULT CALLBACK windowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch(message){
		case WM_CREATE:{
			app->wm_create(&hwnd);
		}break;
		case WM_COMMAND:{
			app->wm_command(wParam);
		}break;
		case WM_CHAR:{
			app->wm_char(wParam);
		}break;
		case WM_DESTROY:{
			delete app;
			return 0;
		}break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

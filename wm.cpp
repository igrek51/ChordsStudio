#include "app.h"
#include <commctrl.h>
#include <richedit.h>

void App::wm_create(HWND *window){
	hwnd = *window;
	//kontrolki
	hctrl[0]=CreateWindowEx(WS_EX_CLIENTEDGE,WC_EDIT,"",WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL,0,20,window_w,20,hwnd,0,*hInst,0); //wiersz poleceñ
	hctrl[1]=CreateWindowEx(0,WC_STATIC,"",WS_CHILD|WS_VISIBLE|SS_CENTER|SS_CENTERIMAGE,0,0,window_w,20,hwnd,0,*hInst,0); //konsola
	hctrl[2]=CreateWindowEx(0,WC_BUTTON,"Przechwytywanie klawiszy [F11]",WS_CHILD|WS_VISIBLE|BS_CHECKBOX,25,40,180,20,hwnd,(HMENU)1,*hInst,0);
	//groupbox1
	hctrl[3]=CreateWindowEx(0,WC_BUTTON,"Akordy",WS_CHILD|WS_VISIBLE|BS_GROUPBOX,10,60,window_w-20,150,hwnd,(HMENU)0,*hInst,0);
	for(int i=0; i<12; i++){
		hctrl[4+i]=CreateWindowEx(0,WC_BUTTON,"",WS_CHILD|WS_VISIBLE,20+(i%3)*60,80+(i/3)*30,60,30,hwnd,(HMENU)(2+i),*hInst,0);
	}
	//groupbox2
	hctrl[16]=CreateWindowEx(0,WC_BUTTON,"Rodzaj akordu",WS_CHILD|WS_VISIBLE|BS_GROUPBOX,10,215,window_w-20,140,hwnd,(HMENU)0,*hInst,0);
	hctrl[17]=CreateWindowEx(0,WC_BUTTON,"Pojedynczy dŸwiêk",WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON,30,230,160,20,hwnd,(HMENU)14,*hInst,0);
	hctrl[18]=CreateWindowEx(0,WC_BUTTON,"Power chord",WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON,30,250,160,20,hwnd,(HMENU)15,*hInst,0);
	hctrl[19]=CreateWindowEx(0,WC_BUTTON,"Akord molowy",WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON,30,270,160,20,hwnd,(HMENU)16,*hInst,0);
	hctrl[20]=CreateWindowEx(0,WC_BUTTON,"Akord durowy",WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON,30,290,160,20,hwnd,(HMENU)17,*hInst,0);
	hctrl[21]=CreateWindowEx(0,WC_BUTTON,"Akord molowy septymowy",WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON,30,310,160,20,hwnd,(HMENU)18,*hInst,0);
	hctrl[22]=CreateWindowEx(0,WC_BUTTON,"Akord durowy septymowy",WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON,30,330,160,20,hwnd,(HMENU)19,*hInst,0);
	//kapodaster
	hctrl[23]=CreateWindowEx(0,WC_STATIC,"Kapodaster",WS_CHILD|WS_VISIBLE|SS_CENTER|SS_CENTERIMAGE,55,360,110,25,hwnd,0,*hInst,0);
	hctrl[24]=CreateWindowEx(0,WC_BUTTON,"-1",WS_CHILD|WS_VISIBLE,30,360,25,25,hwnd,(HMENU)20,*hInst,0);
	hctrl[25]=CreateWindowEx(0,WC_BUTTON,"+1",WS_CHILD|WS_VISIBLE,165,360,25,25,hwnd,(HMENU)21,*hInst,0);
	hctrl[26]=CreateWindowEx(0,WC_BUTTON,"-12",WS_CHILD|WS_VISIBLE,5,360,25,25,hwnd,(HMENU)22,*hInst,0);
	hctrl[27]=CreateWindowEx(0,WC_BUTTON,"+12",WS_CHILD|WS_VISIBLE,190,360,25,25,hwnd,(HMENU)23,*hInst,0);
	//g³oœnoœæ
	hctrl[28]=CreateWindowEx(0,WC_STATIC,"G³oœnoœæ",WS_CHILD|WS_VISIBLE|SS_CENTER|SS_CENTERIMAGE,60,390,100,25,hwnd,0,*hInst,0);
	hctrl[29]=CreateWindowEx(0,WC_BUTTON,"-",WS_CHILD|WS_VISIBLE,30,390,25,25,hwnd,(HMENU)24,*hInst,0);
	hctrl[30]=CreateWindowEx(0,WC_BUTTON,"+",WS_CHILD|WS_VISIBLE,165,390,25,25,hwnd,(HMENU)25,*hInst,0);
	//haki
	hExe = GetModuleHandle(NULL);
	hHookkb = SetWindowsHookEx(WH_KEYBOARD_LL, hpkb, hExe, 0);
	//ustawienia
	load_config();
	//ustawienia pocz¹tkowe
	checkbox1_click(1);
	radiobutton1_click(2);
	kapodaster=0;
	capo_add(0);
	volume=100;
	volume_add(0);
	//czcionki
	fontsize=13;
	fontface="MS Shell Dlg 2";
	for(int i=0; i<ctrls_num; i++){
		change_font(hctrl[i]);
	}
	SetFocus(hctrl[0]);
	//subclassing
	subclass(0);
	//midi init
	midi_device=midi_init();
	echo("wersja "+version);
}

void App::wm_command(WPARAM wParam){
	if(wParam==1){ //przechwytywanie klawiszy
		checkbox1_click();
	}
	if(wParam>=2&&wParam<=13){ //wybór rodzaju akordu
		button_chord(wParam-2);
	}
	if(wParam>=14&&wParam<=19){ //wybór rodzaju akordu
		radiobutton1_click(wParam-13);
	}
	if(wParam==20) capo_add(-1);
	if(wParam==21) capo_add(+1);
	if(wParam==22) capo_add(-12);
	if(wParam==23) capo_add(+12);
	if(wParam==24) volume_add(-10);
	if(wParam==25) volume_add(+10);
}

void App::wm_char(WPARAM wParam){
	CallWindowProc(wndproc_new, hctrl[0], WM_CHAR, wParam, NULL);
}

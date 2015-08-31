#include "app.h"
#include <richedit.h>

LRESULT CALLBACK App::subclass_wndproc_new(HWND hwdp, UINT message, WPARAM wParam, LPARAM lParam){
	//rozpoznanie numeru kontrolki
	int ctrl=-1;
	for(int i=0; i<ctrls_num; i++){
		if(hwdp==hctrl[i]){
			ctrl=i;
			break;
		}
	}
	if(ctrl==-1) return 0;
	//nowe procedury kontrolek
	if(ctrl==0){ //wiersz poleceñ
		switch(message){
			case WM_CHAR:{
				if(wParam==VK_ESCAPE){
					SetFocus(hwnd);
					return 0;
				}
				if(wParam==VK_RETURN){
					exec_cmd();
					return 0; //przechwycenie
				}

				if(!checkbox1){
					if(wParam=='c'){ //c
						button_chord(0);
					}
					if(wParam=='C'){ //c#
						button_chord(1);
					}
					if(wParam=='d'){ //d
						button_chord(2);
					}
					if(wParam=='D'){ //d#
						button_chord(3);
					}
					if(wParam=='e'){ //e
						button_chord(4);
					}
					if(wParam=='f'){ //f
						button_chord(5);
					}
					if(wParam=='F'){ //f#
						button_chord(6);
					}
					if(wParam=='g'){ //g
						button_chord(7);
					}
					if(wParam=='G'){ //g#
						button_chord(8);
					}
					if(wParam=='a'){ //a
						button_chord(9);
					}
					if(wParam=='b'){ //b
						button_chord(10);
					}
					if(wParam=='h'){ //h
						button_chord(11);
					}
				}


			}break;
		}
	}
	return CallWindowProc(wndproc_old[ctrl], hwdp, message, wParam, lParam);
}

void App::subclass(int ctrl){
	wndproc_old[ctrl] = (WNDPROC) SetWindowLong(hctrl[ctrl],GWL_WNDPROC,(LONG)wndproc_new);
}

void App::un_subclass(int ctrl){
	if(wndproc_old[ctrl]==NULL) return;
	SetWindowLong(hctrl[ctrl],GWL_WNDPROC,(LONG)wndproc_old[ctrl]);
}

#include "app.h"

int App::keyboard_hook(WPARAM wParam, LPARAM lParam){
	KBDLLHOOKSTRUCT h_key = *((KBDLLHOOKSTRUCT*)lParam);
	if(wParam==WM_KEYDOWN||wParam==WM_SYSKEYDOWN){
		if(h_key.vkCode==VK_F11){
   		checkbox1_click(); return 1;
   	}
		if(checkbox1==false) return 0;
		//akordy
		if(!(GetAsyncKeyState(VK_CONTROL)&0x8000)){ //bez kontrola
      if(h_key.vkCode=='C'&&!(GetAsyncKeyState(VK_SHIFT)&0x8000)){ //c
        button_chord(0);
        if(GetFocus()!=hctrl[0]) return 1;
      }
      if(h_key.vkCode=='C'&&GetAsyncKeyState(VK_SHIFT)&0x8000){ //c#
        button_chord(1);
        if(GetFocus()!=hctrl[0]) return 1;
      }
		}
		if(h_key.vkCode=='D'&&!(GetAsyncKeyState(VK_SHIFT)&0x8000)){ //d
   		button_chord(2);
   		if(GetFocus()!=hctrl[0]) return 1;
		}
		if(h_key.vkCode=='D'&&GetAsyncKeyState(VK_SHIFT)&0x8000){ //d#
   		button_chord(3);
   		if(GetFocus()!=hctrl[0]) return 1;
		}
		if(h_key.vkCode=='E'){ //e
   		button_chord(4);
   		if(GetFocus()!=hctrl[0]) return 1;
		}
		if(h_key.vkCode=='F'&&!(GetAsyncKeyState(VK_SHIFT)&0x8000)){ //f
   		button_chord(5);
   		if(GetFocus()!=hctrl[0]) return 1;
		}
		if(h_key.vkCode=='F'&&GetAsyncKeyState(VK_SHIFT)&0x8000){ //f#
   		button_chord(6);
   		if(GetFocus()!=hctrl[0]) return 1;
		}
		if(h_key.vkCode=='G'&&!(GetAsyncKeyState(VK_SHIFT)&0x8000)){ //g
   		button_chord(7);
   		if(GetFocus()!=hctrl[0]) return 1;
		}
		if(h_key.vkCode=='G'&&GetAsyncKeyState(VK_SHIFT)&0x8000){ //g#
   		button_chord(8);
   		if(GetFocus()!=hctrl[0]) return 1;
		}
		if(h_key.vkCode=='A'){ //a
   		button_chord(9);
   		if(GetFocus()!=hctrl[0]) return 1;
		}
		if(h_key.vkCode=='B'){ //b
   		button_chord(10);
   		if(GetFocus()!=hctrl[0]) return 1;
		}
		if(h_key.vkCode=='H'){ //h
   		button_chord(11);
   		if(GetFocus()!=hctrl[0]) return 1;
		}
		if((GetAsyncKeyState(VK_CONTROL)&0x8000)&&!(GetAsyncKeyState(VK_MENU)&0x8000)){ //ctrl
			if(h_key.vkCode=='0'||h_key.vkCode==VK_NUMPAD0){
				capo_add(-kapodaster); return 1;
			}
		}
	}
	return 0;
}

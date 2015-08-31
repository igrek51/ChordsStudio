#ifndef APP_H
#define APP_H

#include <windows.h>
#include <sstream>

using namespace std;

class App{
public:
	App(int w, int h, string version, int ctrls = 0);
	~App();
	HWND *hctrl;
	void setInstance(HINSTANCE *hInst);
	int window_w, window_h;
	string version;
	//io
	string *argv;
	int argc;
	void get_argv(LPSTR lpCmdLine);
	bool is_arg(string par);
	void clear_file(string filename);
	void log(string l);
	void log(int l);
	void echo(string s);
	void echo(int e);
	void echo();
	bool file_exists(string name);
	void message(string m);
	void ss_clear(stringstream &sstream);
	stringstream ss;
	//config
	void load_config();
	void reload_config();
	int instrument, basetone, keyshift;
	//WM
	void wm_create(HWND *window);
	void wm_command(WPARAM wParam);
	void wm_char(WPARAM wParam);
	//cmd
	string last_cmd, param;
	void exec_cmd();
	void exec_cmd(char *str2);
	//subclassing
	WNDPROC windowProc, wndproc_new, *wndproc_old;
	LRESULT CALLBACK subclass_wndproc_new(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	void subclass(int ctrl);
	void un_subclass(int ctrl);
	//hook
	HHOOK hHookkb;
	HINSTANCE hExe;
	HOOKPROC hpkb;
	int keyboard_hook(WPARAM wParam, LPARAM lParam);
	//czcionki
	int fontsize;
	string fontface;
	void change_font(HWND hwdp);
	//program - inne funkcje
	int checkbox1;
	void checkbox1_click(int set=2);
	int radiobutton1;
	void radiobutton1_click(int set);
	int kapodaster;
	void capo_add(int add);
	int volume;
	void volume_add(int add);
	void refresh_buttons12();
	void button_chord(int button_nr);
	//midi
	HMIDIOUT *midi_device;
	HMIDIOUT* midi_init();
	void midi_play_note(int note);
	void midi_play_chord(int note, int chord_type);
	void midi_close(HMIDIOUT *midi_device);
private:
	int ctrls_num;
	HWND hwnd;
	HINSTANCE* hInst;
};

#endif // APP_H

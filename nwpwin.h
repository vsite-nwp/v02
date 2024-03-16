#include <windows.h>
#include <string>
#include <tchar.h>
#ifdef UNICODE
#define to_tstring std::to_wstring
#else
#define to_tstring std::to_string
#endif

namespace vsite::nwp {

class application
	/*Služi za globalne stvari. Sakriva nam message petlju.
	U WinMainu bi trebali moæi pozvati samo run od applicationa jer se
	unutra krije message loop.*/
{
public:
	int run();
};

class window
{
	HWND hw { 0 };

protected:
	/*class_name je virtualna funkcija. Znaèi ako ju overrideamo i damo
	neki class name tipa button ili listbox, pa ne bude prazan, æe
	zvati CreateWindow s njim (vidi definiciju).*/
	virtual std::string class_name();
	bool register_class(const std::string& name);
	std::string generate_class_name();

public:
	bool create(HWND parent, DWORD style, LPCTSTR caption = 0, int id_or_menu = 0,
		int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int width = CW_USEDEFAULT, int height = CW_USEDEFAULT);

	operator HWND();
	static LRESULT CALLBACK proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);  // Funkcija koja glumi Window proceduru.

	//	messages
protected:
	virtual int on_create(CREATESTRUCT*) { return 0; }
	virtual void on_command(int) { }
	virtual void on_destroy() { }
};

void set_icons(HINSTANCE instance, HWND window, int icon_id);

} // namespace

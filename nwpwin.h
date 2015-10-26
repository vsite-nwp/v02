#include <windows.h>
#include <string>

class Application 
{
public:
	int Run();
};

class Window
{
	HWND hw;

protected:
	virtual std::string ClassName();
	bool Register(const std::string& name);
	std::string GenerateClassName();

public:
	Window();

	bool Create(HWND parent, DWORD style, PCSTR caption=0, int IdOrMenu=0, 
		int x=CW_USEDEFAULT, int y=CW_USEDEFAULT, int width=CW_USEDEFAULT, int height=CW_USEDEFAULT);

	operator HWND();
	static LRESULT CALLBACK Proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

//	messages
protected:
	virtual int OnCreate(CREATESTRUCT*) { return 0; }
	virtual void OnCommand(int)  { }
	virtual void OnDestroy()  { }
};


class Edit : public Window
{
public:
	std::string ClassName(){ return "EDIT"; }
};

class Button : public Window
{
public:
	std::string ClassName(){ return "BUTTON"; }
};

class ListBox : public Window
{
public:
	std::string ClassName(){ return "LISTBOX"; }
};



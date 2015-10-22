#include <windows.h>
#include <string>

//Moji define-ovi za ovu konkretnu aplikaciju:
#define CW_XORIGIN 100
#define CW_YORIGIN 100
#define CW_WIDTH 300
#define CW_HEIGHT 300

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
		int x=CW_XORIGIN, int y=CW_YORIGIN, int width=CW_WIDTH, int height=CW_HEIGHT);

	operator HWND();
	static LRESULT CALLBACK Proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

//	messages
protected:
	virtual int OnCreate(CREATESTRUCT*) { return 0; }
	virtual void OnCommand(int)  { }
	virtual void OnDestroy()  { }
};

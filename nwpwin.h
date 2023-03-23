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
{
public:
	int run();
};

class window
{
	HWND hw { 0 };

protected:
	HWND addButton;
	HWND removeButton;

	virtual std::string class_name();
	bool register_class(const std::string& name);
	std::string generate_class_name();

public:
	bool create(HWND parent, DWORD style, LPCTSTR caption = 0, int id_or_menu = 0,
		int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int width = CW_USEDEFAULT, int height = CW_USEDEFAULT);

	operator HWND();
	static LRESULT CALLBACK proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	//	messages
protected:
	virtual int on_create(CREATESTRUCT*) { return 0; }
	virtual void on_command(int, int n = 0) { }
	virtual void on_destroy() { }
};

class listboxWindow : public window
{
protected:
	std::string class_name() override;
};

class editWindow : public window
{
protected:
	std::string class_name() override;
};

class buttonWindow : public window
{
protected:
	std::string class_name() override;
};

void set_icons(HINSTANCE instance, HWND window, int icon_id);

} // namespace


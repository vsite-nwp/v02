#include "nwpwin.h"

namespace vsite::nwp {

int application::run()
{
	MSG msg;
	while (::GetMessage(&msg, NULL, 0, 0)) {
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
	return msg.wParam;
}

std::string window::class_name()
{
	return std::string();
}

bool window::register_class(const std::string& name)
{
	WNDCLASS wc{};
	wc.lpfnWndProc = proc;
	wc.lpszClassName = name.c_str();
	wc.cbWndExtra = sizeof(window*);

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wc.hCursor = ::LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));

	return ::RegisterClass(&wc) != 0;
}

std::string window::generate_class_name()
{
	static int n = 1;
	return _T("NWP") + to_tstring(n++);
}

bool window::create(HWND parent, DWORD style, LPCTSTR caption, int id_or_menu,
	int x, int y, int width, int height)
{
	std::string cn = class_name();
	if (cn.empty())
		register_class(cn = generate_class_name());
	hw = ::CreateWindow(cn.c_str(), caption, style, x, y, width, height, parent, (HMENU)id_or_menu, 0, this);
	return hw != 0;
}

window::operator HWND()
{
	return hw;
}

LRESULT CALLBACK window::proc(HWND hw, UINT msg, WPARAM wp, LPARAM lp)
{
	if (msg == WM_CREATE) {
		CREATESTRUCT* pcs = reinterpret_cast<CREATESTRUCT*>(lp);
		window* pw = reinterpret_cast<window*>(pcs->lpCreateParams);
		::SetWindowLong(hw, 0, reinterpret_cast<long>(pw));
		pw->hw = hw;
		return pw->on_create(pcs);
	}

	window* pw = reinterpret_cast<window*>(::GetWindowLong(hw, 0));
	switch (msg)
	{
		case WM_COMMAND: pw->on_command(LOWORD(wp)); return 0;
		case WM_DESTROY: pw->on_destroy(); return 0;
	}
	return ::DefWindowProc(hw, msg, wp, lp);
}

void set_icons(HINSTANCE instance, HWND window, int icon_id)
{
	HICON hib = (HICON)::LoadImage(instance, MAKEINTRESOURCE(icon_id), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	::PostMessage(window, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hib));
	HICON his = (HICON)::LoadImage(instance, MAKEINTRESOURCE(icon_id), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	::PostMessage(window, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(his));
}

} // namespace

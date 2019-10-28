#include "nwpwin.h"
#include "res.h"
#include <sstream>
class Button : public Window
{
public: std::string ClassName() {
	return "Button";
}
};
class Edit : public Window
{
public: std::string ClassName() {
	return "Edit";
}
};
class ListBox : public Window
{
public: std::string ClassName() {
	return "ListBox";
}
};

class MainWindow : public Window
{
protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
};

int MainWindow::OnCreate(CREATESTRUCT* pcs)
{
	Button b1, b2;
	b1.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 400, 200, 60, 50);
	b2.Create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 400, 260, 60, 50);

	Edit e;
	e.Create(*this, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, "", IDC_EDIT, 300, 260, 40, 50);
	ListBox l;
	l.Create(*this, WS_VISIBLE | WS_CHILD | LBS_STANDARD | LBS_NOTIFY, "", IDC_LB, 300, 200, 100, 50);
	EnableWindow(b2, FALSE);
	return 0;
}

void MainWindow::OnCommand(int id) {
	switch (id) {
	case ID_FILE_EXIT:
		OnDestroy();
		break;

	case ID_HELP_ABOUT:
		MessageBox(*this, "Vjezba 2 NWP", "About", MB_OK | MB_ICONINFORMATION);
		break;

	case IDC_ADD:

		char text[50];
		if (GetDlgItemText(*this, IDC_EDIT, text, sizeof(text)))
		{
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)text);
			SetDlgItemText(*this, IDC_EDIT, "");

			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
		}
		break;


	case IDC_REMOVE:
		int place = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
		if (place == LB_ERR)
			return;
		SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, place, 0);
		if (!SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0))
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
		break;
	}
}

void MainWindow::OnDestroy()
{
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDM_V2));
	MainWindow w;
	w.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)hMenu);
	// set icons
	HICON hib = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	PostMessage(w, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hib));
	HICON his = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	PostMessage(w, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(his));

	Application a;
	return a.Run();
}
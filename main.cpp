#include "nwpwin.h"
#include "res.h"

class Button : public Window {
public:
	std::string ClassName() override { return "BUTTON"; }
};
class Edit : public Window {
public:
	std::string ClassName() override { return "EDIT"; }
};
class ListBox : public Window {
public:
	std::string ClassName() override { return "LISTBOX"; }
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
	Button b_add; b_add.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 110, 100, 100, 30);
	Button b_remove; b_remove.Create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 110, 140, 100, 30);
	Edit e; e.Create(*this, WS_CHILD | WS_VISIBLE|WS_BORDER, "Edit", IDC_EDIT, 110, 60, 100, 30);
	ListBox lb; lb.Create(*this, WS_CHILD | WS_VISIBLE|WS_BORDER, "ListBox", IDC_LB, 5, 50, 100, 150);

	EnableWindow(b_remove, false);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			DestroyWindow(*this);
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "Tekst", "HELP", MB_OK);
			break;
		case IDC_ADD:
			char text[200];
			GetDlgItemText(*this, IDC_EDIT, text, 200);
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)text);
			EnableWindow(GetDlgItem(*this,IDC_REMOVE), true);
			break;
		case IDC_REMOVE:
			LRESULT x;
			x = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			if (x != LB_ERR) {
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, x, 0);
			}
			if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0) <= 0) {
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
			}
			break;
	}
}

void MainWindow::OnDestroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDM_V2));
	MainWindow wnd; 
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)hMenu);	
	// set icons
	HICON hib = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hib));
	HICON his = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(his));

	Application app; 
	return app.Run();
}

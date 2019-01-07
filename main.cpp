#include "nwpwin.h"
#include "res.h"


class ListBox : public Window 
{
	std::string ClassName() override { return "LISTBOX"; }
};
class Edit : public Window
{
	std::string ClassName() override { return "EDIT"; }
};
class Button : public Window
{
	std::string ClassName() override { return "BUTTON"; }
};
class MainWindow : public Window
{
protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
	void Add();
	void Remove();
};

int MainWindow::OnCreate(CREATESTRUCT* pcs)
{
	ListBox lb;
	lb.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 50, 50, 100, 150);
	Button bt_add;
	bt_add.Create(*this, WS_CHILD | WS_VISIBLE , "Add", IDC_ADD, 200, 100, 100, 25);
	Button bt_rmv;
	bt_rmv.Create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "Remove", IDC_REMOVE, 200, 150, 100, 25);
	Edit ed;
	ed.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 200, 50, 100, 25);

	return 0;
}
void MainWindow::Remove() {
	LRESULT remove;

	remove = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
	if (remove != LB_ERR) {
		SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, (WPARAM)remove, 0);
		if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0) == 0)
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
	}
}
void MainWindow::Add() {
	char str[50];

	GetDlgItemText(*this, IDC_EDIT, str, 50);
	if (str[0] != NULL) {
		SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)str);
		EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
		SetDlgItemText(*this, IDC_EDIT, "");
	}
}
void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			OnDestroy();
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "text", "help", MB_OK);
			break;
		case IDC_ADD:
			Add();
			break;
		case IDC_REMOVE:
			Remove();
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

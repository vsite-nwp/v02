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
	
	ListBox lb;
	lb.Create(*this, WS_CHILD | WS_VISIBLE, "", IDC_LB, 50, 50, 100, 120);

	Edit ed;
	ed.Create(*this, WS_CHILD | WS_VISIBLE, "", IDC_EDIT, 150, 50, 100, 25);

	Button add;
	add.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 150, 85, 100, 25);

	Button remove;
	remove.Create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 150, 100, 100, 25);
	EnableWindow(remove, false);

	return 0;
}

void MainWindow::OnCommand(int id){
	char item[50];
	switch(id){
		case ID_FILE_EXIT:
			PostQuitMessage(0);
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "NWPL2", "About", MB_OK);
			break;
		case IDC_ADD:
			if (GetDlgItemText(*this, IDC_EDIT, item, sizeof(item) != 0)) {
				SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)item);
				SetDlgItemText(*this, IDC_EDIT, "");
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			}
			break;
		case IDC_REMOVE:
			HWND lb = GetDlgItem(*this, IDC_LB);
			int index = SendMessage(lb, LB_GETCURSEL, NULL, NULL);
			if (index != LB_ERR) {
				SendMessage(lb, LB_DELETESTRING, index, NULL);
			}
			if (SendMessage(lb, LB_GETCOUNT, NULL, NULL) == 0) {
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

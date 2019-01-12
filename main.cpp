#include "nwpwin.h"
#include "res.h"

class ListBox : public Window {
protected:
	std::string ClassName() override { return "LISTBOX"; }
};

class Button : public Window {
protected:
	std::string ClassName() override { return "BUTTON"; }
};

class Edit : public Window {
protected:
	std::string ClassName() override { return "EDIT"; }
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
	ListBox lBox;
	Edit ed;
	Button but1, but2;
	lBox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 50, 50, 100, 120);
	ed.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 170, 50, 100, 25);
	but1.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Add", IDC_ADD, 170, 80, 100, 25);
	but2.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Remove", IDC_REMOVE, 170, 110, 100, 25);
	EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
	return 0;
}

void MainWindow::OnCommand(int id){
	LRESULT sel;
	char text[50];
	switch(id){
		case ID_FILE_EXIT:
			PostQuitMessage(0);
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "Vježba 2", "About", MB_OK);
			break;
		case IDC_ADD:
			if (GetDlgItemText(*this, IDC_EDIT, text, sizeof(text)) != 0) {
				SendMessage(GetDlgItem(*this, IDC_LB), LB_ADDSTRING, 0, (LPARAM)text);
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
				SetDlgItemText(*this, IDC_EDIT, "");
			}
			break;
		case IDC_REMOVE:
			sel = SendMessage(GetDlgItem(*this, IDC_LB), LB_GETCURSEL, 0, 0);
			if (sel != LB_ERR) SendMessage(GetDlgItem(*this, IDC_LB), LB_DELETESTRING, (WPARAM)sel, 0);
			if ((int)SendMessage(GetDlgItem(*this, IDC_LB), LB_GETCOUNT, 0, 0) == 0) EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
			break;
		default:
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

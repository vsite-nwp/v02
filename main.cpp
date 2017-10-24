#include "nwpwin.h"
#include "res.h"

class Button : public Window {
public:
	std::string ClassName() override { return "Button";}
};

class Edit : public Window {
public:
	std::string ClassName() override { return "Edit"; }
};

class ListBox : public Window {
public:
	std::string ClassName() override { return "ListBox"; }
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
	Button c; c.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 150, 100, 50, 30);
	Button a; a.Create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 200, 100, 50, 30);
	Edit e; e.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 250, 100, 50, 30);
	ListBox BL; BL.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 300, 100, 50, 100);
	EnableWindow(a, false);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			OnDestroy();
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "You can do some things here, I hope...", "About", MB_ICONINFORMATION);
			break;
		case IDC_ADD:
			char chars[10];
			GetWindowText(GetDlgItem(*this, IDC_EDIT), chars, 10);
			SendMessage(GetDlgItem(*this, IDC_LB), LB_ADDSTRING, NULL, (LPARAM) chars);
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			break;
		case IDC_REMOVE:
			int x = SendMessage(GetDlgItem(*this, IDC_LB), LB_GETCURSEL, NULL, NULL);
			if (x != LB_ERR) 
				SendMessage(GetDlgItem(*this, IDC_LB), LB_DELETESTRING, x, NULL);
			x = SendMessage(GetDlgItem(*this, IDC_LB), LB_GETCOUNT, NULL, NULL);
			if(x == 0)
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
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

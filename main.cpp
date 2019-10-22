#include "nwpwin.h"
#include "res.h"

class Edit : public Window {
public:
	std::string ClassName() { return "Edit"; };
};
class Button : public Window {
public:
	std::string ClassName() { return "Button"; };
};
class ListBox : public Window {
public:
	std::string ClassName() { return "ListBox"; };
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
	Button btn1, btn2;
	ListBox lb1;
	Edit ed1;
	lb1.Create(*this, WS_CHILD | WS_BORDER | WS_VISIBLE, "", IDC_LB, 10, 10, 200, 300);
	ed1.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 220, 10, 160, 30);
	btn1.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 250, 50, 100, 30);
	btn2.Create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "Remove", IDC_REMOVE, 250, 90, 100, 30);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			DestroyWindow(*this);
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "You need help? Go get help.", "HELP!", MB_OK | MB_ICONQUESTION);
			break;
		case IDC_ADD:
			char text[30];
			GetDlgItemText(*this, IDC_EDIT, text, 30);
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)text);
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			break;
		case IDC_REMOVE:
			// TODO: get listbox selection
			// TODO: if there is a selection, delete selected string
			// TODO: disable "Remove" button if listbox is empty
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

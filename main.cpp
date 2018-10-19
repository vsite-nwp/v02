#include "nwpwin.h"
#include "res.h"


class ListBox :public Window {
protected:
	std::string ClassName() override { return "LISTBOX"; }
};

class Button :public Window {
protected:
	std::string ClassName() override { return "BUTTON"; }
};

class Edit :public Window {
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
	ListBox lb;
	lb.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 50, 50, 130, 150);
	Button add,remove;
	add.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 200, 100, 100, 30);
	remove.Create(*this, WS_CHILD|WS_DISABLED|WS_VISIBLE, "Remove", IDC_REMOVE, 200, 150, 100, 30);
	Edit ed;
	ed.Create(*this, WS_CHILD | WS_VISIBLE|WS_BORDER, "", IDC_EDIT, 200, 50, 100, 30);
	return 0;
}

void HandleAddButton(HWND hw,int id) {
	char buffer[50];
	GetDlgItemTextA(hw, IDC_EDIT, buffer, 50);
	LRESULT result = SendMessage(GetDlgItem(hw, IDC_LB), LB_ADDSTRING, NULL, (LPARAM)buffer);
	if (result != LB_ERR) {
		EnableWindow(GetDlgItem(hw, IDC_REMOVE), true);
		SetDlgItemText(hw, IDC_EDIT, "");
	}
}

void HandleRemoveButton(HWND hw,int id) {
	HWND lb = GetDlgItem(hw, IDC_LB);
	LRESULT result = SendMessage(lb, LB_GETCURSEL, NULL, NULL);
	LRESULT itemCount;
	if (result != LB_ERR) {
		SendMessage(lb, LB_DELETESTRING, (WPARAM)result, NULL);
		itemCount = SendMessage(lb, LB_GETCOUNT, 0, 0);
		if (!itemCount) {
			EnableWindow(GetDlgItem(hw, id), false);
		}
	}
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			OnDestroy();
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "This is second exercise", "About",MB_OK);
			break;
		case IDC_ADD:
			HandleAddButton(*this,id);
			break;
		case IDC_REMOVE:
			HandleRemoveButton(*this,id);
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

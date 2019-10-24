#include "nwpwin.h"
#include "res.h"

class Button : public Window {
protected:
	std::string ClassName() override { return "BUTTON"; }
};
class Edit : public Window {
protected:
	std::string ClassName() override { return "EDIT"; }
};
class ListBox : public Window {
protected:
	std::string ClassName() override { return "LISTBOX"; }
};

class MainWindow : public Window {
protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
	void OnAdd();
	void OnRemove();
};

int MainWindow::OnCreate(CREATESTRUCT* pcs) {
	ListBox lb;
	lb.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 30, 30, 200, 200);
	Edit edit;
	edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 300, 30, 100, 30);
	Button add, remove;
	add.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 300, 70, 100, 30);
	remove.Create(*this, WS_CHILD | WS_DISABLED | WS_VISIBLE, "Remove", IDC_REMOVE, 300, 110, 100, 30);

	return 0;
}

void MainWindow::OnAdd() {
	char buffer[30];
	if (!GetDlgItemText(*this, IDC_EDIT, buffer, sizeof(buffer)))
		return;
	LRESULT result = SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)buffer);
	if (result != LB_ERR) {
		EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
		SetDlgItemText(*this, IDC_EDIT, "");
	}
}

void MainWindow::OnRemove() {
	LRESULT cursel = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, (LPARAM)"");
	if (cursel != LB_ERR) {
		SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, (LPARAM)cursel, 0);
		LRESULT count = SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0);
		if (count == 0) {
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
		}
	}
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			OnDestroy();
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "Help is cool", "Help", MB_OK);
			break;
		case IDC_ADD:
			OnAdd();
			break;
		case IDC_REMOVE:
			OnRemove();
			break;
	}
}

void MainWindow::OnDestroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow) {
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

#include "nwpwin.h"
#include "res.h"

class Edit : public Window
{
protected:
	std::string ClassName() {
		return "EDIT";
	};
};

class Button : public Window
{
protected:
	std::string ClassName() {
		return "BUTTON";
	};
};

class ListBox : public Window
{
protected:
	std::string ClassName() {
		return "LISTBOX";
	};
};

class MainWindow : public Window
{
protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
	void onExit();
	void onAbout();
	void onAdd();
	void onRemove();
};

int MainWindow::OnCreate(CREATESTRUCT* pcs)
{
	Button add, remove;
	Edit edit;
	ListBox listBox;
	add.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 300, 120, 100, 40);
	remove.Create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "Remove", IDC_REMOVE, 300, 190, 100, 40);
	edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "I am text!", IDC_EDIT, 300, 50, 100, 40);
	listBox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "List Box", IDC_LB,  50, 50, 200, 180);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			onExit();
			break;
		case ID_HELP_ABOUT:
			onAbout();
			break;
		case IDC_ADD:
			onAdd();
			break;
		case IDC_REMOVE:
			onRemove();
			break;
	}
}

void MainWindow::OnDestroy() {
	::PostQuitMessage(0);
}

void MainWindow::onExit() {
	if (MessageBox(*this, "Dont go!! Are you leaving?", "My second app", MB_YESNO) == IDYES)
	{
		DestroyWindow(*this);
	}
}

void MainWindow::onAbout() {
	MessageBox(*this, "I'm helping. Very helpful!", "About", MB_OK);
}

void MainWindow::onAdd() {
	char str[32];
	if (GetDlgItemText(*this, IDC_EDIT, str, sizeof(str))) {
		SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)str);
		EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
		SetDlgItemText(*this, IDC_EDIT, "");
	}
}

void MainWindow::onRemove() {
	long res = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
	if (res != LB_ERR) {
		SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, (WPARAM)res, 0);
		if (!SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0))
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
	}
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

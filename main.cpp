#include "nwpwin.h"
#include "res.h"

class Edit: public Window{ std::string ClassName() { return "edit"; }};
class Button : public Window { std::string ClassName() { return "button"; } };
class ListBox : public Window { std::string ClassName() { return "listbox"; } };

class MainWindow : public Window
{
protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
};

int MainWindow::OnCreate(CREATESTRUCT* pcs)
{
	
	Edit editWindow;
	editWindow.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 200, 100, 100, 25);
	
	Button addButton, removeButton;
	addButton.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 300, 100, 100, 25);
	removeButton.Create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 400, 100, 100, 25);

	ListBox listBoxWindow;
	listBoxWindow.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 300, 200, 200, 100);
	EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
	return 0;
}

void MainWindow::OnCommand(int id) {
	switch (id) {
	case ID_FILE_EXIT:
		OnDestroy();
		break;
	case ID_HELP_ABOUT:
		MessageBox(*this, "Drugi labos", "O cemu", MB_OK);
		break;
	case IDC_ADD:
		char buffer[50];
		GetDlgItemText(*this, IDC_EDIT, buffer, sizeof(buffer));
		SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)buffer);
		EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
		break;
	case IDC_REMOVE:
		int index = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
		if (index != LB_ERR) { SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, index, 0); }
		if (!SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0)){ EnableWindow(GetDlgItem(*this, IDC_REMOVE), false); }
		break;
	}
}

void MainWindow::OnDestroy() {
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
#include "nwpwin.h"
#include "res.h"

class Button : public Window {
public:
	std::string ClassName() { return "BUTTON"; }
};
class Edit : public Window {
public:
	std::string ClassName() { return "EDIT"; }
};
class ListBox : public Window {
public:
	std::string ClassName() { return "LISTBOX"; }
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
	ListBox listBox;
	Edit edit;
	Button addButton;
	Button removeButton;

	listBox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 10, 10, 100, 100);
	edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 125, 10, 100, 20);
	addButton.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 125, 40, 100, 20);
	removeButton.Create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 125, 70, 100, 20);

	EnableWindow(removeButton, false);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			
			PostQuitMessage(0);
			break;
		case ID_HELP_ABOUT:

			MessageBox(*this, "About", "NWP 2", MB_OK);
			break;
		case IDC_ADD:

			char content[64];
			GetDlgItemText(*this, IDC_EDIT, content, sizeof(content));
			if (!strcmp(content, "") == 0)
			{
				SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)content);
				SetDlgItemText(*this, IDC_EDIT, "");
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			}
			break;

		case IDC_REMOVE:

			int item = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			if (item != LB_ERR) {
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, (WPARAM)item, 0);
			}
			if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0) == 0) {
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

	HICON hib = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hib));
	HICON his = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(his));

	Application app;
	return app.Run();
}

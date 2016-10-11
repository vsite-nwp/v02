#include "nwpwin.h"
#include "res.h"
//#include "Windowsx.h"
//#include "Winuser.h"

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
	Button addButton, removeButton;
	ListBox lstBox;
	Edit edt;

	lstBox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, NULL, IDC_LB, 110, 70, 80, 100);

	edt.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 200, 70, 80, 20);
	//Edit_LimitText(edt, 20); 

	addButton.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 200, 100, 80, 20);
	removeButton.Create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 200, 130, 80, 20);
	EnableWindow(removeButton, false);
	//Button_Enable(removeButton, false);

	return 0;
}

void MainWindow::OnCommand(int id) {
	char tmpStr[20];

	switch (id) {
	case ID_FILE_EXIT:
		OnDestroy();
		break;
	case ID_HELP_ABOUT:
		MessageBox(*this, "Genato", "About", MB_ICONINFORMATION | MB_HELP);
		break;
	case IDC_ADD:
		GetDlgItemText(*this, IDC_EDIT, tmpStr, 20);
		SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, LPARAM(tmpStr));
		EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
		//EnableWindow(FindWindowEx(*this, NULL, "Button", "Remove"), true);
		break;
	case IDC_REMOVE:
		LPARAM listBoxSelected = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);
		if (listBoxSelected == LB_ERR)
		{
			MessageBox(*this, "Please select the item from ListBox", "No Selection", MB_ICONINFORMATION);
			break;
		}
		else
			SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, listBoxSelected, NULL);

		if (!SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL))
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);

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


#include "nwpwin.h"
#include "res.h"

class ListBox : public Window {
protected:
	std::string ClassName() override {
		return "LISTBOX";
	};
};

class Button : public Window {
protected:
	std::string ClassName() override {
		return "BUTTON";
	};
};

class Edit : public Window {
protected:
	std::string ClassName() override {
		return "EDIT";
	};
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
	Button btn1;
	Button btn2;
	Edit ed;

	lb.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 100, 100, 100, 100);
	ed.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 200, 50, 60, 30);
	btn1.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 200, 100, 60, 30);
	btn2.Create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 200, 150, 60, 30);

	EnableWindow(btn2, false);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			PostQuitMessage(0);
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "Get some help", "About", MB_OK);
			break;
		case IDC_ADD:
			char s[256];

			GetDlgItemText(*this, IDC_EDIT, (LPSTR) s, sizeof(s));
			if (strcmp(s, "") != 0) {
				SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM) s);
				SetDlgItemText(*this, IDC_EDIT, "");
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			}
			break;
		case IDC_REMOVE:
			int itemIndex = (int) SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);
			if (itemIndex != LB_ERR) {
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, itemIndex, NULL);
			}
			if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL) == 0) {
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

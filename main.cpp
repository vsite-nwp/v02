#include "nwpwin.h"
#include "res.h"


class Edit : public Window {
	std::string ClassName() override {
		return "EDIT";
	}
};

class ListBox : public Window {
	std::string ClassName() override {
		return "LISTBOX";
	}
};

class Button : public Window {
	std::string ClassName() override {
		return "BUTTON";
	}
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
	ListBox listbox;
	Edit edit;
	Button Add;
	Button Remove;

	listbox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, NULL, IDC_LB, 120, 120, 120, 120);
	edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, NULL, IDC_EDIT, 250, 120, 100, 20);
	Add.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Add", IDC_ADD, 250, 170, 100, 30);
	Remove.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Remove", IDC_REMOVE, 250, 205, 100, 30);

	EnableWindow(Remove, false);

	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			OnDestroy();
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "Informacije Window-a", "asdasdasd", MB_OK);
			break;
		case IDC_ADD:
			char tekst[100];
			if (GetDlgItemText(*this, IDC_EDIT, tekst, sizeof(tekst))) {
				SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)tekst);
				SetDlgItemText(*this, IDC_EDIT, "");

				HWND RemoveHandler = GetDlgItem(*this, IDC_REMOVE);
				EnableWindow(RemoveHandler, true);
			}
			break;
		case IDC_REMOVE:
			int indeksOdabranog = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);
			if (indeksOdabranog == LB_ERR) break;
			SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, indeksOdabranog, NULL);

			int BrojElemenata = SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL);
			if (SendDlgItemMessage(*this, IDC_LB, LB_SETCURSEL, BrojElemenata - 1, NULL) == LB_ERR) {
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
				break;
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

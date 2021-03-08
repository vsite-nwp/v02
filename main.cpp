#include "nwpwin.h"
#include "res.h"

class Button : public Window {
public:
	std::string ClassName() { return "Button"; }
};
class Edit :public Window {
public:
	std::string ClassName() { return "Edit"; }
};
class ListBox : public Window {
public:
	std::string ClassName() { return "Listbox"; }
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
	Button buttonAdd, buttonRemove;
	buttonAdd.Create(*this, WS_CHILD | WS_VISIBLE, "ADD", IDC_ADD, 125, 50, 100, 40);
	buttonRemove.Create(*this, WS_CHILD | WS_VISIBLE, "REMOVE", IDC_REMOVE, 125, 80, 100, 40);
	Edit e;
	e.Create(*this, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, "", IDC_EDIT, 125, 10, 100, 40);
	ListBox lb;
	lb.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 10, 10, 100, 100);
	EnableWindow(buttonRemove, false);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			OnDestroy();
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "Vjezba 2", "About", MB_OK | MB_ICONINFORMATION);
			break;
		case IDC_ADD:
			char tekst[50];
			if (GetDlgItemText(*this, IDC_EDIT, tekst, sizeof(tekst))) {
				SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)tekst);
				SetDlgItemText(*this, IDC_EDIT, "");
				if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0))
					EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			}
			break;
		case IDC_REMOVE:
			int place = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			if (place == LB_ERR)
				return;
			SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, place, 0);
			if (!SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0))
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

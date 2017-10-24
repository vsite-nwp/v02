#include "nwpwin.h"
#include "res.h"

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

	Edit e;
	Button b1, b2;
	ListBox lb;
	b1.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 250, 40, 100, 30);
	b2.Create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "Remove", IDC_REMOVE, 250, 80, 100, 30);
	e.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 250, 10, 100, 20);
	lb.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "ListBox", IDC_LB, 60, 10, 150, 200);
	return 0;
}

void MainWindow::OnCommand(int id){
	
	

	switch(id){
		case ID_FILE_EXIT:
			DestroyWindow(*this);
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "Vježba 2.", "About", MB_ICONINFORMATION);
			break;
		case IDC_ADD:	
			char text[256];
			GetDlgItemText(*this, IDC_EDIT, text, sizeof(text));
			SendDlgItemMessage (*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)text);			
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);						
			break;
		case IDC_REMOVE:
			int i = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			if (i != LB_ERR) {
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, (WPARAM)i, 0);
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
	// set icons
	HICON hib = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hib));
	HICON his = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(his));

	Application app; 
	return app.Run();
}

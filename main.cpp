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
	int buffsize = 256;
	LPSTR text = new TCHAR[buffsize];
	LPSTR about = "Information about NPW2.";
	int i;
	switch(id){
		case ID_FILE_EXIT:
			DestroyWindow(*this);
			PostQuitMessage(0);
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, about, "About", WS_CAPTION | WS_POPUP | MB_ICONINFORMATION);
			break;
		case IDC_ADD:		
			GetDlgItemText(*this, IDC_EDIT, text, buffsize);
			SendDlgItemMessage (*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)text);			
			SendDlgItemMessage(*this, IDC_REMOVE, 0, 0, EnableWindow(GetDlgItem(*this, IDC_REMOVE), true));						
			break;
		case IDC_REMOVE:
			i = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, (WPARAM)i, 0);		
			if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0) == 0) {
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
			}			
			break;
	}
	delete[] text;
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

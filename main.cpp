#include "nwpwin.h"
#include "res.h"


class Button : public Window
{
public:
	virtual std::string ClassName() override { return "BUTTON"; };
};

class Edit : public Window
{
public:
	virtual std::string ClassName() override { return "EDIT"; };
};

class ListBox : public Window
{
public:
	virtual std::string ClassName() override { return "LISTBOX"; };
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
	ListBox lb; lb.Create(*this, WS_BORDER | WS_CHILD | WS_VISIBLE, "", IDC_LB, 10, 10, 180, 140);
	Button b; b.Create(*this, WS_CHILD | WS_VISIBLE, "add", IDC_ADD, 200, 45, 100, 30);
	Button d; d.Create(*this, WS_CHILD | WS_VISIBLE, "Delete", IDC_REMOVE, 200, 80, 100, 30);
	Edit e; e.Create(*this,WS_BORDER | WS_CHILD | WS_VISIBLE, "", IDC_EDIT, 200, 10, 100, 30);
	EnableWindow(d, false);
	return 0;
}

void MainWindow::OnCommand(int id){
	TCHAR buffer[80];

	switch(id){
		case ID_FILE_EXIT:
			PostQuitMessage(0);
			break;
		case ID_HELP_ABOUT:
			MessageBox(NULL, "help yourself", "Help", MB_YESNOCANCEL);
			break;
		case IDC_ADD:
			GetDlgItemText(*this, IDC_EDIT, buffer, sizeof(buffer)-1);
			
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)buffer);
			
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			break;
		case IDC_REMOVE:
			int itemIndex = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);
			if (itemIndex == LB_ERR)
				{
					break;
				}
			else
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, itemIndex, NULL);
			if (!SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL))
			{
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

#include "nwpwin.h"
#include "res.h"

class Button : public Window{
public:
std::string ClassName() override { return "BUTTON"; }
};

class ListBox : public Window{
public:
	std::string ClassName() override { return "LISTBOX"; }
};

class Edit : public Window{
public:
	std::string ClassName() override { return "EDIT"; }
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
	Button rem; rem.Create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "Remove", IDC_REMOVE, 200, 150, 100, 30);
	Button add; add.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 200, 100, 100, 30);
	Edit edit; edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 200, 50, 100, 30);
	ListBox lbx; lbx.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 50, 50, 100, 150);

	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			DestroyWindow(*this);
			break;
		case ID_HELP_ABOUT:
			MessageBox(NULL, "Pomoæ?: \n Nema je bas...", "Help", MB_OK | MB_ICONINFORMATION);
			break;
		case IDC_ADD:
			char getString[40];
			GetDlgItemText(*this, IDC_EDIT, getString, sizeof(getString));

			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)getString);
			
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
	
			break;
		case IDC_REMOVE:
			//int cnt;
			int itemIndex = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);
			if (itemIndex == LB_ERR)
			{
				MessageBox(NULL, "Please select item from the list!", "Hm...", MB_OK | MB_ICONEXCLAMATION);
				break;
			}
			else
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, itemIndex, NULL);

			//cnt = SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL);
			//if (cnt == 0)
			if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL) == 0)
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
			else
			{
				if (itemIndex == 0)
					SendDlgItemMessage(*this, IDC_LB, LB_SETCURSEL, itemIndex, NULL);
				else
					SendDlgItemMessage(*this, IDC_LB, LB_SETCURSEL, itemIndex - 1, NULL);
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

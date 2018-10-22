#include "nwpwin.h"
#include "res.h"

class ListBox : public Window {
protected: 
std::string ClassName() override { return "LISTBOX"; }
};
class Button : public Window {
protected:
	std::string ClassName() override { return "BUTTON"; }
};

class Edit : public Window {
protected:
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
	ListBox lb;
	lb.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 50, 50, 100, 120);

	Edit ed;
	ed.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "",IDC_EDIT,165, 50, 100, 25);

	Button izbrisi;
	izbrisi.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Remove", IDC_REMOVE, 165, 110, 100, 23);
	EnableWindow(izbrisi,false);

	Button dodaj;
	dodaj.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Add",IDC_ADD, 165, 83, 100, 23);
	

	return 0;
}

void MainWindow::OnCommand(int id){
	switch (id) {

	case ID_FILE_EXIT:
		SendMessage(*this, WM_CLOSE, 0, 0);
		break;

	case ID_HELP_ABOUT:
		MessageBox(*this, "2.vježba iz NWP-a", "Info", MB_ICONINFORMATION | MB_OK);
		break;

	case IDC_ADD:
		char fromEdit[64];
		GetDlgItemText(*this, IDC_EDIT, fromEdit, sizeof(fromEdit));
		
		if (!strlen(fromEdit)==0) {
		SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)fromEdit);
		SetDlgItemText(*this, IDC_EDIT, "");
		EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
		}

	break;
		case IDC_REMOVE:
			HWND lb = GetDlgItem(*this,IDC_LB);
			int sel = SendMessage(lb, LB_GETCURSEL, NULL, NULL);
			if (sel != LB_ERR) {
				SendMessage(lb, LB_DELETESTRING, sel,NULL);
			}
			if (SendMessage(lb,LB_GETCOUNT, NULL,NULL) == 0) {
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

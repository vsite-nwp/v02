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
class Edit : public Window  {
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
	Button b1, b2;
	Edit ed;
	lb.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 50, 50, 100, 100);
	b1.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "add", IDC_ADD, 200, 50, 100, 20);
	b2.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "remove", IDC_REMOVE, 200, 80, 100, 20);
	EnableWindow(b2, false);
	ed.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 200, 110, 100, 20);


	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			SendMessage(*this, WM_CLOSE, 0, 0);
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "NWP druga", "Tekst", MB_ICONINFORMATION | MB_OK);
			break;
		case IDC_ADD:
			char ed[64];
			GetDlgItemText(*this, IDC_EDIT, ed, sizeof(ed));

			if (!strlen(ed) == 0) {
				SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)ed);
				SetDlgItemText(*this, IDC_EDIT, "");
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			}
			
			break;
		case IDC_REMOVE:
			HWND lb = GetDlgItem(*this, IDC_LB);
			int sel = SendMessage(lb, LB_GETCURSEL, NULL, NULL);
			if (sel != LB_ERR) {
				SendMessage(lb, LB_DELETESTRING, sel, NULL);
			}
			if (SendMessage(lb, LB_GETCOUNT, NULL, NULL) == 0) {
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

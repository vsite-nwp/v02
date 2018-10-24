#include "nwpwin.h"
#include "res.h"



enum {ID_LISTBOX=1, ID_BUTTON_ADD, iD_BUTTON_REMOVE, ID_EDIT};


class ListBox : public Window
{protected:
	std::string ClassName() override { return "LISTBOX"; }
	};

class Button : public Window
{
protected:
	std::string ClassName() override { return "BUTTON"; }
};

class Edit : public Window
{
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
	Edit ed;
	Button bt1, bt2;

	lb.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 50, 50, 100, 120);
	ed.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 170, 50, 100, 25);
	bt1.Create(*this,  WS_CHILD | WS_VISIBLE , "Add", IDC_ADD,170, 80, 100, 25);
	bt1.Create(*this, WS_CHILD | WS_VISIBLE , "Remove", IDC_REMOVE, 170, 110, 100, 25);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			PostQuitMessage(0);
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "Vježba 2", "About", MB_OK);
			break;
		case IDC_ADD:
			char text[80];
			
			if (GetDlgItemText(*this, IDC_EDIT, text, sizeof(text)) != 0) {
				SendMessage(GetDlgItem(*this, IDC_LB), LB_ADDSTRING, 0, (LPARAM)text);
				EnableWindow(GetDlgItem(*this, IDC_REMOVE),true);
				SetDlgItemText(*this, IDC_EDIT, "");
			}
			else
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
			break;
		case IDC_REMOVE:
			
			LRESULT sel=SendMessage(GetDlgItem(*this, IDC_LB), LB_GETCURSEL, 0, 0);
			if (sel!=LB_ERR) 
				SendMessage(GetDlgItem(*this, IDC_LB), LB_DELETESTRING, (WPARAM)sel, 0);
			if((int)SendMessage(GetDlgItem(*this, IDC_LB), LB_GETCOUNT, 0, 0)==0)
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

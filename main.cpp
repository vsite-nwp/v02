#include "nwpwin.h"
#include "res.h"


class Edit : public Window
{
protected:
	std::string ClassName() override { return "Edit"; }
};

class Button : public Window
{
protected:
	std::string ClassName() override { return "Button"; }
};

class ListBox : public Window
{
protected:
	std::string ClassName() override { return "ListBox"; }
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
	ListBox lb; lb.Create(*this, WS_VISIBLE | WS_CHILD | WS_BORDER, 0, IDC_LB, 10, 10, 100, 120);
	Edit ed; ed.Create(*this, WS_VISIBLE | WS_CHILD | WS_BORDER, 0, IDC_EDIT, 120, 10, 80, 25); 
	Button b1; b1.Create(*this, WS_VISIBLE | WS_CHILD | WS_BORDER, "Add", IDC_ADD, 120, 50, 80, 25);
	Button b2; b2.Create(*this, WS_VISIBLE | WS_CHILD | WS_BORDER, "Remove", IDC_REMOVE, 120, 85, 80, 25); EnableWindow(b2, false);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			OnDestroy();
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "About Text", "About", MB_OK);
			break;
		case IDC_ADD:
				char buffer[100];
				GetDlgItemText(*this,IDC_EDIT, buffer, 100);
				SendDlgItemMessage(*this,IDC_LB, LB_INSERTSTRING, NULL, (LPARAM)buffer);
				SetDlgItemText(*this,IDC_EDIT, "");
				if (!IsWindowEnabled(GetDlgItem(*this, IDC_REMOVE))) EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			break;
		case IDC_REMOVE:
			HWND LB = GetDlgItem(*this, IDC_LB);
			int itemId = SendMessage(LB, LB_GETCURSEL, 0, 0);
			if(itemId != LB_ERR)
			SendMessage(LB, LB_DELETESTRING, itemId, 0);
			int itemCount = SendMessage(LB, LB_GETCOUNT, 0, 0);
			if (itemCount == 0) EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
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
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)hMenu,CW_USEDEFAULT,CW_USEDEFAULT,300,200);	
	// set icons
	HICON hib = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hib));
	HICON his = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(his));

	Application app; 
	return app.Run();
}

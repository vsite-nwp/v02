#include "nwpwin.h"
#include "res.h"


class Edit : public Window {
	std::string ClassName() override { return "Edit"; }
};

class Button : public Window {
	std::string ClassName() override { return "Button"; }
};

class ListBox : public Window {
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
	Edit edit;
	Button buttonAdd, buttonRemove;
	ListBox listBox;

	char s[128];

	listBox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER,  "", IDC_LB, 20, 20, 150, 200);
	edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER,  "", IDC_EDIT, 180, 20, 150, 50);
	
	LoadString(0, IDS_BUTTON_ADD, s, sizeof s);
	buttonAdd.Create(*this, WS_CHILD | WS_VISIBLE, s, IDC_ADD, 180, 80, 150, 50);

	LoadString(0, IDS_BUTTON_REMOVE, s, sizeof s);
	buttonRemove.Create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, s, IDC_REMOVE, 180, 140, 150, 50);

	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			OnDestroy();
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "NWP 2. VJEZBA", "NWP 2", MB_OK);
			break;
		case IDC_ADD:
			char s[128];
			GetDlgItemText(*this, IDC_EDIT, s, sizeof(s));		

			if (s[0] != 0)						
				SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)s);
			SetDlgItemTextA(*this, IDC_EDIT, "");

			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			
			break;
		case IDC_REMOVE:			
			LRESULT iIndex = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			if (iIndex != LB_ERR)
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, iIndex, NULL);

			int iCount = SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0);
			if (iCount == 0)
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
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)hMenu, CW_USEDEFAULT, CW_USEDEFAULT, 400, 320);
	// set icons
	HICON hib = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hib));
	HICON his = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(his));

	Application app; 
	return app.Run();
}

#include "nwpwin.h"
#include "res.h"

class Edit :public Window {
public:
	std::string ClassName() override { return "EDIT"; }
};

class Button :public Window {
public:
	std::string ClassName() override { return "BUTTON"; }
};

class ListBox:public Window {
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
	Edit edit;
	Button addbtn, removebtn;
	ListBox lbox;
	
	edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 197, 50, 100, 30);
	addbtn.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 197, 82, 100, 50);
	removebtn.Create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "Remove", IDC_REMOVE, 197, 133, 100, 50);
	lbox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 45, 50, 150, 140);

	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			OnDestroy();
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "NWP labos 2", "About", MB_OK);
			break;
		case IDC_ADD:
			char str[255];
			GetDlgItemText(*this, IDC_EDIT, str, sizeof(str));
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)str);
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true); //enable remove button 
			break;
		case IDC_REMOVE:
			LRESULT rem = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			LRESULT count = SendMessage(*this, LB_GETCOUNT, 0, 0);
			SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, (WPARAM)rem, 0);
			if (!count)
			{
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false); //disable remove button
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

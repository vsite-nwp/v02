#include "nwpwin.h"
#include "res.h"


class Edit : public Window {
	public:
		std::string ClassName() override { return "EDIT"; }
};
class Button : public Window {
public : 
	std::string ClassName() override { return "BUTTON"; }
};
class ListBox  : public Window {
public:
	std::string ClassName() override { return "LISTBOX"; }
};

class MainWindow : public Window
{

protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
	void OnAdd( char* str);
	void OnRemove(int id);
};

int MainWindow::OnCreate(CREATESTRUCT* pcs)
{
	ListBox listBox;
	Button add, remove;
	Edit edit;

	edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 200, 50, 100, 30);
	add.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 200, 100, 100, 30);
	remove.Create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "Remove", IDC_REMOVE, 200, 150, 100, 30);
	listBox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 50, 50, 100, 150);


	

	return 0;
}


void MainWindow::OnAdd( char* str) {
	
	GetDlgItemText(*this, IDC_EDIT, str, sizeof(str));

	SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)str);

	EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);

}

void MainWindow::OnRemove(int id) {
	if (id == LB_ERR)
	{
		MessageBox(*this, "Select from list"," ", MB_OK | MB_ICONEXCLAMATION);
	}
	else {
		SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, id, NULL);
	}

	if (id == 0) {
		EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
	}
	else
	{
		SendDlgItemMessage(*this, IDC_LB, LB_SETCURSEL, min(0, id - 1), NULL);  
	}
}


void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			OnDestroy();
			break;
		case ID_HELP_ABOUT:

			MessageBox(*this, "About ", "Help", MB_OK | MB_ICONWARNING);

			break;
		case IDC_ADD:
			char str[255];
			OnAdd(str);

			break;
		case IDC_REMOVE:

			OnRemove(SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL));

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

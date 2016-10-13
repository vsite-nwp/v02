#include "nwpwin.h"
#include "res.h"

class MainWindow : public Window
{
protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
};
class Edit :public Window {
	public:
	std::string ClassName(){
	return "Edit"; }
		
};

class Button :public Window {
	public:
	std::string ClassName(){
	return "Button"; }
};
class ListBox :public Window {
public:
	std::string ClassName() {
		return "ListBox";
	}
};


int MainWindow::OnCreate(CREATESTRUCT* pcs)
{	
	Edit edit; edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 120, 10, 100, 24);
	Button button_add; button_add.Create(*this, WS_CHILD | WS_VISIBLE, "add", IDC_ADD, 120, 40, 100, 24);
	Button button_remove; button_remove.Create(*this, WS_CHILD | WS_VISIBLE, "remove", IDC_REMOVE, 120, 70, 100, 24);
	ListBox listbox; listbox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "listbox", IDC_LB, 10, 10, 100, 120);
	EnableWindow(button_remove, false);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			OnDestroy();
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "some text", "About", MB_OK | MB_ICONINFORMATION);
			break;
		case IDC_ADD:
			char msg[50];
			GetDlgItemText(*this, IDC_EDIT, msg, 50);
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)msg);
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			break;
		case IDC_REMOVE:
			int listBoxSelected = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);
			if (listBoxSelected == LB_ERR){
				MessageBox(*this, "You didn`t select item from ListBox", "No Selected Item", MB_ICONINFORMATION);
				break;
				}
			else
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, listBoxSelected, NULL);

			if (!SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL))
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

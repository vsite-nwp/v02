#include "nwpwin.h"
#include "res.h"

class Button :public Window {
	public: std::string ClassName() {return "BUTTON";}
};
class Edit : public Window {
	public: std::string ClassName() {return "EDIT";}
};
class ListBox : public Window {
	public: std::string ClassName() {return "LISTBOX";}
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
	Button btn_add, btn_remove;
	Edit label_edit;
	ListBox list_box;

	list_box.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 10, 10, 180, 140);
	label_edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 200, 10, 100, 30);
	btn_add.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 200, 45, 100, 30);
	btn_remove.Create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "Remove", IDC_REMOVE, 200, 80, 100, 30);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			DestroyWindow(*this);
			break;

		case ID_HELP_ABOUT:
			MessageBox(NULL, "Meni treba vise pomoc nego tebi...", "HELP", MB_OK | MB_ICONINFORMATION);
			break;

		case IDC_ADD:
			char edit_text[70];
			GetDlgItemText(*this, IDC_EDIT, edit_text, 70);	
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)edit_text);
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			break;

		case IDC_REMOVE:
			int selected_item = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);
			if (selected_item == LB_ERR) 
				MessageBox(*this, "Select item from list", "Info", MB_ICONINFORMATION);
			else
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, selected_item, NULL);
		
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
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)hMenu, CW_USEDEFAULT, CW_USEDEFAULT, 350, 220);
	// set icons
	HICON hib = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hib));
	HICON his = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(his));

	Application app; 
	return app.Run();
}

#include "nwpwin.h"
#include "res.h"


class Edit : public Window{
public:
	std::string ClassName() { return "EDIT"; }

};
class Button : public Window{
public:
	std::string ClassName() { return "BUTTON"; }


};
class ListBox : public Window{
	std::string ClassName() { return "LISTBOX"; }

	//kom

};
class MainWindow : public Window
{
protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
};
//komentar
int MainWindow::OnCreate(CREATESTRUCT* pcs)
{

	Edit edit; edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 200, 0, 150, 40);
	Button button_add; button_add.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Add", IDC_ADD, 200, 50, 150, 40);
	Button button_remove; button_remove.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Remove", IDC_REMOVE, 200, 100, 150, 40);
	ListBox listbox; listbox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 0, 0, 180, 160);

	EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch (id){
	case ID_FILE_EXIT:
		PostMessage(*this, WM_CLOSE, 0, 0);
		break;
	case ID_HELP_ABOUT:

		MessageBox(*this, "vj2", "NWP2", MB_OK);
		break;
	case IDC_ADD:
		char str[200];
		GetDlgItemText(*this, IDC_EDIT, str, sizeof(str));
		SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)str);
		EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);


		break;
	case IDC_REMOVE:
		int position;
		position = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
		if (position>=0){
			SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, position, 0);
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), position>0);

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

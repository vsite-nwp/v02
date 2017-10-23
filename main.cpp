#include "nwpwin.h"
#include "res.h"

class Edit : public Window {
public:
	std::string ClassName() { return "EDIT"; };
};

class Button : public Window {
public:
	std::string ClassName() { return "BUTTON"; };
};

class ListBox : public Window {
public:
	std::string ClassName() { return "LISTBOX"; };
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
	edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER,NULL, IDC_EDIT,110,20,70,20);

	Button bAdd, bRm;
	bAdd.Create(*this, WS_CHILD | WS_VISIBLE, "ADD", IDC_ADD, 110, 50, 70, 20);
	bRm.Create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "REMOVE", IDC_REMOVE, 110, 80, 70, 20);

	ListBox Lbox;
	Lbox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "ListBox", IDC_LB, 10, 10, 100, 100);

	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			DestroyWindow(*this);
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "Samethink", "About", MB_OK | MB_ICONINFORMATION);

			break;
		case IDC_ADD:

			char Buffer[64];
			GetDlgItemText(*this, IDC_EDIT, Buffer,64);
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING,0, (LPARAM)Buffer);
			EnableWindow(GetDlgItem(*this, IDC_REMOVE) , true);
			break;
		case IDC_REMOVE:
			int count;
			int index=SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, NULL);
			if (index != LB_ERR) {
				count = SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, index, NULL);
				if (count != LB_ERR) {
					EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
				}
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

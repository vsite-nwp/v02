#include "nwpwin.h"
#include "res.h"

class Button : public Window {
	public: 
		std::string ClassName() override {
			return "BUTTON";
		}
};

class Edit : public Window {
	public:
		std::string ClassName() override {
			return "EDIT";
		}
};

class Listbox : public Window {
public:
	std::string ClassName() override {
		return "LISTBOX";
	}
};


class MainWindow : public Window
{
protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
	void OnAdd();
	void OnRemove();
};

int MainWindow::OnCreate(CREATESTRUCT* pcs)
{
	Button add_b, rem_b;
	Edit edi;
	Listbox list;
	
	add_b.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 20, 45, 120, 30);
	rem_b.Create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED , "Remove", IDC_REMOVE, 20, 80, 120, 30);
	edi.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 20, 10, 120, 30);
	list.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 160, 10, 250, 140);
	return 0;
}

void MainWindow::OnAdd(){
	char ItemName[50];

	if (GetDlgItemText(*this, IDC_EDIT, ItemName, sizeof(ItemName)) != 0) {
		SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)ItemName);
		EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
		SetDlgItemText(*this, IDC_EDIT, "");
	}
}

void MainWindow::OnRemove() {
	LRESULT Index = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);
	if (Index != LB_ERR)
	{
		SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, Index, NULL);
		if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL) == 0)
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
	}
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			CloseWindow(*this);
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "Help", "Help", MB_OK);
			break;
		case IDC_ADD:
			OnAdd();
			break;
		case IDC_REMOVE:
			OnRemove();
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
	HICON hib = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hib));
	HICON his = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(his));

	Application app; 
	return app.Run();
}

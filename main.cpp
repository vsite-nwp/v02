#include "nwpwin.h"
#include "res.h"


class Button :public Window {
public:
	std::string ClassName() override {
		return "BUTTON";
	}
};
class Edit :public Window {
public:
	std::string ClassName() override { return "EDIT"; }
};
class Listbox :public Window {
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

	Button b_ADD, b_rem;
	Edit edd; Listbox list;
	edd.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 200,10,100,30);
	b_ADD.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 200, 45, 100, 30);
	b_rem.Create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "Remove", IDC_REMOVE, 200, 80, 100, 30);
	list.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 10, 10, 180, 140);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			
			CloseWindow(*this);
			break;
		case ID_HELP_ABOUT:
			
			MessageBox(*this, "helping...", "Help", MB_OK);
			break;
		case IDC_ADD:
			
			char szItemName[80];
			GetDlgItemText(*this, IDC_EDIT,szItemName,sizeof(szItemName));
			
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)szItemName);
			
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			break;
		case IDC_REMOVE:
			
			int itemIndex = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL,NULL);
			if (itemIndex == LB_ERR)
			{
				//No selection
				break;
			}
			else
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, itemIndex, NULL);
			if (SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL)==0)
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

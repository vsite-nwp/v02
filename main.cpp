#include "nwpwin.h"
#include "res.h"

//////////////////////////////////////////////////////
class Button : public Window {
	public:
		std::string ClassName() override { return "BUTTON"; }; 
};

class Edit : public Window {
public:  
	std::string ClassName() override { return "EDIT"; };
};

class ListBox : public Window {
public:  
	std::string ClassName() override { return "LISTBOX"; };
};
/////////////////////////////////////////////////////
class MainWindow : public Window
{
protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
};
////////////////////////////////////////////////////////
int MainWindow::OnCreate(CREATESTRUCT* pcs)
{
	Edit e1;
	Button b1, b2;
	ListBox lb;
	
	e1.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 300, 100, 100, 30);
	b1.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Remove", IDC_REMOVE, 300, 140, 100, 30);
	b2.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Add", IDC_ADD, 300, 180, 100, 30);
	lb.Create(*this, WS_CHILD | WS_VISIBLE |WS_BORDER, "",IDC_LB,100,100,100,100);
	EnableWindow(GetDlgItem(*this,IDC_REMOVE),false);
	return 0;
}
////////////////////////////////////////////////////////
void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			CloseWindow(*this);
			break;
		case ID_HELP_ABOUT:
			MessageBox(NULL,"Dialog in the box","Click ok",MB_OK|MB_ICONINFORMATION);
			break;
		case IDC_ADD:
			char msg[40];
			GetDlgItemText(*this,IDC_EDIT,msg,40);
			SendDlgItemMessage(*this,IDC_LB,LB_ADDSTRING,NULL,(LPARAM)msg);
			EnableWindow(GetDlgItem(*this,IDC_REMOVE),true);
			break;
		case IDC_REMOVE:
			int abc = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);
			SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, (WPARAM)abc, NULL);
			if (!SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL))
				EnableWindow(GetDlgItem(*this,IDC_REMOVE),false);
			break;
	}
}
//////////////////////////////////////////////////////////////////
void MainWindow::OnDestroy(){
	::PostQuitMessage(0);
}
///////////////////////////////////////////////////////////////
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

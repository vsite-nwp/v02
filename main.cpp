#include "nwpwin.h"
#include "res.h"


class Edit : public Window {
public:
	std::string ClassName() { return "EDIT";};
};
class Button : public Window {
	std::string ClassName() { return "BUTTON"; };

};
class ListBox : public Window {
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
	ListBox lb;
	Edit edit;
	Button add, rem;
	lb.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER,"listbox", IDC_LB, 0, 0, 100, 100);
	add.Create(*this, WS_CHILD | WS_VISIBLE, "add", IDC_ADD, 100, 60,70, 20);
	rem.Create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "remove", IDC_REMOVE, 100, 30, 70, 20);
	edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 100, 0, 70, 20);
	return 0;
}

void MainWindow::OnCommand(int id){
	LPSTR text = new TCHAR[15];
	HWND lb = GetDlgItem(*this, IDC_LB);
	HWND rem = GetDlgItem(*this, IDC_REMOVE);
	switch(id){
		case ID_FILE_EXIT:
			PostQuitMessage(0);
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, (LPCSTR)"this is help", (LPCSTR)"HELP", MB_HELP);
			// TODO: show dialog with text
			break;
		case IDC_ADD:
			
			GetDlgItemText(*this, IDC_EDIT,(LPSTR) text, 15);
			SendMessage(lb, LB_ADDSTRING, 0, (LPARAM) text);
			EnableWindow(rem, TRUE);
			break;
		case IDC_REMOVE:
			int index = SendMessage(lb, LB_GETCURSEL, 0, 0);
			SendMessage(lb, LB_DELETESTRING, (WPARAM)index, 0);
			if (SendMessage(lb, LB_GETCOUNT, 0, 0) == 0) {
				EnableWindow(rem, FALSE);
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

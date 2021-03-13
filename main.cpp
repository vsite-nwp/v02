#include "nwpwin.h"
#include "res.h"
using namespace std;

class Edit : public Window {
	string ClassName() { return "edit"; }
};

class Button : public Window {
	string ClassName() { return "button"; }
};

class ListBox : public Window {
	string ClassName() { return "listbox"; }
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
	Button b_add, b_remove;
	Edit e;
	ListBox ls;
	
	ls.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER,  "listbox", IDC_LB, 20, 40, 110, 180);
	e.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 150, 40, 140, 40);

	b_add.Create(*this, WS_CHILD | WS_VISIBLE, "add", IDC_ADD, 150, 100, 100, 40);
	b_remove.Create(*this, WS_CHILD | WS_VISIBLE, "remove", IDC_REMOVE, 150, 150, 100, 40);

	// GetDlgItem - Retrieves a handle to a control in the specified dialog box.
	EnableWindow(GetDlgItem(*this, IDC_REMOVE), false); // disable remove

	return 0;
}

void MainWindow::OnCommand(int id){

	switch(id){

		case ID_FILE_EXIT:

			OnDestroy();
			break;

		case ID_HELP_ABOUT:

			MessageBox(*this, "About me", "About", MB_OK);
			break;

		case IDC_ADD:

			char text[40];
			
			if (GetDlgItemText(*this, IDC_EDIT, text, sizeof(text))) {

				SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)text); // send message
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			}

			SetDlgItemText(*this, IDC_EDIT, ""); // reset edit text to empty
			
			break;

		case IDC_REMOVE:
			LRESULT sel = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			
			// LB_OKAY = 0; LB_ERR = -1; LB_ERRSPACE = -2 
			if (!sel) {
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, sel, 0);
				if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0) == 0)
				{
					EnableWindow(GetDlgItem(*this, IDC_REMOVE), false); // disable remove
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

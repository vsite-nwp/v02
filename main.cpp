#include "nwpwin.h"
#include "res.h"

// DONE: prepare classes (Edit, Button, ListBox) for child windows
// DONE: derive from Window, override ClassName
class Edit : public Window {
protected:
	std::string ClassName()override { return "Edit"; }
};
class Button : public Window {
protected:
	std::string ClassName()override { return "Button"; }
};
class ListBox : public Window {
protected:
	std::string ClassName()override { return "ListBox"; }
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
	// DONE: create all child windows
	Button buttonAdd, buttonRemove;
	buttonAdd.Create(*this, WS_CHILD | WS_VISIBLE, "ADD", IDC_ADD, 125, 50, 100, 40);
	buttonRemove.Create(*this, WS_CHILD | WS_VISIBLE, "REMOVE", IDC_REMOVE, 125, 80, 100, 40);
	Edit e;
	e.Create(*this, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, "", IDC_EDIT, 125, 10, 100, 40);
	ListBox lb;
	lb.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 10, 10, 100, 100);
	// DONE: disable "Remove" button
	EnableWindow(buttonRemove, false);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			OnDestroy();
			// DONE: close main window
			break;
		case ID_HELP_ABOUT:
			// DONE: show dialog with text
			MessageBox(*this, "Vjezba 02", "Help", MB_OK);
			break;
		case IDC_ADD:
			// DONE: get text from edit control
			// DONE: add string to listbox control
			// DONE: enable "Remove" button
			char text[50];
			if (GetDlgItemText(*this, IDC_EDIT, text, sizeof(text)) != 0) {
				SendMessage(GetDlgItem(*this, IDC_LB), LB_ADDSTRING, 0, (LPARAM)text);
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
				SetDlgItemText(*this, IDC_EDIT, "");
			}
			break;
		case IDC_REMOVE:
			// DONE: get listbox selection
			// DONE: if there is a selection, delete selected string
			// DONE: disable "Remove" button if listbox is empty
			int itemIndex = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			if (itemIndex == LB_ERR)
				break;
			else
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, itemIndex, 0);
			if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0) == 0)
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

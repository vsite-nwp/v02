#include "nwpwin.h"
#include "res.h"


// TODO: prepare classes (Edit, Button, ListBox) for child windows
class Button : public Window{
public:
	std::string ClassName() { return "BUTTON"; }
};

class Edit : public Window{
public:
	std::string ClassName() { return "EDIT"; }
};

class ListBox : public Window{
public:
	std::string ClassName() { return "LISTBOX"; }
};
// TODO: derive from Window, override ClassName



class MainWindow : public Window
{
	Edit edit;
	Button button_add;
	Button button_remove;
	ListBox listbox;
protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
};

int MainWindow::OnCreate(CREATESTRUCT* pcs)
{
	// TODO: create all child windows
	edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "" ,IDC_EDIT ,250, 25, 100, 100);
	button_add.Create(*this, WS_CHILD | WS_VISIBLE, "Add" ,IDC_ADD, 250, 150, 100, 50);
	button_remove.Create(*this, WS_CHILD | WS_VISIBLE, "Remove",IDC_REMOVE, 250, 225, 100, 50);
	listbox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 100, 25, 100, 200);
	// TODO: disable "Remove" button
	EnableWindow(button_remove, FALSE);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			// TODO: close main window
			OnDestroy();
			break;
		case ID_HELP_ABOUT:
			// TODO: show dialog with text
			MessageBox(*this, "Upiši tekst u edit i klikni Add za dodavanje u listbox. Remove mièe tekst iz listboxa.", "NWP 2", MB_OK);
			break;
		case IDC_ADD:
			// TODO: get text from edit control
			char s[256];
			GetDlgItemText(*this, IDC_EDIT, s, sizeof s);
			// TODO: add string to listbox control
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)s);
			// TODO: enable "Remove" button
			EnableWindow(button_remove, TRUE);
			break;
		case IDC_REMOVE:
			// TODO: get listbox selection
			SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);
			// TODO: if there is a selection, delete selected string
			SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, (WPARAM)s, NULL);
			// TODO: disable "Remove" button if listbox is empty
			EnableWindow(button_remove, FALSE);
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

#include "nwpwin.h"
#include "res.h"

// TODO: prepare classes (Edit, Button, ListBox) for child windows
// TODO: derive from Window, override ClassName
class Button : public Window {
public:
	std::string ClassName() override { return "BUTTON"; }
};

class Edit : public Window {
public:
	std::string ClassName() override { return "EDIT"; }
};

class ListBox : public Window {
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
	// TODO: create all child windows
	// TODO: disable "Remove" button
	Edit e;
	Button b1, b2;
	ListBox lb;
	b1.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 250, 100, 100, 30);
	b2.Create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 250, 140, 100, 30);
	e.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 250, 60, 100, 20);
	lb.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER | LB_ADDSTRING, "ListBox", IDC_LB, 60, 10, 150, 200);
	EnableWindow(b2, false);
	return 0;
}

void MainWindow::OnCommand(int id){
	int buffsize = 1024;
	LPSTR text = new TCHAR[buffsize];
	LPSTR about = "Information about NPW2.";
	switch(id){
		case ID_FILE_EXIT:
			// TODO: close main window
			DestroyWindow(*this);
			PostQuitMessage(1);
			break;
		case ID_HELP_ABOUT:
			// TODO: show dialog with text
			//DialogBox(hInst, MAKEINTRESOURCE(ID_HELP_ABOUT), *this, about);
			MessageBox(*this, about, "About", WS_CAPTION | WS_POPUP);
			break;
		case IDC_ADD:
			// TODO: get text from edit control			
			GetDlgItemText(*this, IDC_EDIT, text, buffsize);
			// TODO: add string to listbox control
			SendDlgItemMessage (*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)text);
			// TODO: enable "Remove" button
			EnableWindow(*this, true);		
			break;
		case IDC_REMOVE:
			// TODO: get listbox selection
			// TODO: if there is a selection, delete selected string
			// TODO: disable "Remove" button if listbox is empty
			SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL | LB_DELETESTRING, 0, 0);
			if (!SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0)) {
				EnableWindow(*this, false);
			}			
			break;
	}
	delete[] text;
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

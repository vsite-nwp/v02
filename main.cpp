#include "nwpwin.h"
#include "res.h"
#include<windows.h>





// TODO: prepare classes (Edit, Button, ListBox) for child windows
// TODO: derive from Window, override ClassName
class Edit :public Window {
public:
	std::string ClassName() { return "EDIT"; }

};
class Button :public Window {
public:
	std::string ClassName() { return "BUTTON"; }

};
class ListBox :public Window{
	public:
		std::string ClassName() { return "LISTBOX"; }

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
	
	CreateWindow("LISTBOX", " ", WS_CHILD | WS_VISIBLE|WS_BORDER,
		0, 0, 200, 100, hw, (HMENU)IDC_LB, 0, 0);
	CreateWindow("EDIT", " ", WS_CHILD | WS_VISIBLE | WS_BORDER,
		300, 0, 100, 30, hw, (HMENU)IDC_EDIT, 0, 0);
	CreateWindow("BUTTON", "Add ", WS_CHILD | WS_VISIBLE | WS_BORDER,
		300, 50, 100, 30, hw, (HMENU)IDC_ADD, 0, 0);
	CreateWindow("BUTTON", "Remove ", WS_CHILD | WS_VISIBLE | WS_BORDER,
		300, 100, 100, 30, hw, (HMENU)IDC_REMOVE, 0, 0);

	
	// TODO: disable "Remove" button
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			// TODO: close main window
			break;
		case ID_HELP_ABOUT:
			// TODO: show dialog with text
			break;
		case IDC_ADD:
			// TODO: get text from edit control
			// TODO: add string to listbox control
			// TODO: enable "Remove" button
			break;
		case IDC_REMOVE:
			// TODO: get listbox selection
			// TODO: if there is a selection, delete selected string
			// TODO: disable "Remove" button if listbox is empty
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

#include "nwpwin.h"
#include "res.h"

class Edit : public Window
{
protected:
	std::string ClassName() override { return "Edit"; }
};

class Button : public Window
{
protected:
	std::string ClassName() override { return "Button"; }
};

class ListBox : public Window
{
protected:
	std::string ClassName() override { return "ListBox"; }
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
	ListBox lb; lb.Create(*this, WS_VISIBLE | WS_CHILD | WS_BORDER, 0, 1, 10, 10, 100, 120);
	Edit ed; ed.Create(*this, WS_VISIBLE | WS_CHILD | WS_BORDER, 0, 1, 120, 10, 80, 25);
	Button b1; b1.Create(*this, WS_VISIBLE | WS_CHILD | WS_BORDER, "Add", 1, 120, 50, 80, 25);
	Button b2; b2.Create(*this, WS_VISIBLE | WS_CHILD | WS_BORDER, "Remove", 1, 120, 85, 80, 25);
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

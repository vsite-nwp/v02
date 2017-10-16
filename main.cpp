#include "nwpwin.h"
#include "res.h"

// TODO: prepare classes (Edit, Button, ListBox) for child windows
// TODO: derive from Window, override ClassName

class Edit : public Window {
protected:
	std::string ClassName()override { return "EDIT"; }
};

class Button : public Window {
protected:
	std::string ClassName()override { return "BUTTON"; }
	
};

class ListBox : public Window {
protected:
	std::string ClassName()override { return "LISTBOX"; }
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
	Button add, remove;
	add.Create(*this, WS_CHILD|WS_VISIBLE, "Add", IDC_ADD, 200, 100, 60, 30);
	remove.Create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_ADD, 200, 150, 60, 30);
	EnableWindow(remove, false);

	ListBox lBox;
	lBox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_ADD, 50, 50, 100, 200);

	Edit ebox;
	ebox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_ADD, 200, 60, 80, 40);

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

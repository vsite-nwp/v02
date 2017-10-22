#include "nwpwin.h"
#include "res.h"


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
	Button b_add,b_remove; 
	b_add.Create(*this,WS_CHILD|WS_VISIBLE, "Add",IDC_ADD,160,90,70,30);
	b_remove.Create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 160, 130, 70, 30);
	Edit e;
	e.Create(*this, WS_CHILD | WS_VISIBLE|WS_BORDER, "", IDC_EDIT, 160, 50, 70, 30);
	ListBox l;
	l.Create(*this, WS_CHILD | WS_VISIBLE|WS_BORDER, "", IDC_LB, 50, 50, 100, 130);

	EnableWindow(b_remove, false);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			OnDestroy();
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "Ovo je druga vjezba iz NWP", "About...", MB_OK);
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

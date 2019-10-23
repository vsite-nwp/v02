#include "nwpwin.h"
#include "res.h"
using namespace std;

// TODO: prepare classes (Edit, Button, ListBox) for child windows
// TODO: derive from Window, override ClassName
class Button : public Window {
public:
	std::string ClassName(){
	return "BUTTON"; }
	
};
class Edit : public Window {
	std::string ClassName() {
		return "EDIT";
	}
};
class LBox : public Window {
	std::string ClassName() {
		return "LISTBOX";
	}
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
	Button b1;
	b1.Create(*this, WS_VISIBLE | WS_CHILD, "Add",IDC_ADD,500, 150 ,150 ,40);
	Button b2;
	b2.Create(*this, WS_VISIBLE | WS_CHILD, "Remove", IDC_ADD, 500, 200, 150, 40);
	LBox l;
	l.Create(*this, WS_VISIBLE | WS_CHILD | LBS_STANDARD | LBS_NOTIFY ,"LIST",100, 300, 150 ,150, 150);
	Edit e;
	e.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 300, 100, 200, 25);
	// TODO: create all child windows
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

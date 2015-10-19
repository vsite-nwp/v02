#include "nwpwin.h"
#include "res.h"

// TODO: prepare classes (Edit, Button, ListBox) for child windows
// TODO: derive from Window, override ClassName

class MainWindow : public Window
{
public:
	Edit edit;
	Button button;
	ListBox listBox;
protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
};

int MainWindow::OnCreate(CREATESTRUCT* pcs)
{
	//texstbox
	edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 220, 10, 150, 50);

	char s[128];
	//Kreirai buttoni
	LoadString(0, IDS_Add, s, sizeof s);	
	button.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, s, IDC_ADD, 220, 70, 150, 50);
	LoadString(0, IDS_Remove, s, sizeof s);
	button.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, s, IDC_REMOVE, 220, 130, 150, 50);

	//Listbox
	listBox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 10, 10, 200, 300);

	

	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			DestroyWindow(*this);
			break;
		case ID_HELP_ABOUT:
			// TODO: show dialog with text
			break;
		case IDC_ADD:
			char buffer[256];
			if (GetWindowText(edit, buffer, 256))
			{
				SendMessage(listBox, LB_INSERTSTRING, 0, (LPARAM)buffer);
			}
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

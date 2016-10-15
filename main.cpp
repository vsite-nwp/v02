#include "nwpwin.h"
#include "res.h"


class Button : public Window {
public:
	std::string ClassName() { return "BUTTON"; }
};
class Edit : public Window {
public:
	std::string ClassName() { return "EDIT"; }
};
class ListBox : public Window {
public:
	std::string ClassName() { return "LISTBOX"; }
};
// TODO: derive from Window, override ClassName

class MainWindow : public Window
{
public:
	Button button_add, button_remove;
	Edit edit;
	ListBox list_box;
protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
};

int MainWindow::OnCreate(CREATESTRUCT* pcs)
{
	edit.Create(*this, WS_CHILD | WS_VISIBLE, "edit", IDC_EDIT, 125, 10, 100, 25);
	button_add.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 125, 45, 100, 25);
	button_remove.Create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 125, 85, 100, 25);
	list_box.Create(*this, WS_CHILD | WS_VISIBLE, "ListBox", IDC_LB, 10, 10, 100, 100);
	
	EnableWindow(button_remove, FALSE);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			OnDestroy();
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "Upisite tekst u edit polje, zatim kliknite na Add button za dodavanje u listbox. Remove button mice selektirani tekst iz listbox-a.", "NWP 2", MB_OK);
			break;
		case IDC_ADD:
			char text[250];
			GetDlgItemText(*this, IDC_EDIT, text, sizeof(text));
			
			SendDlgItemMessage(*this, IDC_LB,LB_ADDSTRING, NULL,LPARAM(text));
			
			int count;
			count = SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL);
			if(count) 
				EnableWindow(button_remove, true);
			break;
		case IDC_REMOVE:
			
			int count_1 = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);
			
			if (count_1 >= 0) SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, (WPARAM)count, NULL);
			
			count_1 = SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL);
			if (count_1 == 0) EnableWindow(button_remove, FALSE);
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

#include "nwpwin.h"
#include "res.h"

// TODO: prepare classes (Edit, Button, ListBox) for child windows
class Edit : public Window {
public:
	std::string ClassName() { return "EDIT";}
};

class Button: public Window{
	std::string ClassName() { return "BUTTON"; }
};

class ListBox : public Window {
	std::string ClassName() { return "LISTBOX"; }
};
// TODO: derive from Window, override ClassName

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
	Edit edit; edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, NULL, IDC_EDIT,130,20,100,25);
	Button button_add; button_add.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 130,55,100,25);
	Button button_remove; button_remove.Create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE,130,90,100,25);
	ListBox listbox; listbox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB,10,20,100,125);


	// TODO: disable "Remove" button
	EnableWindow(button_remove, false);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			// TODO: close main window
			PostQuitMessage(0);

			break;
		case ID_HELP_ABOUT:
			// TODO: show dialog with text
			MessageBox(*this, "About....", "About", MB_OK | MB_ICONINFORMATION);
			break;
		case IDC_ADD:
			// TODO: get text from edit control
			// TODO: add string to listbox control
			// TODO: enable "Remove" button

			char txtEdit[64];
			HWND removeButt;
			if (GetDlgItemText(*this, IDC_EDIT, txtEdit, 32)) 
			{
				SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)txtEdit);
				SetDlgItemText(*this, IDC_EDIT, "");

				
				int br = SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL);

				if (br) 
				{
					removeButt = GetDlgItem(*this, IDC_REMOVE);
					EnableWindow(removeButt, true);
				}
			}
			break;
		case IDC_REMOVE:
			// TODO: get listbox selection
			// TODO: if there is a selection, delete selected string
			// TODO: disable "Remove" button if listbox is empty
			
			
			int index = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);

			
			if (index >= 0)
			{
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, (WPARAM)index, NULL);
			}
			
			
			int br = SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL);
			
			if (br < 1)
			{
				removeButt = GetDlgItem(*this, IDC_REMOVE);
				EnableWindow(removeButt, false);
			}
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
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)hMenu, 150, 150, 300, 300);	
	// set icons
	HICON hib = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hib));
	HICON his = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(his));

	Application app; 
	return app.Run();
}

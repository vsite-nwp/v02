#include "nwpwin.h"
#include "res.h"

// TODO: prepare classes (Edit, Button, ListBox) for child windows

class Edit : public Window{
public:
	std::string ClassName() { return "Edit"; }

};

class Button : public Window{
public:
	std::string ClassName() { return "Button"; }

};

class ListBox : public Window{
public:
	std::string ClassName() { return "ListBox"; }

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
	ListBox listbox; listbox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 10, 10, 180, 150);
	Edit edit; edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 202, 10, 150, 40);
	Button button_add; button_add.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Add", IDC_ADD, 202, 60, 150, 40);
	Button button_remove; button_remove.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Remove", IDC_REMOVE, 202, 110, 150, 40);

	// TODO: disable "Remove" button
	EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);

	//disable "Add" button until something is written in edit 
	//EnableWindow(GetDlgItem(*this, IDC_ADD), false);


	return 0;
}

void MainWindow::OnCommand(int id){
	switch (id){
	case ID_FILE_EXIT:
		// TODO: close main window

		PostMessage(*this, WM_CLOSE, 0, 0);

		break;

	case ID_HELP_ABOUT:
		// TODO: show dialog with text
		MessageBox(*this, "ABOUT", "NWP", MB_OK | MB_ICONWARNING);

		break;
	
	/*
	case IDC_EDIT:
	{
	int num = SendDlgItemMessage(*this, IDC_EDIT, LB_GETTEXTLEN, 0, 0);

	// TODO: disable "ADD" button if edit is empty
	if (num > 0)
		EnableWindow(GetDlgItem(*this, IDC_ADD), true);
	else if (num == 0)
		EnableWindow(GetDlgItem(*this, IDC_ADD), false);
	}
	*/
	case IDC_ADD:
		// TODO: get text from edit control
		char buff[1024];
		GetDlgItemText(*this, IDC_EDIT, buff, sizeof buff);

		// TODO: add string to listbox control
		SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)buff);
		SetWindowText(GetDlgItem(*this, IDC_EDIT), "");

		// TODO: enable "Remove" button
		EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
		break;

	case IDC_REMOVE:
		// TODO: get listbox selection
		int selectedID = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);

		// TODO: if there is a selection, delete selected string
		if (selectedID >= 0){
			SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, selectedID, 0);

			int num = SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0);
		
			// TODO: disable "Remove" button if listbox is empty
			if (num > 0)
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			else if (num == 0)
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
			//kada obrisemo zadnji koji je selektiran, smanji selectedID za jedan!
			if (num == selectedID)
				--selectedID;

			//Kada obrisemo zadnji automatski selektiraj zadnji!
			SendDlgItemMessage(*this, IDC_LB, LB_SETCURSEL, selectedID, 0);
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
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)hMenu);	
	// set icons
	HICON hib = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hib));
	HICON his = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(his));

	Application app; 
	return app.Run();
}

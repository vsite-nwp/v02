#include "nwpwin.h"
#include "res.h"


class MainWindow : public Window
{
protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
};

class Button : public Window {
protected:
	std::string ClassName() override {
		return "BUTTON";
	}
};

class ListBox : public Window {
protected: 
	std::string ClassName() override {
		return "LISTBOX";
	}
};

class Edit : public Window {
protected: 
	std::string ClassName() override {
		return "EDIT";
	}
};

int MainWindow::OnCreate(CREATESTRUCT* pcs)
{
	ListBox listbox;
	Edit edit;
	Button buttonAdd;
	Button buttonRemove;

	listbox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, NULL, IDC_LB, 20, 20, 120, 120);
	edit.Create(*this, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, NULL, IDC_EDIT, 150, 20, 100, 25);
	buttonAdd.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 150, 70, 100, 30);
	buttonRemove.Create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 150, 105, 100, 30);

	EnableWindow(buttonRemove, false);
	
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			DestroyWindow(*this);
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "About window opened", "About", MB_OK);
			break;
		case IDC_ADD:

			char edit_text[30];
			if (GetDlgItemText(*this, IDC_EDIT, edit_text, sizeof(edit_text))) {
				SendDlgItemMessage(*this,IDC_LB, LB_ADDSTRING, NULL, (LPARAM)edit_text);
				SetDlgItemText(*this, IDC_EDIT, "");
				
				HWND btnRemoveHandle = GetDlgItem(*this, IDC_REMOVE);
				EnableWindow(btnRemoveHandle, true);
			}
			break;
		case IDC_REMOVE:

			int selectedItemIndex = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);
			if (selectedItemIndex == LB_ERR) break;
			SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, selectedItemIndex, NULL);

			//Selects last item in listbox to make removing easier
			long numberOfItems = SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL);
			if (SendDlgItemMessage(*this, IDC_LB, LB_SETCURSEL, numberOfItems - 1, NULL) == LB_ERR) {
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
				break;
			}
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

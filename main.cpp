#include "nwpwin.h"
#include "res.h"


class Edit : public Window {
public:
	std::string ClassName() { return "EDIT"; }
};

class Button : public Window {
public:
	std::string ClassName() { return "BUTTON"; }
};

class ListBox : public Window {
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
	Button add;
	Button remove;
	Edit edit;
	ListBox listBox;

	add.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 200, 200, 100, 50);
	remove.Create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 200, 300, 100, 50);
	edit.Create(*this, WS_CHILD | WS_VISIBLE, "Edit", IDC_EDIT, 200, 10, 100, 50);
	listBox.Create(*this, WS_CHILD | WS_VISIBLE, "ListBox", IDC_LB, 10, 10, 75, 400);

	::EnableWindow(remove, false);

	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			this->OnDestroy();
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "About", "Vjezba 2", MB_OK);
			break;
		case IDC_ADD:
			char tekst[11];
			GetDlgItemText(*this, IDC_EDIT, tekst, sizeof(tekst));		// ?
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)tekst);
			::EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			break;
		case IDC_REMOVE:
			LRESULT izabrano = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);
			if (izabrano == LB_ERR)
				break;
			else
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, izabrano, 0);
			if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0) == 0)	
				::EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
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

#include "nwpwin.h"
#include "res.h"

class Button : public Window 
{
public:
	std::string ClassName() { return "BUTTON"; }
};

class Edit : public Window 
{
public:
	std::string ClassName() { return "EDIT"; }
};

class ListBox : public Window 
{
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
	Button add, remove;
	add.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 240, 40, 150, 25);
	remove.Create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "Remove", IDC_REMOVE, 240, 70, 150, 25);

	Edit edit;
	edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, "", IDC_EDIT, 240, 10, 150, 25);

	ListBox listbox;
	listbox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 10, 10, 220, 150);
	
	return 0;
}

void MainWindow::OnCommand(int id)
{
	switch(id)
	{
		case ID_FILE_EXIT:
			OnDestroy();
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "Puno zuji, malo meda daje...", "O Programu", MB_OK | MB_ICONINFORMATION);
			break;
		case IDC_ADD:
			char editText[21];
			if (GetDlgItemText(*this, IDC_EDIT, editText, sizeof(editText)))
			{
				SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)editText);
				SetDlgItemText(*this, IDC_EDIT, "");
				if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0))
					EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			}			
			break;
		case IDC_REMOVE:
			int selectedIndex = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			if (selectedIndex == LB_ERR)
				return;
			SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, selectedIndex, 0);
			if (!SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0))
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
			break;
	}
}

void MainWindow::OnDestroy()
{
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
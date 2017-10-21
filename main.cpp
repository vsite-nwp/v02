#include "nwpwin.h"
#include "res.h"

class ListBox : public Window {
public:
	std::string ClassName() override { return "LISTBOX"; }
};

class Edit : public Window {
public:
	std::string ClassName() override { return "EDIT"; }
};

class Button : public Window {
public:
	std::string ClassName() override { return "BUTTON"; }
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
	Button b1, b2 ;
	Edit e1;
	ListBox l1;
	b1.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 250, 150, 150, 30);
	b2.Create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "Remove", IDC_REMOVE, 250, 200, 150, 30);
	e1.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT,250, 100, 150, 30);
	l1.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 50, 100, 150, 150);

	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL)) {
				int yesno = MessageBoxA(*this, "Are you sure? All data will be lost.", "Remove", MB_YESNO | MB_ICONWARNING);
				if (yesno == IDYES) {
					PostQuitMessage(0);
				}
			}
			else {
				PostQuitMessage(0);
			}
			break;
		case ID_HELP_ABOUT:
			MessageBoxA(*this, "Druga vježba.", "About", MB_OK | MB_ICONINFORMATION);
			break;
		case IDC_ADD:
			char text[100];
			GetDlgItemTextA(*this, IDC_EDIT, text, 100);
			if (strlen(text) == 0) 
			{
				MessageBoxA(*this, "There is no text to add.", "Info", MB_OK | MB_ICONINFORMATION);
			}
			else
			{
				SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)text);
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			}
			break;
		case IDC_REMOVE:
			int selected = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);
			if (selected == LB_ERR) 
			{
				MessageBoxA(*this, "Nothing to delete, item is not selected.", "Info", MB_OK | MB_ICONINFORMATION);
			}
			else 
			{	
				int yesno = MessageBoxA(*this, "Are you sure? An item will be deleted.", "Remove", MB_YESNO | MB_ICONWARNING);
				if (yesno == IDYES) {
					SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, selected, NULL);
					MessageBoxA(*this, "Item is deleted.", "Info", MB_OK | MB_ICONINFORMATION);
					if (!SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL))
						EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
				}	
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

	HICON hib = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hib));
	HICON his = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(his));

	Application app; 
	return app.Run();
}

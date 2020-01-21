#include "nwpwin.h"
#include "res.h"
using namespace std;

class ListBox : public Window {
protected:
	string ClassName() override { 
		return "LISTBOX"; 
	}
};

class Button : public Window {
protected:
	string ClassName() override { 
		return "BUTTON"; 
	}
};

class Edit : public Window {
protected:
	string ClassName() override { 
		return "EDIT";
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
	ListBox listBox;
	Edit edit;
	Button add;
	Button remove;

	listBox.Create(*this, WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL , "", IDC_LB, 10, 10, 150, 250);
	edit.Create(*this, WS_BORDER | WS_CHILD | WS_VISIBLE, "", IDC_EDIT, 170, 10, 150, 20);
	add.Create(*this, WS_BORDER | WS_CHILD | WS_VISIBLE, "ADD", IDC_ADD, 170, 192, 150, 25);
	remove.Create(*this, WS_BORDER | WS_CHILD | WS_VISIBLE, "REMOVE", IDC_REMOVE, 170, 227, 150, 25);
	EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			PostQuitMessage(0);
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "Vježba 2", "About", MB_OK | MB_ICONINFORMATION);
			break;
		case IDC_ADD:
			char text[100];
			if (GetDlgItemText(*this, IDC_EDIT, text, sizeof(text)) != 0) {
				SendMessage(GetDlgItem(*this, IDC_LB), LB_ADDSTRING, 0, (LPARAM)text);
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
				SetDlgItemText(*this, IDC_EDIT, "");
			}
			break;
		case IDC_REMOVE:
			int index = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			if (index != LB_ERR) {
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, index, 0);
			}
			else {
				break;
			}

			if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0) == 0) {
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
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

#include "nwpwin.h"
#include "res.h"
#include<windows.h>
#include<iostream>

class Edit :public Window {
public:
	std::string ClassName() { return "EDIT"; }

};
class Button :public Window {
public:
	std::string ClassName() { return "BUTTON"; }

};
class ListBox :public Window {
public:
	std::string ClassName() { return "LISTBOX"; }

}; // 



class MainWindow : public Window
{
protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
};

int MainWindow::OnCreate(CREATESTRUCT* pcs)
{
	Edit edit;
	edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, " ", IDC_EDIT, 150, 0, 100, 30);

	ListBox listbox;
	listbox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 0, 0, 100, 150);

	Button button_add;
	button_add.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Add", IDC_ADD, 150, 50, 100, 30);

	Button button_remove;
	button_remove.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Remove", IDC_REMOVE, 150, 100, 100, 30);
	
	EnableWindow(button_remove, false); //deaktiviraj remove gumb prilikom pokretanja programa
		
	return 0;
}

void MainWindow::OnCommand(int id) {
	switch (id) {
	case ID_FILE_EXIT:
		
		PostQuitMessage(0);
		break;
	
	case ID_HELP_ABOUT:
		
		MessageBox(*this, "Unesite tekst sa Add, Uklonite tekst sa Remove ", "Vježba2",MB_APPLMODAL );
		break;
	
	case IDC_ADD:
		
		char  word[32];
		GetDlgItemText(*this, IDC_EDIT, word, 32);  //pokupi string iz edita u word
		SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, LPARAM(word)); //pošalji string u listbox
		
		HWND enable_button;
		enable_button = GetDlgItem(*this, IDC_REMOVE);
		int num;
		num=SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL);
		if (num) {
			EnableWindow(enable_button, true); //ako je word dodan aktiviraj gumb "Remove"
		}
		break;
	case IDC_REMOVE:
		
		HWND disable_button;
		disable_button = GetDlgItem(*this, IDC_REMOVE);
		int num1=SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL);
		if (num1 == 0) {
			EnableWindow(disable_button, false);  //ako je listbox prazan, deaktiviraj gumb "Remove"
		}
		int id = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);
		if (id >= 0) {
			SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, WPARAM(id), NULL); //briši odabrani string iz listboxa
		}
			break;
	}
}

void MainWindow::OnDestroy() {
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
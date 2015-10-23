#include "nwpwin.h"
#include "res.h"
#include<windows.h>
#include<iostream>





// TODO: prepare classes (Edit, Button, ListBox) for child windows
// TODO: derive from Window, override ClassName
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
	// TODO: create all child windows


	Edit edit;
	edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, " ", IDC_EDIT, 150, 0, 100, 30);

	ListBox listbox;
	listbox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 0, 0, 100, 150);

	Button button_add;
	button_add.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Add", IDC_ADD, 150, 50, 100, 30);

	Button button_remove;
	button_remove.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Remove", IDC_REMOVE, 150, 100, 100, 30);
	
	// TODO: disable "Remove" button
	
	EnableWindow(button_remove, false); //deaktiviraj remove gumb prilikom pokretanja programa
		

	
	return 0;
}

void MainWindow::OnCommand(int id) {
	switch (id) {
	case ID_FILE_EXIT:
		
		// TODO: close main window
		PostQuitMessage(0);
		break;
	case ID_HELP_ABOUT:
		// TODO: show dialog with text
		MessageBox(*this, "Unesite tekst sa Add, Uklonite tekst sa Remove ", "Vježba2",WS_CHILD | WS_VISIBLE );
		break;
	case IDC_ADD:
		char  word[32];
		// TODO: get text from edit control
		GetDlgItemText(*this, IDC_EDIT, word, 32);  //pokupi string iz edita u word
		// TODO: add string to listbox control
		SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, LPARAM(word)); //pošalji string u listbox
		// TODO: enable "Remove" button
		
		HWND enable_button;
		enable_button = GetDlgItem(*this, IDC_REMOVE);
		int num;
		num = SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL);
		if (num) {
			EnableWindow(enable_button, true); //ako je word dodan aktiviraj gumb "Remove"
		}
		break;
	case IDC_REMOVE:
		
		// TODO: disable "Remove" button if listbox is empty
		
		HWND disable_button;
		disable_button = GetDlgItem(*this, IDC_REMOVE);
		int num1;
		num1 = SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL);
		if (num1 == 0) {
			EnableWindow(disable_button, false);  //ako je listbox prazan, deaktiviraj gumb "Remove"
		}
		// TODO: get listbox selection
		int id;
		id = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);
		if (id >=0)
			SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, WPARAM(id), NULL); //briši odabrani string iz listboxa
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
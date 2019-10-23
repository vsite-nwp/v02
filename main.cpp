#include "nwpwin.h"
#include "res.h"

class ListBox :public Window {
protected:
	std::string ClassName() override { return "LISTBOX"; }
};

class Button :public Window {
protected:
	std::string ClassName() override { return "BUTTON"; }
};

class Edit : public Window {
protected:
	std::string ClassName() override { return "EDIT"; }
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
	ListBox lBox;
	Edit edit;
	Button butt_1, butt_2;

	lBox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 20, 20, 100, 120);
	edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 130, 20, 100, 25);
	butt_1.Create(*this, WS_CHILD | WS_VISIBLE , "ADD", IDC_ADD, 130, 50, 100, 25);
	butt_2.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "REMOVE", IDC_REMOVE, 130, 80, 100, 25);
	EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
	
	return 0;
}

void MainWindow::OnCommand(int id){
	
	switch(id){
		case ID_FILE_EXIT:
			PostQuitMessage(0);
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "Ovo je 2. vjezba ", "Help", MB_OK);
			break;
		case IDC_ADD:
			char text[50];
			if (GetDlgItemText(*this, IDC_EDIT, text, sizeof(text))!=0) {  //da ne mozemo staviti prazan string
				SendMessage(GetDlgItem(*this, IDC_LB), LB_ADDSTRING, 0, (LPARAM)text);  //salje u LB ono sto smo napiasli
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
				SetDlgItemText(*this, IDC_EDIT, "");         //brise iz edita ono sto smo napisali
			}
			break;
		case IDC_REMOVE:
			int itemIndex = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			if (itemIndex == LB_ERR)
				break;
			else
				SendDlgItemMessage(*this , IDC_LB, LB_DELETESTRING, itemIndex, 0);

			if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0) == 0)
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);

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

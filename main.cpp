#include "nwpwin.h"
#include "res.h"

class Edit : public Window {
protected:
	std::string ClassName()override { return "edit"; }
};
class ListBox : public Window {
protected:
	std::string ClassName()override { return "listBox"; }
};
class Button : public Window {
protected:
	std::string ClassName()override { return "button"; }
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
	ListBox LBox;
	Edit edit;
	Button button_1, button_2;
	LBox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 50, 50, 100, 120);
	edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 170, 50, 100, 25);
	button_1.Create(*this, WS_CHILD | WS_VISIBLE, "ADD", IDC_ADD, 170, 80, 100, 25);
	button_2.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "REMOVE", IDC_REMOVE, 170, 110, 100, 25);
	
	return 0;
}

void MainWindow::OnCommand(int id){
	
	

	switch(id){
		
		case ID_FILE_EXIT:
			PostQuitMessage(0);
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "Druga vjezba", "Pomoc", MB_OK);
			break;
		case IDC_ADD:
			char text[100];
			if (GetDlgItemText(*this, IDC_EDIT,text, sizeof(text)) != 0) {
				SendMessage(GetDlgItem(*this, IDC_LB), LB_ADDSTRING, 0, (LPARAM)text);  
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
				SetDlgItemText(*this, IDC_EDIT, "");       
			}
			break;
		case IDC_REMOVE:
			int itemIndex = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			if (itemIndex == LB_ERR)
				break;
			else
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, itemIndex, 0);
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
	
	HICON hib = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hib));
	HICON his = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(his));

	Application app; 
	return app.Run();
}

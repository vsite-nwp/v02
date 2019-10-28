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

	Button Button_Add, Button_Remove;
	Button_Add.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 150 , 90 , 120, 30);
	Button_Remove.Create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "Remove", IDC_REMOVE, 150 , 130, 120, 30);

	Edit e;
	e.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 150, 30, 120, 30);

	ListBox lb;
	lb.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 30, 30, 90, 150);



	return 0;
}

void MainWindow::OnCommand(int id){

	

	switch(id){
		case ID_FILE_EXIT:
			DestroyWindow(*this);
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "Some msg", "About", MB_OK);
			break;
		case IDC_ADD:
			
			char TextBox_Text[30];
			if (GetDlgItemText(*this, IDC_EDIT, TextBox_Text, sizeof(TextBox_Text)))
			{
				SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)TextBox_Text);
				if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0) > 0)
				{
					EnableWindow(GetDlgItem(*this, IDC_REMOVE), TRUE);

				}

			}
			SetDlgItemText(*this, IDC_EDIT, "");
			break;
		case IDC_REMOVE:
			LRESULT selected = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);


			// if(selected) -> cannot delete first entry
			if (selected != LB_ERR)
			{
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, selected, 0);
				if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0) == 0)
				{
					EnableWindow(GetDlgItem(*this, IDC_REMOVE), FALSE);
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
	// set icons
	HICON hib = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hib));
	HICON his = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(his));

	Application app; 
	return app.Run();
}

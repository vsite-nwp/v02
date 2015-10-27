#include "nwpwin.h"
#include "res.h"

// TODO: prepare classes (Edit, Button, ListBox) for child windows
class Edit:public Window{
public:
	 std::string ClassName()
		 {return "Edit";}
};

class Button:public Window{
public:
	std::string ClassName()
	{return "Button";}
};
class ListBox:public Window{
public:
	std::string ClassName()
	{return "ListBox";}
};


// TODO: derive from Window, override ClassName

class MainWindow : public Window
{
protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
};

int MainWindow::OnCreate(CREATESTRUCT* pcs)
{
	Edit edit; edit.Create(* this,WS_CHILD | WS_VISIBLE | WS_BORDER,"",IDC_EDIT,120,10,100,24 );
	Button button_add; button_add.Create(* this,WS_CHILD | WS_VISIBLE,"add",IDC_ADD,120,40,100,24);
	Button button_remove; button_remove.Create(* this,WS_CHILD | WS_VISIBLE,"remove",IDC_REMOVE,120,70,100,24);
	ListBox listbox; listbox.Create(* this,WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL,"listbox",IDC_LB,10,10,100,100);
	EnableWindow(GetDlgItem(*this,IDC_REMOVE),false);
	// TODO: create all child windows
	// TODO: disable "Remove" button
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			// TODO: close main window
			PostMessage(*this,WM_CLOSE,0,0);
			break;
		case ID_HELP_ABOUT:
			// TODO: show dialog with text
			MessageBox(*this,"Vjezba_2","NWP",MB_OK);
			break;
		case IDC_ADD:
			// TODO: get text from edit control
			char c[128];
			GetDlgItemText(*this,IDC_EDIT,c,sizeof c);
			// TODO: add string to listbox control
			SendDlgItemMessage(*this,IDC_LB,LB_ADDSTRING,0,(LPARAM)c);
			// TODO: enable "Remove" button
			EnableWindow(GetDlgItem(*this,IDC_REMOVE),true);
			break;
		case IDC_REMOVE:
			int ind=SendDlgItemMessage(*this,IDC_REMOVE,LB_GETCURSEL,0,0);
			// TODO: get listbox selection
			    SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, ind, 0);
				int cnt = SendDlgItemMessage(*this, IDC_REMOVE	, LB_GETCOUNT, 0, 0);
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), cnt > 0);
				if(ind == cnt) --ind;
				SendDlgItemMessage(*this, IDC_REMOVE, LB_SETCURSEL, ind, 0);

			// TODO: if there is a selection, delete selected string
			// TODO: disable "Remove" button if listbox is empty
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

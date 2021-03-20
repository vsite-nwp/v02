#include "nwpwin.h"
#include "res.h"
#include "Windows.h"


class button :public Window {
	virtual std::string ClassName() { return "BUTTON"; }

};
class edit : public Window {
	virtual std::string ClassName() { return "EDIT"; }
};
class listBox :public Window {
	virtual std::string ClassName() { return "LISTBOX"; }
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
	
	button b1;
	b1.Create(*this, WS_CHILD| WS_VISIBLE, "ADD", IDC_ADD,150,60,100,25);
	edit e1;
	e1.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "EDIT", IDC_EDIT, 150, 25, 100, 25);
	
	listBox l1;
	l1.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "LISTBOX", IDC_LB, 25, 25, 100, 100);

	button m1;
	m1.Create(*this, WS_CHILD | WS_VISIBLE, "REMOVE", IDC_REMOVE, 150, 90, 100, 25);



	
	EnableWindow(GetDlgItem(*this, IDC_REMOVE),false);


	
	return 0;
}


void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
		{
			OnDestroy();
			break;
		}
		case ID_HELP_ABOUT:
		{
			
			MessageBox(*this, "Help", "HELP", ID_HELP_ABOUT);
			break;
		}
		case IDC_ADD:
		{
			char buffer[100];
			GetDlgItemText(*this, IDC_EDIT, buffer, sizeof(buffer));

			if(buffer!=" ")
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)buffer);
			
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			break;
		}
		case IDC_REMOVE:
		{
			int index = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			
			if(index!=LB_ERR)
			SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, index, 0);
			
			
			if (LB_GETCOUNT==0) {
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
			}
			break;
		}
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

#include "nwpwin.h"
#include "res.h"
using namespace std;


class Button : public Window {
public:
	std::string ClassName(){
	return "BUTTON"; }
	
};
class Edit : public Window {
	std::string ClassName() {
		return "EDIT";
	}
};
class LBox : public Window {
	std::string ClassName() {
		return "LISTBOX";
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
	Button b1;
	b1.Create(*this, WS_VISIBLE | WS_CHILD, "Add",IDC_ADD,500, 150 ,150 ,40);
	Button b2;
	b2.Create(*this, WS_VISIBLE | WS_CHILD, "Remove", IDC_REMOVE, 500, 200, 150, 40);
	LBox l;
	l.Create(*this, WS_VISIBLE | WS_CHILD | LBS_STANDARD | LBS_NOTIFY ,"",IDC_LB, 300, 150 ,150, 150);
	Edit e;
	e.Create(*this, WS_VISIBLE | WS_CHILD | WS_BORDER, "", IDC_EDIT, 300, 100, 200, 25);
	EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
	
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			PostQuitMessage(0);
			
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "This is dialog with text", "About", MB_OK);
			
			break;
		case IDC_ADD:
			char word[100];

			GetDlgItemText(*this, IDC_EDIT, word, sizeof(word));
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)word);
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			SetDlgItemText(*this, IDC_EDIT, "");
				
			
			break;
		case IDC_REMOVE:
			int ind = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);
			if (ind != -1)
			{
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, (WPARAM)ind, NULL);
				if (!SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL))
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

#include "nwpwin.h"
#include "res.h"

class Button : public Window
{
protected:
	std::string ClassName()
	{
		return "Button";
	}
};

class Edit : public Window
{
protected:
	std::string ClassName()
	{
		return "Edit";
	}
};

class ListBox : public Window
{
protected:
	std::string ClassName()
	{
		return "ListBox";
	}
};

class MainWindow : public Window
{
protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
	void onAbout();
	void onAdd();
	void onRemove();
	void onExit();
};

int MainWindow::OnCreate(CREATESTRUCT* pcs)
{
	
	Button mButtonAdd, mButtonRemove;
	ListBox mListBox;
	Edit mEdit;

	mButtonAdd.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 200, 70, 100, 20);
	mButtonRemove.Create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "Remove", IDC_REMOVE, 200, 90, 100, 20);
	mEdit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 200, 50, 100, 20);
	mListBox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 50, 50, 150, 150);

	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			onExit();
			break;
		case ID_HELP_ABOUT:
			onAbout();
			break;
		case IDC_ADD:
			onAdd();
			break;
		case IDC_REMOVE:
			onRemove();
			break;
	}
}

void MainWindow::onAbout() 
{
	MessageBox(*this, "GUI program with buttons!! \n !Patent Pending!", "About", MB_OK | MB_ICONINFORMATION);
}

void MainWindow::onExit() 
{
	if (MessageBox(*this, "Do you want to exit?", "Exit?", MB_YESNOCANCEL | MB_ICONEXCLAMATION) == IDYES)
	{
		DestroyWindow(*this);
	}
}

void MainWindow::onAdd() 
{
	char userInput[255+1];
	if (GetDlgItemText(*this, IDC_EDIT, userInput, sizeof(userInput)))
	{
		SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(userInput));
		EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
		SetDlgItemText(*this, IDC_EDIT, "");
	}	   
}

void MainWindow::onRemove()
{
	long res = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
	if (res != LB_ERR) {
		SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, static_cast<WPARAM>(res), 0);
		if (!SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0))
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
	}
}

void MainWindow::OnDestroy()
{
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


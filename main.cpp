#include "nwpwin.h"
#include "res.h"
class Button : public Window
{
protected:
	virtual std::string ClassName() override;
};

class ListBox : public Window
{
protected:
	virtual std::string ClassName() override;
};

class Edit : public Window
{
protected:
	virtual std::string ClassName() override;
};

std::string Button::ClassName()
{
	return "Button";
}

std::string ListBox::ClassName()
{
	return "ListBox";
}

std::string Edit::ClassName()
{
	return "Edit";
}

class MainWindow : public Window
{
protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
	void OnClose();
	void OnAdd();
	void OnRemove();
private:
	Button mButton;
	ListBox mListBox;
	Edit mEdit;
};

int MainWindow::OnCreate(CREATESTRUCT* pcs)
{
	mListBox.Create(*this, WS_VISIBLE | WS_CHILD | WS_BORDER, "", IDC_LB, 50, 100, 100, 200);
	mEdit.Create(*this, WS_VISIBLE | WS_CHILD | WS_BORDER, "", IDC_EDIT, 160, 100, 120, 30);

	char str[40]; LoadString(0, IDS_ADD, str, std::size(str));
	mButton.Create(*this, WS_VISIBLE | WS_CHILD, str, IDC_ADD, 160, 135, 120, 30);

	LoadString(0, IDS_REMOVE, str, std::size(str));
	mButton.Create(*this, WS_VISIBLE | WS_CHILD, str, IDC_REMOVE, 160, 165, 120, 30);

	EnableWindow(mButton, false);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id)
	{
		case ID_FILE_EXIT:
		{
			OnDestroy();
			break;
		}
		case ID_HELP_ABOUT:
		{
			char buff[50];
			LoadString(0, IDS_DIAG_TEXT, buff, std::size(buff));
			MessageBox(*this, buff, "Help", MB_OK);
			break;
		}
		case IDC_ADD:
		{
			OnAdd();
			break;
		}
		case IDC_REMOVE:
		{
			OnRemove();
			break;
		}
	}
}

void MainWindow::OnDestroy()
{
	::PostQuitMessage(0);
}

void MainWindow::OnClose()
{
	if (SendMessage(mListBox, LB_GETCOUNT, 0, 0) > 0)
	{
		char buff[100];
		LoadString(0, IDS_WARN, buff, std::size(buff));
		if (IDNO == MessageBox(*this, buff, "Warn", MB_YESNO | MB_ICONWARNING))
		{
			return;
		}
		//  in case that yes is pressed
		OnDestroy();
	}
	//  in case that there is nothing in ListBox
	OnDestroy();
}

void MainWindow::OnAdd()
{
	char buff[70];
	::GetWindowText(mEdit, buff, std::size(buff));
	if (buff)
	{
		if (std::strlen(buff) != 0)
		{
			//  API function will return LB_ERR if there is issufficent space to store new string.
			if (::SendMessage(mListBox, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(buff)) == LB_ERR)
			{
				LoadString(0, IDS_ERROR, buff, std::size(buff));
				MessageBox(*this, buff, "Error", MB_OK | MB_ICONERROR);
			}
			EnableWindow(mButton, true);
		}
		else
		{
			//  word was not selected
			LoadString(0, IDS_BAD_INDEX, buff, std::size(buff));
			MessageBox(*this, buff, "Error", MB_OK | MB_ICONERROR);
		}
	}
}

void MainWindow::OnRemove()
{
	const int selectedIndex = SendMessage(mListBox, LB_GETCURSEL, 0, 0);
	if (selectedIndex > -1) 
	{
		SendMessage(mListBox, LB_DELETESTRING, selectedIndex, 0);
		if (SendMessage(mListBox, LB_GETCOUNT, 0, 0) <= 0)
		{
			EnableWindow(mButton, false);
		}
	}
	else if(selectedIndex == LB_ERR)
	{
		char buff[100];
		LoadString(0, IDS_ERROR_INDEX, buff, std::size(buff));
		MessageBox(*this, buff, "Error", MB_OK | MB_ICONERROR);
	}
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

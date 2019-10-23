#include "nwpwin.h"
#include "res.h"
class Button : public Window
{
protected:
	std::string ClassName() override;
};

class ListBox : public Window
{
protected:
	std::string ClassName() override;
};

class Edit : public Window
{
protected:
	std::string ClassName() override;
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
	
	std::string LoadMessageFromRes(UINT id);
private:
	Button mAdd;
	Button mRemove;
	ListBox mListBox;
	Edit mEdit;
};

std::string MainWindow::LoadMessageFromRes(UINT id)
{
	char buff[100];
	int len = ::LoadString(0, id, buff, std::size(buff));
	if (len > 0)
	{
		return std::string(buff);
	}
	return std::string();
}

int MainWindow::OnCreate(CREATESTRUCT* pcs)
{
	mListBox.Create(*this, WS_VISIBLE | WS_CHILD | WS_BORDER, "", IDC_LB, 50, 100, 100, 200);
	mEdit.Create(*this, WS_VISIBLE | WS_CHILD | WS_BORDER, "", IDC_EDIT, 160, 100, 120, 30);
	mAdd.Create(*this, WS_VISIBLE | WS_CHILD, LoadMessageFromRes(IDS_ADD).c_str(), IDC_ADD, 160, 135, 120, 30);
	mRemove.Create(*this, WS_VISIBLE | WS_CHILD, LoadMessageFromRes(IDS_REMOVE).c_str(), IDC_REMOVE, 160, 165, 120, 30);

	EnableWindow(mRemove, false);
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
			MessageBox(*this, LoadMessageFromRes(IDS_DIAG_TEXT).c_str(), LoadMessageFromRes(IDS_CAPT_HELP).c_str(), MB_OK);
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
	const int count = ::SendMessage(mListBox, LB_GETCOUNT, 0, 0);
	if (count > 0)
	{
		if (::MessageBox(*this, LoadMessageFromRes(IDS_WARN).c_str(), LoadMessageFromRes(IDS_CAPT_WARN).c_str(), MB_YESNO | MB_ICONWARNING) == IDNO)
		{
			return;
		}
	}
	//  in case that there is nothing in ListBox and, if yes is pressed
	DestroyWindow(*this);
}

void MainWindow::OnAdd()
{
	char buff[70];
	const int len = ::GetWindowText(mEdit, buff, std::size(buff));
	if (len != 0)
	{
		//  API function will return LB_ERR if there is issufficent space to store new string.
		if (::SendMessage(mListBox, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(buff)) == LB_ERR)
		{
			::MessageBox(*this, LoadMessageFromRes(IDS_ERROR).c_str(), LoadMessageFromRes(IDS_CAPT_ERROR).c_str(), MB_OK | MB_ICONERROR);
		}
		::EnableWindow(mRemove, true);
	}
	else
	{
		//  word was not selected
		::MessageBox(*this, LoadMessageFromRes(IDS_BAD_INDEX).c_str(), LoadMessageFromRes(IDS_CAPT_ERROR).c_str(), MB_OK | MB_ICONERROR);
	}
	
}

void MainWindow::OnRemove()
{
	const int selectedIndex = ::SendMessage(mListBox, LB_GETCURSEL, 0, 0);
	if (selectedIndex > -1) 
	{
		::SendMessage(mListBox, LB_DELETESTRING, selectedIndex, 0);
		const int count = ::SendMessage(mListBox, LB_GETCOUNT, 0, 0);
		if (count <= 0)
		{
			::EnableWindow(mRemove, false);
		}
	}
	else
	{
		::MessageBox(*this, LoadMessageFromRes(IDS_ERROR_INDEX).c_str(), LoadMessageFromRes(IDS_CAPT_ERROR).c_str(), MB_OK | MB_ICONERROR);
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

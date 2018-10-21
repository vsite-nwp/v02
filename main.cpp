#include "nwpwin.h"
#include "res.h"
#include <string>

class ListBox : public Window {
protected:
	std::string ClassName() override {
		return "LISTBOX";
	}
};

class Edit : public Window {
protected:
	std::string ClassName() override {
		return "EDIT";
	}
};

class Button : public Window {
protected:
	std::string ClassName() override {
		return "BUTTON";
	}
};

class MainWindow : public Window {
private:
	std::string ItemsToString(const int count);
	void OnExit();
	void OnAdd();
	void OnRemove(const int selectedItem);
	void RemoveItem(const int selectedItem);
	void AddItem(const char* nameOfItem);
protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
};

int MainWindow::OnCreate(CREATESTRUCT* pcs)
{
	HFONT hf = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

	ListBox listBox;
	Edit edit;
	Button buttonAdd, buttonRemove;

	listBox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 50, 50, 100, 120);
	edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 170, 60, 80, 20);
	buttonAdd.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Add", IDC_ADD, 170, 100, 80, 20);
	buttonRemove.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_DISABLED, "Remove", IDC_REMOVE, 170, 130, 80, 20);

	SendMessage(edit, WM_SETFONT, (WPARAM)hf, 0);
	
	return 0;
}

void MainWindow::OnExit() {
	int count = SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL);

	if (count > 0) {
		int result = MessageBox(*this, ItemsToString(count).c_str(), "Close", MB_YESNO | MB_ICONQUESTION);
		if (result == IDYES) {
			::PostQuitMessage(0);
		}
	}
	else {
		::PostQuitMessage(0);
	}
}

std::string MainWindow::ItemsToString(const int count) {
	std::string allItems = "Items: \"";
	for (int index = 0; index < count; ++index) {
		char text[101];
		SendDlgItemMessage(*this, IDC_LB, LB_GETTEXT, index, (LPARAM)text);
		if (index == count - 1) {
			allItems += text + std::string("");
		}
		else {
			allItems += text + std::string(", ");
		}
	}
	allItems += "\" will be lost!\nDo you want to exit?";

	return allItems;
}

void MainWindow::AddItem(const char* nameOfItem) {
	EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
	SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)nameOfItem);
	SetWindowText(GetDlgItem(*this, IDC_EDIT), "");
}

void MainWindow::OnAdd() {
	char nameOfItem[101];
	GetDlgItemText(*this, IDC_EDIT, nameOfItem, sizeof(nameOfItem));
	if (strlen(nameOfItem)) {
		AddItem(nameOfItem);
	}
	else {
		MessageBox(*this, "Textfield is empty!", "Error", MB_OK | MB_ICONWARNING);
	}
}

void MainWindow::OnRemove(const int selectedItem) {
	char textOfSelectedItem[101];
	SendDlgItemMessage(*this, IDC_LB, LB_GETTEXT, selectedItem, (LPARAM)textOfSelectedItem);

	std::string messageDelete = std::string("Delete ") + textOfSelectedItem + "?";
	int result = MessageBox(*this, messageDelete.c_str(), "Delete", MB_YESNO | MB_ICONQUESTION);

	if (result == IDYES) {
		RemoveItem(selectedItem);
	}	
}

void MainWindow::RemoveItem(const int selectedItem) {
	SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, selectedItem, NULL);
	if (!SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL)) {
		EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
	}
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			OnExit();
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "Exercise No. 2!", "About", MB_OK | MB_ICONINFORMATION);
			break;
		case IDC_ADD:
			OnAdd();
			break;
		case IDC_REMOVE:
			int selectedItem = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);
			if (selectedItem != LB_ERR) {
				OnRemove(selectedItem);
			} else {
				MessageBox(*this, "No selected item!", "Error", MB_OK | MB_ICONINFORMATION);
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
	
	HICON hib = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hib));
	HICON his = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(his));

	Application app; 
	return app.Run();
}

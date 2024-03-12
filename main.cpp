#include "nwpwin.h"
#include "res.h"




INT_PTR CALLBACK AboutDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hwndDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}





class button : public vsite::nwp::window {
protected:
	std::string class_name() override { return "BUTTON"; }
};
class edit : public vsite::nwp::window {
protected:
	std::string class_name() override { return "EDIT"; }
};
class list_box : public vsite::nwp::window {
protected:
	std::string class_name() override { return "LISTBOX"; }
};


// : prepare classes (edit, button, list_box) for child windows
// : derive from window, override class_name

class main_window : public vsite::nwp::window
{
protected:
	int on_create(CREATESTRUCT* pcs) override;
	void on_command(int id) override;
	void on_destroy() override;
};

int main_window::on_create(CREATESTRUCT* pcs)
{
	// : create all child windows
	char remove_text[128];
	::LoadString(0, IDC_REMOVE, remove_text, sizeof(remove_text));
	char add_text[128];
	::LoadString(0, IDC_ADD, add_text, sizeof(add_text));
	
	button add;
	button remove;
	edit edit;
	list_box list_box;

	add.create(*this,WS_CHILD| WS_VISIBLE,add_text, IDC_ADD, 100, 50, 80, 24);
	remove.create(*this,WS_CHILD | WS_VISIBLE,remove_text,IDC_REMOVE, 100, 80, 80, 24);
	edit.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, 0, IDC_EDIT, 100, 20, 80, 24);
	list_box.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, 0, IDC_LB, 20, 20, 70, 90);
	
	EnableWindow(remove, false);
	
	// : disable "Remove" button
	return 0;
}


void main_window::on_command(int id){
	switch(id){
		int textLength;
		char text[256];
		HWND hwListBox;
		HWND hwEdit;
		case ID_FILE_EXIT:
			DestroyWindow(*this);
			// : close main window
			break;
		case ID_HELP_ABOUT:
			// : show dialog with text
			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(ID_HELP_ABOUT), 0, AboutDialogProc);
			break;
		case IDC_ADD:
			textLength = GetWindowTextLength(GetDlgItem(*this, IDC_EDIT)) + 1;
			GetWindowText(GetDlgItem(*this, IDC_EDIT), text, textLength);
			hwListBox = GetDlgItem(*this, IDC_LB);
			hwEdit = GetDlgItem(*this, IDC_EDIT);
			SendMessage(hwListBox, LB_ADDSTRING, 0, (LPARAM)text);
			EnableWindow(GetDlgItem(*this,IDC_REMOVE), true);
			// : get text from edit control
			// : add string to listbox control
			// : enable "Remove" button
			break;
		case IDC_REMOVE:
			int index = SendMessage(GetDlgItem(*this, IDC_LB), LB_GETCURSEL, 0, 0);
			if (index != LB_ERR)
			{
				SendMessage(GetDlgItem(*this, IDC_LB), LB_DELETESTRING, index, 0);
			}
			int count = SendMessage(GetDlgItem(*this, IDC_LB), LB_GETCOUNT, 0, 0);
			if (count == 0)
			{
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
			}
			// : get listbox selection
			// : if there is a selection, delete selected string
			// : disable "Remove" button if listbox is empty
			break;
	}
}

void main_window::on_destroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	main_window w; 
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)::LoadMenu(instance, MAKEINTRESOURCE(IDM_V2)));
	vsite::nwp::set_icons(instance, w, IDI_V2);
	vsite::nwp::application app;
	return app.run();
}

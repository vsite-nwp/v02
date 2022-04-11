#include "nwpwin.h"
#include "res.h"


// : prepare classes (edit, button, list_box) for child windows
// : derive from window, override class_name

class Edit : public vsite::nwp::window {
protected:
	std::string class_name()override { 
		return "Edit"; 
	}
};

class Button : public vsite::nwp::window {
protected:
	std::string class_name()override {
		return "Button";
	}
};

class ListBox : public vsite::nwp::window {
protected:
	std::string class_name()override {
		return "ListBox";
	}
};

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
	// : disable "Remove" button
	Button buttonAdd, buttonRemove;
	buttonAdd.create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 125, 50, 100, 20);
	buttonRemove.create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED , "Remove", IDC_REMOVE, 125, 80, 100, 20);
	
	Edit e;
	e.create(*this, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, "", IDC_EDIT, 125, 10, 100, 40);

	ListBox lib;
	lib.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 10, 10, 100, 100);

	return 0;
}

void main_window::on_command(int id){
	switch(id){
		case ID_FILE_EXIT:
			// : close main window
			on_destroy();
			break;
		case ID_HELP_ABOUT:
			// : show dialog with text
			MessageBox(*this, "Help", "Help", MB_OK);
			break;
		case IDC_ADD:
			// : get text from edit control
			// : add string to listbox control
			// : enable "Remove" button
			char text[50];
			GetDlgItemText(*this, IDC_EDIT, text, sizeof(text));

			if (text[0] != 0)
				SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)text);
			SetDlgItemTextA(*this, IDC_EDIT, "");

			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			break;
		case IDC_REMOVE:
			// : get listbox selection
			// : if there is a selection, delete selected string
			// : disable "Remove" button if listbox is empty
			int lbIndex = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			if (lbIndex == LB_ERR)
				break;
			else
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, lbIndex, 0);
			
			int lbCount = SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0);
			if (lbCount == 0)
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
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

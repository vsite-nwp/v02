#include "nwpwin.h"
#include "res.h"




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
	char text[128];

	button add;
	button remove;
	edit edit;
	list_box list_box;
	::LoadString(0, IDC_ADD, text, sizeof(text));
	add.create(*this,WS_CHILD| WS_VISIBLE,text, IDC_ADD, 100, 50, 80, 24);
	::LoadString(0, IDC_REMOVE, text, sizeof(text));
	remove.create(*this,WS_CHILD | WS_VISIBLE,text,IDC_REMOVE, 100, 80, 80, 24);
	edit.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, 0, IDC_EDIT, 100, 20, 80, 24);
	list_box.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, 0, IDC_LB, 20, 20, 70, 90);
	
	EnableWindow(remove, false);
	
	// : disable "Remove" button
	return 0;
}


void main_window::on_command(int id){
	switch(id){
		char text[256];
		HWND hwListBox;
		HWND hwEdit;
		case ID_FILE_EXIT:
			DestroyWindow(*this);
			// : close main window
			break;
		case ID_HELP_ABOUT:
			// : show dialog with text
			MessageBox(*this, "Neki tekst", "About", 0);
			break;
		case IDC_ADD:
			GetDlgItemText(*this, IDC_EDIT, text, sizeof(text));
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING,0,(LPARAM)text);
			EnableWindow(GetDlgItem(*this,IDC_REMOVE), true);
			// : get text from edit control
			// : add string to listbox control
			// : enable "Remove" button
			break;
		case IDC_REMOVE:
			if (SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0) != LB_ERR)
			{
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, 0, SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0));
			}
			if (SendDlgItemMessage(*this,IDC_LB,LB_GETCOUNT,0,0) == 0)
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

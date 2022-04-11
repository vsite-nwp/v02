#include "nwpwin.h"
#include "res.h"

// TODO: prepare classes (edit, button, list_box) for child windows
// TODO: derive from window, override class_name

class Edit : public vsite::nwp::window {
	std::string class_name() override { return "Edit"; }
};

class Button : public vsite::nwp::window {
	std::string class_name() override { return "Button"; }
};

class ListBox : public vsite::nwp::window {
	std::string class_name() override { return "ListBox"; }
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
	// TODO: create all child windows
	// TODO: disable "Remove" button
	Button btn1, btn2;
	ListBox lb;
	Edit ed;
	lb.create(*this, WS_CHILD | WS_BORDER | WS_VISIBLE, "", IDC_LB, 10, 10, 200, 300);
	ed.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 220, 10, 180, 20);
	btn1.create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 250, 50, 120, 30);
	btn2.create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "Remove", IDC_REMOVE, 250, 90, 120, 30);
	return 0;
}

void main_window::on_command(int id){
	switch(id){
		case ID_FILE_EXIT:
			// TODO: close main window
			DestroyWindow(*this);
			break;
		case ID_HELP_ABOUT:
			// TODO: show dialog with text
			MessageBox(*this, "HELP!", "HELP!", MB_OK | MB_ICONQUESTION);
			break;
		case IDC_ADD:
			// TODO: get text from edit control
			// TODO: add string to listbox control
			// TODO: enable "Remove" button
			char txt[20];
			if (GetDlgItemText(*this, IDC_EDIT, txt, sizeof(txt))) {
				SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)txt);
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
				SetDlgItemText(*this, IDC_EDIT, "");
			}
			break;
		case IDC_REMOVE:
			// TODO: get listbox selection
			// TODO: if there is a selection, delete selected string
			// TODO: disable "Remove" button if listbox is empty
			int index = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			if (index != LB_ERR) {
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, (WPARAM)index, 0);
				if (!SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0))
					EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
				break;
			}
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

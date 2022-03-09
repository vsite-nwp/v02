#include "nwpwin.h"
#include "res.h"

// TODO: prepare classes (edit, button, list_box) for child windows
class button : public vsite::nwp::window {
protected:
	std::string class_name() override { return "BUTTON"; }
};

class Edit : public vsite::nwp::window {
protected:
	std::string class_name() override { return "EDIT"; }
};

class ListBox : public vsite::nwp::window {
protected:
	std::string class_name() override { return "LISTBOX"; }
};

// TODO: derive from window, override class_name

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
	ListBox listbox;
	Edit edit;
	button b1;
	button remove;
	b1.create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 170, 170, 150, 20);
	edit.create(*this, WS_CHILD | WS_VISIBLE, "", IDC_EDIT, 170, 170, 150, 20);
	// TODO: disable "Remove" button
	remove.create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 170, 170, 150, 20);
	EnableWindow(GetDlgItem(*this, IDC_REMOVE ), false);
	return 0;
}

void main_window::on_command(int id){
	switch (id) {
	case ID_FILE_EXIT:
		// TODO: close main window
		PostQuitMessage(0);
		break;
	case ID_HELP_ABOUT:
		// TODO: show dialog with text
		MessageBox(*this, "Vjezba2", "About", MB_OK | MB_ICONINFORMATION);
		break;
	case IDC_ADD:
		char text[100];
		if (GetDlgItemText(*this, IDC_EDIT, text, sizeof(text)) != 0) {
			SendMessage(GetDlgItem(*this, IDC_LB), LB_ADDSTRING, 0, (LPARAM)text);
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			SetDlgItemText(*this, IDC_EDIT, "");
		}
		// TODO: get text from edit control
		// TODO: add string to listbox control
		// TODO: enable "Remove" button
		break;
	case IDC_REMOVE:
		// TODO: get listbox selection
		// TODO: if there is a selection, delete selected string
		// TODO: disable "Remove" button if listbox is empty
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

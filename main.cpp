#include "nwpwin.h"
#include "res.h"

// Classes (edit, button, list_box) for child windows,
// derived from window, override class_name.

class edit : public vsite::nwp::window {
	std::string class_name() override {
		return "EDIT";
	}
};

class button : public vsite::nwp::window {
	std::string class_name() override {
		return "BUTTON";
	}
};

class list_box : public vsite::nwp::window {
	std::string class_name() override {
		return "LISTBOX";
	}
};

class main_window : public vsite::nwp::window
{
	edit editBox;
	button addButton;
	button removeButton;
	list_box listBox;

protected:
	int on_create(CREATESTRUCT* pcs) override;
	void on_command(int id) override;
	void on_destroy() override;
};

int main_window::on_create(CREATESTRUCT* pcs)
{
	// Create all child windows.
	editBox.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, 0, IDC_EDIT, 120, 10, 100, 25);
	addButton.create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 120, 40, 100, 25);
	removeButton.create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 120, 70, 100, 25);
	listBox.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, 0, IDC_LB, 10, 10, 100, 100);
	// Disable "Remove" button.
	::EnableWindow(removeButton, FALSE);
	return 0;
}

void main_window::on_command(int id){
	switch(id){
		case ID_FILE_EXIT:
			// Close main window.
			on_destroy();
			break;
		case ID_HELP_ABOUT:
			// Show dialog with text.
			::MessageBox(*this, "About\nLorem ipsum dolor sit amet.", "NWP 2", MB_OK);
			break;
		case IDC_ADD:
			// Get text from edit control.
			char s[128];
			::GetDlgItemText(*this, IDC_EDIT, s, sizeof(s));
			// Add string to listbox control.
			::SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(s));
			// Clear edit control.
			::SetDlgItemText(*this, IDC_EDIT, "");
			// Enable "Remove" button.
			::EnableWindow(removeButton, TRUE);
			break;
		case IDC_REMOVE:
			// Get listbox selection.
			int selectionIndex = ::SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			// If there is a selection, delete selected string.
			if (selectionIndex != LB_ERR) {
				::SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, selectionIndex, 0);
			}
			// Disable "Remove" button if listbox is empty.
			int count = ::SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0);
			if (count == 0) {
				::EnableWindow(removeButton, FALSE);
			}
			break;
	}
}

void main_window::on_destroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	main_window w; 
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)::LoadMenu(instance, MAKEINTRESOURCE(IDM_V2)), 0, 0, 280, 200);
	vsite::nwp::set_icons(instance, w, IDI_V2);
	vsite::nwp::application app;
	return app.run();
}

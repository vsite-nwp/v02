#include "nwpwin.h"
#include "res.h"

// prepare classes (edit, button, list_box) for child windows
// derive from window, override class_name

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

class main_window : public vsite::nwp::window
{
protected:
	int on_create(CREATESTRUCT* pcs) override;
	void on_command(int id) override;
	void on_destroy() override;
};

int main_window::on_create(CREATESTRUCT* pcs)
{
	// create all child windows
	// disable "Remove" button
	char addButtonLabel[32];
	char removeButtonLabel[32];
	button add;
	button remove;
	edit input;
	list_box lBox;
	input.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, 0, IDC_EDIT, 100, 20, 80, 25);
	::LoadString(0, IDS_ADD, addButtonLabel, sizeof addButtonLabel);
	add.create(*this, WS_CHILD | WS_VISIBLE, addButtonLabel, IDC_ADD, 100, 50, 80, 25);
	::LoadString(0, IDS_REMOVE, removeButtonLabel, sizeof(removeButtonLabel));
	remove.create(*this, WS_CHILD | WS_VISIBLE, removeButtonLabel, IDC_REMOVE, 100, 80, 80, 25);
	EnableWindow(remove, false);

	lBox.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, 0, IDC_LB, 20, 20, 70, 90);
	return 0;
}

void main_window::on_command(int id){
	switch(id){
		char inputText[128];

		case ID_FILE_EXIT:
			// close main window
			DestroyWindow(*this);
			break;

		case ID_HELP_ABOUT:
			// show dialog with text
			char aboutCaption[32];
			char aboutUs[128];
			::LoadString(0, IDS_ABOUT_CAPTION, aboutCaption, sizeof aboutCaption);
			::LoadString(0, IDS_ABOUT_US, aboutUs, sizeof aboutUs);
			MessageBox(*this, aboutUs, aboutCaption, 0);
			break;

		case IDC_ADD:
			// get text from edit control
			// add string to listbox control
			// enable "Remove" button
			GetDlgItemText(*this, IDC_EDIT, inputText, sizeof(inputText));
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)inputText);
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			break;

		case IDC_REMOVE:
			// get listbox selection
			// if there is a selection, delete selected string
			// disable "Remove" button if listbox is empty
			if (SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0) != LB_ERR)
			{
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, 0, SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0));
			}
			if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0) == 0)
			{
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
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
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)::LoadMenu(instance, MAKEINTRESOURCE(IDM_V2)));
	vsite::nwp::set_icons(instance, w, IDI_V2);
	vsite::nwp::application app;
	return app.run();
}

#include "nwpwin.h"
#include "res.h"

//prepare classes (edit, button, list_box) for child windows

class edit : public vsite::nwp::window
{
protected:
	std::string class_name() override { return "EDIT"; }
};

class button : public vsite::nwp::window
{
protected:
	std::string class_name() override { return "BUTTON"; }

};

class list_box : public vsite::nwp::window
{
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
	//create all child windows
	button add;
	add.create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 190, 70, 150, 30);
	button remove;
	remove.create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 190, 120, 150, 30);
	edit Edit;
	Edit.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 190, 20, 150, 30);

	list_box listBox;
	listBox.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 20, 20, 150, 170);


	//disable "Remove" button
	EnableWindow(remove, false);

	return 0;
}

void main_window::on_command(int id) {
	switch (id) {
	case ID_FILE_EXIT:
		//close main window
		DestroyWindow(*this);
		break;
	case ID_HELP_ABOUT:
		//show dialog with text
		MessageBox(*this, "Ovo je program u kojem se u EDIT upiše tekst, a zatim se klikom na gumb ADD isti doda u List Box. Dok se klikom na gumb REMOVE briše iz List Boxa.", "About", MB_OK | MB_ICONINFORMATION);
		break;
	case IDC_ADD:
		//get text from edit control
		char text[25];
		GetDlgItemText(*this, IDC_EDIT, text, sizeof(text));

		//add string to listbox control
		SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)text);


		//enable "Remove" button
		EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
		break;

	case IDC_REMOVE:
		// get listbox selection
		int index = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);


		// TODO: if there is a selection, delete selected string
		if (index != LB_ERR) {
			SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, index, 0);
		}

		//disable "Remove" button if listbox is empty
		if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0) == 0) {
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
		}

		break;
	}
}

void main_window::on_destroy() {
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

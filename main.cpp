#include "nwpwin.h"
#include "res.h"

//  prepare classes (edit, button, list_box) for child windows
class Label : public vsite::nwp::window {
	std::string class_name() override {
		return "Label";
	}
};

class Button : public vsite::nwp::window {
	std::string class_name() override{
		return "Button";
	}
};

class Edit : public vsite::nwp::window {
	std::string class_name() override {
		return "Edit";
	}
};

class ListBox : public vsite::nwp::window {
	std::string class_name() override {
		return "ListBox";
	}
};
//  derive from window, override class_name

class main_window : public vsite::nwp::window
{
protected:
	int on_create(CREATESTRUCT* pcs) override;
	void on_command(int id) override;
	void on_destroy() override;

public:
	Button addButton;
	Button removeButton;
	Button clearButton;
	Edit edit;
	ListBox listBox;
	/*Label listBoxLabel;
	Label editLabel;*/
};

int main_window::on_create(CREATESTRUCT* pcs)
{
	// create all child windows
	//listBoxLabel.create(*this, WS_CHILD | WS_VISIBLE, "Popis", IDC_LBL, 50, 50, 50, 80);
	listBox.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 50, 100, 110, 132);
	edit.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 180, 100, 110, 22);
	addButton.create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 180, 132, 110, 40);
	removeButton.create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "Remove", IDC_REMOVE, 180, 182, 110, 40);
	clearButton.create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "Clear All", IDC_CLEAR, 310, 132, 110, 40);
	// disable "Remove" button
	return 0;
}

void main_window::on_command(int id){
	switch(id){
		int selectedIndex;

		case ID_FILE_EXIT:
			// close main window
			DestroyWindow(*this);
			break;
		case ID_HELP_ABOUT:
			// show dialog with text
			MessageBox(*this, "Klikom na gumb Add se dodaje tekst, a klikom na gumb remove se brise oznaceni tekst iz liste.", "Pomoc", MB_OK | MB_ICONINFORMATION);
			break;
		case IDC_ADD:
			// get text from edit control
			char text[27];
			GetDlgItemText(*this, IDC_EDIT, text, sizeof(text));
			// add string to listbox control
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)text);
			// enable "Remove" button
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			EnableWindow(GetDlgItem(*this, IDC_CLEAR), true);
			SetDlgItemText(*this, IDC_EDIT, "");
			break;
		case IDC_REMOVE:
			// get listbox selection
			selectedIndex = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			// if there is a selection, delete selected string
			if (selectedIndex != LB_ERR) SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, selectedIndex, 0);
			// disable "Remove" button if listbox is empty
			if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0) == 0)
			{
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
				EnableWindow(GetDlgItem(*this, IDC_CLEAR), false);
			}
			break;
		case IDC_CLEAR:
			int count = SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0);
			for (int i = count - 1; i >= 0; --i) {
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, i, 0);
			}
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
			EnableWindow(GetDlgItem(*this, IDC_CLEAR), false);
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

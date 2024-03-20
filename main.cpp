#include "nwpwin.h"
#include "res.h"
#include <random>
#include <time.h>

// DID_IT: prepare classes (edit, button, list_box) for child windows
// DID_IT: derive from window, override class_name
class Label : public vsite::nwp::window {
	std::string class_name() override { return "STATIC"; };
};

class Button : public vsite::nwp::window {
	std::string class_name() override { return "BUTTON"; };
};

class Edit : public vsite::nwp::window {
	std::string class_name() override { return "EDIT"; };
};

class ListBox : public vsite::nwp::window {
	std::string class_name() override { return "LISTBOX"; };
};

class main_window : public vsite::nwp::window
{
protected:
	int on_create(CREATESTRUCT* pcs) override;
	void on_command(int id) override;
	void on_destroy() override;

public:
	Button btn_add;
	Button btn_remove;
	Button btn_clear;
	Button btn_random_input;
	Edit redit;
	ListBox list_items;
	Label listBox_label;
	Label entry_label;
};

int main_window::on_create(CREATESTRUCT* pcs)
{
	// DID_IT: create all child windows	
	// svoj HWND(*this)
	// DID_IT: disable "Remove" button
	listBox_label.create(*this, WS_CHILD | WS_VISIBLE, "Popis stavki:", IDC_LBL, 50, 75, 110, 22);
	entry_label.create(*this, WS_CHILD | WS_VISIBLE, "Kontrole:", IDC_ELBL, 180, 75, 240, 22);
	list_items.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 50, 100, 110, 132);
	redit.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 180, 100, 110, 22);
	btn_add.create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 180, 142, 110, 35);
	btn_remove.create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "Remove", IDC_REMOVE, 180, 187, 110, 35);
	btn_clear.create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "Clear All", IDC_CLEAR, 310, 142, 110, 35);
	btn_random_input.create(*this, WS_CHILD | WS_VISIBLE, "R", IDC_RAND, 290, 100, 22, 22);

	
	return 0;
}

void main_window::on_command(int id){		
	switch(id){
		case ID_FILE_EXIT:
			// DID_IT: close main window
			DestroyWindow(*this);
			break;
		case ID_HELP_ABOUT:
			// DID_IT: show dialog with text
			MessageBox(*this, "Help is needed!!\nASAP!!", "Help me pls.", MB_OK | MB_ICONINFORMATION);
			break;
		case IDC_ADD:
			// DID_IT: get text from edit control
			char insert[25];
			GetDlgItemText(*this, IDC_EDIT, insert, sizeof(insert));
			// DID_IT: add string to listbox control
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, LPARAM(insert));
			// DID_IT: enable "Remove" button
			EnableWindow(btn_remove, true);
			EnableWindow(btn_clear, true);
			SetDlgItemText(*this, IDC_EDIT, "");
			break;
		case IDC_RAND:
			int ascii;
			char input_string[6];
			for (int i = 0; i < 5; ++i) {
				ascii = rand() % (122 - 97 + 1) + 97;
				input_string[i] = static_cast<char>(ascii);
			}
			input_string[5] = '\0';
			SetDlgItemText(*this, IDC_EDIT, input_string);
			break;
		case IDC_REMOVE: {
			// DID_IT: get listbox selection
			int index_of_selection = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			// DID_IT: if there is a selection, delete selected string
			if (index_of_selection != LB_ERR) {
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, index_of_selection, 0);
			}
			// DID_IT: disable "Remove" button if listbox is empty
			if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0) == 0) {
				EnableWindow(btn_remove, false);
			}
			break;
		}
		case IDC_CLEAR:
			SendDlgItemMessage(*this, IDC_LB, LB_RESETCONTENT, 0, 0);
			EnableWindow(btn_clear, false);
			EnableWindow(btn_remove, false);
			break;
	}
}

void main_window::on_destroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	srand(time(0));
	main_window w; 
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)::LoadMenu(instance, MAKEINTRESOURCE(IDM_V2)));
	vsite::nwp::set_icons(instance, w, IDI_V2);
	vsite::nwp::application app;
	return app.run();
}

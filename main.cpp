#include "nwpwin.h"
#include "res.h"

// TODO: prepare classes (edit, button, list_box) for child windows
// TODO: derive from window, override class_name

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
	// TODO: create all child windows
	editBox.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, 0, IDC_EDIT, 120, 10, 100, 25);
	addButton.create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 120, 40, 100, 25);
	removeButton.create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 120, 70, 100, 25);
	listBox.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, 0, IDC_LB, 10, 10, 100, 100);
	// TODO: disable "Remove" button
	::EnableWindow(removeButton, FALSE);
	return 0;
}

void main_window::on_command(int id){
	switch(id){
		case ID_FILE_EXIT:
			// TODO: close main window
			on_destroy();
			break;
		case ID_HELP_ABOUT:
			// TODO: show dialog with text
			::MessageBox(0, "About\nLorem ipsum dolor sit amet.", "NWP 2", MB_OK);
			break;
		case IDC_ADD:
			// TODO: get text from edit control
			char s[128];
			::GetDlgItemText(*this, IDC_EDIT, s, sizeof(s));
			//ili
			//::GetWindowText(editBox, s, sizeof(s));
			// TODO: add string to listbox control
			::SendMessage(listBox, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(s));
			::SendDlgItemMessage(*this, IDC_EDIT, WM_UNDO, 0, 0);
			//ili
			//::SendMessage(editBox, WM_UNDO, 0, 0);
			::SendMessage(editBox, WM_CLEAR, 0, 0);
			// TODO: enable "Remove" button
			::EnableWindow(removeButton, TRUE);
			break;
		case IDC_REMOVE:
			// TODO: get listbox selection
			int selectionIndex = ::SendMessage(listBox, LB_GETCURSEL, 0, 0);
			// TODO: if there is a selection, delete selected string
			if (selectionIndex != LB_ERR) {
				::SendMessage(listBox, LB_DELETESTRING, selectionIndex, 0);
			}
			// TODO: disable "Remove" button if listbox is empty
			int count = ::SendMessage(listBox, LB_GETCOUNT, 0, 0);
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

/*Znaèi, imamo klasu izvedenu iz bazne klase Window, napravimo na njoj
create, a messages rješavamo s overrideanim virtualnim funkcijama.

Sva kompliciranost, znaèi registracija prozora, procedura prozora,
odgovaranje na poruke... sve se krije u baznoj klasi i u njenim
virtualnim funkcijama. Svaka od poruka (on create, on command,
on destroy, on close) je virtualna funkcija u baznoj klasi.*/
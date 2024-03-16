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
protected:
	int on_create(CREATESTRUCT* pcs) override;
	void on_command(int id) override;
	void on_destroy() override;
};

int main_window::on_create(CREATESTRUCT* pcs)
{
	edit ew;
	button bw;
	list_box lbw;
	ew.create(pcs->hwndParent, WS_CHILD | WS_VISIBLE);
	bw.create(pcs->hwndParent, WS_CHILD | WS_VISIBLE);
	lbw.create(pcs->hwndParent, WS_CHILD | WS_VISIBLE);
	// TODO: create all child windows
	// TODO: disable "Remove" button
	return 0;
}

void main_window::on_command(int id){
	switch(id){
		case ID_FILE_EXIT:
			// TODO: close main window
			break;
		case ID_HELP_ABOUT:
			// TODO: show dialog with text
			break;
		case IDC_ADD:
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

/*Znaèi, imamo klasu izvedenu iz bazne klase Window, napravimo na njoj
create, a messages rješavamo s overrideanim virtualnim funkcijama.

Sva kompliciranost, znaèi registracija prozora, procedura prozora,
odgovaranje na poruke... sve se krije u baznoj klasi i u njenim
virtualnim funkcijama. Svaka od poruka (on create, on command,
on destroy, on close) je virtualna funkcija u baznoj klasi.*/
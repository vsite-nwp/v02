#include "nwpwin.h"
#include "res.h"

using namespace std;

//sve samo pisati u main.cpp

// TODO: prepare classes (edit, button, list_box) for child windows
// 

//class edit() {};
//class button:public vsite::nwp::window{};
//class list_box() {};


class button : public vsite::nwp::window {

	string class_name(){
		return "button";
	}
};

class edit : public vsite::nwp::window {

	string class_name(){
		return "edit";
	}
};

class list_box : public vsite::nwp::window {

	string class_name(){
		return "list_box";
	}
};

// izvedene klase
// 
// 
// class button : public vsite::nwp::window{
// protected:
//	std::string class_name() override {return "BUTTON}
// 
// 
// TODO: derive from window, override class_name

class main_window : public vsite::nwp::window  //glavna klasa vec ozvedena
{
protected:
	int on_create(CREATESTRUCT* pcs) override;
	void on_command(int id) override;
	void on_destroy() override;
};

int main_window::on_create(CREATESTRUCT* pcs)
{
	// TODO: create all child windows
	// 
	// button b1;
	// b1.create(*this, WS_CHILD|WS_VISIBLE, "Add", IDC_ADD
	// 
	// list_box lb;
	// lb.create(*this, WS_CHILD|WS_VISIBLE|WS_BORDER
	// 
	// TODO: disable "Remove" button

	button add; add.create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 150, 40, 100, 20 );
	button remove; remove.create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 150, 70, 100, 20 );
	edit edit; edit.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "" ,IDC_EDIT, 150 ,10 ,100,20 );
	list_box list_box; list_box.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 20, 50, 150, 150);


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

			//int index = SendDialogItemMEssage(*this, IDC_LB, LB_GETCURSEL,o0,0);
			//if(index)
			//SendDialogItemMesage

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
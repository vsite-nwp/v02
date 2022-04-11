#include "nwpwin.h"
#include "res.h"

using namespace std;

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
		return "listbox";
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
	button add; add.create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 150, 40, 100, 20 );
	button remove; remove.create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "Remove", IDC_REMOVE, 150, 70, 100, 20 );
	edit edit; edit.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "" ,IDC_EDIT, 150 ,10 ,100,20 );
	list_box list_box; list_box.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 20, 10, 100, 90);


	return 0;
}

void main_window::on_command(int id){
	switch(id){
		case ID_FILE_EXIT:
			on_destroy();
			break;
		case ID_HELP_ABOUT:

			MessageBox(*this, "NWP V2", "About", MB_OK);
			break;
		case IDC_ADD:
			char addItem[256];

			if (GetDlgItemTextA(*this, IDC_EDIT, addItem, sizeof(addItem))) {

				SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(addItem));

				SetDlgItemText(*this, IDC_EDIT, "");

				EnableWindow(GetDlgItem(*this,IDC_REMOVE), true);
			}

			break;
		case IDC_REMOVE:

			int index = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			if (index!=LB_ERR) {
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, static_cast<WPARAM>(index), 0);

				if (!SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0)) {
					EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
				}
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
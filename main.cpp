#include "nwpwin.h"
#include "res.h"


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

class main_window : public vsite::nwp::window
{
protected:
	int on_create(CREATESTRUCT* pcs) override;
	void on_command(int id) override;
	void on_destroy() override;
};

int main_window::on_create(CREATESTRUCT* pcs)
{
	button b1;
	b1.create(*this, WS_BORDER | WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 200, 100, 150, 30);
	button b2;
	b2.create(*this, WS_BORDER | WS_CHILD | WS_VISIBLE | WS_DISABLED, "Remove", IDC_REMOVE, 200, 140, 150, 30);
	ListBox lb;
	lb.create(*this, WS_BORDER | WS_CHILD | WS_VISIBLE, "", IDC_LB, 30, 50, 130, 150);
	Edit ed;
	ed.create(*this, WS_BORDER | WS_CHILD | WS_VISIBLE, "", IDC_EDIT, 200, 50, 150, 30);

	return 0;
}

void main_window::on_command(int id){
	switch(id){
		case ID_FILE_EXIT:
			on_destroy();
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "add-remove TODOs in your list", "Help", MB_ICONINFORMATION | MB_OK);
			break;
		case IDC_ADD:
			char text[15];
			int succes;
			succes = GetDlgItemText(*this, IDC_EDIT, text, sizeof(text));
			if (succes) {
				SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)text);
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
				SetDlgItemText(*this, IDC_EDIT, "");
			}
			break;
		case IDC_REMOVE:
			int index = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, index, 0);
			int count = (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0));
			if (!count)
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);

			break;
	}
}

void main_window::on_destroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	main_window w; 
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)::LoadMenu(instance, MAKEINTRESOURCE(IDM_V2)),1000,500);
	vsite::nwp::set_icons(instance, w, IDI_V2);
	vsite::nwp::application app;
	return app.run();
}

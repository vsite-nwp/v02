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
	ListBox listbox;
	Edit edit;
	button b1;
	button remove;
	listbox.create(*this, WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL, "", IDC_LB, 10, 10, 150, 120);
	b1.create(*this, WS_BORDER | WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 170, 50, 150, 20);
	edit.create(*this, WS_BORDER | WS_CHILD | WS_VISIBLE, "", IDC_EDIT, 170, 10, 150, 20);
	remove.create(*this, WS_BORDER | WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 170, 80, 150, 20);
	EnableWindow(remove, false);
	return 0;
}

void main_window::on_command(int id){
	switch (id) {
	case ID_FILE_EXIT:
		on_destroy();
		break;
	case ID_HELP_ABOUT:
		MessageBox(*this, "NWP - Vjezba 2", "About", MB_OK | MB_ICONINFORMATION);
		break;
	case IDC_ADD:
		char text[100];
		if (GetDlgItemText(*this, IDC_EDIT, text, sizeof(text)) != 0) {
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)text);
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			SetDlgItemText(*this, IDC_EDIT, "");
		}
		break;
	case IDC_REMOVE:
		int index = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
		if (index != LB_ERR) {
			SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, index, 0);
		}
		else {
			break;
		}
		if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0) == 0) {
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

#include "nwpwin.h"
#include "res.h"

class Button : public vsite::nwp::window {
	std::string class_name() override { return "Button"; };
};


class Edit : public vsite::nwp::window {
	std::string class_name() override { return "Edit"; };
};

class ListBox : public vsite::nwp::window {
	std::string class_name() override { return "ListBox"; };
};


class main_window : public vsite::nwp::window
{
protected:
	int on_create(CREATESTRUCT* pcs) override;
	void on_command(int id) override;
	void on_destroy() override;

public:
	ListBox lb;
	Edit e;
	Button btn1;
	Button btn2;
};

int main_window::on_create(CREATESTRUCT* pcs)
{

	lb.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, 0, IDC_LB, 50, 15, 110, 115);
	e.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, 0, IDC_EDIT, 190, 15, 100, 25);
	btn1.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Add", IDC_ADD, 190, 60, 100, 25);
	btn2.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Remove", IDC_REMOVE, 190, 95, 100, 25);

	EnableWindow(btn2, FALSE);

	return 0;
}

void main_window::on_command(int id) {
	switch (id) {
	case ID_FILE_EXIT:
		if (MessageBox(*this, TEXT("Are you sure you want Exit"), TEXT("NWP"), MB_YESNO) == IDYES) {
			PostQuitMessage(0);
		}
		break;
	case ID_HELP_ABOUT:
		MessageBox(*this, TEXT("Help"), TEXT("NWP"), MB_OKCANCEL);
		break;
	case IDC_ADD:
		char buffer[15];
		GetDlgItemText(*this, IDC_EDIT, buffer, 15);
		SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)buffer);
		SendDlgItemMessage(*this, IDC_EDIT, WM_SETTEXT, 0, (LPARAM)"");
		EnableWindow(btn2, TRUE);
		break;
	case IDC_REMOVE:
		int Lbmessage = SendMessage(lb, LB_GETCURSEL, 0, 0);

		if (Lbmessage != LB_ERR) {
			SendMessage(lb, LB_DELETESTRING, Lbmessage, 0);
		}

		if (SendMessage(lb, LB_GETCOUNT, 0, 0) == 0) {
			EnableWindow(btn2, FALSE);
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

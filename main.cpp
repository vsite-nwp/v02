#include "nwpwin.h"
#include "res.h"
class Button : public vsite::nwp::window {
	std::string class_name() override { return "Button"; }
};
class ListBox : public vsite::nwp::window {
	std::string class_name() override { return "ListBox"; }
};

class Edit : public vsite::nwp::window {
	std::string class_name() override { return "Edit"; }
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
	Button rem; rem.create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "Remove", IDC_REMOVE, 200, 150, 100, 30);
	Button add; add.create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 200, 100, 100, 30);
	Edit edit; edit.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 200, 50, 100, 30);
	ListBox lbx; lbx.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 50, 50, 100, 150);

	return 0;
	
}

void main_window::on_command(int id) {
	switch (id) {
	case ID_FILE_EXIT:
		
		on_destroy();
		break;
	case ID_HELP_ABOUT:
		
		MessageBox(*this, "Very important: \n Using same thing...", "Help", MB_OK | MB_ICONINFORMATION);
		break;
	case IDC_ADD:
		char getString[40];
		GetDlgItemText(*this, IDC_EDIT, getString, sizeof(getString));

		SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)getString);

		EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);

		break;
	case IDC_REMOVE:
		
		LRESULT iIndex = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
		if (iIndex != LB_ERR)
			SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, iIndex, NULL);

		int iCount = SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0);
		if (iCount == 0)
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
		break;
	}
}

void main_window::on_destroy() {
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)::LoadMenu(instance, MAKEINTRESOURCE(IDM_V2)), CW_USEDEFAULT, CW_USEDEFAULT, 400, 320);
	vsite::nwp::set_icons(instance, w, IDI_V2);
	vsite::nwp::application app;
	return app.run();
}

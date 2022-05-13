#include "nwpwin.h"
#include "res.h"
#include "windows.h"

// : prepare classes (edit, button, list_box) for child windows
// : derive from window, override class_name
class button :public vsite::nwp::window {
protected:
	std::string class_name() override { return "button"; }
};
class list_box :public vsite::nwp::window {
protected:
	std::string class_name() override { return "listbox"; }
};
class edit : public vsite::nwp::window {
protected:
	std::string class_name() override { return "edit"; }
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
	// : create all child windows
	button b1, b2;
	edit e1;
	list_box lb;
	b1.create(*this, WS_VISIBLE | WS_CHILD | WS_BORDER,"Add", IDC_ADD, 250, 120, 100, 50);
	b2.create(*this, WS_VISIBLE | WS_CHILD | WS_BORDER, "Remove", IDC_REMOVE, 250, 180, 100, 50);
	e1.create(*this, WS_VISIBLE | WS_CHILD | WS_BORDER, "", IDC_EDIT, 250, 80, 100, 30);
	lb.create(*this, WS_VISIBLE | WS_CHILD | WS_BORDER, "", IDC_LB, 80, 80, 160, 170);
	EnableWindow(b2, false);
	// : disable "Remove" button
	return 0;
}

void main_window::on_command(int id){
	switch(id){
		case ID_FILE_EXIT:
			PostQuitMessage(0);
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "HELP WITH SOLUTION", "HELP", MB_OK);
			// : show dialog with text
			break;
		case IDC_ADD:
			char s[128];
			if (GetDlgItemText(*this, IDC_EDIT, s, sizeof(s)) != 0) {
				SendMessage(GetDlgItem(*this, IDC_LB), LB_ADDSTRING, 0, (LPARAM)s);
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
				SetDlgItemText(*this, IDC_EDIT, "");
			}
			// : get text from edit control
			// : add string to listbox control
			// : enable "Remove" button
			break;
		case IDC_REMOVE:
			int ind = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			if (ind == LB_ERR) {
				break;
			}
			else {
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, ind, 0);
			}
			if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0) == 0) {
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
			}
			// : get listbox selection
			// : if there is a selection, delete selected string
			// : disable "Remove" button if listbox is empty
			break;
	}
}

void main_window::on_destroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	main_window w; 
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)::LoadMenu(instance, MAKEINTRESOURCE(IDM_V2)), CW_USEDEFAULT,CW_USEDEFAULT,400,320);
	vsite::nwp::set_icons(instance, w, IDI_V2);
	vsite::nwp::application app;
	return app.run();
}

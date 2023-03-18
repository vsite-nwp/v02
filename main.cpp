#include "nwpwin.h"
#include "res.h"

// prepare classes (edit, button, list_box) for child windows
// derive from window, override class_name
class list_box : public vsite::nwp::window {
	std::string class_name() override { return "listBox"; };
};
class edit : public vsite::nwp::window {
	std::string class_name() override { return "edit"; };
};
class button : public vsite::nwp::window {
	std::string class_name() override { return "button"; };
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
	// create all child windows
	list_box lb;
	lb.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, 0, IDC_LB, 15, 5, 100, 100);
	edit e;
	e.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER , 0, IDC_EDIT, 130, 5, 100, 25);
	button a;
	a.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Add", IDC_ADD, 130, 40, 100, 25);
	button r;
	r.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Remove", IDC_REMOVE, 130, 75, 100, 25);
	// disable "Remove" button
	EnableWindow(r, FALSE);
	return 0;
}

void main_window::on_command(int id){
	switch(id){
		case ID_FILE_EXIT:
			// close main window
			PostQuitMessage(0);
			break;

		case ID_HELP_ABOUT:
			// show dialog with text
			MessageBox(NULL, TEXT("Thank you for using the application."), TEXT("Thank You"), MB_OK | MB_ICONINFORMATION);
			break;

		case IDC_ADD: {
			// get text from edit control
			char text[20];
			GetDlgItemText(*this, IDC_EDIT, text, 20);
			// add string to listbox control
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)text);
			// enable "Remove" button
			HWND rb = GetDlgItem(*this, IDC_REMOVE);
			EnableWindow(rb, TRUE);
			break;
		}

		case IDC_REMOVE: {
			// get listbox selection
			HWND lb = GetDlgItem(*this, IDC_LB);
			int i = SendMessage(lb, LB_GETCURSEL, 0, 0);
			// if there is a selection, delete selected string
			if (i != LB_ERR) {
				SendMessage(lb, LB_DELETESTRING, i, 0);
			}
			// disable "Remove" button if listbox is empty
			int n = SendMessage(lb, LB_GETCOUNT, 0, 0);
			if (n == 0) {
				HWND rb = GetDlgItem(*this, IDC_REMOVE);
				EnableWindow(rb, FALSE);
			}
			break;
		}
	}
}
		

void main_window::on_destroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	main_window w; 
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)::LoadMenu(instance, MAKEINTRESOURCE(IDM_V2)), 800, 300, 260, 180);
	vsite::nwp::set_icons(instance, w, IDI_V2);
	vsite::nwp::application app;
	return app.run();
}

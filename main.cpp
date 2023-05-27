#include "nwpwin.h"
#include "res.h"

class main_window : public vsite::nwp::window
{
protected:
	int on_create(CREATESTRUCT* pcs) override;
	void on_command(int id) override;
	void on_destroy() override;

private:
	vsite::nwp::list_box list_box;
	vsite::nwp::edit edit;
	vsite::nwp::button add_button;
	vsite::nwp::button remove_button;
};

int main_window::on_create(CREATESTRUCT* pcs)
{
	list_box.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, 0, IDC_LB, 10, 10, 120, 240);

	edit.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, 0, IDC_EDIT, 140, 10, 120, 30);

	add_button.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Add", IDC_ADD, 140, 50, 120, 30);

	remove_button.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Remove", IDC_REMOVE, 140, 90, 120, 30);

	// disable "Remove" button
	EnableWindow(remove_button, FALSE);

	return 0;
}

void main_window::on_command(int id){
	switch(id){
		case ID_FILE_EXIT:
			PostQuitMessage(0);
			break;

		case ID_HELP_ABOUT:
			MessageBox(*this, TEXT("This enterprise solution for all your list box management needs is brought to you by GDB INC."), TEXT("About"), MB_OK | MB_ICONINFORMATION);
			break;

		case IDC_ADD:
			// get text from edit control
			char text[32];
			GetDlgItemText(*this, IDC_EDIT, text, 32);

			// add string to listbox control
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)text);

			// enable "Remove" button
			EnableWindow(remove_button, TRUE);

			break;

		case IDC_REMOVE:
			// get listbox selection
			int lb_item_idx = SendMessage(list_box, LB_GETCURSEL, 0, 0);

			// if there is a selection, delete selected string
			if (lb_item_idx != LB_ERR) 
				SendMessage(list_box, LB_DELETESTRING, lb_item_idx, 0);

			// disable "Remove" button if listbox is empty
			int lb_item_count = SendMessage(list_box, LB_GETCOUNT, 0, 0);
			if (!lb_item_count)
				EnableWindow(remove_button, FALSE);

			break;
	}
}

void main_window::on_destroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	main_window w; 
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)::LoadMenu(instance, MAKEINTRESOURCE(IDM_V2)), 817, 387, 285, 305);
	vsite::nwp::set_icons(instance, w, IDI_V2);
	vsite::nwp::application app;
	return app.run();
}

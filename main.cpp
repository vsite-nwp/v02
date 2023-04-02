#include "nwpwin.h"
#include "res.h"

class main_window : public vsite::nwp::window
{
protected:
	vsite::nwp::buttonWindow addButton;
	vsite::nwp::buttonWindow removeButton;
	
	int on_create(CREATESTRUCT* pcs) override;
	void on_command(int id, int not) override;
	void on_destroy() override;
};

int main_window::on_create(CREATESTRUCT* pcs)
{	
	// ListBox
	vsite::nwp::listboxWindow lbWindow;
	lbWindow.create(*this,
		WS_VISIBLE | WS_BORDER | WS_CHILDWINDOW | WS_VSCROLL,	// style
		"", IDC_LB, 25, 25, 150, 200);							// props

	// Edit field
	vsite::nwp::editWindow editWindow;
	editWindow.create(*this,
		WS_VISIBLE | WS_BORDER | WS_CHILDWINDOW,	// style
		"", IDC_EDIT, 200, 25, 150, 21);			// props

	// Add button
	addButton.create(*this,
		WS_VISIBLE | WS_BORDER | WS_CHILDWINDOW | WS_DISABLED,	// style
		"Add", IDC_ADD, 200, 60, 150, 21);						// props

	// Add button
	removeButton.create(*this,
		WS_VISIBLE | WS_CHILDWINDOW | WS_DISABLED,	// style
		"Remove", IDC_REMOVE, 200, 95, 150, 21);	// props

	return 0;
}

void main_window::on_command(int id, int not){
	const int maxMsgSize = 50;
	char msg[maxMsgSize];

	switch(id){
		case IDC_EDIT:
			if (not == EN_CHANGE) {
				GetDlgItemText(*this, IDC_EDIT, msg, maxMsgSize);
				if (msg[0] != 0) {
					EnableWindow(addButton, true);					
				}
				else {
					EnableWindow(addButton, false);
				}
			}
			break;

		case ID_FILE_EXIT:
			on_destroy();
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "This is an example of an about area!", "About", MB_OK);
			break;
		case IDC_ADD:
			GetDlgItemText(*this, IDC_EDIT, msg, maxMsgSize);
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, LPARAM(msg));
			SetDlgItemText(*this, IDC_EDIT, "");
			EnableWindow(addButton, false);
			EnableWindow(removeButton, true);
			break;
		case IDC_REMOVE:
			int listItem = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			if (listItem != LB_ERR) {
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, listItem, 0);
			}

			int itemCount = SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0);
			if (itemCount == 0) 
				EnableWindow(removeButton, false);
			break;
	}
}

void main_window::on_destroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	main_window w; 
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)::LoadMenu(instance, MAKEINTRESOURCE(IDM_V2)), CW_USEDEFAULT, CW_USEDEFAULT, 400, 300);
	vsite::nwp::set_icons(instance, w, IDI_V2);
	vsite::nwp::application app;
	return app.run();
}

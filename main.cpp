#include "nwpwin.h"
#include "res.h"

//: prepare classes (edit, button, list_box) for child windows
//: derive from window, override class_name

class Edit : public vsite::nwp::window {
	std::string class_name() override { return "Edit"; }
};

class Button : public vsite::nwp::window {
	std::string class_name() override { return "Button"; }
};

class ListBox : public vsite::nwp::window {
	std::string class_name() override { return "ListBox"; }
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
	//: create all child windows
	//: disable "Remove" button
	Edit edit;
	Button buttonAdd, buttonRemove;
	ListBox listBox;
	char s[128];

	listBox.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 20, 20, 150, 200);
	edit.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 180, 20, 150, 50);
	
	LoadString(0, IDS_BUTTON_ADD, s, sizeof s);
	buttonAdd.create(*this, WS_CHILD | WS_VISIBLE, s, IDC_ADD, 180, 80, 150, 50);

	LoadString(0, IDS_BUTTON_REMOVE, s, sizeof s);
	buttonRemove.create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, s, IDC_REMOVE, 180, 140, 150, 50);
	return 0;
}

void main_window::on_command(int id){
	switch(id){
		case ID_FILE_EXIT:
			//: close main window
			on_destroy();
			break;
		case ID_HELP_ABOUT:
			//: show dialog with text
			MessageBox(*this, "NWP Labos 2.", "NWP 2", MB_OK);
			break;
		case IDC_ADD:
			//: get text from edit control
			//: add string to listbox control
			//: enable "Remove" button
			char s[128];
			GetDlgItemText(*this, IDC_EDIT, s, sizeof(s));

			if (s[0] != 0)
				SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)s);
			SetDlgItemText(*this, IDC_EDIT, "");

			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			break;
		case IDC_REMOVE:
			//: get listbox selection
			//: if there is a selection, delete selected string
			//: disable "Remove" button if listbox is empty
			LRESULT iIndex = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			if (iIndex != LB_ERR)
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, iIndex, NULL);

			int iCount = SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0);
			if (iCount == 0)
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
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)::LoadMenu(instance, MAKEINTRESOURCE(IDM_V2)), CW_USEDEFAULT, CW_USEDEFAULT, 400, 320);
	vsite::nwp::set_icons(instance, w, IDI_V2);
	vsite::nwp::application app;
	return app.run();
}

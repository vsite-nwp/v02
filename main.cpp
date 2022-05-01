#include "nwpwin.h"
#include "res.h"

// prepare classes (edit, button, list_box) for child windows
// derive from window, override class_name
class Edit : public vsite::nwp::window
{
protected:
	std::string class_name() override { return "Edit"; }
};

class Button : public vsite::nwp::window
{
protected:
	std::string class_name() override { return "Button"; }
};

class ListBox : public vsite::nwp::window
{
protected:
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
	// create all child windows
	// disable "Remove" button
	ListBox listBox;
	Edit edit;
	Button addButton, removeButton;

	listBox.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 25, 25, 100, 120);
	edit.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 135, 25, 100, 25);
	addButton.create(*this, WS_CHILD | WS_VISIBLE, "ADD", IDC_ADD, 135, 55, 100, 25);
	removeButton.create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "REMOVE", IDC_REMOVE, 135, 85, 100, 25);

	return 0;
}

void main_window::on_command(int id)
{
	switch (id)
	{
		case ID_FILE_EXIT:
			// close main window
			::DestroyWindow(*this);
			break;
		case ID_HELP_ABOUT:
			// show dialog with text
			MessageBox(*this, "Helping text", "NWP 2", MB_OK | MB_ICONINFORMATION);
			break;
		case IDC_ADD:
			// get text from edit control
			// add string to listbox control
			// enable "Remove" button
			char text[100];
			if (GetDlgItemText(*this, IDC_EDIT, text, sizeof(text)))
			{
				SendMessage(GetDlgItem(*this, IDC_LB), LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(text));
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
				SetDlgItemText(*this, IDC_EDIT, "");
			}
			break;
		case IDC_REMOVE:
			// get listbox selection
			// if there is a selection, delete selected string
			// disable "Remove" button if listbox is empty
			int itemIndex = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			if (itemIndex == LB_ERR)
				break;
			else
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, itemIndex, 0);
			if (SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0) == 0)
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
			break;
	}
}

void main_window::on_destroy()
{
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

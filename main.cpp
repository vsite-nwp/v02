#include "nwpwin.h"
#include "res.h"


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

private:
	edit et;
	list_box lb;
	button btn1;
	button btn2;
};

int main_window::on_create(CREATESTRUCT* pcs)
{
	
	lb.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, 0, IDC_LB, 30, 20, 100, 100);
	et.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, 0, IDC_EDIT, 150, 20, 100, 25);
	btn1.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Add", IDC_ADD, 150, 60, 100, 25);
	btn2.create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Remove", IDC_REMOVE, 150, 100, 100, 25);
	
	EnableWindow(btn2, FALSE);
	return 0;
}

void main_window::on_command(int id){
	switch(id){
		case ID_FILE_EXIT:
			PostQuitMessage(0);
			break;
		case ID_HELP_ABOUT:
			
			MessageBox(*this, TEXT("A simple grocery list."), TEXT("About application."), MB_OK | MB_ICONINFORMATION);
			break;
		case IDC_ADD:
			
			char text[36];
			GetDlgItemText(*this, IDC_EDIT, text, 36);
			
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)text);
			
			EnableWindow(btn2, TRUE);
			break;
		case IDC_REMOVE:
			
			int i = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			
			if (i != LB_ERR) {
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, 0, 0);
			}
			
			int n = SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0);
			if (n == 0) {
				EnableWindow(btn2, FALSE);
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
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)::LoadMenu(instance, MAKEINTRESOURCE(IDM_V2)), CW_USEDEFAULT, CW_USEDEFAULT, 300, 200);
	vsite::nwp::set_icons(instance, w, IDI_V2);
	vsite::nwp::application app;
	return app.run();
}

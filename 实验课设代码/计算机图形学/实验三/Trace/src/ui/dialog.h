#include "Fl.H"
#include "Fl_Window.H"
#include "Fl_Int_Input.H"
#include "Fl_Text_Display.H"
#include <stdlib.h>

class Dialog2 : public Fl_Group {
	bool pressed;

  static void Button_CB(Fl_Widget *w, void *data) {
       ((Dialog2*)w->parent())->pressed = true;
    }

public:
	Dialog2(int x, int y, int w, int h, const char *l=0) : Fl_Group(x,y,w,h,l) {

	}   

	int getValue() {
	    pressed = false;
		Fl_Window win(200, 100);
		win.label("Enter JPEG quality setting");
		
		Fl_Text_Display label(100,20,0,0,"Enter JPEG quality setting");

		Fl_Int_Input input(85, 30, 30, 20);
		input.value("95");
		
		Fl_Button button(75, 60, 50, 20, "Ok");
		button.callback(Button_CB, (void*)this);
		button.parent(this);

		win.show();
		label.show();
		input.show();
		button.show();
		while (!pressed)
			Fl::wait();
		end();
		
		return atoi(input.value());
	}
};

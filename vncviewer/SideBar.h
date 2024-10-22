#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>

class SideBar : public Fl_Window {
public:
    SideBar(int parent_window_x, int parent_window_y, int parent_window_w, int parent_window_h);
    void update_position(int x, int y, int w, int h);
protected:
    void draw() override;
private:
    Fl_Button* button1;
    Fl_Button* button2;
    static void Start(Fl_Widget* widget, void* data);
    static void SwitchOff(Fl_Widget* widget, void* data);

};

#endif // SIDEBAR_H

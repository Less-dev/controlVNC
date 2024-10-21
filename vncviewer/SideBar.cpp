#include "SideBar.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>

SideBar::SideBar(int parent_window_x, int parent_window_y, int parent_window_w, int parent_window_h)
    : Fl_Window(parent_window_x + parent_window_w - 60, parent_window_y - 10, 60, parent_window_h - 20, nullptr) {

    this->border(0);
    this->box(FL_NO_BOX);

    // Botones
    button1 = new Fl_Button(10, 20, 40, 40, "@+");
    button1->tooltip("Botón 1");
    button1->box(FL_UP_BOX);

    button2 = new Fl_Button(10, 80, 40, 40, "@fileopen");
    button2->tooltip("Botón 2");
    button2->box(FL_UP_BOX);

    this->end();
}

void SideBar::update_position(int x, int y, int w, int h) {
    this->position(x, y + 20);
    this->size(w, h - 40);    
}


void SideBar::draw() {
    fl_color(fl_rgb_color(138, 3, 3)); // background
    fl_rectf(0, 0, w(), h());

    Fl_Window::draw();
}
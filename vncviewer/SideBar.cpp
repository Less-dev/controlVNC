/*
 * Copyright (C) 2024 Daniel Gómez(Less)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "SideBar.h"
#include <iostream>
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
    button1->tooltip("Iniciar dispositivo");
    button1->box(FL_UP_BOX);
    button1->callback(Start);

    button2 = new Fl_Button(10, 80, 40, 40, "@fileopen");
    button2->tooltip("Detener dispositivo");
    button2->box(FL_UP_BOX);
    button2->callback(SwitchOff);

    this->end();
}


// Actions 

void SideBar::Start(Fl_Widget* widget, void* data) {
    std::cout << "Iniciando.." << std::endl;
}

void SideBar::SwitchOff(Fl_Widget* widget, void* data) {
    std::cout << "APAGANDO..." << std::endl;
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
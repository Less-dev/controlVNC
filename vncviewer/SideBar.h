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

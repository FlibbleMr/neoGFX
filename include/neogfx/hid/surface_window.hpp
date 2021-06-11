// surface_window.hpp
/*
  neogfx C++ App/Game Engine
  Copyright (c) 2015, 2020 Leigh Johnston.  All Rights Reserved.
  
  This program is free software: you can redistribute it and / or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <neogfx/neogfx.hpp>
#include <neogfx/core/object.hpp>
#include <neogfx/gui/window/i_native_window.hpp>
#include <neogfx/hid/i_surface_window.hpp>

namespace neogfx
{
    class i_native_window;

    class surface_window : public object<i_surface_window>
    {
    public:
        define_declared_event(DpiChanged, dpi_changed)
        define_declared_event(Rendering, rendering)
        define_declared_event(RenderingFinished, rendering_finished)
        define_declared_event(Closing, closing)
        define_declared_event(Closed, closed)
    public:
        surface_window(i_window& aWindow, std::function<void(i_surface_window&, i_ref_ptr<i_native_window>&)> aNativeWindowCreator);
        ~surface_window();
    public:
        dimension horizontal_dpi() const override;
        dimension vertical_dpi() const override;
        dimension ppi() const override;
        bool metrics_available() const override;
        size extents() const override;
        dimension em_size() const override;
    public:
        i_rendering_engine& rendering_engine() const override;
    public:
        bool is_strong() const override;
        bool is_weak() const override;
        bool can_close() const override;
        bool is_closed() const override;
        void close() override;
        bool has_parent_surface() const override;
        const i_surface& parent_surface() const override;
        i_surface& parent_surface() override;
        bool is_owner_of(const i_surface& aChildSurface) const override;
    public:
        bool is_window() const override;
        const i_surface_window& as_surface_window() const override;
        i_surface_window& as_surface_window() override;
    public:
        neogfx::surface_type surface_type() const override;
        neogfx::logical_coordinate_system logical_coordinate_system() const override;
        void set_logical_coordinate_system(neogfx::logical_coordinate_system aSystem) override;
        neogfx::logical_coordinates logical_coordinates() const override;
        void set_logical_coordinates(const neogfx::logical_coordinates& aCoordinates) override;
        void layout_surface() override;
        void invalidate_surface(const rect& aInvalidatedRect, bool aInternal = true) override;
        bool has_invalidated_area() const override;
        const rect& invalidated_area() const override;
        rect validate() override;
        double rendering_priority() const override;
        void render_surface() override;
        void pause_rendering() override;
        void resume_rendering() override;
        bool has_native_surface() const override;
        const i_native_surface& native_surface() const override;
        i_native_surface& native_surface() override;
        bool has_native_window() const override;
        const i_native_window& native_window() const override;
        i_native_window& native_window() override;
    public:
        void handle_dpi_changed() override;
    public:
        point surface_position() const override;
        void move_surface(const point& aPosition) override;
        size surface_extents() const override;
        void resize_surface(const size& aExtents) override;
        double surface_opacity() const override;
        void set_surface_opacity(double aOpacity) override;
        double surface_transparency() const override;
        void set_surface_transparency(double aTransparency) override;
    public:
        bool has_clicked_widget() const override;
        i_widget& clicked_widget() const override;
        bool has_capturing_widget() const override;
        i_widget& capturing_widget() const override;
        void set_capture(i_widget& aWidget) override;
        void release_capture(i_widget& aWidget) override;
        void non_client_set_capture(i_widget& aWidget) override;
        void non_client_release_capture(i_widget& aWidget) override;
    private:
        mouse_event_location current_mouse_event_location() const override;
        bool is_closing() const override;
        bool native_window_can_close() const override;
        void native_window_closing() override;
        void native_window_closed() override;
        void native_window_focus_gained() override;
        void native_window_focus_lost() override;
        void native_window_resized() override;
        void native_window_moved() override;
        double native_window_rendering_priority() const override;
        bool native_window_ready_to_render() const override;
        void native_window_render(const rect& aInvalidatedRect) const override;
        void native_window_dismiss_children() override;
        void native_window_mouse_wheel_scrolled(mouse_wheel aWheel, const point& aPosition, delta aDelta, key_modifiers_e aKeyModifiers) override;
        void native_window_mouse_button_pressed(mouse_button aButton, const point& aPosition, key_modifiers_e aKeyModifiers) override;
        void native_window_mouse_button_double_clicked(mouse_button aButton, const point& aPosition, key_modifiers_e aKeyModifiers) override;
        void native_window_mouse_button_released(mouse_button aButton, const point& aPosition) override;
        void native_window_mouse_moved(const point& aPosition, key_modifiers_e aKeyModifiers) override;
        void native_window_non_client_mouse_wheel_scrolled(mouse_wheel aWheel, const point& aPosition, delta aDelta, key_modifiers_e aKeyModifiers) override;
        void native_window_non_client_mouse_button_pressed(mouse_button aButton, const point& aPosition, key_modifiers_e aKeyModifiers) override;
        void native_window_non_client_mouse_button_double_clicked(mouse_button aButton, const point& aPosition, key_modifiers_e aKeyModifiers) override;
        void native_window_non_client_mouse_button_released(mouse_button aButton, const point& aPosition) override;
        void native_window_non_client_mouse_moved(const point& aPosition, key_modifiers_e aKeyModifiers) override;
        void native_window_mouse_entered(const point& aPosition) override;
        void native_window_mouse_left() override;
        widget_part native_window_hit_test(const point& aPosition) const override;
        rect native_window_widget_part_rect(widget_part_e aWidgetPart) const override;
        void native_window_key_pressed(scan_code_e aScanCode, key_code_e aKeyCode, key_modifiers_e aKeyModifiers) override;
        void native_window_key_released(scan_code_e aScanCode, key_code_e aKeyCode, key_modifiers_e aKeyModifiers) override;
        void native_window_text_input(i_string const& aText) override;
        void native_window_sys_text_input(i_string const& aText) override;
        neogfx::mouse_cursor native_window_mouse_cursor() const override;
        void native_window_title_text_changed(i_string const& aTitleText) override;
    public:
        window_style style() const override;
        void set_style(window_style aStyle) override;
    public:
        const i_window& as_window() const override;
        i_window& as_window() override;
        const i_widget& as_widget() const override;
        i_widget& as_widget()  override;
    public:
        const i_window& window_at_position(const point& aPosition, bool aForMouseEvent = false) const;
        i_window& window_at_position(const point& aPosition, bool aForMouseEvent = false);
        const i_widget& widget_for_mouse_event(const point& aPosition, bool aForHitTest = false) const;
        i_widget& widget_for_mouse_event(const point& aPosition, bool aForHitTest = false);
    private:
        std::optional<destroyed_flag> iNativeSurfaceDestroyed;
        i_window& iWindow;
        i_rendering_engine& iRenderingEngine;
        ref_ptr<i_native_window> iNativeWindow;
        bool iNativeWindowClosing;
        bool iClosing;
        bool iClosed;
        std::optional<char32_t> iSurrogatePairPart;
        i_widget* iCapturingWidget;
        i_widget* iClickedWidget;
    };
}
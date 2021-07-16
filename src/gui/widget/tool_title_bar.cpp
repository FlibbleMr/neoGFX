// tool_title_bar.cpp
/*
  neogfx C++ App/Game Engine
  Copyright (c) 2020 Leigh Johnston.  All Rights Reserved.
  
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

#include <neogfx/neogfx.hpp>
#include <neogfx/app/i_app.hpp>
#include <neogfx/hid/i_surface_manager.hpp>
#include <neogfx/gui/widget/tool_title_bar.hpp>

namespace neogfx
{
    tool_title_bar::tool_title_bar(i_standard_layout_container& aContainer, std::string const& aTitle) :
        widget{ aContainer.title_bar_layout() },
        iContainer{ aContainer },
        iUpdater{service<i_async_task>(), [this](neolib::callback_timer& aTimer)
        {
            aTimer.again();
            update_state();
        }, std::chrono::milliseconds{ 100 } },
        iLayout{ *this },
        iTitle{ iLayout, aTitle, text_widget_type::SingleLine, text_widget_flags::CutOff },
        iPinButton{ iLayout, push_button_style::TitleBar },
        iUnpinButton{ iLayout, push_button_style::TitleBar },
        iCloseButton{ iLayout, push_button_style::TitleBar },
        iStateActive{ false }
    {
        set_padding(neogfx::padding{2.0_dip});
        layout().set_padding(neogfx::padding{});

        set_background_opacity(1.0);

        iTitle.set_size_policy(size_constraint::Expanding, size_constraint::Minimum);
        iTitle.set_alignment(alignment::Left | alignment::VCenter);

        iPinButton.set_size_policy(neogfx::size_policy{ size_constraint::Minimum, size_constraint::Minimum });
        iUnpinButton.set_size_policy(neogfx::size_policy{ size_constraint::Minimum, size_constraint::Minimum });
        iCloseButton.set_size_policy(neogfx::size_policy{ size_constraint::Minimum, size_constraint::Minimum });

        iPinButton.hide();
        iUnpinButton.hide();

        iSink += service<i_surface_manager>().dpi_changed([this](i_surface&)
        {
            update_textures();
            update_layout();
            update(true);
        });
        iSink += service<i_app>().current_style_changed([this](style_aspect aAspect)
        {
            if ((aAspect & style_aspect::Color) == style_aspect::Color)
                update_textures();
        });

        update_textures();
    }

    const i_widget& tool_title_bar::as_widget() const
    {
        return *this;
    }

    i_widget& tool_title_bar::as_widget()
    {
        return *this;
    }

    i_string const& tool_title_bar::title() const
    {
        return iTitle.text();
    }

    void tool_title_bar::set_title(i_string const& aTitle)
    {
        iTitle.set_text(aTitle);
    }

    size tool_title_bar::minimum_size(optional_size const& aAvailableSpace) const
    {
        if (has_minimum_size())
            return widget::minimum_size(aAvailableSpace);
        else
            return widget::minimum_size(aAvailableSpace) + size{ 2.0_cm, 0.0 };
    }

    widget_type tool_title_bar::widget_type() const
    {
        return neogfx::widget_type::NonClient;
    }

    color tool_title_bar::palette_color(color_role aColorRole) const
    {
        if (has_palette_color(aColorRole))
            return widget::palette_color(aColorRole);
        if (aColorRole == color_role::Background)
        {
            if (!iStateActive)
                return widget::container_background_color();
            else
                return service<i_app>().current_style().palette().color(color_role::Selection);
        }
        else if (aColorRole == color_role::Text)
        {
            if (!iStateActive)
                return service<i_app>().current_style().palette().color(color_role::Text);
            else
                return service<i_app>().current_style().palette().color(color_role::SelectedText);
        }
        return widget::palette_color(aColorRole);
    }

    focus_policy tool_title_bar::focus_policy() const
    {
        if (has_focus_policy())
            return widget::focus_policy();
        return neogfx::focus_policy::ClickFocus;
    }

    void tool_title_bar::focus_gained(focus_reason aFocusReason)
    {
        widget::focus_gained(aFocusReason);
        if (has_focus())
            iContainer.as_widget().set_focus(aFocusReason);
    }

    void tool_title_bar::update_textures()
    {
        auto ink = palette_color(color_role::Text);
        auto paper = background_color();
        static std::string const sCloseTexturePattern
        {
            "[8,8]"
            "{0,paper}"
            "{1,ink}"
            "{2,ink_with_alpha}"

            "12000021"
            "21200212"
            "02122120"
            "00211200"
            "00211200"
            "02122120"
            "21200212"
            "12000021"
        };
        static std::string const sCloseHighDpiTexturePattern
        {
            "[16,16]"
            "{0,paper}"
            "{1,ink}"
            "{2,ink_with_alpha}"

            "1120000000000211"
            "1112000000002111"
            "2111200000021112"
            "0211120000211120"
            "0021112002111200"
            "0002111221112000"
            "0000211111120000"
            "0000021111200000"
            "0000021111200000"
            "0000211111120000"
            "0002111221112000"
            "0021112002111200"
            "0211120000211120"
            "2111200000021112"
            "1112000000002111"
            "1120000000000211"

        };
        if (iCloseTexture == std::nullopt || iCloseTexture->first != ink)
        {
            iCloseTexture.emplace(
                ink,
                !high_dpi() ?
                    neogfx::image{
                        "neogfx::tool_title_bar::iCloseTexture::" + ink.to_string(),
                        sCloseTexturePattern, { { "paper", color{} },{ "ink", ink },{ "ink_with_alpha", ink.with_alpha(0.5) } } } :
                    neogfx::image{
                        "neogfx::tool_title_bar::iCloseHighDpiTexture::" + ink.to_string(),
                        sCloseHighDpiTexturePattern, { { "paper", color{} }, { "ink", ink }, { "ink_with_alpha", ink.with_alpha(0.5) } }, 2.0 });
        }
        iCloseButton.set_image(iCloseTexture->second);
        update();
    }

    void tool_title_bar::update_state()
    {
        bool stateActive = iContainer.as_widget().has_focus() || iContainer.as_widget().child_has_focus();
        if (iStateActive != stateActive)
        {
            iStateActive = stateActive;
            update();
        }
    }
}
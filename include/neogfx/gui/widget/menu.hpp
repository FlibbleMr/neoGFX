// menu.hpp
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
#include <neogfx/core/event.hpp>
#include <neogfx/app/action.hpp>
#include <neogfx/app/i_help.hpp>
#include <neogfx/gfx/texture.hpp>
#include <neogfx/gui/widget/i_menu.hpp>

namespace neogfx
{
    class menu : public i_menu
    {
    public:
        define_declared_event(MenuChanged, menu_changed)
        define_declared_event(ItemAdded, item_added, item_index)
        define_declared_event(ItemRemoved, item_removed, item_index)
        define_declared_event(ItemChanged, item_changed, item_index)
        define_declared_event(Opened, opened)
        define_declared_event(Closed, closed)
        define_declared_event(ItemSelected, item_selected, i_menu_item&)
        define_declared_event(SelectionCleared, selection_cleared)
        define_declared_event(OpenSubMenu, open_sub_menu, i_menu&)
    private:
        typedef std::unique_ptr<i_menu_item> item_pointer;
        typedef std::vector<item_pointer> item_list;
    public:
        menu(i_menu& aParent, std::string const& aTitle = std::string{}, menu_type aType = menu_type::Popup);
        menu(std::string const& aTitle = std::string{}, menu_type aType = menu_type::Popup);
        ~menu();
    public:
        const i_widget& as_widget() const override;
        i_widget& as_widget() override;
        bool has_parent() const override;
        i_menu& parent() override;
        void set_parent(i_menu& aParent) override;
        menu_type type() const override;
        uuid const& group() const override;
        void set_group(uuid const& aGroup) override;
        std::string const& title() const override;
        void set_title(std::string const& aTitle) override;
        const i_texture& image() const override;
        void set_image(std::string const& aUri) override;
        void set_image(const i_image& aImage) override;
        void set_image(const i_texture& aTexture) override;
        uint32_t count() const override;
        uint32_t ideal_insert_index(uuid const& aGroup) const override;
        const i_menu_item& item_at(item_index aItemIndex) const override;
        i_menu_item& item_at(item_index aItemIndex) override;
        void add_sub_menu(i_menu& aSubMenu) override;
        i_menu& add_sub_menu(std::string const& aSubMenuTitle, uuid const& aGroup = {}) override;
        i_action& add_action(i_action& aAction) override;
        i_action& add_action(std::shared_ptr<i_action> aAction) override;
        void add_separator(uuid const& aGroup = {}) override;
        void insert_sub_menu_at(item_index aItemIndex, i_menu& aSubMenu) override;
        i_menu& insert_sub_menu_at(item_index aItemIndex, std::string const& aSubMenuText, uuid const& aGroup = {}) override;
        void insert_action_at(item_index aItemIndex, i_action& aAction) override;
        void insert_action_at(item_index aItemIndex, std::shared_ptr<i_action> aAction) override;
        void insert_separator_at(item_index aItemIndex, uuid const& aGroup = {}) override;
        void remove_at(item_index aItemIndex) override;
        item_index find_sub_menu(uuid const& aGroup) const override;
        item_index find(const i_menu_item& aItem) const override;
        item_index find(const i_menu& aSubMenu) const override;
        bool has_selected_item() const override;
        item_index selected_item() const override;
        void select_item_at(item_index aItemIndex, bool aOpenAnySubMenu = true) override;
        void clear_selection() override;
        bool has_available_items() const override;
        bool item_available_at(item_index aItemIndex) const override;
        item_index first_available_item() const override;
        item_index previous_available_item(item_index aCurrentIndex) const override;
        item_index next_available_item(item_index aCurrentIndex) const override;
        bool is_open() const override;
        void open() override;
        void close() override;
        bool is_modal() const override;
        void set_modal(bool aModal) override;
    public:
        using i_menu::ideal_insert_index;
    private:
        item_index update_grouping_separators(item_index aItemIndex);
    private:
        i_menu* iParent;
        menu_type iType;
        uuid iGroup;
        std::string iTitle;
        texture iImage;
        item_list iItems;
        action iSeparator;
        uint32_t iOpenCount;
        std::optional<item_index> iSelection;
        bool iModal;
    };
}
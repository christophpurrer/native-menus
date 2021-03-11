//
//  Menu.h
//
//  Created by Christoph Purrer on 3/10/21.
//

#pragma once

#include <memory>
#include <string>
#include <vector>

struct IMenuEntry {
    virtual ~IMenuEntry(){};
};

struct MenuEntry : IMenuEntry {
    MenuEntry(const std::string& _title, bool _enabled)
        : IMenuEntry(), title(_title), enabled(_enabled) {}
    MenuEntry(const std::string& _title) : MenuEntry(_title, true) {}
    std::string title;
    bool enabled;
};

struct Separator : IMenuEntry {
    Separator() {}
};

struct Menu {
    std::string title;
    std::vector<std::unique_ptr<IMenuEntry>> entries;
};

static inline std::vector<Menu> createApplicationMenu() {
    std::vector<Menu> appMenu;
    // App menu
    {
        auto menu = Menu{"Application"};
        menu.entries.emplace_back(std::make_unique<MenuEntry>("Preference"));
        menu.entries.emplace_back(std::make_unique<MenuEntry>("Hide Others"));
        menu.entries.emplace_back(std::make_unique<MenuEntry>("Check for Updates"));
        menu.entries.emplace_back(std::make_unique<MenuEntry>("Quit Application"));
        appMenu.emplace_back(std::move(menu));
    }

    // File
    {
        auto menu = Menu{"File"};
        menu.entries.emplace_back(std::make_unique<MenuEntry>("New Document"));
        menu.entries.emplace_back(std::make_unique<MenuEntry>("Log Out"));
        menu.entries.emplace_back(std::make_unique<Separator>());
        menu.entries.emplace_back(std::make_unique<MenuEntry>("Close Window"));
        appMenu.emplace_back(std::move(menu));
    }

    // Help
    {
        auto menu = Menu{"Help"};
        menu.entries.emplace_back(std::make_unique<MenuEntry>("About Application"));
        menu.entries.emplace_back(std::make_unique<MenuEntry>("Factory reset", false));
        menu.entries.emplace_back(std::make_unique<Separator>());
        menu.entries.emplace_back(std::make_unique<MenuEntry>("Submit Feedback", false));
        appMenu.emplace_back(std::move(menu));
    }
    return appMenu;
}

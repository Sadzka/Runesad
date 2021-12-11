//
// Created by Sadza on 17.08.2021.
//

#include <Base/SharedContext.hpp>

State::State(const std::string & guiName) {
    gui = tgui::Group::create({"100%, 100%"});
    SharedContext::getGui()->add(gui, "Group" + guiName);
}

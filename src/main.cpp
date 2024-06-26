#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
				}

				if (Mod::get()->getSettingValue<bool>("hide-newgrounds-button")) {
						auto bottomMenu = this->getChildByID("bottom-menu");
						bottomMenu->removeChildByID("newgrounds-button");
						bottomMenu->updateLayout();
				}

#ifdef GEODE_IS_ANDROID
				if (Loader::get()->isModLoaded("geode.devtools"))
						return true;
#endif
				if (Mod::get()->getSettingValue<bool>("hide-more-games-button")) {
						auto moreGamesMenu = this->getChildByID("more-games-menu");
						moreGamesMenu->removeChildByID("more-games-button");
						moreGamesMenu->updateLayout();
				}	

				return true;
		}
};

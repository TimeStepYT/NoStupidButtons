#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>

bool isSettingEnabled(std::string setting) {
    return Mod::get()->getSettingValue<bool>(setting);
}

class $modify(MyMenuLayer, MenuLayer) {
    bool init() override {
        if (!MenuLayer::init()) {
            return false;
        }

        auto const bottomMenu = this->getChildByID("bottom-menu");
        auto const socialMediaMenu = this->getChildByID("social-media-menu");
        auto const moreGamesMenu = this->getChildByID("more-games-menu");

        if (isSettingEnabled("hide-newgrounds-button")) {
            bottomMenu->removeChildByID("newgrounds-button");
            bottomMenu->updateLayout();
        }

        if (isSettingEnabled("hide-social-media-buttons")) {
            socialMediaMenu->removeChildByID("facebook-button");
            socialMediaMenu->removeChildByID("twitter-button");
            socialMediaMenu->removeChildByID("youtube-button");
            socialMediaMenu->removeChildByID("twitch-button");
            socialMediaMenu->removeChildByID("discord-button");
            socialMediaMenu->updateLayout();
        }

        if (isSettingEnabled("hide-robtop-logo")) {
            socialMediaMenu->removeChildByID("robtop-logo-button");
            socialMediaMenu->updateLayout();
        }
        else if (isSettingEnabled("hide-social-media-buttons")) {
            CCNode* const robtopButtonNode = socialMediaMenu->getChildByID("robtop-logo-button");
            CCNode* const bottomMenuButton = bottomMenu->getChildByID("settings-button");
            robtopButtonNode->setPositionY(bottomMenuButton->getPositionY());
            socialMediaMenu->updateLayout();
        }

#ifdef GEODE_IS_ANDROID
        if (Loader::get()->isModLoaded("geode.devtools"))
            return true;
#endif
        if (isSettingEnabled("hide-more-games-button")) {
            moreGamesMenu->removeChildByID("more-games-button");
            moreGamesMenu->updateLayout();
        }

        return true;
    }
};


class $modify(MyCreatorLayer, CreatorLayer) {
    bool init() {
        if (!CreatorLayer::init()) return false;

        auto creatorButtonsMenu = this->getChildByID("creator-buttons-menu");

        if (!creatorButtonsMenu) return true;

        auto versusButton = creatorButtonsMenu->getChildByID("versus-button");
        auto mapButton = creatorButtonsMenu->getChildByID("map-button");

        if (isSettingEnabled("hide-versus-button"))
            versusButton->removeMeAndCleanup();
        if (isSettingEnabled("hide-map-button"))
            mapButton->removeMeAndCleanup();
        creatorButtonsMenu->updateLayout();
        return true;
    }
};
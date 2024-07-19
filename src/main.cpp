#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>

bool isSettingEnabled(std::string setting) {
    return Mod::get()->getSettingValue<bool>(setting);
}

class $modify(MyMenuLayer, MenuLayer) {
    struct Fields {
        CCNode* bottomMenu;
        CCNode* socialMediaMenu;
        CCNode* moreGamesMenu;
    };

    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        m_fields->bottomMenu = this->getChildByID("bottom-menu");
        m_fields->socialMediaMenu = this->getChildByID("social-media-menu");
        m_fields->moreGamesMenu = this->getChildByID("more-games-menu");

        if (isSettingEnabled("hide-newgrounds-button")) {
            m_fields->bottomMenu->removeChildByID("newgrounds-button");
            m_fields->bottomMenu->updateLayout();
        }

        if (isSettingEnabled("hide-social-media-buttons")) {
            m_fields->socialMediaMenu->removeChildByID("facebook-button");
            m_fields->socialMediaMenu->removeChildByID("twitter-button");
            m_fields->socialMediaMenu->removeChildByID("youtube-button");
            m_fields->socialMediaMenu->removeChildByID("twitch-button");
            m_fields->socialMediaMenu->removeChildByID("discord-button");
            m_fields->socialMediaMenu->updateLayout();
        }

        if (isSettingEnabled("hide-robtop-logo")) {
            m_fields->socialMediaMenu->removeChildByID("robtop-logo-button");
            m_fields->socialMediaMenu->updateLayout();
        }
        else if (isSettingEnabled("hide-social-media-buttons")) {
            CCNode* robtopButtonNode =
                m_fields->socialMediaMenu->getChildByID("robtop-logo-button");
            CCNode* bottomMenuButton = m_fields->bottomMenu->getChildByID("settings-button");
            robtopButtonNode->setPositionY(bottomMenuButton->getPositionY());
            m_fields->socialMediaMenu->updateLayout();
        }

#ifdef GEODE_IS_ANDROID
        if (Loader::get()->isModLoaded("geode.devtools"))
            return true;
#endif
        if (isSettingEnabled("hide-more-games-button")) {
            m_fields->moreGamesMenu->removeChildByID("more-games-button");
            m_fields->moreGamesMenu->updateLayout();
        }

        return true;
    }
};

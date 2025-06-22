#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/MenuLayer.hpp>

bool isSettingEnabled(std::string setting) {
    return Mod::get()->getSettingValue<bool>(setting);
}

void kys(CCNode* victim) {
    victim->setVisible(false);
}

void ignoreInvisible(CCNode* menu) {
    if (!menu) return;

    auto layout = menu->getLayout();
    if (!layout) return;

    layout->ignoreInvisibleChildren(true);
}

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto bottomMenu = this->getChildByID("bottom-menu");
        auto socialMediaMenu = this->getChildByID("social-media-menu");
        auto moreGamesMenu = this->getChildByID("more-games-menu");

        ignoreInvisible(bottomMenu);

        if (isSettingEnabled("hide-newgrounds-button")) {
            auto ngBtn = bottomMenu->getChildByID("newgrounds-button");

            kys(ngBtn);

            bottomMenu->updateLayout();
        }

        if (isSettingEnabled("hide-social-media-buttons") && socialMediaMenu) {
            auto fbBtn = socialMediaMenu->getChildByID("facebook-button");
            auto twitterBtn = socialMediaMenu->getChildByID("twitter-button");
            auto ytBtn = socialMediaMenu->getChildByID("youtube-button");
            auto twitchBtn = socialMediaMenu->getChildByID("twitch-button");
            auto discordBtn = socialMediaMenu->getChildByID("discord-button");

            ignoreInvisible(socialMediaMenu);

            kys(fbBtn);
            kys(twitterBtn);
            kys(ytBtn);
            kys(twitchBtn);
            kys(discordBtn);

            socialMediaMenu->updateLayout();
        }

        if (isSettingEnabled("hide-robtop-logo")) {
            auto robtopBtn = socialMediaMenu->getChildByID("robtop-logo-button");

            ignoreInvisible(socialMediaMenu);

            kys(robtopBtn);

            socialMediaMenu->updateLayout();
        }

        else if (isSettingEnabled("hide-social-media-buttons") && isSettingEnabled("reposition-robtop-logo")) {
            CCNode* const robtopButtonNode = socialMediaMenu->getChildByID("robtop-logo-button");
            CCNode* const bottomMenuButton = bottomMenu->getChildByID("settings-button");
            robtopButtonNode->setPositionY(bottomMenuButton->getPositionY());
        }

        if (isSettingEnabled("hide-social-media-buttons") && isSettingEnabled("hide-robtop-logo")) {
            socialMediaMenu->setVisible(false);

            if (isSettingEnabled("reposition-profile-btn")) {
                auto profileMenu = this->getChildByID("profile-menu");
                auto usernameLabel = this->getChildByID("player-username");

                float prevY = profileMenu->getPositionY();
                float newY = bottomMenu->getPositionY();
                float yOffset = newY - prevY;
                
                profileMenu->setPositionY(newY);
                usernameLabel->setPositionY(usernameLabel->getPositionY() + yOffset);
            }
        }

#ifdef GEODE_IS_MOBILE
        if (Loader::get()->isModLoaded("geode.devtools"))
            return true;
#endif

        if (isSettingEnabled("hide-more-games-button")) {
            auto moreGamesButton = moreGamesMenu->getChildByID("more-games-button");

            ignoreInvisible(moreGamesMenu);

            kys(moreGamesButton);

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

        ignoreInvisible(creatorButtonsMenu);

        auto versusButton = creatorButtonsMenu->getChildByID("versus-button");
        auto mapButton = creatorButtonsMenu->getChildByID("map-button");

        if (isSettingEnabled("hide-versus-button"))
            kys(versusButton);
        if (isSettingEnabled("hide-map-button"))
            kys(mapButton);
        creatorButtonsMenu->updateLayout();
        return true;
    }
};
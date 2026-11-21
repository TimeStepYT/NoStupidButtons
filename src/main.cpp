#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/EditorPauseLayer.hpp>

bool isSettingEnabled(std::string setting) {
    return Mod::get()->getSettingValue<bool>(setting);
}

void kys(CCNode* victim) {
    victim->setVisible(false);
}

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto bottomMenu = this->getChildByID("bottom-menu");
        auto socialMediaMenu = this->getChildByID("social-media-menu");
        auto newsMenu = this->getChildByID("news-menu");

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

            kys(fbBtn);
            kys(twitterBtn);
            kys(ytBtn);
            kys(twitchBtn);
            kys(discordBtn);

            socialMediaMenu->updateLayout();
        }

        if (isSettingEnabled("hide-robtop-logo")) {
            auto robtopBtn = socialMediaMenu->getChildByID("robtop-logo-button");

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

        if (isSettingEnabled("hide-news-button") && newsMenu) {
            auto newsButton = newsMenu->getChildByID("news-button");

            kys(newsButton);

            newsMenu->updateLayout();
        }

        return true;
    }
};

class $modify(MyCreatorLayer, CreatorLayer) {
    bool init() {
        if (!CreatorLayer::init()) return false;

        NodeIDs::provideFor(this);

        auto creatorButtonsMenu = this->getChildByID("creator-buttons-menu");

        if (!creatorButtonsMenu) return true;

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

class $modify(MyEditorPauseLayer, EditorPauseLayer) {
    bool init(LevelEditorLayer* layer) {
        if (!EditorPauseLayer::init(layer))
            return false;

        NodeIDs::provideFor(this);
        
        auto guidelinesMenu = this->getChildByID("guidelines-menu");
        auto resumeMenu = this->getChildByID("resume-menu");

        if (!guidelinesMenu || !resumeMenu)
            return true;

        auto helpButton = guidelinesMenu->getChildByID("help-button");
        auto exitButton = resumeMenu->getChildByID("exit-button");

        if (!helpButton || !exitButton)
            return true;

        if (isSettingEnabled("hide-editor-help-button")) {
            kys(helpButton);
            guidelinesMenu->updateLayout();
        }
        if (isSettingEnabled("hide-editor-exit-button")) {
            kys(exitButton);
            resumeMenu->updateLayout();
        }

        return true;
    }
};
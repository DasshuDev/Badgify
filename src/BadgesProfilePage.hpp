#pragma once

#include <Geode/modify/ProfilePage.hpp>
#include <Geode/Geode.hpp>
#include "Badges.hpp"

using namespace geode::prelude;

class $modify(BadgesProfilePage, ProfilePage) {

    struct Fields {
        CCNode* m_self;
        CCNode* m_usernameMenu;
        CCNode* m_badgeNode;
        CCMenu* m_badgeMenu;
        CCNode* m_infoButton;
        CCSprite* m_separatorLeft;
        CCSprite* m_separatorRight;
        CCMenuItemSpriteExtra* m_badgesButton;
        std::vector<alpha::badgify::BadgeInfo*> m_badges;
        std::vector<std::shared_ptr<alpha::badgify::Badge>> m_owningBadges;
        std::unordered_map<alpha::badgify::BadgeInfo*, Ref<CCNode>> m_badgeNodes;
        std::unordered_map<CCNode*, CCNode*> m_btnToBadge;

        bool m_alterativeDesign;

        ~Fields() {
            for (const auto& owningBadge : m_owningBadges) {
                Badges::get()->removeFromActiveBadges(owningBadge);
            }
        };
    };
    
    bool init(int accountID, bool ownProfile);
    void loadPageFromUserInfo(GJUserScore* score);
    void addBadge(alpha::badgify::BadgeInfo* info, CCNode* badgeNode, std::shared_ptr<alpha::badgify::Badge> badge);
    void removeBadge(alpha::badgify::BadgeInfo* info);
    void updateBadges();
    void setupBadgeNode();
    void fixInfoButton(float dt);
    void unregisterTouchesRecursive(CCNode* node);
    void addToBadgeContainer(alpha::badgify::BadgeInfo* info, CCNode* badgeNode);
    void onBadges(CCObject* sender);

};
#pragma once

#include <Geode/modify/CommentCell.hpp>
#include <Geode/Geode.hpp>
#include "Badges.hpp"

using namespace geode::prelude;

class $modify(BadgesCommentCell, CommentCell) {

    struct Fields {
        CCNode* m_self;
        CCNode* m_usernameNode;
        CCNode* m_usernameMenu;
        CCNode* m_badgeNode;
        CCMenuItemSpriteExtra* m_badgesButton;
        std::vector<alpha::badgify::BadgeInfo*> m_badges;
        std::vector<std::shared_ptr<alpha::badgify::Badge>> m_owningBadges;
        std::unordered_map<alpha::badgify::BadgeInfo*, Ref<CCNode>> m_badgeNodes;
        bool m_canAddBadge = false;

        ~Fields() {
            for (const auto& owningBadge : m_owningBadges) {
                Badges::get()->removeFromActiveBadges(owningBadge);
            }
        };
    };

    void loadFromComment(GJComment* comment);
    void addBadge(alpha::badgify::BadgeInfo* info, CCNode* badgeNode, std::shared_ptr<alpha::badgify::Badge> badge);
    void removeBadge(alpha::badgify::BadgeInfo* info);
    void setupBadges();
    void updateBadges();
    void unregisterTouchesRecursive(CCNode* node);
    void addToBadgeContainer(alpha::badgify::BadgeInfo* info, CCNode* badgeNode);
    void onBadges(CCObject* sender);
};
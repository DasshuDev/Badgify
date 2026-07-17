#pragma once

#include <Geode/Geode.hpp>
#include "Badgify.hpp"
#include "Badges.hpp"
#include "RenderNode.hpp"

using namespace geode::prelude;

class BadgesPopup : public Popup {
public:
    static BadgesPopup* create(GJUserScore* score, alpha::badgify::ModStatus modStatus, std::vector<alpha::badgify::BadgeInfo*>* info, alpha::badgify::BadgeInfo* current);
    void addBadge(alpha::badgify::BadgeInfo* info, CCNode* badgeNode, std::shared_ptr<alpha::badgify::Badge> badge);
    void removeBadge(alpha::badgify::BadgeInfo* info);
    GJUserScore* getScore();

    virtual ~BadgesPopup() {
        for (const auto&  owningBadge : m_owningBadges) {
            Badges::get()->removeFromActiveBadges(owningBadge);
        }
    };

protected:
    bool init(GJUserScore* score, alpha::badgify::ModStatus modStatus, std::vector<alpha::badgify::BadgeInfo*>* info, alpha::badgify::BadgeInfo* current);
    void goToNextPage(CCObject* sender);
    void goToPrevPage(CCObject* sender);
    void setBadge(int page, float opacity, float xOffset, float scale, bool instant);
    void setNavigationButtonStates();
    void goToPage(bool instant = false);
    void keyDown(cocos2d::enumKeyCodes key, double p1) override;

    int m_page = 0;
    GJUserScore* m_score;
    CCMenuItemSpriteExtra* m_prevButton;
    CCMenuItemSpriteExtra* m_nextButton;
    CCNode* m_badgesContainer;
    CCLabelBMFont* m_title;
    MDTextArea* m_description;
    std::unordered_map<CCNode*, alpha::badgify::BadgeInfo*> m_badges;
    std::unordered_map<alpha::badgify::BadgeInfo*, alpha::badgify::RenderNode*> m_nodes;
    std::unordered_map<alpha::badgify::BadgeInfo*, CCNode*> m_realNodes;
    std::unordered_map<CCNode*, float> m_renderScales;
    
    std::vector<std::shared_ptr<alpha::badgify::Badge>> m_owningBadges;
};
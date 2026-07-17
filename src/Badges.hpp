#pragma once

#include "Badgify.hpp"
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class BadgesCommentCell;
class BadgesProfilePage;
class BadgesPopup;

class Badges {
public:

    static Badges* get();

    void showBadge(const alpha::badgify::Badge& badge, cocos2d::CCNode* badgeNode);
    void removeBadge(std::shared_ptr<alpha::badgify::Badge> badge, alpha::badgify::BadgeInfo* badgeInfo);

    void setName(ZStringView id, ZStringView name);
    Result<ZStringView> getName(ZStringView id);

    void setDescription(ZStringView id, ZStringView description);
    Result<ZStringView> getDescription(ZStringView id);

    void setProfileCallback(ZStringView id, alpha::badgify::ProfileCallback onProfile);
    void registerBadge(ZStringView id, ZStringView name, ZStringView description, alpha::badgify::ProfileCallback onProfile);
    void unregisterBadge(ZStringView id);

    void addToActiveNodes(CCNode* node);

    void removeFromActiveBadges(std::shared_ptr<alpha::badgify::Badge> badge);
    void removeFromActiveNodes(CCNode* node);

    alpha::badgify::Badge badgeForNode(CCNode* node, ZStringView id);

private:
    void onProfile(cocos2d::CCNode* node, GJUserScore* score, alpha::badgify::ModStatus modStatus, alpha::badgify::Location location);
    StringMap<alpha::badgify::BadgeInfo> m_badges;
    std::vector<alpha::badgify::BadgeInfo*> m_badgesIndexed;
    StringMap<std::vector<std::shared_ptr<alpha::badgify::Badge>>> m_activeBadges;
    std::set<CCNode*> m_activeNodes;

    friend class BadgesCommentCell;
    friend class BadgesProfilePage;
    friend class BadgesPopup;
};
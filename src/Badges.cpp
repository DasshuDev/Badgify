#include "Badges.hpp"
#include "Badgify.hpp"
#include "BadgesCommentCell.hpp"
#include "BadgesPopup.hpp"
#include "BadgesProfilePage.hpp"

Badges* Badges::get() {
    static Badges instance;
    return &instance;
}

void Badges::showBadge(const alpha::badgify::Badge& badge, CCNode* badgeNode) {
    auto badgeIter = m_badges.find(badge.badgeID);
    if (badgeIter == m_badges.end()) return;

    if (!m_activeNodes.contains(badge.target)) return;

    auto& vec = m_activeBadges[badge.badgeID];
    vec.push_back(std::make_shared<alpha::badgify::Badge>(badge));

    auto& activeBadge = vec.back();

    if (badge.location == alpha::badgify::Location::Comment) {
        reinterpret_cast<BadgesCommentCell*>(badge.target.data())->addBadge(&badgeIter->second, badgeNode, activeBadge);
    }
    else if (badge.location == alpha::badgify::Location::Profile) {
        reinterpret_cast<BadgesProfilePage*>(badge.target.data())->addBadge(&badgeIter->second, badgeNode, activeBadge);
    }
    else if (badge.location == alpha::badgify::Location::InfoPopup) {
        static_cast<BadgesPopup*>(badge.target.data())->addBadge(&badgeIter->second, badgeNode, activeBadge);
    }
}

void Badges::removeBadge(std::shared_ptr<alpha::badgify::Badge> badge, alpha::badgify::BadgeInfo* badgeInfo) {
    if (!m_activeNodes.contains(badge->target)) return;

    if (badge->location == alpha::badgify::Location::Comment) {
        reinterpret_cast<BadgesCommentCell*>(badge->target.data())->removeBadge(badgeInfo);
    }
    else if (badge->location == alpha::badgify::Location::Profile) {
        reinterpret_cast<BadgesProfilePage*>(badge->target.data())->removeBadge(badgeInfo);
    }
    else if (badge->location == alpha::badgify::Location::InfoPopup) {
        static_cast<BadgesPopup*>(badge->target.data())->removeBadge(badgeInfo);
    }
}

void Badges::setName(ZStringView id, ZStringView name) {
    auto badgeIter = m_badges.find(id);
    if (badgeIter == m_badges.end()) return;
    badgeIter->second.name = name;
}

Result<ZStringView> Badges::getName(ZStringView id) {
    auto badgeIter = m_badges.find(id);
    if (badgeIter == m_badges.end()) return geode::Err("Badge not found for id: {}", id);
    return geode::Ok(badgeIter->second.name);
}

void Badges::setDescription(ZStringView id, ZStringView description) {
    auto badgeIter = m_badges.find(id);
    if (badgeIter == m_badges.end()) return;
    badgeIter->second.description = description;
}

Result<ZStringView> Badges::getDescription(ZStringView id) {
    auto badgeIter = m_badges.find(id);
    if (badgeIter == m_badges.end()) return geode::Err("Badge not found for id: {}", id);
    return geode::Ok(badgeIter->second.description);
}

void Badges::setProfileCallback(ZStringView id, alpha::badgify::ProfileCallback onProfile) {
    auto badgeIter = m_badges.find(id);
    if (badgeIter == m_badges.end()) return;
    badgeIter->second.onProfile = std::move(onProfile);
}

void Badges::registerBadge(ZStringView id, ZStringView name, ZStringView description, alpha::badgify::ProfileCallback onProfile) {
    auto [it, b] = m_badges.emplace(id, alpha::badgify::BadgeInfo{id, name, description, std::move(onProfile)});
    
    auto badgeInfo = &(*it).second;
    m_badgesIndexed.push_back(badgeInfo);

    for (auto node : m_activeNodes) {
        auto badge = badgeForNode(node, id);
        if (badgeInfo->onProfile) {
            badgeInfo->onProfile(badge);
        }
    }
}

void Badges::unregisterBadge(ZStringView id) {
    auto badgeIter = m_badges.find(id);
    if (badgeIter == m_badges.end()) return;

    auto activeIt = m_activeBadges.find(id);
    if (activeIt == m_activeBadges.end()) return;

    for (auto& badge : activeIt->second) {
        removeBadge(badge, &m_badges.at(id));
    }

    m_badgesIndexed.erase(std::remove(m_badgesIndexed.begin(), m_badgesIndexed.end(), &badgeIter->second), m_badgesIndexed.end());
    m_badges.erase(badgeIter);
}

void Badges::addToActiveNodes(CCNode* node) {
    m_activeNodes.insert(node);
}

void Badges::removeFromActiveNodes(CCNode* node) {
    m_activeNodes.erase(node);
}

alpha::badgify::Badge Badges::badgeForNode(CCNode* node, ZStringView id) {
    auto location = alpha::badgify::Location::None;
    GJUserScore* score = nullptr;

    if (auto commentCell = typeinfo_cast<CommentCell*>(node)) {
        location = alpha::badgify::Location::Comment;
        score = commentCell->m_comment->m_userScore;
    }
    if (auto profile = typeinfo_cast<ProfilePage*>(node)) {
        location = alpha::badgify::Location::Profile;
        score = profile->m_score;
    }
    if (auto badgesPopup = typeinfo_cast<BadgesPopup*>(node)) {
        location = alpha::badgify::Location::InfoPopup;
        score = badgesPopup->getScore();
    }

    return {id, location, static_cast<alpha::badgify::ModStatus>(score->m_modBadge), score, node};
}

void Badges::removeFromActiveBadges(std::shared_ptr<alpha::badgify::Badge> badge) {
    auto& vec = m_activeBadges[badge->badgeID];
    vec.erase(std::remove(vec.begin(), vec.end(), badge), vec.end());
}

void Badges::onProfile(CCNode* node, GJUserScore* score, alpha::badgify::ModStatus modStatus, alpha::badgify::Location location) {
    for (auto badge : m_badgesIndexed) {
        if (badge->onProfile) {
            badge->onProfile({badge->id, location, modStatus, score, node});
        }
    }
}
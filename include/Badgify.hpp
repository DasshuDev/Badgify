#pragma once

#include <Geode/cocos/base_nodes/CCNode.h>
#include <Geode/binding/GJUserScore.hpp>
#include <Geode/loader/Event.hpp>
#include <Geode/loader/Dispatch.hpp>
#include <Geode/utils/ZStringView.hpp>
#include <Geode/utils/cocos.hpp>

#define MY_MOD_ID "alphalaneous.badgify"

namespace alpha::badgify {

    enum class ModStatus {
        None = 0,
        Regular = 1,
        Elder = 2,
        Leaderboard = 3
    };

    enum class Location {
        None = -1,
        Profile,
        Comment,
        InfoPopup
    };

    struct Badge {
        std::string badgeID;
        Location location;
        ModStatus modStatus;
        geode::Ref<GJUserScore> user;
        geode::Ref<cocos2d::CCNode> target;
    };

    using ProfileCallback = geode::Function<void(const Badge& badge)>;

    struct BadgeInfo {
        std::string id;
        std::string name;
        std::string description;
        ProfileCallback onProfile;
    };

    inline bool isLoaded() {
        return geode::Loader::get()->getLoadedMod("alphalaneous.badgify") != nullptr;
    }

    template <typename F>
    void waitForBadgify(F&& callback) {
        if (isLoaded()) {
            callback();
        } 
        else {
            auto badgify = geode::Loader::get()->getInstalledMod("alphalaneous.badgify");
            if (!badgify) return;

            geode::ModStateEvent(geode::ModEventType::Loaded, badgify).listen(
                [callback = std::forward<F>(callback)]() {
                    callback();
                }
            ).leak();
        }
    }

    inline void registerBadge(geode::ZStringView id, geode::ZStringView name, geode::ZStringView description, ProfileCallback onProfile)
    GEODE_EVENT_EXPORT_NORES(&registerBadge, (id, name, description, std::move(onProfile)));

    inline void unregisterBadge(geode::ZStringView id)
    GEODE_EVENT_EXPORT_NORES(&unregisterBadge, (id));

    inline void setName(geode::ZStringView id, geode::ZStringView name)
    GEODE_EVENT_EXPORT_NORES(&setName, (id, name));

    inline geode::Result<geode::ZStringView> getName(geode::ZStringView id) 
    GEODE_EVENT_EXPORT(&getName, (id));

    inline void setDescription(geode::ZStringView id, geode::ZStringView description)
    GEODE_EVENT_EXPORT_NORES(&setDescription, (id, description));

    inline geode::Result<geode::ZStringView> getDescription(geode::ZStringView id) 
    GEODE_EVENT_EXPORT(&getDescription, (id));

    inline void setProfileCallback(geode::ZStringView id, ProfileCallback onProfile)
    GEODE_EVENT_EXPORT_NORES(&setProfileCallback, (id, std::move(onProfile)));

    inline void showBadge(const Badge& badge, cocos2d::CCNode* badgeNode)
    GEODE_EVENT_EXPORT_NORES(&showBadge, (badge, badgeNode));

}
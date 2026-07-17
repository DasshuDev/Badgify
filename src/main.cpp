#include <Geode/Geode.hpp>
#include "Badgify.hpp"
#include "Badges.hpp"

using namespace geode::prelude;

$on_mod(Loaded) {

    Badges::get()->registerBadge("moderator"_spr, 
        "Moderator", 
        "A Moderator is identifiable through the Moderator badge in Geometry Dash. This role can be granted only by RobTop himself, meaning that Moderators represent him as well as Geometry Dash directly. Their main task is suggesting good levels to RobTop for a rating. They also have more power when voting for Demon difficulty.", 
        [] (const alpha::badgify::Badge& badge) {
            if (badge.modStatus == alpha::badgify::ModStatus::Regular) {
                CCSprite* spr;
                if (badge.location == alpha::badgify::Location::InfoPopup) {
                    spr = CCSprite::create("mod-large.png"_spr);
                }
                else {
                    spr = CCSprite::createWithSpriteFrameName("modBadge_01_001.png");
                }
                Badges::get()->showBadge(badge, spr);
            }
        }
    );

    Badges::get()->registerBadge("elder-moderator"_spr, 
        "Elder Moderator", 
        "An Elder Moderator is identifiable through the Elder Moderator badge in Geometry Dash. Elder Moderators are tasked not only with sending good levels, but also moderating the in-game comment sections, whitelisting users on Newgrounds, unlocking updates for older rated levels, and some other tasks.", 
        [] (const alpha::badgify::Badge& badge) {
            if (badge.modStatus == alpha::badgify::ModStatus::Elder) {
                CCSprite* spr;
                if (badge.location == alpha::badgify::Location::InfoPopup) {
                    spr = CCSprite::create("elder-mod-large.png"_spr);
                }
                else {
                    spr = CCSprite::createWithSpriteFrameName("modBadge_02_001.png");
                }
                Badges::get()->showBadge(badge, spr);
            }
        }
    );

    Badges::get()->registerBadge("leaderboard-moderator"_spr, 
        "Leaderboard Moderator", 
        "Leaderboard Moderators manage the Leaderboards within the game. They manage the Top 1000 whitelist and can ban players from both the Global and Level Leaderboards. It is worth noting that they are not necessarily a normal Moderator too.", 
        [] (const alpha::badgify::Badge& badge) {
            if (badge.modStatus == alpha::badgify::ModStatus::Leaderboard) {
                CCSprite* spr;
                if (badge.location == alpha::badgify::Location::InfoPopup) {
                    spr = CCSprite::create("leaderboard-mod-large.png"_spr);
                }
                else {
                    spr = CCSprite::createWithSpriteFrameName("modBadge_03_001.png");
                }
                Badges::get()->showBadge(badge, spr);
            }
        }
    );
}
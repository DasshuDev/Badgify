#include <Geode/Geode.hpp>
#include "Badgify.hpp"
#include "Badges.hpp"

using namespace geode::prelude;

$on_mod(Loaded) {

    // Moderator
    Badges::get()->registerBadge("moderator"_spr, 
        "Moderator", 
        "A <cs>Moderator</c> is identifiable through the Moderator badge in Geometry Dash. This role can be granted only by <co>RobTop</c> himself, meaning that Moderators represent him as well as Geometry Dash directly. Their main task is suggesting good levels to RobTop for a rating. They also have more power when voting for Demon difficulty.", 
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

    // Elder Moderator
    Badges::get()->registerBadge("elder-moderator"_spr,
        "Elder Moderator", 
        "An <co>Elder Moderator</c> is identifiable through the Elder Moderator badge in Geometry Dash. Elder Moderators are tasked not only with sending good levels, but also moderating the in-game comment sections, whitelisting users on Newgrounds, unlocking updates for older rated levels, and some other tasks.", 
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

    // Leaderboard Moderator
    Badges::get()->registerBadge("leaderboard-moderator"_spr, 
        "Leaderboard Moderator", 
        "<cl>Leaderboard Moderators</c> manage the Leaderboards within the game. They manage the Top 1000 whitelist and can ban players from both the Global and Level Leaderboards. It is worth noting that they are not necessarily a normal Moderator too.", 
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

    // Apply prio and colors to Mod and Elder;
    // Leaderboard mod is not *technically* listed as 
    // moderator, so it is not affected by prio and
    // color changes.

    // Also to note; color and prio changes are applied
    // AFTER badge application. This may be fixed in a
    // future update, but for now it is not a big deal.

    // ¯\_(ツ)_/¯

    Badges::get()->setPriority("moderator"_spr, 2147483647);
    Badges::get()->setCommentColor("moderator"_spr, {200, 255, 200});

    Badges::get()->setPriority("elder-moderator"_spr, 2147483647);
    Badges::get()->setCommentColor("elder-moderator"_spr, {75, 255, 75});
}
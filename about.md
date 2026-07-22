# Badgify

An API for adding badges to profiles and comments easily.

## The API

The API is extremely simple to use, here's an example on how to register and modify a new badge:

```cpp
// Important note: using this namespace is OPTIONAL!
// When using Badgify's API, you either need to use
// this namespace or write "alpha::badgify::" in
// front of every function.

using namespace alpha::badgify;

$execute {
    registerBadge(
        // A unique ID for your badge.
        "your-badge-id"_spr, 
        // The name shown when clicking the badge.
        "Badge Name", 
        // The description shown when clicking the badge.
        "This is a description that goes along with the badge.", 
        // Show the badge when a Location::Profile, Location::Comment, or Location::InfoPopup is loaded.
        // showBadge can be called at any time and requires the Badge object and the node for the badge.
        [] (const Badge& badge) {
            if (badge.modStatus == ModStatus::Regular) {
                showBadge(badge, CCSprite::createWithSpriteFrameName("modBadge_01_001.png"));
            }
        }
    );

    // Unregistering.
    unregisterBadge("your-badge-id"_spr);

    // Setting name.
    setName("your-badge-id"_spr, "New Badge Name");

    // Setting description.
    setDescription("your-badge-id"_spr, "New Description");

    // Setting the callback for showing the badge when a Location::Profile, Location::Comment, or Location::InfoPopup is loaded.
    setProfileCallback("your-badge-id"_spr, [] (const Badge& badge) {
        if (badge.user->m_userName == "Alphalaneous" && badge.location == Location::Comment) {
            showBadge(badge, CCSprite::createWithSpriteFrameName("modBadge_01_001.png"));
        }
    });

    // Getting the name.
    log::info("Name: {}", getName("your-badge-id"_spr).unwrapOrDefault());

    // Getting the description.
    log::info("Description: {}", getDescription("your-badge-id"_spr).unwrapOrDefault());
}
```

How to set comment color per badge:

```cpp
// Setting different colors per badge.
Badges::get()->setCommentColor("your-badge-id"_spr, color1);
Badges::get()->setCommentColor("another-badge-id"_spr, color2);
```

How to set badge priotiry:

```cpp
// Setting different priorities per badges.
// These may overlap with other mods, and
// that is NOT a Badgify issue to fix.
Badges::get()->setPriority("your-badge-id"_spr, int1);
Badges::get()->setPriority("another-badge-id"_spr, int2);
```

**Vanilla Moderator badge descriptions from the [Geometry Dash Mod Wiki](https://www.robtopgames.com/faq/en/answers/moderator/)**
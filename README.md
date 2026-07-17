# Badgify

An API for adding badges to profiles and comments easily.

## The API

It is extremely simple, here's an example on how to register and modify badge:

```cpp
$execute {
    alpha::badgify::registerBadge(
        // A unique ID for your badge.
        "your-badge-id"_spr, 
        // The name shown when clicking the badge.
        "Badge Name", 
        // The description shown when clicking the badge.
        "This is a description that goes along with the badge.", 
        // Show the badge when a Location::Profile, Location::Comment, or Location::InfoPopup is loaded.
        // alpha::badgify::showBadge can be called at any time and requires the Badge object and the node for the badge.
        [] (const alpha::badgify::Badge& badge) {
            if (badge.modStatus == ModStatus::Regular) {
                alpha::badgify::showBadge(badge, CCSprite::createWithSpriteFrameName("modBadge_01_001.png"));
            }
        }
    );

    // Unregistering.
    alpha::badgify::unregisterBadge("your-badge-id"_spr);

    // Setting name.
    alpha::badgify::setName("your-badge-id"_spr, "New Badge Name");

    // Setting description.
    alpha::badgify::setDescription("your-badge-id"_spr, "New Description");

    // Setting the callback for showing the badge when a Location::Profile, Location::Comment, or Location::InfoPopup is loaded.
    alpha::badgify::setProfileCallback("your-badge-id"_spr, [] (const alpha::badgify::Badge& badge) {
        if (badge.user->m_userName == "Alphalaneous" && badge.location == alpha::badgify::Location::Comment) {
            alpha::badgify::showBadge(badge, CCSprite::createWithSpriteFrameName("modBadge_01_001.png"));
        }
    });

    // Getting the name.
    log::info("Name: {}", alpha::badgify::getName("your-badge-id"_spr).unwrapOrDefault());

    // Getting the description.
    log::info("Description: {}", alpha::badgify::getDescription("your-badge-id"_spr).unwrapOrDefault());
}
```

**Mod badge descriptions from https://www.robtopgames.com/faq/en/answers/moderator/**
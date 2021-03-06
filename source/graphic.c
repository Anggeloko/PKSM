/*
* This file is part of PKSM
* Copyright (C) 2016 Bernardo Giordano
*
* This software is provided 'as-is', 
* without any express or implied warranty. 
* In no event will the authors be held liable for any damages 
* arising from the use of this software.
*
* This code is subject to the following restrictions:
*
* 1) The origin of this software must not be misrepresented; 
* 2) You must not claim that you wrote the original software. 
*
*/

#include <sf2d.h>
#include <sftd.h>
#include <sfil.h>
#include <stdio.h>
#include <time.h>
#include "graphic.h"
#include "editor.h"
#include "http.h"

sftd_font *fontBold18, *fontBold15, *fontBold14, *fontBold12, *fontBold11, *fontBold9, *fontFixed; 
sf2d_texture *topBorder, *distributionsBottom, *distributionsTop, *bottomBorder, *slimDarkBar, *slimRedBar, *gameSelectorBottom, *gameSelectorTop, *mainMenuBottom, *darkBar, *redBar, *mainMenuTop, *darkButton, *eventTop, *left, *leftTop, *lightButton, *redButton, *right, *rightTop, *spritesSmall, *shinySpritesSmall, *eventMenuBottomBar, *eventMenuTopBarSelected, *eventMenuTopBar, *eventMenuTop, *warningTopTrasp, *warningBottomTrasp, *PSDates, *editorBar, *boxView, *infoView, *LRBar, *selector, *editorBG, *plus, *minus, *buttonSave, *back, *setting, *selectorCloning, *bankBottomBG, *topButton, *bottomButton, *bottomPopUp, *pokemonBufferBox, *cleanTop, *DSBottomBG, *DSTopBG, *DSBarSelected, *DSBar, *DSEventBottom, *DSLangSelected, *DSLang, *DSEventTop, *DSNormalBarL, *DSNormalBarR, *DSSelectedBarL, *DSSelectedBarR, *bottomMovesBar, *bottomMovesBarCut, *bottomMovesBG, *topMovesBG, *topSelectedMove, *settings, *item, *alternativeSpritesSmall;

int trasp = 254;
bool vanish = true;

static char *abilities[] = {"None", "Stench", "Drizzle", "Speed Boost", "Battle Armor", "Sturdy", "Damp", "Limber", "Sand Veil", "Static", "Volt Absorb", "Water Absorb", "Oblivious", "Cloud Nine", "Compound Eyes", "Insomnia", "Color Change", "Immunity", "Flash Fire", "Shield Dust", "Own Tempo", "Suction Cups", "Intimidate", "Shadow Tag", "Rough Skin", "Wonder Guard", "Levitate", "Effect Spore", "Synchronize", "Clear Body", "Natural Cure", "Lightning Rod", "Serene Grace", "Swift Swim", "Chlorophyll", "Illuminate", "Trace", "Huge Power", "Poison Point", "Inner Focus", "Magma Armor", "Water Veil", "Magnet Pull", "Soundproof", "Rain Dish", "Sand Stream", "Pressure", "Thick Fat", "Early Bird", "Flame Body", "Run Away", "Keen Eye", "Hyper Cutter", "Pickup", "Truant", "Hustle", "Cute Charm", "Plus", "Minus", "Forecast", "Sticky Hold", "Shed Skin", "Guts", "Marvel Scale", "Liquid Ooze", "Overgrow", "Blaze", "Torrent", "Swarm", "Rock Head", "Drought", "Arena Trap", "Vital Spirit", "White Smoke", "Pure Power", "Shell Armor", "Air Lock", "Tangled Feet", "Motor Drive", "Rivalry", "Steadfast", "Snow Cloak", "Gluttony", "Anger Point", "Unburden", "Heatproof", "Simple", "Dry Skin", "Download", "Iron Fist", "Poison Heal", "Adaptability", "Skill Link", "Hydration", "Solar Power", "Quick Feet", "Normalize", "Sniper", "Magic Guard", "No Guard", "Stall", "Technician", "Leaf Guard", "Klutz", "Mold Breaker", "Super Luck", "Aftermath", "Anticipation", "Forewarn", "Unaware", "Tinted Lens", "Filter", "Slow Start", "Scrappy", "Storm Drain", "Ice Body", "Solid Rock", "Snow Warning", "Honey Gather", "Frisk", "Reckless", "Multitype", "Flower Gift", "Bad Dreams", "Pickpocket", "Sheer Force", "Contrary", "Unnerve", "Defiant", "Defeatist", "Cursed Body", "Healer", "Friend Guard", "Weak Armor", "Heavy Metal", "Light Metal", "Multiscale", "Toxic Boost", "Flare Boost", "Harvest", "Telepathy", "Moody", "Overcoat", "Poison Touch", "Regenerator", "Big Pecks", "Sand Rush", "Wonder Skin", "Analytic", "Illusion", "Imposter", "Infiltrator", "Mummy", "Moxie", "Justified", "Rattled", "Magic Bounce", "Sap Sipper", "Prankster", "Sand Force", "Iron Barbs", "Zen Mode", "Victory Star", "Turboblaze", "Teravolt", "Aroma Veil", "Flower Veil", "Cheek Pouch", "Protean", "Fur Coat", "Magician", "Bulletproof", "Competitive", "Strong Jaw", "Refrigerate", "Sweet Veil", "Stance Change", "Gale Wings", "Mega Launcher", "Grass Pelt", "Symbiosis", "Tough Claws", "Pixilate", "Gooey", "Aerilate", "Parental Bond", "Dark Aura", "Fairy Aura", "Aura Break", "Primordial Sea", "Desolate Land", "Delta Stream", "Stamina", "Wimp Out", "Emergency Exit", "Water Compaction", "Merciless", "Shields Down", "Stakeout", "Water Bubble", "Steelworker", "Berserk", "Slush Rush", "Long Reach", "Liquid Voice", "Triage", "Galvanize", "Surge Surfer", "Schooling", "Disguise", "Battle Bond", "Power Construct", "Corrosion", "Comatose", "Queenly Majesty", "Innards Out", "Dancer", "Battery", "Fluffy", "Dazzling", "Soul-Heart", "Tangling Hair", "Receiver", "Power of Alchemy", "Beast Boost", "RKS System", "Electric Surge", "Psychic Surge", "Misty Surge", "Grassy Surge", "Full Metal Body", "Shadow Shield", "Prism Armor"};
static char *moves[] = {"None", "Pound", "Karate Chop", "Double Slap", "Comet Punch", "Mega Punch", "Pay Day", "Fire Punch", "Ice Punch", "Thunder Punch", "Scratch", "Vice Grip", "Guillotine", "Razor Wind", "Swords Dance", "Cut", "Gust", "Wing Attack", "Whirlwind", "Fly", "Bind", "Slam", "Vine Whip", "Stomp", "Double Kick", "Mega Kick", "Jump Kick", "Rolling Kick", "Sand Attack", "Headbutt", "Horn Attack", "Fury Attack", "Horn Drill", "Tackle", "Body Slam", "Wrap", "Take Down", "Thrash", "Double-Edge", "Tail Whip", "Poison Sting", "Twineedle", "Pin Missile", "Leer", "Bite", "Growl", "Roar", "Sing", "Supersonic", "Sonic Boom", "Disable", "Acid", "Ember", "Flamethrower", "Mist", "Water Gun", "Hydro Pump", "Surf", "Ice Beam", "Blizzard", "Psybeam", "Bubble Beam", "Aurora Beam", "Hyper Beam", "Peck", "Drill Peck", "Submission", "Low Kick", "Counter", "Seismic Toss", "Strength", "Absorb", "Mega Drain", "Leech Seed", "Growth", "Razor Leaf", "Solar Beam", "Poison Powder", "Stun Spore", "Sleep Powder", "Petal Dance", "String Shot", "Dragon Rage", "Fire Spin", "Thunder Shock", "Thunderbolt", "Thunder Wave", "Thunder", "Rock Throw", "Earthquake", "Fissure", "Dig", "Toxic", "Confusion", "Psychic", "Hypnosis", "Meditate", "Agility", "Quick Attack", "Rage", "Teleport", "Night Shade", "Mimic", "Screech", "Double Team", "Recover", "Harden", "Minimize", "Smokescreen", "Confuse Ray", "Withdraw", "Defense Curl", "Barrier", "Light Screen", "Haze", "Reflect", "Focus Energy", "Bide", "Metronome", "Mirror Move", "Self-Destruct", "Egg Bomb", "Lick", "Smog", "Sludge", "Bone Club", "Fire Blast", "Waterfall", "Clamp", "Swift", "Skull Bash", "Spike Cannon", "Constrict", "Amnesia", "Kinesis", "Soft-Boiled", "High Jump Kick", "Glare", "Dream Eater", "Poison Gas", "Barrage", "Leech Life", "Lovely Kiss", "Sky Attack", "Transform", "Bubble", "Dizzy Punch", "Spore", "Flash", "Psywave", "Splash", "Acid Armor", "Crabhammer", "Explosion", "Fury Swipes", "Bonemerang", "Rest", "Rock Slide", "Hyper Fang", "Sharpen", "Conversion", "Tri Attack", "Super Fang", "Slash", "Substitute", "Struggle", "Sketch", "Triple Kick", "Thief", "Spider Web", "Mind Reader", "Nightmare", "Flame Wheel", "Snore", "Curse", "Flail", "Conversion 2", "Aeroblast", "Cotton Spore", "Reversal", "Spite", "Powder Snow", "Protect", "Mach Punch", "Scary Face", "Feint Attack", "Sweet Kiss", "Belly Drum", "Sludge Bomb", "Mud-Slap", "Octazooka", "Spikes", "Zap Cannon", "Foresight", "Destiny Bond", "Perish Song", "Icy Wind", "Detect", "Bone Rush", "Lock-On", "Outrage", "Sandstorm", "Giga Drain", "Endure", "Charm", "Rollout", "False Swipe", "Swagger", "Milk Drink", "Spark", "Fury Cutter", "Steel Wing", "Mean Look", "Attract", "Sleep Talk", "Heal Bell", "Return", "Present", "Frustration", "Safeguard", "Pain Split", "Sacred Fire", "Magnitude", "Dynamic Punch", "Megahorn", "Dragon Breath", "Baton Pass", "Encore", "Pursuit", "Rapid Spin", "Sweet Scent", "Iron Tail", "Metal Claw", "Vital Throw", "Morning Sun", "Synthesis", "Moonlight", "Hidden Power", "Cross Chop", "Twister", "Rain Dance", "Sunny Day", "Crunch", "Mirror Coat", "Psych Up", "Extreme Speed", "Ancient Power", "Shadow Ball", "Future Sight", "Rock Smash", "Whirlpool", "Beat Up", "Fake Out", "Uproar", "Stockpile", "Spit Up", "Swallow", "Heat Wave", "Hail", "Torment", "Flatter", "Will-O-Wisp", "Memento", "Facade", "Focus Punch", "Smelling Salts", "Follow Me", "Nature Power", "Charge", "Taunt", "Helping Hand", "Trick", "Role Play", "Wish", "Assist", "Ingrain", "Superpower", "Magic Coat", "Recycle", "Revenge", "Brick Break", "Yawn", "Knock Off", "Endeavor", "Eruption", "Skill Swap", "Imprison", "Refresh", "Grudge", "Snatch", "Secret Power", "Dive", "Arm Thrust", "Camouflage", "Tail Glow", "Luster Purge", "Mist Ball", "Feather Dance", "Teeter Dance", "Blaze Kick", "Mud Sport", "Ice Ball", "Needle Arm", "Slack Off", "Hyper Voice", "Poison Fang", "Crush Claw", "Blast Burn", "Hydro Cannon", "Meteor Mash", "Astonish", "Weather Ball", "Aromatherapy", "Fake Tears", "Air Cutter", "Overheat", "Odor Sleuth", "Rock Tomb", "Silver Wind", "Metal Sound", "Grass Whistle", "Tickle", "Cosmic Power", "Water Spout", "Signal Beam", "Shadow Punch", "Extrasensory", "Sky Uppercut", "Sand Tomb", "Sheer Cold", "Muddy Water", "Bullet Seed", "Aerial Ace", "Icicle Spear", "Iron Defense", "Block", "Howl", "Dragon Claw", "Frenzy Plant", "Bulk Up", "Bounce", "Mud Shot", "Poison Tail", "Covet", "Volt Tackle", "Magical Leaf", "Water Sport", "Calm Mind", "Leaf Blade", "Dragon Dance", "Rock Blast", "Shock Wave", "Water Pulse", "Doom Desire", "Psycho Boost", "Roost", "Gravity", "Miracle Eye", "Wake-Up Slap", "Hammer Arm", "Gyro Ball", "Healing Wish", "Brine", "Natural Gift", "Feint", "Pluck", "Tailwind", "Acupressure", "Metal Burst", "U-turn", "Close Combat", "Payback", "Assurance", "Embargo", "Fling", "Psycho Shift", "Trump Card", "Heal Block", "Wring Out", "Power Trick", "Gastro Acid", "Lucky Chant", "Me First", "Copycat", "Power Swap", "Guard Swap", "Punishment", "Last Resort", "Worry Seed", "Sucker Punch", "Toxic Spikes", "Heart Swap", "Aqua Ring", "Magnet Rise", "Flare Blitz", "Force Palm", "Aura Sphere", "Rock Polish", "Poison Jab", "Dark Pulse", "Night Slash", "Aqua Tail", "Seed Bomb", "Air Slash", "X-Scissor", "Bug Buzz", "Dragon Pulse", "Dragon Rush", "Power Gem", "Drain Punch", "Vacuum Wave", "Focus Blast", "Energy Ball", "Brave Bird", "Earth Power", "Switcheroo", "Giga Impact", "Nasty Plot", "Bullet Punch", "Avalanche", "Ice Shard", "Shadow Claw", "Thunder Fang", "Ice Fang", "Fire Fang", "Shadow Sneak", "Mud Bomb", "Psycho Cut", "Zen Headbutt", "Mirror Shot", "Flash Cannon", "Rock Climb", "Defog", "Trick Room", "Draco Meteor", "Discharge", "Lava Plume", "Leaf Storm", "Power Whip", "Rock Wrecker", "Cross Poison", "Gunk Shot", "Iron Head", "Magnet Bomb", "Stone Edge", "Captivate", "Stealth Rock", "Grass Knot", "Chatter", "Judgment", "Bug Bite", "Charge Beam", "Wood Hammer", "Aqua Jet", "Attack Order", "Defend Order", "Heal Order", "Head Smash", "Double Hit", "Roar of Time", "Spacial Rend", "Lunar Dance", "Crush Grip", "Magma Storm", "Dark Void", "Seed Flare", "Ominous Wind", "Shadow Force", "Hone Claws", "Wide Guard", "Guard Split", "Power Split", "Wonder Room", "Psyshock", "Venoshock", "Autotomize", "Rage Powder", "Telekinesis", "Magic Room", "Smack Down", "Storm Throw", "Flame Burst", "Sludge Wave", "Quiver Dance", "Heavy Slam", "Synchronoise", "Electro Ball", "Soak", "Flame Charge", "Coil", "Low Sweep", "Acid Spray", "Foul Play", "Simple Beam", "Entrainment", "After You", "Round", "Echoed Voice", "Chip Away", "Clear Smog", "Stored Power", "Quick Guard", "Ally Switch", "Scald", "Shell Smash", "Heal Pulse", "Hex", "Sky Drop", "Shift Gear", "Circle Throw", "Incinerate", "Quash", "Acrobatics", "Reflect Type", "Retaliate", "Final Gambit", "Bestow", "Inferno", "Water Pledge", "Fire Pledge", "Grass Pledge", "Volt Switch", "Struggle Bug", "Bulldoze", "Frost Breath", "Dragon Tail", "Work Up", "Electroweb", "Wild Charge", "Drill Run", "Dual Chop", "Heart Stamp", "Horn Leech", "Sacred Sword", "Razor Shell", "Heat Crash", "Leaf Tornado", "Steamroller", "Cotton Guard", "Night Daze", "Psystrike", "Tail Slap", "Hurricane", "Head Charge", "Gear Grind", "Searing Shot", "Techno Blast", "Relic Song", "Secret Sword", "Glaciate", "Bolt Strike", "Blue Flare", "Fiery Dance", "Freeze Shock", "Ice Burn", "Snarl", "Icicle Crash", "V-create", "Fusion Flare", "Fusion Bolt", "Flying Press", "Mat Block", "Belch", "Rototiller", "Sticky Web", "Fell Stinger", "Phantom Force", "Trick-or-Treat", "Noble Roar", "Ion Deluge", "Parabolic Charge", "Forest’s Curse", "Petal Blizzard", "Freeze-Dry", "Disarming Voice", "Parting Shot", "Topsy-Turvy", "Draining Kiss", "Crafty Shield", "Flower Shield", "Grassy Terrain", "Misty Terrain", "Electrify", "Play Rough", "Fairy Wind", "Moonblast", "Boomburst", "Fairy Lock", "King’s Shield", "Play Nice", "Confide", "Diamond Storm", "Steam Eruption", "Hyperspace Hole", "Water Shuriken", "Mystical Fire", "Spiky Shield", "Aromatic Mist", "Eerie Impulse", "Venom Drench", "Powder", "Geomancy", "Magnetic Flux", "Happy Hour", "Electric Terrain", "Dazzling Gleam", "Celebrate", "Hold Hands", "Baby-Doll Eyes", "Nuzzle", "Hold Back", "Infestation", "Power-Up Punch", "Oblivion Wing", "Thousand Arrows", "Thousand Waves", "Land’s Wrath", "Light of Ruin", "Origin Pulse", "Precipice Blades", "Dragon Ascent", "Hyperspace Fury", "Breakneck Blitz", "Breakneck Blitz", "All-Out Pummeling", "All-Out Pummeling", "Supersonic Skystrike", "Supersonic Skystrike", "Acid Downpour", "Acid Downpour", "Tectonic Rage", "Tectonic Rage", "Continental Crush", "Continental Crush", "Savage Spin-Out", "Savage Spin-Out", "Never-Ending Nightmare", "Never-Ending Nightmare", "Corkscrew Crash", "Corkscrew Crash", "Inferno Overdrive", "Inferno Overdrive", "Hydro Vortex", "Hydro Vortex", "Bloom Doom", "Bloom Doom", "Gigavolt Havoc", "Gigavolt Havoc", "Shattered Psyche", "Shattered Psyche", "Subzero Slammer", "Subzero Slammer", "Devastating Drake", "Devastating Drake", "Black Hole Eclipse", "Black Hole Eclipse", "Twinkle Tackle", "Twinkle Tackle", "Catastropika", "Shore Up", "First Impression", "Baneful Bunker", "Spirit Shackle", "Darkest Lariat", "Sparkling Aria", "Ice Hammer", "Floral Healing", "High Horsepower", "Strength Sap", "Solar Blade", "Leafage", "Spotlight", "Toxic Thread", "Laser Focus", "Gear Up", "Throat Chop", "Pollen Puff", "Anchor Shot", "Psychic Terrain", "Lunge", "Fire Lash", "Power Trip", "Burn Up", "Speed Swap", "Smart Strike", "Purify", "Revelation Dance", "Core Enforcer", "Trop Kick", "Instruct", "Beak Blast", "Clanging Scales", "Dragon Hammer", "Brutal Swing", "Aurora Veil", "Sinister Arrow Raid", "Malicious Moonsault", "Oceanic Operetta", "Guardian of Alola", "Soul-Stealing 7-Star Strike", "Stoked Sparksurfer", "Pulverizing Pancake", "Extreme Evoboost", "Genesis Supernova", "Shell Trap", "Fleur Cannon", "Psychic Fangs", "Stomping Tantrum", "Shadow Bone", "Accelerock", "Liquidation", "Prismatic Laser", "Spectral Thief", "Sunsteel Strike", "Moongeist Beam", "Tearful Look", "Zing Zap", "Nature’s Madness", "Multi-Attack", "10,000,000 Volt Thunderbolt"};
static char *movesSorted[] = {"None", "Absorb", "Accelerock", "Acid", "Acid Armor", "Acid Downpour", "Acid Downpour", "Acid Spray", "Acrobatics", "Acupressure", "Aerial Ace", "Aeroblast", "After You", "Agility", "Air Cutter", "Air Slash", "All-Out Pummeling", "All-Out Pummeling", "Ally Switch", "Amnesia", "Anchor Shot", "Ancient Power", "Aqua Jet", "Aqua Ring", "Aqua Tail", "Arm Thrust", "Aromatherapy", "Aromatic Mist", "Assist", "Assurance", "Astonish", "Attack Order", "Attract", "Aura Sphere", "Aurora Beam", "Aurora Veil", "Autotomize", "Avalanche", "Baby-Doll Eyes", "Baneful Bunker", "Barrage", "Barrier", "Baton Pass", "Beak Blast", "Beat Up", "Belch", "Belly Drum", "Bestow", "Bide", "Bind", "Bite", "Black Hole Eclipse", "Black Hole Eclipse", "Blast Burn", "Blaze Kick", "Blizzard", "Block", "Bloom Doom", "Bloom Doom", "Blue Flare", "Body Slam", "Bolt Strike", "Bone Club", "Bone Rush", "Bonemerang", "Boomburst", "Bounce", "Brave Bird", "Breakneck Blitz", "Breakneck Blitz", "Brick Break", "Brine", "Brutal Swing", "Bubble", "Bubble Beam", "Bug Bite", "Bug Buzz", "Bulk Up", "Bulldoze", "Bullet Punch", "Bullet Seed", "Burn Up", "Calm Mind", "Camouflage", "Captivate", "Catastropika", "Celebrate", "Charge", "Charge Beam", "Charm", "Chatter", "Chip Away", "Circle Throw", "Clamp", "Clanging Scales", "Clear Smog", "Close Combat", "Coil", "Comet Punch", "Confide", "Confuse Ray", "Confusion", "Constrict", "Continental Crush", "Continental Crush", "Conversion", "Conversion 2", "Copycat", "Core Enforcer", "Corkscrew Crash", "Corkscrew Crash", "Cosmic Power", "Cotton Guard", "Cotton Spore", "Counter", "Covet", "Crabhammer", "Crafty Shield", "Cross Chop", "Cross Poison", "Crunch", "Crush Claw", "Crush Grip", "Curse", "Cut", "Dark Pulse", "Dark Void", "Darkest Lariat", "Dazzling Gleam", "Defend Order", "Defense Curl", "Defog", "Destiny Bond", "Detect", "Devastating Drake", "Devastating Drake", "Diamond Storm", "Dig", "Disable", "Disarming Voice", "Discharge", "Dive", "Dizzy Punch", "Doom Desire", "Double Hit", "Double Kick", "Double Slap", "Double Team", "Double-Edge", "Draco Meteor", "Dragon Ascent", "Dragon Breath", "Dragon Claw", "Dragon Dance", "Dragon Hammer", "Dragon Pulse", "Dragon Rage", "Dragon Rush", "Dragon Tail", "Drain Punch", "Draining Kiss", "Dream Eater", "Drill Peck", "Drill Run", "Dual Chop", "Dynamic Punch", "Earth Power", "Earthquake", "Echoed Voice", "Eerie Impulse", "Egg Bomb", "Electric Terrain", "Electrify", "Electro Ball", "Electroweb", "Embargo", "Ember", "Encore", "Endeavor", "Endure", "Energy Ball", "Entrainment", "Eruption", "Explosion", "Extrasensory", "Extreme Evoboost", "Extreme Speed", "Facade", "Fairy Lock", "Fairy Wind", "Fake Out", "Fake Tears", "False Swipe", "Feather Dance", "Feint", "Feint Attack", "Fell Stinger", "Fiery Dance", "Final Gambit", "Fire Blast", "Fire Fang", "Fire Lash", "Fire Pledge", "Fire Punch", "Fire Spin", "First Impression", "Fissure", "Flail", "Flame Burst", "Flame Charge", "Flame Wheel", "Flamethrower", "Flare Blitz", "Flash", "Flash Cannon", "Flatter", "Fleur Cannon", "Fling", "Floral Healing", "Flower Shield", "Fly", "Flying Press", "Focus Blast", "Focus Energy", "Focus Punch", "Follow Me", "Force Palm", "Foresight", "Forest’s Curse", "Foul Play", "Freeze Shock", "Freeze-Dry", "Frenzy Plant", "Frost Breath", "Frustration", "Fury Attack", "Fury Cutter", "Fury Swipes", "Fusion Bolt", "Fusion Flare", "Future Sight", "Gastro Acid", "Gear Grind", "Gear Up", "Genesis Supernova", "Geomancy", "Giga Drain", "Giga Impact", "Gigavolt Havoc", "Gigavolt Havoc", "Glaciate", "Glare", "Grass Knot", "Grass Pledge", "Grass Whistle", "Grassy Terrain", "Gravity", "Growl", "Growth", "Grudge", "Guard Split", "Guard Swap", "Guardian of Alola", "Guillotine", "Gunk Shot", "Gust", "Gyro Ball", "Hail", "Hammer Arm", "Happy Hour", "Harden", "Haze", "Head Charge", "Head Smash", "Headbutt", "Heal Bell", "Heal Block", "Heal Order", "Heal Pulse", "Healing Wish", "Heart Stamp", "Heart Swap", "Heat Crash", "Heat Wave", "Heavy Slam", "Helping Hand", "Hex", "Hidden Power", "High Horsepower", "High Jump Kick", "Hold Back", "Hold Hands", "Hone Claws", "Horn Attack", "Horn Drill", "Horn Leech", "Howl", "Hurricane", "Hydro Cannon", "Hydro Pump", "Hydro Vortex", "Hydro Vortex", "Hyper Beam", "Hyper Fang", "Hyper Voice", "Hyperspace Fury", "Hyperspace Hole", "Hypnosis", "Ice Ball", "Ice Beam", "Ice Burn", "Ice Fang", "Ice Hammer", "Ice Punch", "Ice Shard", "Icicle Crash", "Icicle Spear", "Icy Wind", "Imprison", "Incinerate", "Inferno", "Inferno Overdrive", "Inferno Overdrive", "Infestation", "Ingrain", "Instruct", "Ion Deluge", "Iron Defense", "Iron Head", "Iron Tail", "Judgment", "Jump Kick", "Karate Chop", "Kinesis", "King’s Shield", "Knock Off", "Land’s Wrath", "Laser Focus", "Last Resort", "Lava Plume", "Leaf Blade", "Leaf Storm", "Leaf Tornado", "Leafage", "Leech Life", "Leech Seed", "Leer", "Lick", "Light Screen", "Light of Ruin", "Liquidation", "Lock-On", "Lovely Kiss", "Low Kick", "Low Sweep", "Lucky Chant", "Lunar Dance", "Lunge", "Luster Purge", "Mach Punch", "Magic Coat", "Magic Room", "Magical Leaf", "Magma Storm", "Magnet Bomb", "Magnet Rise", "Magnetic Flux", "Magnitude", "Malicious Moonsault", "Mat Block", "Me First", "Mean Look", "Meditate", "Mega Drain", "Mega Kick", "Mega Punch", "Megahorn", "Memento", "Metal Burst", "Metal Claw", "Metal Sound", "Meteor Mash", "Metronome", "Milk Drink", "Mimic", "Mind Reader", "Minimize", "Miracle Eye", "Mirror Coat", "Mirror Move", "Mirror Shot", "Mist", "Mist Ball", "Misty Terrain", "Moonblast", "Moongeist Beam", "Moonlight", "Morning Sun", "Mud Bomb", "Mud Shot", "Mud Sport", "Mud-Slap", "Muddy Water", "Multi-Attack", "Mystical Fire", "Nasty Plot", "Natural Gift", "Nature Power", "Nature’s Madness", "Needle Arm", "Never-Ending Nightmare", "Never-Ending Nightmare", "Night Daze", "Night Shade", "Night Slash", "Nightmare", "Noble Roar", "Nuzzle", "Oblivion Wing", "Oceanic Operetta", "Octazooka", "Odor Sleuth", "Ominous Wind", "Origin Pulse", "Outrage", "Overheat", "Pain Split", "Parabolic Charge", "Parting Shot", "Pay Day", "Payback", "Peck", "Perish Song", "Petal Blizzard", "Petal Dance", "Phantom Force", "Pin Missile", "Play Nice", "Play Rough", "Pluck", "Poison Fang", "Poison Gas", "Poison Jab", "Poison Powder", "Poison Sting", "Poison Tail", "Pollen Puff", "Pound", "Powder", "Powder Snow", "Power Gem", "Power Split", "Power Swap", "Power Trick", "Power Trip", "Power Whip", "Power-Up Punch", "Precipice Blades", "Present", "Prismatic Laser", "Protect", "Psybeam", "Psych Up", "Psychic", "Psychic Fangs", "Psychic Terrain", "Psycho Boost", "Psycho Cut", "Psycho Shift", "Psyshock", "Psystrike", "Psywave", "Pulverizing Pancake", "Punishment", "Purify", "Pursuit", "Quash", "Quick Attack", "Quick Guard", "Quiver Dance", "Rage", "Rage Powder", "Rain Dance", "Rapid Spin", "Razor Leaf", "Razor Shell", "Razor Wind", "Recover", "Recycle", "Reflect", "Reflect Type", "Refresh", "Relic Song", "Rest", "Retaliate", "Return", "Revelation Dance", "Revenge", "Reversal", "Roar", "Roar of Time", "Rock Blast", "Rock Climb", "Rock Polish", "Rock Slide", "Rock Smash", "Rock Throw", "Rock Tomb", "Rock Wrecker", "Role Play", "Rolling Kick", "Rollout", "Roost", "Rototiller", "Round", "Sacred Fire", "Sacred Sword", "Safeguard", "Sand Attack", "Sand Tomb", "Sandstorm", "Savage Spin-Out", "Savage Spin-Out", "Scald", "Scary Face", "Scratch", "Screech", "Searing Shot", "Secret Power", "Secret Sword", "Seed Bomb", "Seed Flare", "Seismic Toss", "Self-Destruct", "Shadow Ball", "Shadow Bone", "Shadow Claw", "Shadow Force", "Shadow Punch", "Shadow Sneak", "Sharpen", "Shattered Psyche", "Shattered Psyche", "Sheer Cold", "Shell Smash", "Shell Trap", "Shift Gear", "Shock Wave", "Shore Up", "Signal Beam", "Silver Wind", "Simple Beam", "Sing", "Sinister Arrow Raid", "Sketch", "Skill Swap", "Skull Bash", "Sky Attack", "Sky Drop", "Sky Uppercut", "Slack Off", "Slam", "Slash", "Sleep Powder", "Sleep Talk", "Sludge", "Sludge Bomb", "Sludge Wave", "Smack Down", "Smart Strike", "Smelling Salts", "Smog", "Smokescreen", "Snarl", "Snatch", "Snore", "Soak", "Soft-Boiled", "Solar Beam", "Solar Blade", "Sonic Boom", "Soul-Stealing 7-Star Strike", "Spacial Rend", "Spark", "Sparkling Aria", "Spectral Thief", "Speed Swap", "Spider Web", "Spike Cannon", "Spikes", "Spiky Shield", "Spirit Shackle", "Spit Up", "Spite", "Splash", "Spore", "Spotlight", "Stealth Rock", "Steam Eruption", "Steamroller", "Steel Wing", "Sticky Web", "Stockpile", "Stoked Sparksurfer", "Stomp", "Stomping Tantrum", "Stone Edge", "Stored Power", "Storm Throw", "Strength", "Strength Sap", "String Shot", "Struggle", "Struggle Bug", "Stun Spore", "Submission", "Substitute", "Subzero Slammer", "Subzero Slammer", "Sucker Punch", "Sunny Day", "Sunsteel Strike", "Super Fang", "Superpower", "Supersonic", "Supersonic Skystrike", "Supersonic Skystrike", "Surf", "Swagger", "Swallow", "Sweet Kiss", "Sweet Scent", "Swift", "Switcheroo", "Swords Dance", "Synchronoise", "Synthesis", "Tackle", "Tail Glow", "Tail Slap", "Tail Whip", "Tailwind", "Take Down", "Taunt", "Tearful Look", "Techno Blast", "Tectonic Rage", "Tectonic Rage", "Teeter Dance", "Telekinesis", "Teleport", "Thief", "Thousand Arrows", "Thousand Waves", "Thrash", "Throat Chop", "Thunder", "Thunder Fang", "Thunder Punch", "Thunder Shock", "Thunder Wave", "Thunderbolt", "Tickle", "Topsy-Turvy", "Torment", "Toxic", "Toxic Spikes", "Toxic Thread", "Transform", "Tri Attack", "Trick", "Trick Room", "Trick-or-Treat", "Triple Kick", "Trop Kick", "Trump Card", "Twineedle", "Twinkle Tackle", "Twinkle Tackle", "Twister", "U-turn", "Uproar", "V-create", "Vacuum Wave", "Venom Drench", "Venoshock", "Vice Grip", "Vine Whip", "Vital Throw", "Volt Switch", "Volt Tackle", "Wake-Up Slap", "Water Gun", "Water Pledge", "Water Pulse", "Water Shuriken", "Water Sport", "Water Spout", "Waterfall", "Weather Ball", "Whirlpool", "Whirlwind", "Wide Guard", "Wild Charge", "Will-O-Wisp", "Wing Attack", "Wish", "Withdraw", "Wonder Room", "Wood Hammer", "Work Up", "Worry Seed", "Wrap", "Wring Out", "X-Scissor", "Yawn", "Zap Cannon", "Zen Headbutt", "Zing Zap", "10,000,000 Volt Thunderbolt"};
static char *pokemon[] = {"Egg", "Bulbasaur", "Ivysaur", "Venusaur", "Charmander", "Charmeleon", "Charizard", "Squirtle", "Wartortle", "Blastoise", "Caterpie", "Metapod", "Butterfree", "Weedle", "Kakuna", "Beedrill", "Pidgey", "Pidgeotto", "Pidgeot", "Rattata", "Raticate", "Spearow", "Fearow", "Ekans", "Arbok", "Pikachu", "Raichu", "Sandshrew", "Sandslash", "Nidoran♀", "Nidorina", "Nidoqueen", "Nidoran♂", "Nidorino", "Nidoking", "Clefairy", "Clefable", "Vulpix", "Ninetales", "Jigglypuff", "Wigglytuff", "Zubat", "Golbat", "Oddish", "Gloom", "Vileplume", "Paras", "Parasect", "Venonat", "Venomoth", "Diglett", "Dugtrio", "Meowth", "Persian", "Psyduck", "Golduck", "Mankey", "Primeape", "Growlithe", "Arcanine", "Poliwag", "Poliwhirl", "Poliwrath", "Abra", "Kadabra", "Alakazam", "Machop", "Machoke", "Machamp", "Bellsprout", "Weepinbell", "Victreebel", "Tentacool", "Tentacruel", "Geodude", "Graveler", "Golem", "Ponyta", "Rapidash", "Slowpoke", "Slowbro", "Magnemite", "Magneton", "Farfetch’d", "Doduo", "Dodrio", "Seel", "Dewgong", "Grimer", "Muk", "Shellder", "Cloyster", "Gastly", "Haunter", "Gengar", "Onix", "Drowzee", "Hypno", "Krabby", "Kingler", "Voltorb", "Electrode", "Exeggcute", "Exeggutor", "Cubone", "Marowak", "Hitmonlee", "Hitmonchan", "Lickitung", "Koffing", "Weezing", "Rhyhorn", "Rhydon", "Chansey", "Tangela", "Kangaskhan", "Horsea", "Seadra", "Goldeen", "Seaking", "Staryu", "Starmie", "Mr. Mime", "Scyther", "Jynx", "Electabuzz", "Magmar", "Pinsir", "Tauros", "Magikarp", "Gyarados", "Lapras", "Ditto", "Eevee", "Vaporeon", "Jolteon", "Flareon", "Porygon", "Omanyte", "Omastar", "Kabuto", "Kabutops", "Aerodactyl", "Snorlax", "Articuno", "Zapdos", "Moltres", "Dratini", "Dragonair", "Dragonite", "Mewtwo", "Mew", "Chikorita", "Bayleef", "Meganium", "Cyndaquil", "Quilava", "Typhlosion", "Totodile", "Croconaw", "Feraligatr", "Sentret", "Furret", "Hoothoot", "Noctowl", "Ledyba", "Ledian", "Spinarak", "Ariados", "Crobat", "Chinchou", "Lanturn", "Pichu", "Cleffa", "Igglybuff", "Togepi", "Togetic", "Natu", "Xatu", "Mareep", "Flaaffy", "Ampharos", "Bellossom", "Marill", "Azumarill", "Sudowoodo", "Politoed", "Hoppip", "Skiploom", "Jumpluff", "Aipom", "Sunkern", "Sunflora", "Yanma", "Wooper", "Quagsire", "Espeon", "Umbreon", "Murkrow", "Slowking", "Misdreavus", "Unown", "Wobbuffet", "Girafarig", "Pineco", "Forretress", "Dunsparce", "Gligar", "Steelix", "Snubbull", "Granbull", "Qwilfish", "Scizor", "Shuckle", "Heracross", "Sneasel", "Teddiursa", "Ursaring", "Slugma", "Magcargo", "Swinub", "Piloswine", "Corsola", "Remoraid", "Octillery", "Delibird", "Mantine", "Skarmory", "Houndour", "Houndoom", "Kingdra", "Phanpy", "Donphan", "Porygon2", "Stantler", "Smeargle", "Tyrogue", "Hitmontop", "Smoochum", "Elekid", "Magby", "Miltank", "Blissey", "Raikou", "Entei", "Suicune", "Larvitar", "Pupitar", "Tyranitar", "Lugia", "Ho-Oh", "Celebi", "Treecko", "Grovyle", "Sceptile", "Torchic", "Combusken", "Blaziken", "Mudkip", "Marshtomp", "Swampert", "Poochyena", "Mightyena", "Zigzagoon", "Linoone", "Wurmple", "Silcoon", "Beautifly", "Cascoon", "Dustox", "Lotad", "Lombre", "Ludicolo", "Seedot", "Nuzleaf", "Shiftry", "Taillow", "Swellow", "Wingull", "Pelipper", "Ralts", "Kirlia", "Gardevoir", "Surskit", "Masquerain", "Shroomish", "Breloom", "Slakoth", "Vigoroth", "Slaking", "Nincada", "Ninjask", "Shedinja", "Whismur", "Loudred", "Exploud", "Makuhita", "Hariyama", "Azurill", "Nosepass", "Skitty", "Delcatty", "Sableye", "Mawile", "Aron", "Lairon", "Aggron", "Meditite", "Medicham", "Electrike", "Manectric", "Plusle", "Minun", "Volbeat", "Illumise", "Roselia", "Gulpin", "Swalot", "Carvanha", "Sharpedo", "Wailmer", "Wailord", "Numel", "Camerupt", "Torkoal", "Spoink", "Grumpig", "Spinda", "Trapinch", "Vibrava", "Flygon", "Cacnea", "Cacturne", "Swablu", "Altaria", "Zangoose", "Seviper", "Lunatone", "Solrock", "Barboach", "Whiscash", "Corphish", "Crawdaunt", "Baltoy", "Claydol", "Lileep", "Cradily", "Anorith", "Armaldo", "Feebas", "Milotic", "Castform", "Kecleon", "Shuppet", "Banette", "Duskull", "Dusclops", "Tropius", "Chimecho", "Absol", "Wynaut", "Snorunt", "Glalie", "Spheal", "Sealeo", "Walrein", "Clamperl", "Huntail", "Gorebyss", "Relicanth", "Luvdisc", "Bagon", "Shelgon", "Salamence", "Beldum", "Metang", "Metagross", "Regirock", "Regice", "Registeel", "Latias", "Latios", "Kyogre", "Groudon", "Rayquaza", "Jirachi", "Deoxys", "Turtwig", "Grotle", "Torterra", "Chimchar", "Monferno", "Infernape", "Piplup", "Prinplup", "Empoleon", "Starly", "Staravia", "Staraptor", "Bidoof", "Bibarel", "Kricketot", "Kricketune", "Shinx", "Luxio", "Luxray", "Budew", "Roserade", "Cranidos", "Rampardos", "Shieldon", "Bastiodon", "Burmy", "Wormadam", "Mothim", "Combee", "Vespiquen", "Pachirisu", "Buizel", "Floatzel", "Cherubi", "Cherrim", "Shellos", "Gastrodon", "Ambipom", "Drifloon", "Drifblim", "Buneary", "Lopunny", "Mismagius", "Honchkrow", "Glameow", "Purugly", "Chingling", "Stunky", "Skuntank", "Bronzor", "Bronzong", "Bonsly", "Mime Jr.", "Happiny", "Chatot", "Spiritomb", "Gible", "Gabite", "Garchomp", "Munchlax", "Riolu", "Lucario", "Hippopotas", "Hippowdon", "Skorupi", "Drapion", "Croagunk", "Toxicroak", "Carnivine", "Finneon", "Lumineon", "Mantyke", "Snover", "Abomasnow", "Weavile", "Magnezone", "Lickilicky", "Rhyperior", "Tangrowth", "Electivire", "Magmortar", "Togekiss", "Yanmega", "Leafeon", "Glaceon", "Gliscor", "Mamoswine", "Porygon-Z", "Gallade", "Probopass", "Dusknoir", "Froslass", "Rotom", "Uxie", "Mesprit", "Azelf", "Dialga", "Palkia", "Heatran", "Regigigas", "Giratina", "Cresselia", "Phione", "Manaphy", "Darkrai", "Shaymin", "Arceus", "Victini", "Snivy", "Servine", "Serperior", "Tepig", "Pignite", "Emboar", "Oshawott", "Dewott", "Samurott", "Patrat", "Watchog", "Lillipup", "Herdier", "Stoutland", "Purrloin", "Liepard", "Pansage", "Simisage", "Pansear", "Simisear", "Panpour", "Simipour", "Munna", "Musharna", "Pidove", "Tranquill", "Unfezant", "Blitzle", "Zebstrika", "Roggenrola", "Boldore", "Gigalith", "Woobat", "Swoobat", "Drilbur", "Excadrill", "Audino", "Timburr", "Gurdurr", "Conkeldurr", "Tympole", "Palpitoad", "Seismitoad", "Throh", "Sawk", "Sewaddle", "Swadloon", "Leavanny", "Venipede", "Whirlipede", "Scolipede", "Cottonee", "Whimsicott", "Petilil", "Lilligant", "Basculin", "Sandile", "Krokorok", "Krookodile", "Darumaka", "Darmanitan", "Maractus", "Dwebble", "Crustle", "Scraggy", "Scrafty", "Sigilyph", "Yamask", "Cofagrigus", "Tirtouga", "Carracosta", "Archen", "Archeops", "Trubbish", "Garbodor", "Zorua", "Zoroark", "Minccino", "Cinccino", "Gothita", "Gothorita", "Gothitelle", "Solosis", "Duosion", "Reuniclus", "Ducklett", "Swanna", "Vanillite", "Vanillish", "Vanilluxe", "Deerling", "Sawsbuck", "Emolga", "Karrablast", "Escavalier", "Foongus", "Amoonguss", "Frillish", "Jellicent", "Alomomola", "Joltik", "Galvantula", "Ferroseed", "Ferrothorn", "Klink", "Klang", "Klinklang", "Tynamo", "Eelektrik", "Eelektross", "Elgyem", "Beheeyem", "Litwick", "Lampent", "Chandelure", "Axew", "Fraxure", "Haxorus", "Cubchoo", "Beartic", "Cryogonal", "Shelmet", "Accelgor", "Stunfisk", "Mienfoo", "Mienshao", "Druddigon", "Golett", "Golurk", "Pawniard", "Bisharp", "Bouffalant", "Rufflet", "Braviary", "Vullaby", "Mandibuzz", "Heatmor", "Durant", "Deino", "Zweilous", "Hydreigon", "Larvesta", "Volcarona", "Cobalion", "Terrakion", "Virizion", "Tornadus", "Thundurus", "Reshiram", "Zekrom", "Landorus", "Kyurem", "Keldeo", "Meloetta", "Genesect", "Chespin", "Quilladin", "Chesnaught", "Fennekin", "Braixen", "Delphox", "Froakie", "Frogadier", "Greninja", "Bunnelby", "Diggersby", "Fletchling", "Fletchinder", "Talonflame", "Scatterbug", "Spewpa", "Vivillon", "Litleo", "Pyroar", "Flabébé", "Floette", "Florges", "Skiddo", "Gogoat", "Pancham", "Pangoro", "Furfrou", "Espurr", "Meowstic", "Honedge", "Doublade", "Aegislash", "Spritzee", "Aromatisse", "Swirlix", "Slurpuff", "Inkay", "Malamar", "Binacle", "Barbaracle", "Skrelp", "Dragalge", "Clauncher", "Clawitzer", "Helioptile", "Heliolisk", "Tyrunt", "Tyrantrum", "Amaura", "Aurorus", "Sylveon", "Hawlucha", "Dedenne", "Carbink", "Goomy", "Sliggoo", "Goodra", "Klefki", "Phantump", "Trevenant", "Pumpkaboo", "Gourgeist", "Bergmite", "Avalugg", "Noibat", "Noivern", "Xerneas", "Yveltal", "Zygarde", "Diancie", "Hoopa", "Volcanion", "Rowlet", "Dartrix", "Decidueye", "Litten", "Torracat", "Incineroar", "Popplio", "Brionne", "Primarina", "Pikipek", "Trumbeak", "Toucannon", "Yungoos", "Gumshoos", "Grubbin", "Charjabug", "Vikavolt", "Crabrawler", "Crabominable", "Oricorio", "Cutiefly", "Ribombee", "Rockruff", "Lycanroc", "Wishiwashi", "Mareanie", "Toxapex", "Mudbray", "Mudsdale", "Dewpider", "Araquanid", "Fomantis", "Lurantis", "Morelull", "Shiinotic", "Salandit", "Salazzle", "Stufful", "Bewear", "Bounsweet", "Steenee", "Tsareena", "Comfey", "Oranguru", "Passimian", "Wimpod", "Golisopod", "Sandygast", "Palossand", "Pyukumuku", "Type: Null", "Silvally", "Minior", "Komala", "Turtonator", "Togedemaru", "Mimikyu", "Bruxish", "Drampa", "Dhelmise", "Jangmo-o", "Hakamo-o", "Kommo-o", "Tapu Koko", "Tapu Lele", "Tapu Bulu", "Tapu Fini", "Cosmog", "Cosmoem", "Solgaleo", "Lunala", "Nihilego", "Buzzwole", "Pheromosa", "Xurkitree", "Celesteela", "Kartana", "Guzzlord", "Necrozma", "Magearna", "Marshadow"};
static char *natures[] = {"Hardy", "Lonely", "Brave", "Adamant", "Naughty", "Bold", "Docile", "Relaxed", "Impish", "Lax", "Timid", "Hasty", "Serious", "Jolly", "Naive", "Modest", "Mild", "Quiet", "Bashful", "Rash", "Calm", "Gentle", "Sassy", "Careful", "Quirky"};
static char *items[] = {"None", "Master Ball", "Ultra Ball", "Great Ball", "Poke Ball", "Safari Ball", "Net Ball", "Dive Ball", "Nest Ball", "Repeat Ball", "Timer Ball", "Luxury Ball", "Premier Ball", "Dusk Ball", "Heal Ball", "Quick Ball", "Cherish Ball", "Potion", "Antidote", "Burn Heal", "Ice Heal", "Awakening", "Paralyze Heal", "Full Restore", "Max Potion", "Hyper Potion", "Super Potion", "Full Heal", "Revive", "Max Revive", "Fresh Water", "Soda Pop", "Lemonade", "Moomoo Milk", "Energy Powder", "Energy Root", "Heal Powder", "Revival Herb", "Ether", "Max Ether", "Elixir", "Max Elixir", "Lava Cookie", "Berry Juice", "Sacred Ash", "HP Up", "Protein", "Iron", "Carbos", "Calcium", "Rare Candy", "PP Up", "Zinc", "PP Max", "Old Gateau", "Guard Spec.", "Dire Hit", "X Attack", "X Defense", "X Speed", "X Accuracy", "X Sp. Atk", "X Sp. Def", "Poké Doll", "Fluffy Tail", "Blue Flute", "Yellow Flute", "Red Flute", "Black Flute", "White Flute", "Shoal Salt", "Shoal Shell", "Red Shard", "Blue Shard", "Yellow Shard", "Green Shard", "Super Repel", "Max Repel", "Escape Rope", "Repel", "Sun Stone", "Moon Stone", "Fire Stone", "Thunder Stone", "Water Stone", "Leaf Stone", "Tiny Mushroom", "Big Mushroom", "Pearl", "Big Pearl", "Stardust", "Star Piece", "Nugget", "Heart Scale", "Honey", "Growth Mulch", "Damp Mulch", "Stable Mulch", "Gooey Mulch", "Root Fossil", "Claw Fossil", "Helix Fossil", "Dome Fossil", "Old Amber", "Armor Fossil", "Skull Fossil", "Rare Bone", "Shiny Stone", "Dusk Stone", "Dawn Stone", "Oval Stone", "Odd Keystone", "Griseous Orb", "???", "???", "???", "Douse Drive", "Shock Drive", "Burn Drive", "Chill Drive", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "Sweet Heart", "Adamant Orb", "Lustrous Orb", "Greet Mail", "Favored Mail", "RSVP Mail", "Thanks Mail", "Inquiry Mail", "Like Mail", "Reply Mail", "Bridge Mail S", "Bridge Mail D", "Bridge Mail T", "Bridge Mail V", "Bridge Mail M", "Cheri Berry", "Chesto Berry", "Pecha Berry", "Rawst Berry", "Aspear Berry", "Leppa Berry", "Oran Berry", "Persim Berry", "Lum Berry", "Sitrus Berry", "Figy Berry", "Wiki Berry", "Mago Berry", "Aguav Berry", "Iapapa Berry", "Razz Berry", "Bluk Berry", "Nanab Berry", "Wepear Berry", "Pinap Berry", "Pomeg Berry", "Kelpsy Berry", "Qualot Berry", "Hondew Berry", "Grepa Berry", "Tamato Berry", "Cornn Berry", "Magost Berry", "Rabuta Berry", "Nomel Berry", "Spelon Berry", "Pamtre Berry", "Watmel Berry", "Durin Berry", "Belue Berry", "Occa Berry", "Passho Berry", "Wacan Berry", "Rindo Berry", "Yache Berry", "Chople Berry", "Kebia Berry", "Shuca Berry", "Coba Berry", "Payapa Berry", "Tanga Berry", "Charti Berry", "Kasib Berry", "Haban Berry", "Colbur Berry", "Babiri Berry", "Chilan Berry", "Liechi Berry", "Ganlon Berry", "Salac Berry", "Petaya Berry", "Apicot Berry", "Lansat Berry", "Starf Berry", "Enigma Berry", "Micle Berry", "Custap Berry", "Jaboca Berry", "Rowap Berry", "Bright Powder", "White Herb", "Macho Brace", "Exp. Share", "Quick Claw", "Soothe Bell", "Mental Herb", "Choice Band", "King’s Rock", "Silver Powder", "Amulet Coin", "Cleanse Tag", "Soul Dew", "Deep Sea Tooth", "Deep Sea Scale", "Smoke Ball", "Everstone", "Focus Band", "Lucky Egg", "Scope Lens", "Metal Coat", "Leftovers", "Dragon Scale", "Light Ball", "Soft Sand", "Hard Stone", "Miracle Seed", "Black Glasses", "Black Belt", "Magnet", "Mystic Water", "Sharp Beak", "Poison Barb", "Never-Melt Ice", "Spell Tag", "Twisted Spoon", "Charcoal", "Dragon Fang", "Silk Scarf", "Up-Grade", "Shell Bell", "Sea Incense", "Lax Incense", "Lucky Punch", "Metal Powder", "Thick Club", "Stick", "Red Scarf", "Blue Scarf", "Pink Scarf", "Green Scarf", "Yellow Scarf", "Wide Lens", "Muscle Band", "Wise Glasses", "Expert Belt", "Light Clay", "Life Orb", "Power Herb", "Toxic Orb", "Flame Orb", "Quick Powder", "Focus Sash", "Zoom Lens", "Metronome", "Iron Ball", "Lagging Tail", "Destiny Knot", "Black Sludge", "Icy Rock", "Smooth Rock", "Heat Rock", "Damp Rock", "Grip Claw", "Choice Scarf", "Sticky Barb", "Power Bracer", "Power Belt", "Power Lens", "Power Band", "Power Anklet", "Power Weight", "Shed Shell", "Big Root", "Choice Specs", "Flame Plate", "Splash Plate", "Zap Plate", "Meadow Plate", "Icicle Plate", "Fist Plate", "Toxic Plate", "Earth Plate", "Sky Plate", "Mind Plate", "Insect Plate", "Stone Plate", "Spooky Plate", "Draco Plate", "Dread Plate", "Iron Plate", "Odd Incense", "Rock Incense", "Full Incense", "Wave Incense", "Rose Incense", "Luck Incense", "Pure Incense", "Protector", "Electirizer", "Magmarizer", "Dubious Disc", "Reaper Cloth", "Razor Claw", "Razor Fang", "TM01", "TM02", "TM03", "TM04", "TM05", "TM06", "TM07", "TM08", "TM09", "TM10", "TM11", "TM12", "TM13", "TM14", "TM15", "TM16", "TM17", "TM18", "TM19", "TM20", "TM21", "TM22", "TM23", "TM24", "TM25", "TM26", "TM27", "TM28", "TM29", "TM30", "TM31", "TM32", "TM33", "TM34", "TM35", "TM36", "TM37", "TM38", "TM39", "TM40", "TM41", "TM42", "TM43", "TM44", "TM45", "TM46", "TM47", "TM48", "TM49", "TM50", "TM51", "TM52", "TM53", "TM54", "TM55", "TM56", "TM57", "TM58", "TM59", "TM60", "TM61", "TM62", "TM63", "TM64", "TM65", "TM66", "TM67", "TM68", "TM69", "TM70", "TM71", "TM72", "TM73", "TM74", "TM75", "TM76", "TM77", "TM78", "TM79", "TM80", "TM81", "TM82", "TM83", "TM84", "TM85", "TM86", "TM87", "TM88", "TM89", "TM90", "TM91", "TM92", "HM01", "HM02", "HM03", "HM04", "HM05", "HM06", "???", "???", "Explorer Kit", "Loot Sack", "Rule Book", "Poké Radar", "Point Card", "Journal", "Seal Case", "Fashion Case", "Seal Bag", "Pal Pad", "Works Key", "Old Charm", "Galactic Key", "Red Chain", "Town Map", "Vs. Seeker", "Coin Case", "Old Rod", "Good Rod", "Super Rod", "Sprayduck", "Poffin Case", "Bike", "Suite Key", "Oak’s Letter", "Lunar Wing", "Member Card", "Azure Flute", "S.S. Ticket", "Contest Pass", "Magma Stone", "Parcel", "Coupon 1", "Coupon 2", "Coupon 3", "Storage Key", "Secret Potion", "Vs. Recorder", "Gracidea", "Secret Key", "Apricorn Box", "Unown Report", "Berry Pots", "Dowsing Machine", "Blue Card", "Slowpoke Tail", "Clear Bell", "Card Key", "Basement Key", "Squirt Bottle", "Red Scale", "Lost Item", "Pass", "Machine Part", "Silver Wing", "Rainbow Wing", "Mystery Egg", "Red Apricorn", "Blue Apricorn", "Yellow Apricorn", "Green Apricorn", "Pink Apricorn", "White Apricorn", "Black Apricorn", "Fast Ball", "Level Ball", "Lure Ball", "Heavy Ball", "Love Ball", "Friend Ball", "Moon Ball", "Sport Ball", "Park Ball", "Photo Album", "GB Sounds", "Tidal Bell", "Rage Candy Bar", "Data Card 01", "Data Card 02", "Data Card 03", "Data Card 04", "Data Card 05", "Data Card 06", "Data Card 07", "Data Card 08", "Data Card 09", "Data Card 10", "Data Card 11", "Data Card 12", "Data Card 13", "Data Card 14", "Data Card 15", "Data Card 16", "Data Card 17", "Data Card 18", "Data Card 19", "Data Card 20", "Data Card 21", "Data Card 22", "Data Card 23", "Data Card 24", "Data Card 25", "Data Card 26", "Data Card 27", "Jade Orb", "Lock Capsule", "Red Orb", "Blue Orb", "Enigma Stone", "Prism Scale", "Eviolite", "Float Stone", "Rocky Helmet", "Air Balloon", "Red Card", "Ring Target", "Binding Band", "Absorb Bulb", "Cell Battery", "Eject Button", "Fire Gem", "Water Gem", "Electric Gem", "Grass Gem", "Ice Gem", "Fighting Gem", "Poison Gem", "Ground Gem", "Flying Gem", "Psychic Gem", "Bug Gem", "Rock Gem", "Ghost Gem", "Dragon Gem", "Dark Gem", "Steel Gem", "Normal Gem", "Health Wing", "Muscle Wing", "Resist Wing", "Genius Wing", "Clever Wing", "Swift Wing", "Pretty Wing", "Cover Fossil", "Plume Fossil", "Liberty Pass", "Pass Orb", "Dream Ball", "Poké Toy", "Prop Case", "Dragon Skull", "Balm Mushroom", "Big Nugget", "Pearl String", "Comet Shard", "Relic Copper", "Relic Silver", "Relic Gold", "Relic Vase", "Relic Band", "Relic Statue", "Relic Crown", "Casteliacone", "Dire Hit 2", "X Speed 2", "X Sp. Atk 2", "X Sp. Def 2", "X Defense 2", "X Attack 2", "X Accuracy 2", "X Speed 3", "X Sp. Atk 3", "X Sp. Def 3", "X Defense 3", "X Attack 3", "X Accuracy 3", "X Speed 6", "X Sp. Atk 6", "X Sp. Def 6", "X Defense 6", "X Attack 6", "X Accuracy 6", "Ability Urge", "Item Drop", "Item Urge", "Reset Urge", "Dire Hit 3", "Light Stone", "Dark Stone", "TM93", "TM94", "TM95", "Xtransceiver", "???", "Gram 1", "Gram 2", "Gram 3", "Xtransceiver", "Medal Box", "DNA Splicers", "DNA Splicers", "Permit", "Oval Charm", "Shiny Charm", "Plasma Card", "Grubby Hanky", "Colress Machine", "Dropped Item", "Dropped Item", "Reveal Glass", "Weakness Policy", "Assault Vest", "Holo Caster", "Prof’s Letter", "Roller Skates", "Pixie Plate", "Ability Capsule", "Whipped Dream", "Sachet", "Luminous Moss", "Snowball", "Safety Goggles", "Poké Flute", "Rich Mulch", "Surprise Mulch", "Boost Mulch", "Amaze Mulch", "Gengarite", "Gardevoirite", "Ampharosite", "Venusaurite", "Charizardite X", "Blastoisinite", "Mewtwonite X", "Mewtwonite Y", "Blazikenite", "Medichamite", "Houndoominite", "Aggronite", "Banettite", "Tyranitarite", "Scizorite", "Pinsirite", "Aerodactylite", "Lucarionite", "Abomasite", "Kangaskhanite", "Gyaradosite", "Absolite", "Charizardite Y", "Alakazite", "Heracronite", "Mawilite", "Manectite", "Garchompite", "Latiasite", "Latiosite", "Roseli Berry", "Kee Berry", "Maranga Berry", "Sprinklotad", "TM96", "TM97", "TM98", "TM99", "TM100", "Power Plant Pass", "Mega Ring", "Intriguing Stone", "Common Stone", "Discount Coupon", "Elevator Key", "TMV Pass", "Honor of Kalos", "Adventure Rules", "Strange Souvenir", "Lens Case", "Makeup Bag", "Travel Trunk", "Lumiose Galette", "Shalour Sable", "Jaw Fossil", "Sail Fossil", "Looker Ticket", "Bike", "Holo Caster", "Fairy Gem", "Mega Charm", "Mega Glove", "Mach Bike", "Acro Bike", "Wailmer Pail", "Devon Parts", "Soot Sack", "Basement Key", "Pokéblock Kit", "Letter", "Eon Ticket", "Scanner", "Go-Goggles", "Meteorite", "Key to Room 1", "Key to Room 2", "Key to Room 4", "Key to Room 6", "Storage Key", "Devon Scope", "S.S. Ticket", "HM07", "Devon Scuba Gear", "Contest Costume", "Contest Costume", "Magma Suit", "Aqua Suit", "Pair of Tickets", "Mega Bracelet", "Mega Pendant", "Mega Glasses", "Mega Anchor", "Mega Stickpin", "Mega Tiara", "Mega Anklet", "Meteorite", "Swampertite", "Sceptilite", "Sablenite", "Altarianite", "Galladite", "Audinite", "Metagrossite", "Sharpedonite", "Slowbronite", "Steelixite", "Pidgeotite", "Glalitite", "Diancite", "Prison Bottle", "Mega Cuff", "Cameruptite", "Lopunnite", "Salamencite", "Beedrillite", "Meteorite", "Meteorite", "Key Stone", "Meteorite Shard", "Eon Flute", "Normalium Z", "Firium Z", "Waterium Z", "Electrium Z", "Grassium Z", "Icium Z", "Fightinium Z", "Poisonium Z", "Groundium Z", "Flyinium Z", "Psychium Z", "Buginium Z", "Rockium Z", "Ghostium Z", "Dragonium Z", "Darkinium Z", "Steelium Z", "Fairium Z", "Pikanium Z", "Bottle Cap", "Gold Bottle Cap", "Z-Ring", "Decidium Z", "Incinium Z", "Primarium Z", "Tapunium Z", "Marshadium Z", "Aloraichium Z", "Snorlium Z", "Eevium Z", "Mewnium Z", "Normalium Z", "Firium Z", "Waterium Z", "Electrium Z", "Grassium Z", "Icium Z", "Fightinium Z", "Poisonium Z", "Groundium Z", "Flyinium Z", "Psychium Z", "Buginium Z", "Rockium Z", "Ghostium Z", "Dragonium Z", "Darkinium Z", "Steelium Z", "Fairium Z", "Pikanium Z", "Decidium Z", "Incinium Z", "Primarium Z", "Tapunium Z", "Marshadium Z", "Aloraichium Z", "Snorlium Z", "Eevium Z", "Mewnium Z", "Pikashunium Z", "Pikashunium Z", "???", "???", "???", "???", "Forage Bag", "Fishing Rod", "Professor’s Mask", "Festival Ticket", "Sparkling Stone", "Adrenaline Orb", "Zygarde Cube", "???", "Ice Stone", "Ride Pager", "Beast Ball", "Big Malasada", "Red Nectar", "Yellow Nectar", "Pink Nectar", "Purple Nectar", "Sun Flute", "Moon Flute", "???", "Enigmatic Card", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "Terrain Extender", "Protective Pads", "Electric Seed", "Psychic Seed", "Misty Seed", "Grassy Seed", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "Fighting Memory", "Flying Memory", "Poison Memory", "Ground Memory", "Rock Memory", "Bug Memory", "Ghost Memory", "Steel Memory", "Fire Memory", "Water Memory", "Grass Memory", "Electric Memory", "Psychic Memory", "Ice Memory", "Dragon Memory", "Dark Memory", "Fairy Memory"};
static char *itemsSorted[] = {"None", "Ability Capsule", "Ability Urge", "Abomasite", "Absolite", "Absorb Bulb", "Acro Bike", "Adamant Orb", "Adrenaline Orb", "Adventure Rules", "Aerodactylite", "Aggronite", "Aguav Berry", "Air Balloon", "Alakazite", "Aloraichium Z", "Aloraichium Z", "Altarianite", "Amaze Mulch", "Ampharosite", "Amulet Coin", "Antidote", "Apicot Berry", "Apricorn Box", "Aqua Suit", "Armor Fossil", "Aspear Berry", "Assault Vest", "Audinite", "Awakening", "Azure Flute", "Babiri Berry", "Balm Mushroom", "Banettite", "Basement Key", "Basement Key", "Beast Ball", "Beedrillite", "Belue Berry", "Berry Juice", "Berry Pots", "Big Malasada", "Big Mushroom", "Big Nugget", "Big Pearl", "Big Root", "Bike", "Bike", "Binding Band", "Black Apricorn", "Black Belt", "Black Flute", "Black Glasses", "Black Sludge", "Blastoisinite", "Blazikenite", "Blue Apricorn", "Blue Card", "Blue Flute", "Blue Orb", "Blue Scarf", "Blue Shard", "Bluk Berry", "Boost Mulch", "Bottle Cap", "Bridge Mail D", "Bridge Mail M", "Bridge Mail S", "Bridge Mail T", "Bridge Mail V", "Bright Powder", "Bug Gem", "Bug Memory", "Buginium Z", "Buginium Z", "Burn Drive", "Burn Heal", "Calcium", "Cameruptite", "Carbos", "Card Key", "Casteliacone", "Cell Battery", "Charcoal", "Charizardite X", "Charizardite Y", "Charti Berry", "Cheri Berry", "Cherish Ball", "Chesto Berry", "Chilan Berry", "Chill Drive", "Choice Band", "Choice Scarf", "Choice Specs", "Chople Berry", "Claw Fossil", "Cleanse Tag", "Clear Bell", "Clever Wing", "Coba Berry", "Coin Case", "Colbur Berry", "Colress Machine", "Comet Shard", "Common Stone", "Contest Costume", "Contest Costume", "Contest Pass", "Cornn Berry", "Coupon 1", "Coupon 2", "Coupon 3", "Cover Fossil", "Custap Berry", "Damp Mulch", "Damp Rock", "Dark Gem", "Dark Memory", "Dark Stone", "Darkinium Z", "Darkinium Z", "Data Card 01", "Data Card 02", "Data Card 03", "Data Card 04", "Data Card 05", "Data Card 06", "Data Card 07", "Data Card 08", "Data Card 09", "Data Card 10", "Data Card 11", "Data Card 12", "Data Card 13", "Data Card 14", "Data Card 15", "Data Card 16", "Data Card 17", "Data Card 18", "Data Card 19", "Data Card 20", "Data Card 21", "Data Card 22", "Data Card 23", "Data Card 24", "Data Card 25", "Data Card 26", "Data Card 27", "Dawn Stone", "Decidium Z", "Decidium Z", "Deep Sea Scale", "Deep Sea Tooth", "Destiny Knot", "Devon Parts", "Devon Scope", "Devon Scuba Gear", "Diancite", "Dire Hit", "Dire Hit 2", "Dire Hit 3", "Discount Coupon", "Dive Ball", "DNA Splicers", "DNA Splicers", "Dome Fossil", "Douse Drive", "Dowsing Machine", "Draco Plate", "Dragon Fang", "Dragon Gem", "Dragon Memory", "Dragon Scale", "Dragon Skull", "Dragonium Z", "Dragonium Z", "Dread Plate", "Dream Ball", "Dropped Item", "Dropped Item", "Dubious Disc", "Durin Berry", "Dusk Ball", "Dusk Stone", "Earth Plate", "Eevium Z", "Eevium Z", "Eject Button", "Electirizer", "Electric Gem", "Electric Memory", "Electric Seed", "Electrium Z", "Electrium Z", "Elevator Key", "Elixir", "Energy Powder", "Energy Root", "Enigma Berry", "Enigma Stone", "Enigmatic Card", "Eon Flute", "Eon Ticket", "Escape Rope", "Ether", "Everstone", "Eviolite", "Exp. Share", "Expert Belt", "Explorer Kit", "Fairium Z", "Fairium Z", "Fairy Gem", "Fairy Memory", "Fashion Case", "Fast Ball", "Favored Mail", "Festival Ticket", "Fighting Gem", "Fighting Memory", "Fightinium Z", "Fightinium Z", "Figy Berry", "Fire Gem", "Fire Memory", "Fire Stone", "Firium Z", "Firium Z", "Fishing Rod", "Fist Plate", "Flame Orb", "Flame Plate", "Float Stone", "Fluffy Tail", "Flying Gem", "Flying Memory", "Flyinium Z", "Flyinium Z", "Focus Band", "Focus Sash", "Forage Bag", "Fresh Water", "Friend Ball", "Full Heal", "Full Incense", "Full Restore", "Galactic Key", "Galladite", "Ganlon Berry", "Garchompite", "Gardevoirite", "GB Sounds", "Gengarite", "Genius Wing", "Ghost Gem", "Ghost Memory", "Ghostium Z", "Ghostium Z", "Glalitite", "Go-Goggles", "Gold Bottle Cap", "Good Rod", "Gooey Mulch", "Gracidea", "Gram 1", "Gram 2", "Gram 3", "Grass Gem", "Grass Memory", "Grassium Z", "Grassium Z", "Grassy Seed", "Great Ball", "Green Apricorn", "Green Scarf", "Green Shard", "Greet Mail", "Grepa Berry", "Grip Claw", "Griseous Orb", "Ground Gem", "Ground Memory", "Groundium Z", "Groundium Z", "Growth Mulch", "Grubby Hanky", "Guard Spec.", "Gyaradosite", "Haban Berry", "Hard Stone", "Heal Ball", "Heal Powder", "Health Wing", "Heart Scale", "Heat Rock", "Heavy Ball", "Helix Fossil", "Heracronite", "HM01", "HM02", "HM03", "HM04", "HM05", "HM06", "HM07", "Holo Caster", "Holo Caster", "Hondew Berry", "Honey", "Honor of Kalos", "Houndoominite", "HP Up", "Hyper Potion", "Iapapa Berry", "Ice Gem", "Ice Heal", "Ice Memory", "Ice Stone", "Icicle Plate", "Icium Z", "Icium Z", "Icy Rock", "Incinium Z", "Incinium Z", "Inquiry Mail", "Insect Plate", "Intriguing Stone", "Iron", "Iron Ball", "Iron Plate", "Item Drop", "Item Urge", "Jaboca Berry", "Jade Orb", "Jaw Fossil", "Journal", "Kangaskhanite", "Kasib Berry", "Kebia Berry", "Kee Berry", "Kelpsy Berry", "Key Stone", "Key to Room 1", "Key to Room 2", "Key to Room 4", "Key to Room 6", "King’s Rock", "Lagging Tail", "Lansat Berry", "Latiasite", "Latiosite", "Lava Cookie", "Lax Incense", "Leaf Stone", "Leftovers", "Lemonade", "Lens Case", "Leppa Berry", "Letter", "Level Ball", "Liberty Pass", "Liechi Berry", "Life Orb", "Light Ball", "Light Clay", "Light Stone", "Like Mail", "Lock Capsule", "Looker Ticket", "Loot Sack", "Lopunnite", "Lost Item", "Love Ball", "Lucarionite", "Luck Incense", "Lucky Egg", "Lucky Punch", "Lum Berry", "Luminous Moss", "Lumiose Galette", "Lunar Wing", "Lure Ball", "Lustrous Orb", "Luxury Ball", "Mach Bike", "Machine Part", "Macho Brace", "Magma Stone", "Magma Suit", "Magmarizer", "Magnet", "Mago Berry", "Magost Berry", "Makeup Bag", "Manectite", "Maranga Berry", "Marshadium Z", "Marshadium Z", "Master Ball", "Mawilite", "Max Elixir", "Max Ether", "Max Potion", "Max Repel", "Max Revive", "Meadow Plate", "Medal Box", "Medichamite", "Mega Anchor", "Mega Anklet", "Mega Bracelet", "Mega Charm", "Mega Cuff", "Mega Glasses", "Mega Glove", "Mega Pendant", "Mega Ring", "Mega Stickpin", "Mega Tiara", "Member Card", "Mental Herb", "Metagrossite", "Metal Coat", "Metal Powder", "Meteorite", "Meteorite", "Meteorite", "Meteorite", "Meteorite Shard", "Metronome", "Mewnium Z", "Mewnium Z", "Mewtwonite X", "Mewtwonite Y", "Micle Berry", "Mind Plate", "Miracle Seed", "Misty Seed", "Moomoo Milk", "Moon Ball", "Moon Flute", "Moon Stone", "Muscle Band", "Muscle Wing", "Mystery Egg", "Mystic Water", "Nanab Berry", "Nest Ball", "Net Ball", "Never-Melt Ice", "Nomel Berry", "Normal Gem", "Normalium Z", "Normalium Z", "Nugget", "Oak’s Letter", "Occa Berry", "Odd Incense", "Odd Keystone", "Old Amber", "Old Charm", "Old Gateau", "Old Rod", "Oran Berry", "Oval Charm", "Oval Stone", "Pair of Tickets", "Pal Pad", "Pamtre Berry", "Paralyze Heal", "Parcel", "Park Ball", "Pass", "Pass Orb", "Passho Berry", "Payapa Berry", "Pearl", "Pearl String", "Pecha Berry", "Permit", "Persim Berry", "Petaya Berry", "Photo Album", "Pidgeotite", "Pikanium Z", "Pikanium Z", "Pikashunium Z", "Pikashunium Z", "Pinap Berry", "Pink Apricorn", "Pink Nectar", "Pink Scarf", "Pinsirite", "Pixie Plate", "Plasma Card", "Plume Fossil", "Poffin Case", "Point Card", "Poison Barb", "Poison Gem", "Poison Memory", "Poisonium Z", "Poisonium Z", "Poké Ball", "Poké Doll", "Poké Flute", "Poké Radar", "Poké Toy", "Pokéblock Kit", "Pomeg Berry", "Potion", "Power Anklet", "Power Band", "Power Belt", "Power Bracer", "Power Herb", "Power Lens", "Power Plant Pass", "Power Weight", "PP Max", "PP Up", "Premier Ball", "Pretty Wing", "Primarium Z", "Primarium Z", "Prism Scale", "Prison Bottle", "Prof’s Letter", "Professor’s Mask", "Prop Case", "Protective Pads", "Protector", "Protein", "Psychic Gem", "Psychic Memory", "Psychic Seed", "Psychium Z", "Psychium Z", "Pure Incense", "Purple Nectar", "Qualot Berry", "Quick Ball", "Quick Claw", "Quick Powder", "Rabuta Berry", "Rage Candy Bar", "Rainbow Wing", "Rare Bone", "Rare Candy", "Rawst Berry", "Razor Claw", "Razor Fang", "Razz Berry", "Reaper Cloth", "Red Apricorn", "Red Card", "Red Chain", "Red Flute", "Red Nectar", "Red Orb", "Red Scale", "Red Scarf", "Red Shard", "Relic Band", "Relic Copper", "Relic Crown", "Relic Gold", "Relic Silver", "Relic Statue", "Relic Vase", "Repeat Ball", "Repel", "Reply Mail", "Reset Urge", "Resist Wing", "Reveal Glass", "Revival Herb", "Revive", "Rich Mulch", "Ride Pager", "Rindo Berry", "Ring Target", "Rock Gem", "Rock Incense", "Rock Memory", "Rockium Z", "Rockium Z", "Rocky Helmet", "Roller Skates", "Root Fossil", "Rose Incense", "Roseli Berry", "Rowap Berry", "RSVP Mail", "Rule Book", "S.S. Ticket", "S.S. Ticket", "Sablenite", "Sachet", "Sacred Ash", "Safari Ball", "Safety Goggles", "Sail Fossil", "Salac Berry", "Salamencite", "Scanner", "Sceptilite", "Scizorite", "Scope Lens", "Sea Incense", "Seal Bag", "Seal Case", "Secret Key", "Secret Potion", "Shalour Sable", "Sharp Beak", "Sharpedonite", "Shed Shell", "Shell Bell", "Shiny Charm", "Shiny Stone", "Shoal Salt", "Shoal Shell", "Shock Drive", "Shuca Berry", "Silk Scarf", "Silver Powder", "Silver Wing", "Sitrus Berry", "Skull Fossil", "Sky Plate", "Slowbronite", "Slowpoke Tail", "Smoke Ball", "Smooth Rock", "Snorlium Z", "Snorlium Z", "Snowball", "Soda Pop", "Soft Sand", "Soot Sack", "Soothe Bell", "Soul Dew", "Sparkling Stone", "Spell Tag", "Spelon Berry", "Splash Plate", "Spooky Plate", "Sport Ball", "Sprayduck", "Sprinklotad", "Squirt Bottle", "Stable Mulch", "Star Piece", "Stardust", "Starf Berry", "Steel Gem", "Steel Memory", "Steelium Z", "Steelium Z", "Steelixite", "Stick", "Sticky Barb", "Stone Plate", "Storage Key", "Storage Key", "Strange Souvenir", "Suite Key", "Sun Flute", "Sun Stone", "Super Potion", "Super Repel", "Super Rod", "Surprise Mulch", "Swampertite", "Sweet Heart", "Swift Wing", "Tamato Berry", "Tanga Berry", "Tapunium Z", "Tapunium Z", "Terrain Extender", "Thanks Mail", "Thick Club", "Thunder Stone", "Tidal Bell", "Timer Ball", "Tiny Mushroom", "TM01", "TM02", "TM03", "TM04", "TM05", "TM06", "TM07", "TM08", "TM09", "TM10", "TM100", "TM11", "TM12", "TM13", "TM14", "TM15", "TM16", "TM17", "TM18", "TM19", "TM20", "TM21", "TM22", "TM23", "TM24", "TM25", "TM26", "TM27", "TM28", "TM29", "TM30", "TM31", "TM32", "TM33", "TM34", "TM35", "TM36", "TM37", "TM38", "TM39", "TM40", "TM41", "TM42", "TM43", "TM44", "TM45", "TM46", "TM47", "TM48", "TM49", "TM50", "TM51", "TM52", "TM53", "TM54", "TM55", "TM56", "TM57", "TM58", "TM59", "TM60", "TM61", "TM62", "TM63", "TM64", "TM65", "TM66", "TM67", "TM68", "TM69", "TM70", "TM71", "TM72", "TM73", "TM74", "TM75", "TM76", "TM77", "TM78", "TM79", "TM80", "TM81", "TM82", "TM83", "TM84", "TM85", "TM86", "TM87", "TM88", "TM89", "TM90", "TM91", "TM92", "TM93", "TM94", "TM95", "TM96", "TM97", "TM98", "TM99", "TMV Pass", "Town Map", "Toxic Orb", "Toxic Plate", "Travel Trunk", "Twisted Spoon", "Tyranitarite", "Ultra Ball", "Unown Report", "Up-Grade", "Venusaurite", "Vs. Recorder", "Vs. Seeker", "Wacan Berry", "Wailmer Pail", "Water Gem", "Water Memory", "Water Stone", "Waterium Z", "Waterium Z", "Watmel Berry", "Wave Incense", "Weakness Policy", "Wepear Berry", "Whipped Dream", "White Apricorn", "White Flute", "White Herb", "Wide Lens", "Wiki Berry", "Wise Glasses", "Works Key", "X Accuracy", "X Accuracy 2", "X Accuracy 3", "X Accuracy 6", "X Attack", "X Attack 2", "X Attack 3", "X Attack 6", "X Defense", "X Defense 2", "X Defense 3", "X Defense 6", "X Sp. Atk", "X Sp. Atk 2", "X Sp. Atk 3", "X Sp. Atk 6", "X Sp. Def", "X Sp. Def 2", "X Sp. Def 3", "X Sp. Def 6", "X Speed", "X Speed 2", "X Speed 3", "X Speed 6", "Xtransceiver", "Xtransceiver", "Yache Berry", "Yellow Apricorn", "Yellow Flute", "Yellow Nectar", "Yellow Scarf", "Yellow Shard", "Z-Ring", "Zap Plate", "Zinc", "Zoom Lens", "Zygarde Cube", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???"};
char *hpList[] = {"Fighting", "Flying", "Poison", "Ground", "Rock", "Bug", "Ghost", "Steel", "Fire", "Water", "Grass", "Electric", "Psychic", "Ice", "Dragon", "Dark"};

void GUIElementsInit() {
	fontBold18 = sftd_load_font_file("romfs:/res/Bold.ttf");
	fontBold15 = sftd_load_font_file("romfs:/res/Bold.ttf");
	fontBold14 = sftd_load_font_file("romfs:/res/Bold.ttf");
	fontBold12 = sftd_load_font_file("romfs:/res/Bold.ttf");
	fontBold11 = sftd_load_font_file("romfs:/res/Bold.ttf");
	fontBold9 = sftd_load_font_file("romfs:/res/Bold.ttf");
	fontFixed = sftd_load_font_file("romfs:/res/VeraMono.ttf");
	warningTopTrasp = sfil_load_PNG_file("romfs:/res/Warning Top Trasp.png", SF2D_PLACE_RAM);
	warningBottomTrasp = sfil_load_PNG_file("romfs:/res/Warning Bottom Trasp.png", SF2D_PLACE_RAM);
	
	init_font_cache();
	
	alternativeSpritesSmall = sfil_load_PNG_file("/pk/romfs/alternativeSpritesSmall.png", SF2D_PLACE_RAM);
	spritesSmall = sfil_load_PNG_file("/pk/romfs/pokemon_icons_spritesheet.png", SF2D_PLACE_RAM);
	shinySpritesSmall = sfil_load_PNG_file("/pk/romfs/pokemon_shiny_icons_spritesheet.png", SF2D_PLACE_RAM);
}

void GUIElementsSpecify(int game) {
	settings = sfil_load_PNG_file("romfs:/res/Settings.png", SF2D_PLACE_RAM);
	
	if (game < 6) {
		distributionsBottom = sfil_load_PNG_file("romfs:/res/Distributions Bottom.png", SF2D_PLACE_RAM);
		distributionsTop = sfil_load_PNG_file("romfs:/res/Distributions Top.png", SF2D_PLACE_RAM);
		slimDarkBar = sfil_load_PNG_file("romfs:/res/Event Menu Dark Bar.png", SF2D_PLACE_RAM);
		slimRedBar = sfil_load_PNG_file("romfs:/res/Event Menu Red Bar.png", SF2D_PLACE_RAM);
		mainMenuBottom = sfil_load_PNG_file("romfs:/res/Main Menu Bottom.png", SF2D_PLACE_RAM);
		darkBar = sfil_load_PNG_file("romfs:/res/Main Menu Dark Bar.png", SF2D_PLACE_RAM);
		redBar = sfil_load_PNG_file("romfs:/res/Main Menu Red Bar.png", SF2D_PLACE_RAM);
		mainMenuTop = sfil_load_PNG_file("romfs:/res/Main Menu Top.png", SF2D_PLACE_RAM);
		darkButton = sfil_load_PNG_file("romfs:/res/Dark Button.png", SF2D_PLACE_RAM);
		eventTop = sfil_load_PNG_file("romfs:/res/Event Top.png", SF2D_PLACE_RAM);
		left = sfil_load_PNG_file("romfs:/res/Left.png", SF2D_PLACE_RAM);
		leftTop = sfil_load_PNG_file("romfs:/res/Left Top.png", SF2D_PLACE_RAM);
		lightButton = sfil_load_PNG_file("romfs:/res/Light Button.png", SF2D_PLACE_RAM);
		redButton = sfil_load_PNG_file("romfs:/res/Red Button.png", SF2D_PLACE_RAM);
		right = sfil_load_PNG_file("romfs:/res/Right.png", SF2D_PLACE_RAM);
		rightTop = sfil_load_PNG_file("romfs:/res/Right Top.png", SF2D_PLACE_RAM);
		eventMenuTop = sfil_load_PNG_file("romfs:/res/Event Menu Top BG.png", SF2D_PLACE_RAM);
		eventMenuBottomBar = sfil_load_PNG_file("romfs:/res/Event Menu Bottom Bar.png", SF2D_PLACE_RAM);
		eventMenuTopBarSelected = sfil_load_PNG_file("romfs:/res/Event Menu Top Bar Selected.png", SF2D_PLACE_RAM);
		eventMenuTopBar = sfil_load_PNG_file("romfs:/res/Event Menu Top Bar.png", SF2D_PLACE_RAM);
		PSDates = sfil_load_PNG_file("romfs:/res/Powersaves Dates.png", SF2D_PLACE_RAM);
		editorBar = sfil_load_PNG_file("romfs:/res/Editor Bar.png", SF2D_PLACE_RAM);
		boxView = sfil_load_PNG_file("romfs:/res/Poke Edit Bottom BG.png", SF2D_PLACE_RAM);
		infoView = sfil_load_PNG_file("romfs:/res/Info View.png", SF2D_PLACE_RAM);
		LRBar = sfil_load_PNG_file("romfs:/res/LR Bar.png", SF2D_PLACE_RAM);
		selector = sfil_load_PNG_file("romfs:/res/Selector.png", SF2D_PLACE_RAM);
		selectorCloning = sfil_load_PNG_file("romfs:/res/Selector (cloning).png", SF2D_PLACE_RAM);
		editorBG = sfil_load_PNG_file("romfs:/res/Editor Bottom BG.png", SF2D_PLACE_RAM);
		plus = sfil_load_PNG_file("romfs:/res/Plus.png", SF2D_PLACE_RAM);
		minus = sfil_load_PNG_file("romfs:/res/Minus.png", SF2D_PLACE_RAM);
		buttonSave = sfil_load_PNG_file("romfs:/res/Save Button.png", SF2D_PLACE_RAM);
		back = sfil_load_PNG_file("romfs:/res/Back Button.png", SF2D_PLACE_RAM);
		setting = sfil_load_PNG_file("romfs:/res/Setting.png", SF2D_PLACE_RAM);
		bankBottomBG = sfil_load_PNG_file("romfs:/res/Bank Bottom BG.png", SF2D_PLACE_RAM);
		topButton = sfil_load_PNG_file("romfs:/res/Top Button.png", SF2D_PLACE_RAM);
		bottomButton = sfil_load_PNG_file("romfs:/res/Bottom Button.png", SF2D_PLACE_RAM);
		bottomPopUp = sfil_load_PNG_file("romfs:/res/Bottom Pop-Up.png", SF2D_PLACE_RAM);
		pokemonBufferBox = sfil_load_PNG_file("romfs:/res/Pokemon Box.png", SF2D_PLACE_RAM);
		cleanTop = sfil_load_PNG_file("romfs:/res/Clean Top.png", SF2D_PLACE_RAM);
		bottomMovesBar = sfil_load_PNG_file("romfs:/res/Bottom Moves Bar.png", SF2D_PLACE_RAM);
		bottomMovesBarCut = sfil_load_PNG_file("romfs:/res/Bottom Moves Bar2.png", SF2D_PLACE_RAM);
		bottomMovesBG = sfil_load_PNG_file("romfs:/res/Bottom Moves BG.png", SF2D_PLACE_RAM);
		topMovesBG = sfil_load_PNG_file("romfs:/res/Top Moves.png", SF2D_PLACE_RAM);
		topSelectedMove = sfil_load_PNG_file("romfs:/res/Top Selected Move.png", SF2D_PLACE_RAM);
		item = sfil_load_PNG_file("romfs:/res/item.png", SF2D_PLACE_RAM);
	} else {
		DSBottomBG = sfil_load_PNG_file("romfs:/res/Bottom BG.png", SF2D_PLACE_RAM);
		DSTopBG = sfil_load_PNG_file("romfs:/res/Top BG.png", SF2D_PLACE_RAM);
		DSBarSelected = sfil_load_PNG_file("romfs:/res/Bar Selected.png", SF2D_PLACE_RAM);
		DSBar = sfil_load_PNG_file("romfs:/res/Bar.png", SF2D_PLACE_RAM);
		DSEventBottom = sfil_load_PNG_file("romfs:/res/DS Menu Bottom BG.png", SF2D_PLACE_RAM);
		DSLangSelected = sfil_load_PNG_file("romfs:/res/Language Button Selected.png", SF2D_PLACE_RAM);
		DSLang = sfil_load_PNG_file("romfs:/res/Language Button.png", SF2D_PLACE_RAM);
		DSEventTop = sfil_load_PNG_file("romfs:/res/Event Database BG.png", SF2D_PLACE_RAM);
		DSNormalBarL = sfil_load_PNG_file("romfs:/res/Normal L.png", SF2D_PLACE_RAM);
		DSNormalBarR = sfil_load_PNG_file("romfs:/res/Normal R.png", SF2D_PLACE_RAM);
		DSSelectedBarL = sfil_load_PNG_file("romfs:/res/Selected L.png", SF2D_PLACE_RAM);
		DSSelectedBarR = sfil_load_PNG_file("romfs:/res/Selected R.png", SF2D_PLACE_RAM);
	}
}

void GUIGameElementsInit() {
	topBorder = sfil_load_PNG_file("romfs:/res/3DS Border.png", SF2D_PLACE_RAM);
	bottomBorder = sfil_load_PNG_file("romfs:/res/DS Border.png", SF2D_PLACE_RAM);
	gameSelectorBottom = sfil_load_PNG_file("romfs:/res/Game Selection Screen Bottom.png", SF2D_PLACE_RAM);
	gameSelectorTop = sfil_load_PNG_file("romfs:/res/Game Selection Screen Top.png", SF2D_PLACE_RAM);
}

void GUIGameElementsExit() {
	sf2d_free_texture(gameSelectorBottom);
	sf2d_free_texture(gameSelectorTop);
	sf2d_free_texture(topBorder);
	sf2d_free_texture(bottomBorder);
}

void GUIElementsExit() {
	sf2d_free_texture(alternativeSpritesSmall);
	sf2d_free_texture(item);
	sf2d_free_texture(settings);
	sf2d_free_texture(bottomMovesBG);
	sf2d_free_texture(bottomMovesBar);
	sf2d_free_texture(bottomMovesBarCut);
	sf2d_free_texture(topMovesBG);
	sf2d_free_texture(topSelectedMove);
	sf2d_free_texture(DSEventBottom);
	sf2d_free_texture(DSLangSelected);
	sf2d_free_texture(DSLang);
	sf2d_free_texture(DSEventTop);
	sf2d_free_texture(DSNormalBarL);
	sf2d_free_texture(DSNormalBarR);
	sf2d_free_texture(DSSelectedBarL);
	sf2d_free_texture(DSSelectedBarR);
	sf2d_free_texture(DSBottomBG);
	sf2d_free_texture(DSTopBG);
	sf2d_free_texture(DSBarSelected);
	sf2d_free_texture(DSBar);
	sf2d_free_texture(cleanTop);
	sf2d_free_texture(bottomPopUp);
	sf2d_free_texture(pokemonBufferBox);
	sf2d_free_texture(topButton);
	sf2d_free_texture(bottomButton);
	sf2d_free_texture(bankBottomBG);
	sf2d_free_texture(selectorCloning);
	sf2d_free_texture(back);
	sf2d_free_texture(setting);
	sf2d_free_texture(editorBG);
	sf2d_free_texture(plus);
	sf2d_free_texture(minus);
	sf2d_free_texture(buttonSave);
	sf2d_free_texture(boxView);
	sf2d_free_texture(infoView);
	sf2d_free_texture(LRBar);
	sf2d_free_texture(selector);
	sf2d_free_texture(editorBar);
	sf2d_free_texture(PSDates);
	sf2d_free_texture(warningTopTrasp);
	sf2d_free_texture(warningBottomTrasp);
	sf2d_free_texture(eventMenuTop);
	sf2d_free_texture(eventMenuBottomBar);
	sf2d_free_texture(eventMenuTopBarSelected);
	sf2d_free_texture(eventMenuTopBar);
	sf2d_free_texture(spritesSmall);
	sf2d_free_texture(shinySpritesSmall);
	sf2d_free_texture(darkButton);
	sf2d_free_texture(eventTop);
	sf2d_free_texture(left);
	sf2d_free_texture(leftTop);
	sf2d_free_texture(lightButton);
	sf2d_free_texture(redButton);
	sf2d_free_texture(right);
	sf2d_free_texture(rightTop);
	sf2d_free_texture(distributionsBottom);
	sf2d_free_texture(distributionsTop);
	sf2d_free_texture(slimDarkBar);
	sf2d_free_texture(slimRedBar);
	sf2d_free_texture(mainMenuBottom);
	sf2d_free_texture(darkBar);
	sf2d_free_texture(redBar);
	sf2d_free_texture(mainMenuTop);
	sftd_free_font(fontBold9);
	sftd_free_font(fontBold11);
	sftd_free_font(fontBold12);
	sftd_free_font(fontBold14);
	sftd_free_font(fontBold15);
	sftd_free_font(fontBold18);
	sftd_free_font(fontFixed);
}

void init_font_cache() {
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sftd_draw_text(fontBold18, 0, 0, RGBA8(0, 0, 0, 0), 18, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890:-.'!?()\"end");
		sftd_draw_text(fontBold14, 0, 0, RGBA8(0, 0, 0, 0), 14, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890:-.'!?()\"end");
		sftd_draw_text(fontBold15, 0, 0, RGBA8(0, 0, 0, 0), 15, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890:-.'!?()\"end");
		sftd_draw_text(fontBold12, 0, 0, RGBA8(0, 0, 0, 0), 12, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890:-.'!?()\"end");
		sftd_draw_text(fontBold11, 0, 0, RGBA8(0, 0, 0, 0), 11, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890:-.'!?()\"end");
		sftd_draw_text(fontBold9, 0, 0, RGBA8(0, 0, 0, 0), 9, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890:-.'!?()\"end");
		sftd_draw_text(fontFixed, 0, 0, RGBA8(0, 0, 0, 0), 10, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890:-.'!?()\"end");
	sf2d_end_frame();
	sf2d_swapbuffers();
}

void infoDisp(char* message) {
	while (aptMainLoop()) {
		hidScanInput();

		if (hidKeysDown() & KEY_A) break;
		
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
			sf2d_draw_texture(warningTopTrasp, 0, 0);
			sftd_draw_text(fontBold15, (400 - sftd_get_text_width(fontBold15, 15, message)) / 2, 95, RGBA8(255, 255, 255, giveTransparence()), 15, message);
			sftd_draw_text(fontBold12, (400 - sftd_get_text_width(fontBold12, 12, "Press A to continue.")) / 2, 130, WHITE, 12, "Press A to continue.");
		sf2d_end_frame();
		
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			sf2d_draw_texture(warningBottomTrasp, 0, 0);
		sf2d_end_frame();
		sf2d_swapbuffers();
	}
}

int confirmDisp(char* message) {
	while (aptMainLoop()) {
		hidScanInput();

		if (hidKeysDown() & KEY_A) return 1;
		if (hidKeysDown() & KEY_B) return 0;
		
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
			sf2d_draw_texture(warningTopTrasp, 0, 0);
			sftd_draw_text(fontBold15, (400 - sftd_get_text_width(fontBold15, 15, message)) / 2, 95, RGBA8(255, 255, 255, giveTransparence()), 15, message);
			sftd_draw_text(fontBold12, (400 - sftd_get_text_width(fontBold12, 12, "Press A to continue, B to cancel.")) / 2, 130, WHITE, 12, "Press A to continue, B to cancel.");
		sf2d_end_frame();
		
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			sf2d_draw_texture(warningBottomTrasp, 0, 0);
		sf2d_end_frame();
		sf2d_swapbuffers();
	}
	return 0;
}

void freezeMsg(char* message) {
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(warningTopTrasp, 0, 0);
		sftd_draw_text(fontBold15, (400 - sftd_get_text_width(fontBold15, 15, message)) / 2, 95, WHITE, 15, message);
		sftd_draw_text(fontBold12, (400 - sftd_get_text_width(fontBold12, 12, "Please wait.")) / 2, 130, WHITE, 12, "Please wait.");
	sf2d_end_frame();
	
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(warningBottomTrasp, 0, 0);
	sf2d_end_frame();
	sf2d_swapbuffers();
}

void progressBar(char* message, u32 current, u32 sz) {
	char* progress = (char*)malloc(40 * sizeof(char));
	snprintf(progress, 40, "Progress: %lu/%lu bytes", current, sz);
	
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(warningTopTrasp, 0, 0);
		sftd_draw_text(fontBold15, (400 - sftd_get_text_width(fontBold15, 15, message)) / 2, 95, WHITE, 15, message);
		sftd_draw_text(fontBold12, (400 - sftd_get_text_width(fontBold12, 12, progress)) / 2, 130, WHITE, 12, progress);
	sf2d_end_frame();
	
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(warningBottomTrasp, 0, 0);
	sf2d_end_frame();
	sf2d_swapbuffers();
	
	free(progress);
}

int giveTransparence() {
	if (vanish && trasp > 126) trasp -= 1;
	if (trasp == 126) vanish = false;
	if (!(vanish) && trasp < 254) trasp += 1;
	if (trasp == 254) vanish = true;
	
	return trasp;
}

void drawMenuTop(int game) {
	char* version = (char*)malloc(10 * sizeof(char));
	snprintf(version, 10, "v%d.%d.%d", V1, V2, V3);
	
	if (game < 6) {
		sf2d_draw_texture(mainMenuTop, 0, 0);
	}
	else 
		sf2d_draw_texture(DSTopBG, 0, 0);
	
	sftd_draw_text(fontBold9, (398 - sftd_get_text_width(fontBold9, 9, version)), 229, RGBA8(255, 255, 255, 130), 9, version);
	
	free(version);
}

void printTitle(const char* title) {
	sftd_draw_text(fontBold14, (400 - sftd_get_text_width(fontBold14, 14, title)) / 2, 4, RED, 14, title);
}

void gameSelectorMenu(int n) {
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(gameSelectorTop, 0, 0);
		sftd_draw_text(fontBold9, (400 - sftd_get_text_width(fontBold9, 9, "Cart has priority over digital copy.")) / 2, 5, WHITE, 9, "Cart has priority over digital copy.");
		switch (n) {
			case GAME_X    : { sf2d_draw_texture(topBorder, 22, 114); break; }
			case GAME_Y    : { sf2d_draw_texture(topBorder, 82, 114); break; }
			case GAME_OR   : { sf2d_draw_texture(topBorder, 142, 114); break; }
			case GAME_AS   : { sf2d_draw_texture(topBorder, 202, 114); break; }
			case GAME_SUN  : { sf2d_draw_texture(topBorder, 262, 114); break; }
			case GAME_MOON : { sf2d_draw_texture(topBorder, 322, 114); break; }
		}
	sf2d_end_frame();
	
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(gameSelectorBottom, 0, 0);
		switch (n) {
			case GAME_DIAMOND  : { sf2d_draw_texture(bottomBorder, 57, 65); break; }
			case GAME_PEARL    : { sf2d_draw_texture(bottomBorder, 99, 65); break; }
			case GAME_PLATINUM : { sf2d_draw_texture(bottomBorder, 141, 65); break; }
			case GAME_HG       : { sf2d_draw_texture(bottomBorder, 183, 65); break; }
			case GAME_SS	   : { sf2d_draw_texture(bottomBorder, 225, 65); break; }
			case GAME_B1	   : { sf2d_draw_texture(bottomBorder, 78, 124); break; }
			case GAME_W1	   : { sf2d_draw_texture(bottomBorder, 120, 124); break; }
			case GAME_B2	   : { sf2d_draw_texture(bottomBorder, 162, 124); break; }
			case GAME_W2	   : { sf2d_draw_texture(bottomBorder, 204, 124); break; }
		}
		sf2d_draw_rectangle(60, 68, 32, 32, RGBA8(0, 0, 0, 210));
		sf2d_draw_rectangle(102, 68, 32, 32, RGBA8(0, 0, 0, 210));
		sf2d_draw_rectangle(144, 68, 32, 32, RGBA8(0, 0, 0, 210));
		sftd_draw_text(fontBold9, (320 - sftd_get_text_width(fontBold9, 9, "Press A continue, B to exit.")) / 2, 226, WHITE, 9, "Press A continue, B to exit.");
	sf2d_end_frame();
	sf2d_swapbuffers();
}

void mainMenu(int currentEntry) {
	char* menu[3] = {"EVENTS", "EDITOR", "OTHER"};
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		drawMenuTop(0);
	sf2d_end_frame();
	
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(mainMenuBottom, 0, 0);
		sf2d_draw_texture(settings, 298, 205);
		for (int i = 0; i < 3; i++) {
			if (i == currentEntry)
				sf2d_draw_texture(redBar, (320 - redBar->width) / 2, 50 + i * (redBar->height + 10));
			else
				sf2d_draw_texture(darkBar, (320 - darkBar->width) / 2, 50 + i * (darkBar->height + 10));
			sftd_draw_text(fontBold18, (320 - sftd_get_text_width(fontBold18, 18, menu[i])) / 2, 48 + (darkBar->height - 18) / 2 + i * (darkBar->height + 10), WHITE, 18, menu[i]);
		}
		sftd_draw_text(fontBold9, (320 - sftd_get_text_width(fontBold9, 9, "Press START to save, X to exit.")) / 2, 226, WHITE, 9, "Press START to save, X to exit.");
	sf2d_end_frame();
	sf2d_swapbuffers();
}

void mainMenuDS(int currentEntry) {
	char* menu[2] = {"EVENTS", "OTHER"};
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		drawMenuTop(7);
	sf2d_end_frame();
	
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(DSBottomBG, 0, 0);
		for (int i = 0; i < 2; i++) {
			if (i == currentEntry)
				sf2d_draw_texture(DSBarSelected, (320 - DSBarSelected->width) / 2, 66 + i * (DSBarSelected->height + 16) + i + 1);
			else
				sf2d_draw_texture(DSBar, (320 - DSBar->width) / 2, 66 + i * (DSBar->height + 16));
			sftd_draw_text(fontBold18, (320 - sftd_get_text_width(fontBold18, 18, menu[i])) / 2, 67 + (DSBar->height - 18) / 2 + i * (DSBar->height + 16), WHITE, 18, menu[i]);
		}
		sftd_draw_text(fontBold9, (320 - sftd_get_text_width(fontBold9, 9, "Press START to save, X to exit.")) / 2, 222, RGBA8(255, 255, 255, 130), 9, "Press START to save, X to exit.");
	sf2d_end_frame();
	sf2d_swapbuffers();
}

void menu4(int currentEntry, char* menu[], int n) {
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		drawMenuTop(0);
	sf2d_end_frame();
	
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(mainMenuBottom, 0, 0);
		sf2d_draw_texture(back, 298, 207);
		
		for (int i = 0; i < n; i++) {
			if (i == currentEntry)
				sf2d_draw_texture(slimRedBar, (320 - slimRedBar->width) / 2, 40 + i * (slimRedBar->height + 10));
			else
				sf2d_draw_texture(slimDarkBar, (320 - slimDarkBar->width) / 2, 40 + i * (slimDarkBar->height + 10));
			sftd_draw_text(fontBold15, (320 - sftd_get_text_width(fontBold15, 15, menu[i])) / 2, 38 + (slimDarkBar->height - 15) / 2 + i * (slimDarkBar->height + 10), WHITE, 15, menu[i]);
		}
		sftd_draw_text(fontBold9, (320 - sftd_get_text_width(fontBold9, 9, "Press A to select an option.")) / 2, 226, WHITE, 9, "Press A to select an option.");
	sf2d_end_frame();
	sf2d_swapbuffers();
}

void menu3(int currentEntry, char* menu[], int n) {
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		drawMenuTop(0);
	sf2d_end_frame();
	
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(mainMenuBottom, 0, 0);
		sf2d_draw_texture(back, 298, 207);
		
		for (int i = 0; i < n; i++) {
			if (i == currentEntry)
				sf2d_draw_texture(slimRedBar, (320 - slimRedBar->width) / 2, 60 + i * (slimRedBar->height + 10));
			else
				sf2d_draw_texture(slimDarkBar, (320 - slimDarkBar->width) / 2, 60 + i * (slimDarkBar->height + 10));
			sftd_draw_text(fontBold15, (320 - sftd_get_text_width(fontBold15, 15, menu[i])) / 2, 59 + (slimDarkBar->height - 15) / 2 + i * (slimDarkBar->height + 10), WHITE, 15, menu[i]);
		}
		sftd_draw_text(fontBold9, (320 - sftd_get_text_width(fontBold9, 9, "Press A to select an option.")) / 2, 226, WHITE, 9, "Press A to select an option.");
	sf2d_end_frame();
	sf2d_swapbuffers();
}

void printCredits() {
	u8* buf = (u8*)malloc(1500 * sizeof(u8));
	loadFile(buf, "romfs:/res/credits.txt");
	
	while (aptMainLoop() && !(hidKeysUp() & KEY_B)) {
		hidScanInput();
		touchPosition touch;
		hidTouchRead(&touch);		
		if ((hidKeysDown() & KEY_TOUCH) && touch.px > 298 && touch.px < 320 && touch.py > 207 && touch.py < 225) break;
		
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
			sf2d_draw_texture(cleanTop, 0, 0);
			printTitle("Credits");
			sftd_draw_text(fontBold11, 32, 29,  DARKGREY, 11, (char*)buf);
		sf2d_end_frame();

		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			sf2d_draw_texture(distributionsBottom, 0, 0);
			sf2d_draw_texture(back, 298, 207);
			sftd_draw_text(fontBold9, (320 - sftd_get_text_width(fontBold9, 9, "Press B to return.")) / 2, 226, WHITE, 9, "Press B to return.");
		sf2d_end_frame();
		sf2d_swapbuffers();
	}
	
	free(buf);
}

void printDistribution(char *url) {
	u8* buf = (u8*)malloc(1500 * sizeof(u8));
	Result ret = http_download(buf, url);
	if (ret != 0) return;
	
	while (aptMainLoop() && !(hidKeysUp() & KEY_B)) {
		hidScanInput();
		touchPosition touch;
		hidTouchRead(&touch);		
		if ((hidKeysDown() & KEY_TOUCH) && touch.px > 298 && touch.px < 320 && touch.py > 207 && touch.py < 225) break;
		
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
			sf2d_draw_texture(distributionsTop, 0, 0);
			sftd_draw_text(fontFixed, 52, 46,  WHITE, 10, (char*)buf);
		sf2d_end_frame();

		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			sf2d_draw_texture(distributionsBottom, 0, 0);
			sf2d_draw_texture(back, 298, 207);
			
			sftd_draw_text(fontBold9, (320 - sftd_get_text_width(fontBold9, 9, "Press B to return.")) / 2, 226, WHITE, 9, "Press B to return.");
		sf2d_end_frame();
		sf2d_swapbuffers();
	}
	
	free(buf);
}

void printPSDates() {
	int i = 0;
	int max = 11;
	char *pages = (char*)malloc(20 * sizeof(char));
	char *path = (char*)malloc(40 * sizeof(char));
	u8* buf = (u8*)malloc(1500 * sizeof(u8));
	
	snprintf(path, 40, "romfs:/psdates/hacked%d.txt", i + 1);
	snprintf(pages, 20, "Page %d/%d", i + 1, max);
	loadFile(buf, path);
	
	while (aptMainLoop() && !(hidKeysUp() & KEY_B)) {
		hidScanInput();
		touchPosition touch;
		hidTouchRead(&touch);		
		if ((hidKeysDown() & KEY_TOUCH) && touch.px > 298 && touch.px < 320 && touch.py > 207 && touch.py < 225) break;
		
		if (hidKeysDown() & KEY_R) {
			if (i < max - 1) i++;
			else if (i == max - 1) i = 0;
			
			snprintf(path, 40, "romfs:/psdates/hacked%d.txt", i + 1);
			snprintf(pages, 20, "Page %d/%d", i + 1, max);
			loadFile(buf, path);
		}

		if (hidKeysDown() & KEY_L) {
			if (i > 0) i--;
			else if (i == 0) i = max - 1;
			
			snprintf(path, 40, "romfs:/psdates/hacked%d.txt", i + 1);
			snprintf(pages, 20, "Page %d/%d", i + 1, max);
			loadFile(buf, path);
		}
		
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
			sf2d_draw_texture(PSDates, 0, 0);
			sftd_draw_text(fontFixed, 52, 46,  WHITE, 10, (char*)buf);
		sf2d_end_frame();

		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			sf2d_draw_texture(mainMenuBottom, 0, 0);
			sf2d_draw_texture(back, 298, 207);
			sf2d_draw_texture(eventMenuBottomBar, (320 - eventMenuBottomBar->width) / 2, 45);
			sftd_draw_textf(fontBold12, (320 - sftd_get_text_width(fontBold12, 12, pages)) / 2, 38 + eventMenuBottomBar->height / 2, WHITE, 12, pages);
			sftd_draw_text(fontBold9, (320 - sftd_get_text_width(fontBold9, 9, "Press B to exit.")) / 2, 226, WHITE, 9, "Press B to exit.");
		sf2d_end_frame();
		sf2d_swapbuffers();
	}
	
	free(pages);
	free(path);
	free(buf);
}

void printDatabase6(char *database[], int currentEntry, int page, int spriteArray[]) {
	int pk, y = 41;
	char *pages = (char*)malloc(10 * sizeof(char));
	snprintf(pages, 10, "%d/%d", page + 1, 205);
	
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(eventMenuTop, 0, 0);
		
		for (int i = 0; i < 5; i++) {
			pk = spriteArray[page * 10 + i];
			if (i == currentEntry)
				sf2d_draw_texture(eventMenuTopBarSelected, 18, y);
			else
				sf2d_draw_texture(eventMenuTopBar, 18, y);
			
			if (pk != -1)
				sf2d_draw_texture_part(spritesSmall, 20, y + 2, 40 * (pk % 25) + 4, 30 * (pk / 25), 34, 30);
			if (sftd_get_text_width(fontBold9, 9, database[page * 10 + i]) <= 148)
				sftd_draw_text(fontBold9, 53, y + 14, WHITE, 9, database[page * 10 + i]);
			else
				sftd_draw_text_wrap(fontBold9, 53, y + 3, WHITE, 9, 148, database[page * 10 + i]);
			
			y += eventMenuTopBarSelected->height;
		}
		
		y = 41;
		for (int i = 5; i < 10; i++) {
			pk = spriteArray[page * 10 + i];
			if (i == currentEntry)
				sf2d_draw_texture(eventMenuTopBarSelected, 200, y);
			else
				sf2d_draw_texture(eventMenuTopBar, 200, y);
			
			if (pk != -1)
				sf2d_draw_texture_part(spritesSmall, 202, y + 2, 40 * (pk % 25) + 4, 30 * (pk / 25), 34, 30);
			if (sftd_get_text_width(fontBold9, 9, database[page * 10 + i]) <= 148)
				sftd_draw_text(fontBold9, 233, y + 14, WHITE, 9, database[page * 10 + i]);
			else
				sftd_draw_text_wrap(fontBold9, 233, y + 3, WHITE, 9, 148, database[page * 10 + i]);
			
			y += eventMenuTopBarSelected->height;
		}
	sf2d_end_frame();

	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(mainMenuBottom, 0, 0);
		sf2d_draw_texture(back, 298, 207);
		sf2d_draw_texture(eventMenuBottomBar, (320 - eventMenuBottomBar->width) / 2, 45);
		sftd_draw_textf(fontBold12, (320 - sftd_get_text_width(fontBold12, 12, pages)) / 2, 38 + eventMenuBottomBar->height / 2, WHITE, 12, pages);
		sftd_draw_text(fontBold9, (320 - sftd_get_text_width(fontBold9, 9, "Press A to continue, B to return.")) / 2, 226, WHITE, 9, "Press A to continue, B to return.");
	sf2d_end_frame();
	sf2d_swapbuffers();
	
	free(pages);
}

void printDatabase5(char *database[], int currentEntry, int page, int spriteArray[], bool isSelected, int langSelected, bool langVett[]) {
	int pk, y = 41;
	
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(DSEventTop, 0, 0);
		
		for (int i = 0; i < 5; i++) {
			pk = spriteArray[page * 10 + i];
			if (i == currentEntry)
				sf2d_draw_texture(DSSelectedBarL, 18, y);
			else
				sf2d_draw_texture(DSNormalBarL, 18, y);
			
			if (pk != -1)
				sf2d_draw_texture_part(spritesSmall, 22, y + 2, 40 * (pk % 25) + 4, 30 * (pk / 25), 34, 30);
			if (sftd_get_text_width(fontBold9, 9, database[page * 10 + i]) <= 148)
				sftd_draw_text(fontBold9, 55, y + 14, WHITE, 9, database[page * 10 + i]);
			else
				sftd_draw_text_wrap(fontBold9, 55, y + 3, WHITE, 9, 148, database[page * 10 + i]);
			
			y += DSSelectedBarL->height;
		}
		
		y = 41;
		for (int i = 5; i < 10; i++) {
			pk = spriteArray[page * 10 + i];
			if (i == currentEntry)
				sf2d_draw_texture(DSSelectedBarR, 200, y);
			else
				sf2d_draw_texture(DSNormalBarR, 200, y);
			
			if (pk != -1)
				sf2d_draw_texture_part(spritesSmall, 204, y + 2, 40 * (pk % 25) + 4, 30 * (pk / 25), 34, 30);
			if (sftd_get_text_width(fontBold9, 9, database[page * 10 + i]) <= 148)
				sftd_draw_text(fontBold9, 235, y + 14, WHITE, 9, database[page * 10 + i]);
			else
				sftd_draw_text_wrap(fontBold9, 235, y + 3, WHITE, 9, 148, database[page * 10 + i]);
			
			y += DSSelectedBarR->height;
		}
	sf2d_end_frame();

	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(DSEventBottom, 0, 0);
		sftd_draw_text(fontBold9, (320 - sftd_get_text_width(fontBold9, 9, isSelected ? "Press START to inject, B to return" : "Press A to select, B to return.")) / 2, 222, RGBA8(255, 255, 255, 130), 9, isSelected ? "Press START to inject, B to return" : "Press A to select, B to return.");
		
		if (isSelected) {
			char *languages[7] = {"JPN", "ENG", "FRE", "ITA", "GER", "SPA", "KOR"};
			char *path = (char*)malloc(40 * sizeof(char));
			u8* buf = (u8*)malloc(1500 * sizeof(u8));
			memset(buf, 0, 1500);
			snprintf(path, 40, "romfs:/database/gen5/%d.txt", page * 10 + currentEntry);
			loadFile(buf, path);
			
			sftd_draw_text(fontFixed, 8, 2,  WHITE, 10, (char*)buf);
			
			for (int t = 0; t < 7; t++) {
				int x = 0, y = 178;
				switch (t) {
					case 0 : { x = 25; break; }
					case 1 : { x = 63; break; }
					case 2 : { x = 101; break; }
					case 3 : { x = 139; break; }
					case 4 : { x = 177; break; }
					case 5 : { x = 215; break; }
					case 6 : { x = 253; break; }
				}
				
				sf2d_draw_texture(DSLang, x, y);
				if (langVett[t]) {
					if (t == langSelected) sf2d_draw_texture(DSLangSelected, x, y);
					sftd_draw_text(fontBold12, x + (36 - sftd_get_text_width(fontBold12, 12, languages[t])) / 2, y + 4, WHITE, 12, languages[t]);
				}
				else {
					if (t == langSelected) sf2d_draw_texture(DSLangSelected, x, y);
					sftd_draw_text(fontBold12, x + (36 - sftd_get_text_width(fontBold12, 12, languages[t])) / 2, y + 4, RGBA8(255, 255, 255, 100), 12, languages[t]);
				}
			}

			free(path);
			free(buf);
		}
	
	sf2d_end_frame();
	sf2d_swapbuffers();
}

void printDatabase4(char *database[], int currentEntry, int page, int spriteArray[], bool isSelected, int langSelected, bool langVett[]) {
	int pk, y = 41;
	
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(DSEventTop, 0, 0);
		
		for (int i = 0; i < 5; i++) {
			pk = spriteArray[page * 10 + i];
			if (i == currentEntry)
				sf2d_draw_texture(DSSelectedBarL, 18, y);
			else
				sf2d_draw_texture(DSNormalBarL, 18, y);
			
			if (pk != -1)
				sf2d_draw_texture_part(spritesSmall, 22, y + 2, 40 * (pk % 25) + 4, 30 * (pk / 25), 34, 30);
			if (sftd_get_text_width(fontBold9, 9, database[page * 10 + i]) <= 148)
				sftd_draw_text(fontBold9, 55, y + 14, WHITE, 9, database[page * 10 + i]);
			else
				sftd_draw_text_wrap(fontBold9, 55, y + 3, WHITE, 9, 148, database[page * 10 + i]);
			
			y += DSSelectedBarL->height;
		}
		
		y = 41;
		for (int i = 5; i < 10; i++) {
			pk = spriteArray[page * 10 + i];
			if (i == currentEntry)
				sf2d_draw_texture(DSSelectedBarR, 200, y);
			else
				sf2d_draw_texture(DSNormalBarR, 200, y);
			
			if (pk != -1)
				sf2d_draw_texture_part(spritesSmall, 204, y + 2, 40 * (pk % 25) + 4, 30 * (pk / 25), 34, 30);
			if (sftd_get_text_width(fontBold9, 9, database[page * 10 + i]) <= 148)
				sftd_draw_text(fontBold9, 235, y + 14, WHITE, 9, database[page * 10 + i]);
			else
				sftd_draw_text_wrap(fontBold9, 235, y + 3, WHITE, 9, 148, database[page * 10 + i]);
			
			y += DSSelectedBarR->height;
		}
	sf2d_end_frame();

	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(DSEventBottom, 0, 0);
		sftd_draw_text(fontBold9, (320 - sftd_get_text_width(fontBold9, 9, isSelected ? "Press START to inject, B to return" : "Press A to select, B to return.")) / 2, 222, RGBA8(255, 255, 255, 130), 9, isSelected ? "Press START to inject, B to return" : "Press A to select, B to return.");
		
		if (isSelected) {
			char *languages[7] = {"JPN", "ENG", "FRE", "ITA", "GER", "SPA", "KOR"};
			char *path = (char*)malloc(40 * sizeof(char));
			u8* buf = (u8*)malloc(1500 * sizeof(u8));
			memset(buf, 0, 1500);
			snprintf(path, 40, "romfs:/database/gen4/%d.txt", page * 10 + currentEntry);
			loadFile(buf, path);
			
			sftd_draw_text(fontFixed, 8, 2,  WHITE, 10, (char*)buf);
			
			for (int t = 0; t < 7; t++) {
				int x = 0, y = 178;
				switch (t) {
					case 0 : { x = 25; break; }
					case 1 : { x = 63; break; }
					case 2 : { x = 101; break; }
					case 3 : { x = 139; break; }
					case 4 : { x = 177; break; }
					case 5 : { x = 215; break; }
					case 6 : { x = 253; break; }
				}
				
				sf2d_draw_texture(DSLang, x, y);
				if (langVett[t]) {
					if (t == langSelected) sf2d_draw_texture(DSLangSelected, x, y);
					sftd_draw_text(fontBold12, x + (36 - sftd_get_text_width(fontBold12, 12, languages[t])) / 2, y + 4, WHITE, 12, languages[t]);
				}
				else {
					if (t == langSelected) sf2d_draw_texture(DSLangSelected, x, y);
					sftd_draw_text(fontBold12, x + (36 - sftd_get_text_width(fontBold12, 12, languages[t])) / 2, y + 4, RGBA8(255, 255, 255, 100), 12, languages[t]);
				}
			}

			free(path);
			free(buf);
		}
	
	sf2d_end_frame();
	sf2d_swapbuffers();
}

void printDB7(int sprite, int i, bool langVett[], bool adapt, bool overwrite, int langSelected, int nInjected) {
	char *languages[] = {"JPN", "ENG", "FRE", "ITA", "GER", "SPA", "KOR", "CHS", "CHT"};
	char *path = (char*)malloc(30 * sizeof(char));
	char *cont = (char*)malloc(3 * sizeof(char));
	u8* buf = (u8*)malloc(1500 * sizeof(u8));
	memset(buf, 0, 1499);
	snprintf(path, 30, "romfs:/database/%d.txt", i);
	snprintf(cont, 3, "%d", nInjected + 1);
	loadFile(buf, path);
	
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(eventTop, 0, 0);
		if (sprite != -1)
			sf2d_draw_texture_part_scale(spritesSmall, 282, 46, 40 * (sprite % 25) + 4, 30 * (sprite / 25), 34, 30, 2, 2);
		sftd_draw_text(fontFixed, 5, 28,  WHITE, 10, (char*)buf);
	sf2d_end_frame();
	
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(mainMenuBottom, 0, 0);
		sftd_draw_text(fontBold14, 16, 50, RGBA8(0, 0, 0, 200), 14, "Languages:");
		sftd_draw_text(fontBold14, 33, 112, RGBA8(0, 0, 0, 200), 14, "Overwrite Wondercard:");
		sftd_draw_text(fontBold14, 33, 140, RGBA8(0, 0, 0, 200), 14, "Adapt language to WC:");
		sftd_draw_text(fontBold14, 33, 170, RGBA8(0, 0, 0, 200), 14, "Inject WC in slot:");
		
		for (int t = 0; t < 9; t++) {
			int x = 0, y = 0;
			switch (t) {
				case 0 : { x = 114; y = 50; break; }
				case 1 : { x = 153; y = 50; break; }
				case 2 : { x = 192; y = 50; break; }
				case 3 : { x = 231; y = 50; break; }
				case 4 : { x = 270; y = 50; break; }
				case 5 : { x = 133; y = 74; break; }
				case 6 : { x = 172; y = 74; break; }
				case 7 : { x = 211; y = 74; break; }
				case 8 : { x = 250; y = 74; break; }
			}
			if (langVett[t]) {
				sf2d_draw_texture(darkButton, x, y);
				if (t == langSelected) sf2d_draw_texture(redButton, x, y);
				sftd_draw_text(fontBold14, x + (36 - sftd_get_text_width(fontBold14, 14, languages[t])) / 2, y + 2, WHITE, 14, languages[t]);
			}
			else {
				sf2d_draw_texture(lightButton, x, y);
				if (t == langSelected) sf2d_draw_texture(redButton, x, y);
				sftd_draw_text(fontBold14, x + (36 - sftd_get_text_width(fontBold14, 14, languages[t])) / 2, y + 2, RGBA8(255, 255, 255, 120), 14, languages[t]);
			}
		}
			
		if (overwrite) {
			sf2d_draw_texture(redButton, 210, 110);
			sf2d_draw_texture(darkButton, 249, 110);
		}
		else {
			sf2d_draw_texture(darkButton, 210, 110);
			sf2d_draw_texture(redButton, 249, 110);			
		}
		
		if (adapt) {
			sf2d_draw_texture(redButton, 210, 138);
			sf2d_draw_texture(darkButton, 249, 138);
		}
		else {
			sf2d_draw_texture(darkButton, 210, 138);
			sf2d_draw_texture(redButton, 249, 138);
		}
		
		sf2d_draw_texture(darkButton, 229, 168);	
		
		sftd_draw_text(fontBold14, 210 + (36 - sftd_get_text_width(fontBold14, 14, "Yes")) / 2, 112, WHITE, 14, "Yes");
		sftd_draw_text(fontBold14, 249 + (36 - sftd_get_text_width(fontBold14, 14, "No")) / 2, 112, WHITE, 14, "No");
		sftd_draw_text(fontBold14, 210 + (36 - sftd_get_text_width(fontBold14, 14, "Yes")) / 2, 140, WHITE, 14, "Yes");
		sftd_draw_text(fontBold14, 249 + (36 - sftd_get_text_width(fontBold14, 14, "No")) / 2, 140, WHITE, 14, "No");
		sftd_draw_text(fontBold14, 229 + (36 - sftd_get_text_width(fontBold14, 14, cont)) / 2, 170, WHITE, 14, cont);
		
		sftd_draw_text(fontBold9, (320 - sftd_get_text_width(fontBold9, 9, "Press START to inject, B to return.")) / 2, 226, WHITE, 9, "Press START to inject, B to return.");
	sf2d_end_frame();
	sf2d_swapbuffers();
	
	free(buf);
	free(cont);
	free(path);
}

void printDB6(int sprite, int i, bool langVett[], bool adapt, bool overwrite, int langSelected, int nInjected) {
	char *languages[7] = {"JPN", "ENG", "FRE", "ITA", "GER", "SPA", "KOR"};
	char *path = (char*)malloc(30 * sizeof(char));
	char *cont = (char*)malloc(3 * sizeof(char));
	u8* buf = (u8*)malloc(1500 * sizeof(u8));
	memset(buf, 0, 1499);
	snprintf(path, 30, "romfs:/database/%d.txt", i);
	snprintf(cont, 3, "%d", nInjected + 1);
	loadFile(buf, path);
	
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(eventTop, 0, 0);
		if (sprite != -1)
			sf2d_draw_texture_part_scale(spritesSmall, 282, 46, 40 * (sprite % 25) + 4, 30 * (sprite / 25), 34, 30, 2, 2);
		sftd_draw_text(fontFixed, 5, 28,  WHITE, 10, (char*)buf);
	sf2d_end_frame();
	
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(mainMenuBottom, 0, 0);
		sftd_draw_text(fontBold14, 33, 50, RGBA8(0, 0, 0, 200), 14, "Languages:");
		sftd_draw_text(fontBold14, 33, 112, RGBA8(0, 0, 0, 200), 14, "Overwrite Wondercard:");
		sftd_draw_text(fontBold14, 33, 140, RGBA8(0, 0, 0, 200), 14, "Adapt language to WC:");
		sftd_draw_text(fontBold14, 33, 170, RGBA8(0, 0, 0, 200), 14, "Inject WC in slot:");
		
		for (int t = 0; t < 7; t++) {
			int x = 0, y = 0;
			switch (t) {
				case 0 : { x = 132; y = 50; break; }
				case 1 : { x = 171; y = 50; break; }
				case 2 : { x = 210; y = 50; break; }
				case 3 : { x = 249; y = 50; break; }
				case 4 : { x = 151; y = 74; break; }
				case 5 : { x = 190; y = 74; break; }
				case 6 : { x = 229; y = 74; break; }
			}
			if (langVett[t]) {
				sf2d_draw_texture(darkButton, x, y);
				if (t == langSelected) sf2d_draw_texture(redButton, x, y);
				sftd_draw_text(fontBold14, x + (36 - sftd_get_text_width(fontBold14, 14, languages[t])) / 2, y + 2, WHITE, 14, languages[t]);
			}
			else {
				sf2d_draw_texture(lightButton, x, y);
				if (t == langSelected) sf2d_draw_texture(redButton, x, y);
				sftd_draw_text(fontBold14, x + (36 - sftd_get_text_width(fontBold14, 14, languages[t])) / 2, y + 2, RGBA8(255, 255, 255, 120), 14, languages[t]);
			}
		}
			
		if (overwrite) {
			sf2d_draw_texture(redButton, 210, 110);
			sf2d_draw_texture(darkButton, 249, 110);
		}
		else {
			sf2d_draw_texture(darkButton, 210, 110);
			sf2d_draw_texture(redButton, 249, 110);			
		}
		
		if (adapt) {
			sf2d_draw_texture(redButton, 210, 138);
			sf2d_draw_texture(darkButton, 249, 138);
		}
		else {
			sf2d_draw_texture(darkButton, 210, 138);
			sf2d_draw_texture(redButton, 249, 138);
		}
		
		sf2d_draw_texture(darkButton, 229, 168);	
		
		sftd_draw_text(fontBold14, 210 + (36 - sftd_get_text_width(fontBold14, 14, "Yes")) / 2, 112, WHITE, 14, "Yes");
		sftd_draw_text(fontBold14, 249 + (36 - sftd_get_text_width(fontBold14, 14, "No")) / 2, 112, WHITE, 14, "No");
		sftd_draw_text(fontBold14, 210 + (36 - sftd_get_text_width(fontBold14, 14, "Yes")) / 2, 140, WHITE, 14, "Yes");
		sftd_draw_text(fontBold14, 249 + (36 - sftd_get_text_width(fontBold14, 14, "No")) / 2, 140, WHITE, 14, "No");
		sftd_draw_text(fontBold14, 229 + (36 - sftd_get_text_width(fontBold14, 14, cont)) / 2, 170, WHITE, 14, cont);
		
		sftd_draw_text(fontBold9, (320 - sftd_get_text_width(fontBold9, 9, "Press START to inject, B to return.")) / 2, 226, WHITE, 9, "Press START to inject, B to return.");
	sf2d_end_frame();
	sf2d_swapbuffers();
	
	free(buf);
	free(cont);
	free(path);
}

void printEditor(u8* mainbuf, int game, int currentEntry, int langCont, int badgeCont) {
	int y = 41;
	char *languages[] = {"JPN", "ENG", "FRE", "ITA", "GER", "SPA", "KOR", "CHS", "CHT"};
	char *badges = (char*)malloc(2 * sizeof(char));
	snprintf(badges, 2, "%d", badgeCont);

	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(cleanTop, 0, 0);
		printTitle("Save File Editor");
		
		for (int i = 0; i < 5; i++) {
			if (i == currentEntry)
				sf2d_draw_texture(editorBar, 18, y);
			else
				sf2d_draw_texture(eventMenuTopBar, 18, y);
			
			switch (i) {
				case 0 : {
					int x = 140;
					sftd_draw_text(fontBold12, 40, y + 13, DARKGREY, 12, "Language:");
					sf2d_draw_texture(darkButton, x, y + 10);
					sftd_draw_text(fontBold12, x + (36 - sftd_get_text_width(fontBold12, 12, languages[langCont])) / 2, y + 13, WHITE, 12, languages[langCont]);
					break;
				}
				case 1 : { sftd_draw_text(fontBold12, 18 + (182 - sftd_get_text_width(fontBold12, 12, "Set Heals to max")) / 2, y + 13, DARKGREY, 12, "Set Heals to max"); break; }
				case 2 : { sftd_draw_text(fontBold12, 18 + (182 - sftd_get_text_width(fontBold12, 12, "Set Items to max")) / 2, y + 13, DARKGREY, 12, "Set Items to max"); break; }
				case 3 : { sftd_draw_text(fontBold12, 18 + (182 - sftd_get_text_width(fontBold12, 12, "Set Berries to max")) / 2, y + 13, DARKGREY, 12, "Set Berries to max"); break; }
				case 4 : { sftd_draw_text(fontBold12, 18 + (182 - sftd_get_text_width(fontBold12, 12, "Set all TMs")) / 2, y + 13, DARKGREY, 12, "Set all TMs"); break; }
			}
			
			y += eventMenuTopBarSelected->height;
		}
		
		y = 41;
		for (int i = 5; i < 10; i++) {
			if (i == currentEntry)
				sf2d_draw_texture(editorBar, 200, y);
			else
				sf2d_draw_texture(eventMenuTopBar, 200, y);
			
			switch (i) {
				case 5 : {
					int x = 310;
					sftd_draw_text(fontBold12, 240, y + 13, DARKGREY, 12, "Badges:");
					sf2d_draw_texture(darkButton, x, y + 10);
					sftd_draw_text(fontBold12, x + (36 - sftd_get_text_width(fontBold12, 12, badges)) / 2, y + 13, WHITE, 12, badges);
					break;
				}
				case 6 : { sftd_draw_text(fontBold12, 200 + (182 - sftd_get_text_width(fontBold12, 12, "Clear Mystery Gift box")) / 2, y + 13, DARKGREY, 12, "Clear Mistery Gift box"); break; }
			}
			
			y += eventMenuTopBarSelected->height;
		}
	sf2d_end_frame();

	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(mainMenuBottom, 0, 0);
		sf2d_draw_texture(back, 298, 207);
		
		y = 32;
		// money
		sftd_draw_textf(fontBold11, 15, y + 1, BLACK, 11, "Money: %u$", getMoney(mainbuf, game));
		sf2d_draw_texture(darkButton, 260, y - 3);
		sftd_draw_text(fontBold12, 266, y, WHITE, 12, "SET"); 
		y += 24;
		
		// BP
		sftd_draw_textf(fontBold11, 15, y + 1, BLACK, 11, "Battle Points: %hu", getBP(mainbuf, game));
		sf2d_draw_texture(darkButton, 260, y - 3);
		sftd_draw_text(fontBold12, 266, y, WHITE, 12, "SET"); 
		y += 24;

		sftd_draw_text(fontBold9, (320 - sftd_get_text_width(fontBold9, 9, "Press START to edit, A to toggle, B to exit.")) / 2, 226, WHITE, 9, "Press START to edit, A to toggle, B to exit.");
	sf2d_end_frame();
	sf2d_swapbuffers();
	
	free(badges);
}

u16 getAlternativeSprite(u8* pkmn) {
    u16 tempspecies;
    if (getForm(pkmn)) {
		memcpy(&tempspecies, &personal.pkmData[getPokedexNumber(pkmn)][0x1C], 2);
		
		switch (tempspecies) {
			case 829 : return 2;
			case 922 : return 3;
			case 828 : return 4;
			case 827 : return 5;
			case 945 : return 6;
			case 917 : return 7;
			case 916 : return 8;
			case 921 : return 10;
			case 920 : return 11;
			case 826 : return 12;
			case 919 : return 13;
			case 907 : return 14;
			case 823 : return 15;
			case 918 : return 16;
			case 898 : return 17;
			case 944 : return 18;
			case 913 : return 19;
			case 912 : return 20;
			case 808 : return 21;
			case 911 : return 22;
			case 909 : return 23;
			case 923 : return 24;
			case 908 : return 25;
			case 924 : return 26;
			case 914 : return 27;
			case 915 : return 28;
			case 809 : return 30;
		}
	}
	
	return 0;
}

void printElement(u8* pkmn, u16 n, int x, int y) {
	u16 t = getAlternativeSprite(pkmn);
	if (t) {
		t -= 1;
		sf2d_draw_texture_part(alternativeSpritesSmall, x, y, 40 * (t % 6) + 4, 30 * (t / 6), 34, 30); 
	} else {
		if (isShiny(pkmn))
			sf2d_draw_texture_part(shinySpritesSmall, x, y, 40 * (n % 25) + 4, 30 * (n / 25), 34, 30); 
		else 
			sf2d_draw_texture_part(spritesSmall, x, y, 40 * (n % 25) + 4, 30 * (n / 25), 34, 30);
	}
	if (isEgg(pkmn))
		sf2d_draw_texture_part(spritesSmall, x + 6, y + 6, 40 * (EGGSPRITEPOS % 25) + 4, 30 * (EGGSPRITEPOS / 25), 34, 30);
	if (getItem(pkmn))
		sf2d_draw_texture(item, x + 3, y + 21);
}

void infoViewer(u8* pkmn, const char* title) {
	int y_desc = 33;
	char* entries[] = {"Species:", "Level:", "OT:", "Nickname:", "Nature:", "Ability:", "Item:", "Shiny:", "Pokerus:", "Friendship:", "TID:", "SID:", "Hidden Power:"};
	char* values[] = {"HP:", "Attack:", "Defence:", "Sp. Atk.:", "Sp. Def.:", "Speed:"};
	
	sf2d_draw_texture(infoView, 0, 0);
	sftd_draw_text(fontBold12, 4, 9, WHITE, 12, title);
	sftd_draw_text(fontBold12, 285, 18, WHITE, 12, "STATS");
	sftd_draw_text(fontBold12, 285, 33, WHITE, 12, "IV");
	sftd_draw_text(fontBold12, 315, 33, WHITE, 12, "EV");
	sftd_draw_text(fontBold12, 347, 33, WHITE, 12, "TOTAL");
	sftd_draw_text(fontBold12, 281, 153, WHITE, 12, "MOVES");		
	for (int i = 0; i < 13; i++) {
		sftd_draw_text(fontBold12, 4, y_desc, WHITE, 12, entries[i]);
		y_desc += 15;
	}
	
	y_desc = 48;
	for (int i = 0; i < 6; i++) {
		sftd_draw_text(fontBold12, 216, y_desc, WHITE, 12, values[i]);
		y_desc += 15;
	}
	
	if (getPokedexNumber(pkmn)) {
		sftd_draw_text(fontBold12, 86, 33, WHITE, 12, pokemon[getPokedexNumber(pkmn)]);
		
		char* level = (char*)malloc(4 * sizeof(char));
		snprintf(level, 4, "%u", getLevel(pkmn));
		sftd_draw_text(fontBold12, 86, 48, WHITE, 12, level);
		free(level);
		
		char *ot_name = (char*)malloc(0x17 * sizeof(char));
		sftd_draw_text(fontBold12, 86, 63, WHITE, 12, getOT(pkmn, ot_name));
		free(ot_name);
		
		char *nick = (char*)malloc(26 * sizeof(char));
		sftd_draw_text(fontBold12, 86, 78, WHITE, 12, getNickname(pkmn, nick));
		free(nick);
		
		sftd_draw_text(fontBold12, 86, 93, WHITE, 12, natures[getNature(pkmn)]);
		sftd_draw_text(fontBold12, 86, 108, WHITE, 12, abilities[getAbility(pkmn)]);
		sftd_draw_text(fontBold12, 86, 123, WHITE, 12, items[getItem(pkmn)]);
		sftd_draw_text(fontBold12, 86, 138, WHITE, 12, isShiny(pkmn) ? "Yes" : "No");
		sftd_draw_text(fontBold12, 86, 153, WHITE, 12, isInfected(pkmn) ? "Yes" : "No");
		sftd_draw_textf(fontBold12, 86, 168, WHITE, 12, "%u", getFriendship(pkmn));
		sftd_draw_textf(fontBold12, 86, 183, WHITE, 12, "%u", getOTID(pkmn));
		sftd_draw_textf(fontBold12, 86, 198, WHITE, 12, "%u", getSOTID(pkmn));
		sftd_draw_text(fontBold12, 100, 213, WHITE, 12, hpList[getHPType(pkmn)]);
		
		int pos = 279;
		int max = sftd_get_text_width(fontBold12, 12, "252");
		char* hp_iv = (char*)malloc(3 * sizeof(char));
		char* atk_iv = (char*)malloc(3 * sizeof(char));
		char* def_iv = (char*)malloc(3 * sizeof(char));
		char* spa_iv = (char*)malloc(3 * sizeof(char));
		char* spd_iv = (char*)malloc(3 * sizeof(char));
		char* spe_iv = (char*)malloc(3 * sizeof(char));
		char* hp_ev = (char*)malloc(4 * sizeof(char));
		char* atk_ev = (char*)malloc(4 * sizeof(char));
		char* def_ev = (char*)malloc(4 * sizeof(char));
		char* spa_ev = (char*)malloc(4 * sizeof(char));
		char* spd_ev = (char*)malloc(4 * sizeof(char));
		char* spe_ev = (char*)malloc(4 * sizeof(char));
		char* hp_stat = (char*)malloc(4 * sizeof(char));
		char* atk_stat = (char*)malloc(4 * sizeof(char));
		char* def_stat = (char*)malloc(4 * sizeof(char));
		char* spa_stat = (char*)malloc(4 * sizeof(char));
		char* spd_stat = (char*)malloc(4 * sizeof(char));
		char* spe_stat = (char*)malloc(4 * sizeof(char));
		snprintf(hp_iv, 3, "%d", getIV(pkmn, 0));
		snprintf(atk_iv, 3, "%d", getIV(pkmn, 1));
		snprintf(def_iv, 3, "%d", getIV(pkmn, 2));
		snprintf(spa_iv, 3, "%d", getIV(pkmn, 4));
		snprintf(spd_iv, 3, "%d", getIV(pkmn, 5));
		snprintf(spe_iv, 3, "%d", getIV(pkmn, 3));
		snprintf(hp_ev, 4, "%d", getEV(pkmn, 0));
		snprintf(atk_ev, 4, "%d", getEV(pkmn, 1));
		snprintf(def_ev, 4, "%d", getEV(pkmn, 2));
		snprintf(spa_ev, 4, "%d", getEV(pkmn, 4));
		snprintf(spd_ev, 4, "%d", getEV(pkmn, 5));
		snprintf(spe_ev, 4, "%d", getEV(pkmn, 3));
		snprintf(hp_stat, 4, "%d", getStat(pkmn, 0));
		snprintf(atk_stat, 4, "%d", getStat(pkmn, 1));
		snprintf(def_stat, 4, "%d", getStat(pkmn, 2));
		snprintf(spa_stat, 4, "%d", getStat(pkmn, 4));
		snprintf(spd_stat, 4, "%d", getStat(pkmn, 5));
		snprintf(spe_stat, 4, "%d", getStat(pkmn, 3));
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, hp_iv)) / 2, 48, WHITE, 12, hp_iv);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, atk_iv)) / 2, 63, WHITE, 12, atk_iv);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, def_iv)) / 2, 78, WHITE, 12, def_iv);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, spa_iv)) / 2, 93, WHITE, 12, spa_iv);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, spd_iv)) / 2, 108, WHITE, 12, spd_iv);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, spe_iv)) / 2, 123, WHITE, 12, spe_iv);
		pos = 311;
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, hp_ev)) / 2, 48, WHITE, 12, hp_ev);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, atk_ev)) / 2, 63, WHITE, 12, atk_ev);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, def_ev)) / 2, 78, WHITE, 12, def_ev);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, spa_ev)) / 2, 93, WHITE, 12, spa_ev);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, spd_ev)) / 2, 108, WHITE, 12, spd_ev);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, spe_ev)) / 2, 123, WHITE, 12, spe_ev);
		pos = 354;
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, hp_stat)) / 2, 48, WHITE, 12, hp_stat);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, atk_stat)) / 2, 63, WHITE, 12, atk_stat);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, def_stat)) / 2, 78, WHITE, 12, def_stat);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, spa_stat)) / 2, 93, WHITE, 12, spa_stat);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, spd_stat)) / 2, 108, WHITE, 12, spd_stat);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, spe_stat)) / 2, 123, WHITE, 12, spe_stat);
		
		int y_moves = 168;
		for (int i = 0; i < 4; i++) {
			if (getMove(pkmn, i)) {
				sftd_draw_text(fontBold12, 216, y_moves, WHITE, 12, moves[getMove(pkmn, i)]);
			}
			y_moves += 15;
		}
		
		free(hp_iv);
		free(atk_iv);
		free(def_iv);
		free(spa_iv);
		free(spd_iv);
		free(spe_iv);
		free(hp_ev);
		free(atk_ev);
		free(def_ev);
		free(spa_ev);
		free(spd_ev);
		free(spe_ev);
		free(hp_stat);
		free(atk_stat);
		free(def_stat);
		free(spa_stat);
		free(spd_stat);
		free(spe_stat);
	}
}

void printPKViewer(u8* mainbuf, int game, int currentEntry, int box, bool cloning) {
	int x;
	char* page = (char*)malloc(7 * sizeof(char));
	snprintf(page, 7, "Box %d", box + 1);
	
	u8* pkmn = (u8*)malloc(PKMNLENGTH * sizeof(u8));
	getPkmn(mainbuf, box, currentEntry, pkmn, game);
	
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		infoViewer(pkmn, "POKEMON EDITOR");
	sf2d_end_frame();

	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(boxView, 0, 0);
		sf2d_draw_texture(LRBar, 12, 10);
		sftd_draw_text(fontBold12, 12 + (LRBar->width - sftd_get_text_width(fontBold12, 12, page)) / 2, 15, WHITE, 12, page);
		sf2d_draw_texture(left, 2, 11);
		sf2d_draw_texture(right, LRBar->width+7, 11);
		sf2d_draw_texture(back, 288, 217);
		if(!(cloning)) {
			sf2d_draw_texture(topButton, 214, 89);
			sftd_draw_text(fontBold12, 214 + (106 - sftd_get_text_width(fontBold12, 12, "A: EDIT")) / 2, 96, BLACK, 12, "A: EDIT");
		}
		sf2d_draw_texture(bottomButton, 214, 121);
		sftd_draw_text(fontBold12, 214 + (106 - sftd_get_text_width(fontBold12, 12, "Y: CLONE")) / 2, 128, BLACK, 12, "Y: CLONE");
		
		int y = 45;
		int pointer[2] = {0, 0};
		for (int i = 0; i < 5; i++) {
			x = 4;
			for (int j = 0; j < 6; j++) {
				getPkmn(mainbuf, box, i*6+j, pkmn, game);
				u16 n = getPokedexNumber(pkmn);
				if (n)
					printElement(pkmn, n, x, y);

				if (currentEntry == (i * 6 + j)) {
					pointer[0] = x + 18;
					pointer[1] = y - 8;
				}
				x += 34;
			}
			y += 30;
		}
		if (!(cloning))
			sf2d_draw_texture(selector, pointer[0], pointer[1]);
		else {
			sf2d_draw_texture(selectorCloning, pointer[0], pointer[1]);
			sf2d_draw_texture(bottomPopUp, 0, 201);
			sftd_draw_text(fontBold11, 10, 214, WHITE, 11, "Press A to clone in selected slot, B to cancel");
		}
		
	sf2d_end_frame();
	sf2d_swapbuffers();
	
	free(pkmn);
	free(page);
}

void printPKEditor(u8* pkmn, int game, bool speedy) {
	int y_desc = 41;
	int max = sftd_get_text_width(fontBold12, 12, "252");
	char* entries[9] = {"Level:", "Nature:", "Friendship:", "Item:", "Shiny:", "Pokerus:", "Ability:", "Nickname:", "Hidden Power:"};
	char* values[6] = {"HP:", "Attack:", "Defence:", "Sp. Atk.:", "Sp. Def.:", "Speed:"};
	u16 n = getPokedexNumber(pkmn);
	
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sftd_draw_text(fontBold15, (400 - sftd_get_text_width(fontBold15, 15, "Edit your Pokemon in the bottom screen")) / 2, 95, RGBA8(255, 255, 255, giveTransparence()), 15, "Edit your Pokemon in the bottom screen");
		sftd_draw_text(fontBold15, (400 - sftd_get_text_width(fontBold15, 15, "Tap SAVE when you're done")) / 2, 115, RGBA8(255, 255, 255, giveTransparence()), 15, "Tap SAVE when you're done");
	sf2d_end_frame();
	
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(editorBG, 0, 0);
		sf2d_draw_texture(bottomButton, 200, 140);
		sf2d_draw_texture(buttonSave, 200, 170);
		sftd_draw_text(fontBold12, 230, 147, BLACK, 12, "MOVES");
		sftd_draw_text(fontBold12, 236, 177, BLACK, 12, "SAVE");
		
		printElement(pkmn, n, 1, -2);

		sftd_draw_text(fontBold14, 38, 5, BLACK, 14, pokemon[n]);
		
		for (int i = 0; i < 9; i++) {
			sftd_draw_text(fontBold12, 5, y_desc, WHITE, 12, entries[i]);
			y_desc += 17;
		}
		
		y_desc = 27;
		for (int i = 0; i < 6; i++) {
			sftd_draw_text(fontBold12, 151, y_desc, WHITE, 12, values[i]);
			y_desc += 17;
		}
		
		sftd_draw_text(fontBold12, 225, 10, WHITE, 12, "IV");
		sftd_draw_text(fontBold12, 274, 10, WHITE, 12, "EV");

		sf2d_draw_texture(minus, 86, 42);
		sf2d_draw_texture(plus, 127, 42);
		
		y_desc = 60;
		for (int i = 0; i < 5; i++) {
			if (i != 1)
				sf2d_draw_texture(setting, 126, y_desc);
			y_desc += 17;
		}

		sf2d_draw_texture(setting, 150, 144);
		sf2d_draw_texture(minus, 86, 76);
		sf2d_draw_texture(plus, 127, 76);
		sf2d_draw_texture(setting, 162, 162);
		sf2d_draw_texture(setting, 162, 178);

		char* level = (char*)malloc(4 * sizeof(char));
		snprintf(level, 4, "%u", getLevel(pkmn));
		sftd_draw_text(fontBold12, 100 + (max - sftd_get_text_width(fontBold12, 12, level)) / 2, 41, GOLD, 12, level);
		free(level);
			
		sftd_draw_text(fontBold12, 124 - sftd_get_text_width(fontBold12, 12, natures[getNature(pkmn)]), 58, GOLD, 12, natures[getNature(pkmn)]);
		sftd_draw_text(fontBold12, 148 - sftd_get_text_width(fontBold12, 12, abilities[getAbility(pkmn)]), 143, GOLD, 12, abilities[getAbility(pkmn)]);
		sftd_draw_text(fontBold12, 124 - sftd_get_text_width(fontBold12, 12, items[getItem(pkmn)]), 92, GOLD, 12, items[getItem(pkmn)]);
		sftd_draw_text(fontBold12, 124 - sftd_get_text_width(fontBold12, 12, isShiny(pkmn) ? "Yes" : "No"), 109, GOLD, 12, isShiny(pkmn) ? "Yes" : "No");
		sftd_draw_text(fontBold12, 124 - sftd_get_text_width(fontBold12, 12, isInfected(pkmn) ? "Yes" : "No"), 126, GOLD, 12, isInfected(pkmn) ? "Yes" : "No");
		
		char* friendship = (char*)malloc(4 * sizeof(char));
		snprintf(friendship, 4, "%u", getFriendship(pkmn));
		sftd_draw_text(fontBold12, 100 + (max - sftd_get_text_width(fontBold12, 12, friendship)) / 2, 75, GOLD, 12, friendship);
		free(friendship);
		
		char *nick = (char*)malloc(26 * sizeof(char));
		sftd_draw_text(fontBold12, 72, 160, GOLD, 12, getNickname(pkmn, nick));
		free(nick);
		
		sftd_draw_text(fontBold12, 159 - sftd_get_text_width(fontBold12, 12, hpList[getHPType(pkmn)]), 177, GOLD, 12, hpList[getHPType(pkmn)]);
		
		char* hp_iv = (char*)malloc(3 * sizeof(char));
		char* atk_iv = (char*)malloc(3 * sizeof(char));
		char* def_iv = (char*)malloc(3 * sizeof(char));
		char* spa_iv = (char*)malloc(3 * sizeof(char));
		char* spd_iv = (char*)malloc(3 * sizeof(char));
		char* spe_iv = (char*)malloc(3 * sizeof(char));
		char* hp_ev = (char*)malloc(4 * sizeof(char));
		char* atk_ev = (char*)malloc(4 * sizeof(char));
		char* def_ev = (char*)malloc(4 * sizeof(char));
		char* spa_ev = (char*)malloc(4 * sizeof(char));
		char* spd_ev = (char*)malloc(4 * sizeof(char));
		char* spe_ev = (char*)malloc(4 * sizeof(char));
		snprintf(hp_iv, 3, "%d", getIV(pkmn, 0));
		snprintf(atk_iv, 3, "%d", getIV(pkmn, 1));
		snprintf(def_iv, 3, "%d", getIV(pkmn, 2));
		snprintf(spa_iv, 3, "%d", getIV(pkmn, 4));
		snprintf(spd_iv, 3, "%d", getIV(pkmn, 5));
		snprintf(spe_iv, 3, "%d", getIV(pkmn, 3));
		snprintf(hp_ev, 4, "%d", getEV(pkmn, 0));
		snprintf(atk_ev, 4, "%d", getEV(pkmn, 1));
		snprintf(def_ev, 4, "%d", getEV(pkmn, 2));
		snprintf(spa_ev, 4, "%d", getEV(pkmn, 4));
		snprintf(spd_ev, 4, "%d", getEV(pkmn, 5));
		snprintf(spe_ev, 4, "%d", getEV(pkmn, 3));
		
		int pos = 219;
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, hp_iv)) / 2, 27, GOLD, 12, hp_iv);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, atk_iv)) / 2, 44, GOLD, 12, atk_iv);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, def_iv)) / 2, 61, GOLD, 12, def_iv);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, spa_iv)) / 2, 78, GOLD, 12, spa_iv);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, spd_iv)) / 2, 95, GOLD, 12, spd_iv);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, spe_iv)) / 2, 112, GOLD, 12, spe_iv);
		pos = 270;
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, hp_ev)) / 2, 27, GOLD, 12, hp_ev);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, atk_ev)) / 2, 44, GOLD, 12, atk_ev);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, def_ev)) / 2, 61, GOLD, 12, def_ev);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, spa_ev)) / 2, 78, GOLD, 12, spa_ev);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, spd_ev)) / 2, 95, GOLD, 12, spd_ev);
		sftd_draw_text(fontBold12, pos + (max - sftd_get_text_width(fontBold12, 12, spe_ev)) / 2, 112, GOLD, 12, spe_ev);
		
		y_desc = 27;
		for (int i = 0; i < 6; i++) {
			sf2d_draw_texture(minus, 207, y_desc);
			sf2d_draw_texture(plus, 242, y_desc);
			sf2d_draw_texture(minus, 257, y_desc);
			sf2d_draw_texture(plus, 296, y_desc);
			y_desc += 17;
		}
		
		free(hp_iv);
		free(atk_iv);
		free(def_iv);
		free(spa_iv);
		free(spd_iv);
		free(spe_iv);
		free(hp_ev);
		free(atk_ev);
		free(def_ev);
		free(spa_ev);
		free(spd_ev);
		free(spe_ev);
		
		sf2d_draw_texture(bottomPopUp, 0, 201);
		sf2d_draw_texture(back, 288, 213);
		sftd_draw_textf(fontBold11, 10, 214, WHITE, 11, "You can switch speed using (L/R): %s", speedy ? "FAST" : "SLOW");
		
	sf2d_end_frame();
	sf2d_swapbuffers();
}

void printPKBank(u8* bankbuf, u8* mainbuf, u8* pkmnbuf, int game, int currentEntry, int box, bool isBank) {
	int x;
	char* page = (char*)malloc(10 * sizeof(char));
	
	if (isBank) snprintf(page, 10, "Bank %d", box + 1);
	else snprintf(page, 10, "Save %d", box + 1);
	
	u8* pkmn = (u8*)malloc(PKMNLENGTH * sizeof(u8));
	if (isBank)
		memcpy(pkmn, &bankbuf[box * 30 * PKMNLENGTH + currentEntry * PKMNLENGTH], PKMNLENGTH);
	else
		getPkmn(mainbuf, box, currentEntry, pkmn, game);
	
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		infoViewer(pkmn, "BANK");
	sf2d_end_frame();

	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		if (!(isBank))
			sf2d_draw_texture(boxView, 0, 0);
		else
			sf2d_draw_texture(bankBottomBG, 0, 0);
		sf2d_draw_texture(LRBar, 12, 10);
		sftd_draw_text(fontBold12, 12 + (LRBar->width - sftd_get_text_width(fontBold12, 12, page)) / 2, 15, WHITE, 12, page);
		sf2d_draw_texture(left, 2, 11);
		sf2d_draw_texture(right, LRBar->width+7, 11);
		sf2d_draw_texture(topButton, 214, 12);
		sf2d_draw_texture(topButton, 214, 44);
		sf2d_draw_texture(topButton, 214, 76);
		sf2d_draw_texture(bottomButton, 214, 108);
		sftd_draw_text(fontBold12, 214 + (106 - sftd_get_text_width(fontBold12, 12, "A: BUFFER")) / 2, 19, BLACK, 12, "A: BUFFER");
		sftd_draw_text(fontBold12, 214 + (106 - sftd_get_text_width(fontBold12, 12, "X: SWITCH B/S")) / 2, 51, BLACK, 12, "X: SWITCH B/S");
		
		sftd_draw_text(fontBold12, 214 + (106 - sftd_get_text_width(fontBold12, 12, "CLEAN")) / 2, 83, BLACK, 12, "CLEAN");
		sftd_draw_text(fontBold12, 214 + (106 - sftd_get_text_width(fontBold12, 12, "SWAP")) / 2, 115, BLACK, 12, "SWAP");

		sf2d_draw_texture(pokemonBufferBox, 238, 150);
		u16 n = getPokedexNumber(pkmnbuf);
		if (n) {
			if (isShiny(pkmnbuf))
				sf2d_draw_texture_part(shinySpritesSmall, 250, 159, 40 * (n % 25) + 4, 30 * (n / 25), 34, 30); 
			else 
				sf2d_draw_texture_part(spritesSmall, 250, 159, 40 * (n % 25) + 4, 30 * (n / 25), 34, 30);
		}
		
		int y = 45;
		int pointer[2] = {0, 0};
		for (int i = 0; i < 5; i++) {
			x = 4;
			for (int j = 0; j < 6; j++) {
				if (isBank)	memcpy(pkmn, &bankbuf[box * 30 * PKMNLENGTH + (i*6+j) * PKMNLENGTH], PKMNLENGTH);
				else getPkmn(mainbuf, box, i*6+j, pkmn, game);
				u16 n = getPokedexNumber(pkmn);
				if (n)
					printElement(pkmn, n, x, y);

				if (currentEntry == (i * 6 + j)) {
					pointer[0] = x + 18;
					pointer[1] = y - 8;
				}
				x += 34;
			}
			y += 30;
		}
		
		sf2d_draw_texture(selectorCloning, pointer[0], pointer[1]);	
		
		sf2d_draw_texture(back, 288, 217);
	sf2d_end_frame();
	sf2d_swapbuffers();
	
	free(pkmn);
	free(page);
}

void printMassInjector(int currentEntry) {
	int y = 41;
	char* entries[] = {"XD Collection", "Colosseum Collection", "10th Anniversary Collection", "N's Collection", "Entree Forest Collection", "Dream Radar Collection", "Living Dex", "Oblivia Deoxys Collection", "Pokemon Ranch Collection", "KOR Events Collection"};
	int boxes[] = {3, 2, 1, 1, 1, 1, 24, 1, 1, 1};
	
	char* message = (char*)malloc(30 * sizeof(char));
	snprintf(message, 30, "%d boxes will be replaced.", boxes[currentEntry]);
	
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(cleanTop, 0, 0);
		printTitle("Mass Injector");
		
		for (int i = 0; i < 5; i++) {
			if (i == currentEntry)
				sf2d_draw_texture(editorBar, 18, y);
			else
				sf2d_draw_texture(eventMenuTopBar, 18, y);
			
			sftd_draw_text(fontBold12, 18 + (182 - sftd_get_text_width(fontBold12, 12, entries[i])) / 2, y + 13, DARKGREY, 12, entries[i]);
			
			y += eventMenuTopBarSelected->height;
		}
		
		y = 41;
		for (int i = 5; i < 10; i++) {
			if (i == currentEntry)
				sf2d_draw_texture(editorBar, 200, y);
			else
				sf2d_draw_texture(eventMenuTopBar, 200, y);
			
			sftd_draw_text(fontBold12, 200 + (182 - sftd_get_text_width(fontBold12, 12, entries[i])) / 2, y + 13, DARKGREY, 12, entries[i]);
			
			y += eventMenuTopBarSelected->height;
		}
	sf2d_end_frame();

	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(mainMenuBottom, 0, 0);
		sf2d_draw_texture(back, 298, 207);
		sftd_draw_text(fontBold12, (320 - sftd_get_text_width(fontBold12, 12, message)) / 2, 114, BLACK, 12, message);
		sftd_draw_text(fontBold9, (320 - sftd_get_text_width(fontBold9, 9, "Press START to inject, B to exit.")) / 2, 226, WHITE, 9, "Press START to inject, B to exit.");
	sf2d_end_frame();
	sf2d_swapbuffers();
	
	free(message);
}

void printMoves(u8* pkmn, int currentEntry, int entryBottom, int page) {
	int y = 0, x = 30;
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(topMovesBG, 0, 0);
		
		for (int i = 0; i < 20; i++) {
			if (i == currentEntry) sf2d_draw_texture(topSelectedMove, x, y);
			sftd_draw_textf(fontBold9, x + 2, y, WHITE, 9, "%d - %s", 40 * page + i, movesSorted[40 * page + i]);
			y += topSelectedMove->height;
		}
		
		y = 0;
		x = 200;
		
		for (int i = 20; i < 40; i++) {
			if (i == currentEntry) sf2d_draw_texture(topSelectedMove, x, y);
			sftd_draw_textf(fontBold9, x + 2, y, WHITE, 9, "%d - %s", 40 * page + i, movesSorted[40 * page + i]);
			y += topSelectedMove->height;
		}	
	sf2d_end_frame();

	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(bottomMovesBG, 0, 0);
		
		x = 123;
		y = 10;
		for (int i = 0; i < 4; i++) {
			sf2d_draw_texture(bottomMovesBar, x, y);
			sf2d_draw_texture(bottomMovesBar, x, y + 119);
			sftd_draw_text(fontBold11, x + 15, y + 5, (i == entryBottom) ? BLACK : WHITE, 11, moves[getMove(pkmn, i)]);
			sftd_draw_text(fontBold11, x + 15, y + 119 + 5, (i == entryBottom - 4) ? BLACK : WHITE, 11, moves[getEggMove(pkmn, i)]);
			
			if (i == entryBottom)
				sf2d_draw_texture(left, 302, y + 2);
			else if (i == entryBottom - 4)
				sf2d_draw_texture(left, 302, y + 119 + 2);
			
			y += 26;
		}
		
		sf2d_draw_texture(bottomMovesBarCut, 0, 23);
		sf2d_draw_texture(bottomMovesBarCut, 0, 142);
		sftd_draw_text(fontBold11, 12, 28, WHITE, 11, "Moves");
		sftd_draw_text(fontBold11, 12, 147, WHITE, 11, "Relearn Moves");
	sf2d_end_frame();
	sf2d_swapbuffers();	
}

void printItems(u8* pkmn, int currentEntry, int page) {
	int y = 0, x = 30;
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(topMovesBG, 0, 0);
		
		for (int i = 0; i < 20; i++) {
			if (i == currentEntry) sf2d_draw_texture(topSelectedMove, x, y);
			sftd_draw_textf(fontBold9, x + 2, y, WHITE, 9, "%d - %s", 40 * page + i, itemsSorted[40 * page + i]);
			y += topSelectedMove->height;
		}
		
		y = 0;
		x = 200;
		
		for (int i = 20; i < 40; i++) {
			if (i == currentEntry) sf2d_draw_texture(topSelectedMove, x, y);
			sftd_draw_textf(fontBold9, x + 2, y, WHITE, 9, "%d - %s", 40 * page + i, itemsSorted[40 * page + i]);
			y += topSelectedMove->height;
		}
		
	sf2d_end_frame();

	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(bottomMovesBG, 0, 0);
		
		x = (320 - bottomMovesBar->width) / 2;
		y = (240 - bottomMovesBar->height) / 2;

		sf2d_draw_texture(bottomMovesBar, x, y);
		sftd_draw_text(fontBold11, (320 - sftd_get_text_width(fontBold11, 11, items[getItem(pkmn)])) / 2, y + 5, WHITE, 11, items[getItem(pkmn)]);

		sftd_draw_text(fontBold9, (320 - sftd_get_text_width(fontBold9, 9, "Press A to set, B to return.")) / 2, 226, WHITE, 9, "Press A to set, B to return.");
	sf2d_end_frame();
	sf2d_swapbuffers();	
}

void printSettings(int box, bool speedy, int game) {
	char *gamesList[] = {"X", "Y", "OR", "AS", "S", "M", "D", "P", "PL", "HG", "SS", "B", "W", "W2", "B2"};
	char *bakpath = (char*)malloc(80 * sizeof(char));
	char *bankbakpath = (char*)malloc(80 * sizeof(char));
	
	time_t unixTime = time(NULL);
	struct tm* timeStruct = gmtime((const time_t *)&unixTime);		
	snprintf(bakpath, 80, "main_%s_%i%i%i%02i%02i%02i", gamesList[game], timeStruct->tm_mday, timeStruct->tm_mon + 1, timeStruct->tm_year + 1900, timeStruct->tm_hour, timeStruct->tm_min, timeStruct->tm_sec);
	snprintf(bankbakpath, 80, "bank_%i%i%i%02i%02i%02i", timeStruct->tm_mday, timeStruct->tm_mon + 1, timeStruct->tm_year + 1900, timeStruct->tm_hour, timeStruct->tm_min, timeStruct->tm_sec);
	
	int y = 45;
	
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		drawMenuTop(0);
	sf2d_end_frame();
	
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(mainMenuBottom, 0, 0);
		sf2d_draw_texture(back, 298, 207);
		
		// bank size
		sftd_draw_textf(fontBold11, 15, y + 1, BLACK, 11, "Bank size: %d boxes", box);
		sf2d_draw_texture(darkButton, 220, y - 3);
		sf2d_draw_texture(minus, 223, y + 1);
		sf2d_draw_texture(plus, 240, y + 1);
		sf2d_draw_texture(darkButton, 260, y - 3);
		sftd_draw_text(fontBold12, 268, y, WHITE, 12, "OK"); 
		
		// save backup
		y += 27;
		sftd_draw_textf(fontBold11, 15, y + 1, BLACK, 11, "Backup save: %s", bakpath);
		sf2d_draw_texture(darkButton, 260, y - 3);
		sftd_draw_text(fontBold12, 268, y, WHITE, 12, "OK");
		
		// save bank backup
		y += 27;
		sftd_draw_textf(fontBold11, 15, y + 1, BLACK, 11, "Backup bank: %s", bankbakpath);
		sf2d_draw_texture(darkButton, 260, y - 3);
		sftd_draw_text(fontBold12, 268, y, WHITE, 12, "OK");

		sftd_draw_textf(fontBold9, 15, 200, DARKGREY, 9, "You can switch speed using (L/R): %s", speedy ? "FAST" : "SLOW");
		sftd_draw_text(fontBold9, (320 - sftd_get_text_width(fontBold9, 9, "Press B to return.")) / 2, 226, WHITE, 9, "Press B to return.");
	sf2d_end_frame();
	sf2d_swapbuffers();
	
	free(bakpath);
	free(bankbakpath);
}
# 3DS Card Collection

A project that's main purpose is to experiment with 3DS local wireless (UDS).
Plus, I love card games and think the 3DS would be a perfect platform for a
plethora of them.

This project aims to be a card game *engine*, allowing people to write their
own games (eventually in Lua, but for now just in C++).

## The Table Engine

The core of this project is going to be split into 3 parts: the table engine,
board engine, and scene manager.  I'll go into some details about the
architecture of each and how they communicate.

For the table engine, it's job is simple: to facilitate and manage the local
wireless communication, and synchronize packets between consoles. For example,
let's say the board engine pushes an update where they draw a the 4 of spades.
The table engine would then recieve the new board state, calculate a diff, and
forward it to all the consoles.

In cases of a conflict, where the diff cannot be applied, then the client
shoud request a resync frame from the host (a frame containing the entire state
of the game) and go from there (if the same action can be applied, just with a
different result, then do that). If a client sends a diff that the host cannot
apply, then the host will automatically send a resync frame to the client.

### Game frames

There's 3 (will change later) types of frames:

1. Initalization frame - sends the required game data (the Lua file, if external
game, or game ID if a built-in game)
2. Sync frame - contains all *public* information about the game:
    * shuffled deck state
    * any table-bound cards (the card in-play for Uno)
    * player hands (you should trust your friends, so you should trust your
    friends game clients)
        * possibly use a different appdata ID for dev and release builds, so
        you KNOW if your friends could potentially cheat with devtools
3. Diff frame - doesn't contain all game data, just a diffed format of the game
details (for example, a note that you drew from the deck, or that you played a
certain card)
    * specifics of this frame's format will be unclear for now - still need to
    weight the tradeoff of small packets and ensuring data is synchronized

## Board Engine

Main data layer of the application - interacted with by the individual games
(eventually lua-based, C++ classes for now). Synchronizes data to and from the
table engine, applying diffs and requesting resync frames. Then, package this
data for the scene manager to render the scene.

When making games in Lua, the data and visual representation will be very
similar. For example, you'd have a `Hand` meta-object that both synchronizes a
player's cards and renders into a fan or grid of cards on the bottom screen

The board engine will always render underneath the scene's menu layout, for UI
and such.

## Scene Manager

This is the part I'm most unsure about, because I've not really made
scene-based apps in C++ or with SDL before. Nevertheless, the scene manager
will have a hierarchy of scenes that it can load into, and scenes can transfer
between themselves as needed passing state.

As an example, you'd load into a `MainMenu` scene (an instance of `MenuScene`)
that would instantiate `MenuButton` objects that handle rendering and touch
detection, and optionally a gamepad button binding or menu grid organization.

TODO - a lot of thinking about this.

## Note about this README

This readme is just my initial ramblings about how this project will be
structured. I'm going to document my code along the way so you can see
*exactly* where I'm taking this inital rambling. Eventually, this will contain
information about building from source/installing a CIA, along with community
games and game creation.

Also, I have not modified anything I've typed so far. I sat down, opened this
file, and let my fingers just go. Please excuse the overuse of examples and
lack of polish. I just want this repository to have an initial commit.

# Class structure design document
Classes should be made to manage everything practical to do with one part of the game. For instance, the `gameManager` class should store current game state and handle other classes like `mapManager`, `playerCharacter`, and provide functions for `main()` to use.

If you feel like there is anything missing, submit a PR with an explanation of what changed and why for review, and be prepared to discuss your choices further. Please make one commit per change (for instance, changing a name *and its usages*) so that if one is wanted and the other is not, it's easier to manage.

## gameManager
- Game time tracking, including functions to get, set, and advance by X amount of time
- currentMap tracking. Pointer to `mapManager`, and index (likely through enum) for current map
- Character tracking, both PCs and NPCs. Array of pointers to `character` objects.

## mapManager
- Array of pointers for map objects, and enum for builtins
- Functions to load in new maps, and destroy unneeded ones in case of low memory
- Functions for switching maps, and handling map events in unloaded maps (such as NPC navigation)

## map
- Implementation of map structure, both textures and collision data
- Loading in texture chunks of 512x512 pixels (subject to change so don't hardcode the maths)
- Calculating which map chunks should be rendered on screen, given current resolution and camera location
- Functions for calculating if map should be unlocked, available, etc
- Keeping track of transition points, to move to new map

## character
- Hold sprite for rendering, movement speed, and status

## playerCharacter
- Hold current inventory, monetary balance, and more detailed status effects
- Hold information about relationships, skills, and experience

## nonPlayerCharacter
- Hold schedule and pathing data
- Hold relationship data and dialogue trees



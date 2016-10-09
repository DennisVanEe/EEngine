# EEngine
A 2D video game engine based on SFML with support for the AngelScript language.

The Game Engine has no UI and is a single executable. The game is programmed entirely through AngelScript modules that control graphics, resource loading, sound etc. Resources (like levels and textures and sprites) are defined using xml. The necessary files are placed in the same directory as the engine executable, and running the engine executable will in turn execute the initialization module which will execute the rest of the modules (resource loading, AI, etc.)

Currently, the engine works on a single thread and uses a queue-messenger for modules to communicate with the engine (loading resources) and between modules (sending data). Data can also be stored either in a data module (an AngelScript module) or a data container, which is a proprietary binary file that associates data with strings and can be used as a "save file".

The Aeneid Video Game was being built for the EEngine
https://github.com/DennisVanEe/Aeneid_the_Video_Game

The EEngine did not provide any help when it comes to syntax checking for the individual modules. For this reason, a separate program was created to only check the syntax of AngelScript modules written for the EEngine.
https://github.com/DennisVanEe/EEngine_Syntax_Checker

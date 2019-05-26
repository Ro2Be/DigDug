# DigDug
Git: https://github.com/Ro2Be/DigDug

Made by Demey Robbe

Description:
Assignment for DAE - Game Development - Programming 4
Making a 2D game engine from scratch and make the Dig Dug game in that engine.

Game controlls:
asdw to move
e to attack
Controller to controll fygar

Engine commands (in console):
ShowGameObjects to see active gameobjects
Pause to pause the game
Unpause to unpause the game

Design choices:
- Very basic base component
Components don't need to be anything, they only need a WakeUp and an Update function, and a isActive variable. This allows a general call of all the wakeups at the start of the scene and the update calls during the game, the isActive allows to disable certain components.

- RenderableComponent
This is a basecomponent for all components that need to get rendered, I know inheretance, but this allows the renderer to call the virtual renderableComponent.Draw() function an all the renderableComponents. The renderer knows about these components because of the shared baseconstructor that saves a pointer to the component in the renderer. At this point there are only two type of renderable components: texture and tilemap (the tilemap is used for the background and the healthdisplay)

- Component system without default reference to the gameobject
Since you can always pass the active gameobject as a parameter (awake, update, ...) its waistfull to save a copy in the component itself, some components still need a reference to the gameobject to do certain things on events but there is no need to make it default.

- GameObject.GetComponent, GameObjectGetComponents, GameObject.GetActiveComponent
You can acces the first component found of a certain type, all components of a certain type or the first active active component of a certain type. The last one is usefull in the stateComponent system, more on that later.

- Bridging with unordered maps of strings to pointers
I'm using a lot of unordered maps to allow the user to (fast) acces certain data with strings, but the data itself is saved in vector so you can loop fast over them.

- StateComponent
Since a state has update, and a component has an update I tried merging these two in a stateComponent. You just disable the states youre not using, and use the GameObject.GetActiveComponent<StateComponent> to find the active state. The change state function makes sure there is always only one function active.

- Threaded game and engine
The game runs on a different thread than the engine (console), this allows you to give commands to the engine that get info from the game or that pause/unpause the game, more options are possible. Once the game is finished you just add a version of the lib without all the engine code for optimization.

- Crappy code
I loved working on this project, and started with making everything as good as possible, redoing certains systems up to four times just to get it right. And it was fun and I learned a lot, but then you notice how little time you have combined with all the other assignments, and you can't to anything else then just rush it, make it brikka brak, and without trying new stuff. It's a waist because this could have been a nice project to put on our portofolio. So I appologise for any unreadable code, strange ways of doing things, and the fact that the game is unfinished.
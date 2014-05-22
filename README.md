timelinefx
==========

[TimelineFX](http://www.rigzsoft.co.uk/) particle system in C++ with Marmalade as sample.

This is a C++ library to read, process and show particles from [TimelineFX Editor](http://www.rigzsoft.co.uk/).
It's ready to be integrated into your current engine/system (see below).
The sources can be found in *timelinefx/source*.

The editor is **paid**, but there are lots of **free premade effects** [ready for use on their website](http://www.rigzsoft.co.uk/effects-libraries/).
Check out the youtube video at every package.

The library is based on the official TimelineFX's *BlitzMax sources*.

The system should support both fixed and variable timestep with optional tweening between states in Draw, although I didn't test it yet.

I didn't want to bring additional dependency, so you have two options:

1. Unzip the official .eff file before use and edit the sprite paths in data.xml (in the end usually) manually.
2. File->Export .zip from TimelineFX editor, unzip it and you are ready to go.

Sorry for this. Looks more convenient to me than implementing libzip and loading images from memory stream.

[Basic usage is described here](http://www.rigzsoft.co.uk/basic-usage-of-timelinefx-for-blitzmax/).

Usage
-----

### Common C++

1. Take the source from *timelinefx/source*.
2. Take the PugiXML from official website or here from *pugixml*. OR inherit *XMLLoader* and implement your own xml loader.
3. Inherit *AnimImage* to load and keep the sprites.
4. Inherit *ParticleManager* for drawing the images (the particle system is calling DrawSprite with correct parameters).
5. Inherit *EffectsLibrary* and implement two Create methods with correct classes (this is a factory).

Check out *timelinefx-sample/source/MarmaladeEffectsLibrary.h+cpp* for example.

### Marmalade

1. Checkout three projects - *pugixml*, *timelinefx* and *timelinefx-sample*
2. Open *timelinefx-sample.mkb*
3. Run

You can use *timelinefx* subproject directly in your game/app. Simply implement the classes like in **Common C++**.

*timelinefx* subproject can be used as precompiled and linked static libraries (*timelinefx.mkf and .mkb*) or the sources (*timelinefx-source.mkf*).

Technical
---------

There are three parts which can be implemented by you by simple inheriting the specific classes and defining your own behaviour:

1. *XMLLoader* - right now, *PugiXMLLoader* (dependency) is implemented and used, but you can reimplement it by your XML parser.
2. *AnimImage* - you should inherit this to keep image data for your system/engine.
3. *ParticleManager::DrawSprite* - inherit this to take your AnimImage and send/queue it to your rendering system

Except of PugiXML, I implemented Marmalade sample for 2. and 3. There is a sample project showing how to use it. DrawSprite is implemented with basic batching.

Bugs / todo
-----------

There are still some minor issues I know about, especially when using subeffects, but don't hesitate to report or fix.

dan@ger.cz

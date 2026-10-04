

# INTRO

**magno.caliman@orpheusinstituut.be**

<span class="underline">WHY "THE POSSIBILITIES ARE ENDLESS" IS A FALSE STATEMENT; OR, HOW TECHNOLOGY IS NEVER NEUTRAL</span>

From Arduino workshop tomorrow:

> [Arduino is an] ecosystem (**circuitry + programming language + IDE**) that allows us to create logic to interface/control hardware and software

-   Arduino "triangle"
    -   Reconfigurability && modularity
    -   Inherent to programming && electronics (and therefore to the products of those mediums)


# THE "STACK"

Playing a sample on [Sonic Pi](https://sonic-pi.net/)

    sample "/home/magno/googleDrive/Minhas_Tralhas/Aulas/HEMU/gitWorkshopsHEMU/assets/notaPiano.wav"

And on [SuperCollider](https://supercollider.github.io/)

    s.boot
    
    ~mySample = Buffer.read(s, '/home/magno/googleDrive/Minhas_Tralhas/Aulas/HEMU/gitWorkshopsHEMU/assets/notaPiano.wav')
    
    ~mySample.play

-   For fun, see [audioPlayer.c](assets/audioPlayer.c)
    -   Compile with `gcc audioPlayer.c -o audioPlayer`
    -   Run with `padsp ./audioPlayer`

-   Max `sfplay~` [documentation](https://docs.cycling74.com/legacy/max8/refpages/sfplay~) vs. pd `tabread4~` as looping sampler (pd's built-in example B08) and wavetable oscillator (B03). Deep down (or not so deep), they are the same thing. 
    -   Johannes Kreidler - <https://www.youtube.com/watch?v=qpAz8zXvnww>

-   The action of playing a digital sound file in a computer is, in itself, a universe.
-   There's always a stack informing your decisions &#x2013; aka, the possibilities are *not* endless. Choosing how to position yourself, that is part of the toolbox of compositional *technique*.


# IN PRACTICE&#x2026;

-   *LEDWork*
    -   see `./../HEMU/videoExamples`
    -   see `LEDWork_FARM-2025_reaperSession.rpp`

-   *squareFuck*
    -   see `registro/testes`
    -   see `squareFuck_overkill_render.mov`

-   Decision making between *black box* <=> *stack*
    -   Each decision is made in negotiation with some aspect of the technology. The stack is vertical, but projects itself horizontally.
    -   Technology exists as a cultural artefact, which you are in dialog with &#x2013; aka, technology is *never* neutral. Managing that dialog, that
    -   is also part of the toolbox of compositional *technique*.


# YOUR PRACTICE!

-   Practical proposition:
    -   "Peel the onion" exercise: list technologies you are using in some of your current work. Let's break their stack down.
    -   Find the hidden layers of abstraction, the (maybe not consciously acknowledged) points of negotiation.
    -   What do they say about your own artistic and aesthetic *preferences*?


# Welcome to KodPetFlipper

 Under construction...****you will not find progress/support on this project by donating on patreon or others.

        Game prototype and interface for flipper zero. Based on tamagotchi.


![enter image description here](https://cdn.discordapp.com/attachments/1049264648404357130/1055834291038335056/IMG_0012.png)


# Functions Performed

- Action: Feed.
- Action: Medicine.
- Action: Clean/Care.
- Action: Study.
- Action: Work.
- Action: Investigate.
- Action: Train.
- Action: Play --Games in firmware or --AutoGame.
- Action: Tool --App/Plugin in firmware or --AutoTool.
- Action: Random Cycle.
- Action: Duel with friend added
- Status: Hungry, Sick, Dead, Happy, Powered, God, Normal and  Dirty.
- Personality: White, Red, Black, Green and  Grey.
- Logic: Cycle Live combine with EXP-Flipper.
- Logic: Hunger.
- Logic: Happiness.
- Logic: Care.
- Logic: System of evolutions - Egg, Baby, Nano, Mature, Cyber and Quantum.
- Logic: Hospital (If you die, you can pay hospital costs and get healthy again).
- System: Autosave game to prevent loss of progress with updates or others.
- System: Encryption of the savedata to avoid easy cheats.
- Statictics: Intelligence, strength, agility, critic, defend and life.
- System: Level.
- Name: Gets the name of the system.
- System: Social. Shared memorycard (this include the author's name in the savedata) for add in friends or enemies. You might find some curious pets on the internet. You catalogue.
- System: NPC good, bad and neutro. Add more from the internet.
- System: Expedition. You can found (~random) an enemy (active: system battle and regard), npc (active: development) or friend (regard). 
- System: Money
- System: Item and inventory.

   and more in development...

# Target system

- [flipperdevices](https://github.com/flipperdevices)/**[flipperzero-firmware](https://github.com/flipperdevices/flipperzero-firmware)**
- [ClaraCrazy/Flipper-Xtreme](https://github.com/ClaraCrazy/Flipper-Xtreme)


# Test
*Required component for develop in C.

1. gcc -o test kodpet.c
2. Start new game deleted the file: /memorycard/data.txt. (Not delete the file tmp.txt).
2. ./test




# License

Copyright (c) 2022-2023 DevJow

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

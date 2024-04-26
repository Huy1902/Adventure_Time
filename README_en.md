[[Tiếng Việt]](README.md)

# AdventureTime - Huy1902

# Preface

+ Full name: Nguyen Quoc Huy - K68CB

+ Student code: 23020082

+ Big exercise: Adventure Time

# Introducing the game

- Game introduction video:

- Adventure Time is a game in the RPG genre. Gamers take on the role of an unknown warrior on the path to defeat the Lords of Space, who hold the great power of The First Crystal. Continuously confront skilled warriors, gain great power and rise to glory from the ashes.

#0. How to download the game

## a. Method 1: Do not include code.

- Download the AdventureTime!!!.rar file at the following link: [AdventureTime!!!v1.0.0](https://github.com/Huy1902/Adventure_Time/releases/tag/v1.0.0) or you can click on the link to download now: https://github.com/Huy1902/Adventure_Time/releases/download/v1.0.0/AdventureTime.rar
- Extract the game into any folder and click on the Adventure_Time.exe file to start the game.

## b. Method 2: Include code and compile.

**Step 1:** Download the source code file in the release section at the following link: [AdventureTime!!!v1.0.0](https://github.com/Huy1902/Adventure_Time/releases/tag/v1.0.0) or you You can click on this link to download immediately: https://github.com/Huy1902/Adventure_Time/archive/refs/tags/v1.0.0.zip.

- All code is in the Adventure_Time folder.

**Step 2:** Install Visual Studio. When building the program, I use Visual Studio 2022. You can refer to the installation instructions at: https://learn.microsoft.com/en-us/visualstudio/install/install-visual-studio?view=vs- 2022 or on Youtube: https://www.youtube.com/watch?v=HS4c3kBEWr4.

**Step 3:** Open the file Adventure_Time.sln. ![image](demo_resources/install.png)
- You can press `Ctrl + F5` to run the game in Visual Studio.

# 1. Game features
- There is a lively intro when entering the game.
- Menu screen with sound toggle buttons for players.
- The score rankings are updated after each play and the results are saved on the device for re-access.
- Waiting screen with useful tips when playing games.
- Infinite moving background with gentle music.
- SFX when you click buttons.
- The main character has lively actions and accompanying sounds.
- The monster system has its own actions and characteristics.
- Powerful and challenging Boss.
- Different events with achievement screen: saving save point, defeating boss, respawn, being defeated, setting foot on another map.
- Support stopping the game and viewing the character's status.
- Level up mechanism and increase character strength
- Skill system helps players destroy enemies.
- Mechanism to block and stun enemies.
- Crit and miss mechanism for attacks.

# 2. Start the game:
- When starting the game, the program will display the Intro screen. Press the key or left click to continue.
![image](demo_resources/intro_demo.png)

- The game will go straight to the main screen.
![image](demo_resources/main_menu.png)

- Select Play to enter the game or select Score to see the ranking of the three highest scores.
![image](demo_resources/standing.png)

- Press exit to exit the game.

# 3. Instructions for playing the game:
- After pressing Play on the main screen, the player will see the waiting screen. This will also be the screen that appears every time the player switches maps. There are some pretty useful tips out there right now.
![image](demo_resources/loading.png)

- The gaming screen is quite easy to get used to. What you need to pay attention to when playing is the score ![image](demo_resources/Score.png) and the character's health and stamina status ![image](demo_resources/HP_STA.png).
![image](demo_resources/playing.png)

## a. About the character:

- Control keys:

| Control | Key |
|--------|----------|
| LEFT | A |
| RIGHT | D |
| JUMP | K |
| DASH | L |
| ATTACK | J |
| BASH | U |
| SPELL 1 | Q |
| SPELL 2 | E |

- Note: If your character does not move, check to see if you have a language other than English on the device. With Window, select English at Keyboard layout so the character moves smoothly.

## b. About the playing mechanism:
- The character deals damage to enemies with regular attacks or using spells.
![image](demo_resources/darkra.png)

- Characters can stun enemies with bash attacks. When bash the character will not receive damage, and if used at the right time when the enemy attacks, the enemy will be stunned.
![image](demo_resources/bash_success.png)

- When the enemy is stunned, pressing the `J` key will cause the character to perform a critical attack. This is an attack that deals a lot of damage. Take advantage of the mechanism to defeat monsters faster.
![image](demo_resources/crit.png)
   + Note: This mechanism only applies to enemies carrying close-range weapons. Enemies that are archers will be immune to control.

- Characters can save respawn points at portals or bonfires.
![image](demo_resources/bonfire.png)

- Travel to different maps using the green teleportation gate. When you arrive at a land, its name will appear on the screen.
![image](demo_resources/portal.png)

- If an enemy defeats you, the message "You died" will appear.
![image](demo_resources/died.png)

- When defeated, the character will respawn at the nearest save point.
![image](demo_resources/revival.png)

- When defeating the boss, achievements will appear. You have become stronger already.
![image](demo_resources/boss_fallen.png)

- Characters and enemies both have their own LUCK index, and will be able to dodge attacks.
![image](demo_resources/miss.png)

- Using normal or gliding attacks will consume stamina. On the contrary, when using skills, you do not consume stamina but will have cooldown time and deal less damage. Crit attacks do not consume anything.

## c. Enemy
- There are three types of common enemies in the game:

| | Enemy name | Abilities and Powers |
|-------------------------------------------|------- -------------|----------------------------------- -------------------------------------------------- ------------|
| ![gif](demo_resources/Knight.gif) | Barrel Knight | Close combat, diverse moves, buffaloes are difficult to kill with normal attacks. |
| ![gif](demo_resources/small_droid.gif) | Droid Zapper | Medium attack range, high damage |
| ![gif](demo_resources/archer.gif) | Archer | Long range, Cannot be stunned, large arrow damage |

- Discover the most suitable fighting style for each type of monster, and depending on the situation, running is a good option.
## d. Boss
- There is currently only one Lord of Space, "Vagabond", in the game. When you defeat it, you've ruined my game. Try to get maximum points for each game.
- Lord of Space's stats are all high. Be careful!
- Some actions of Vagabond:

| Action | Description |
|--------|----------------------------------------- ---|
| ![gif](demo_resources/boss_attack1.gif) | Slash three consecutive attacks. |
| ![gif](demo_resources/boss_attack2.gif) | Accumulate power, slash hard and teleport a distance |
| ![gif](demo_resources/boss_die.gif) | Knocked out |



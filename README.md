# Chess Plus Plus (In Progress)
Chess Plus Plus is a chess-based game built from scratch in C++. One of the primary goals of this project is to make 
use of object-oriented inheritance principles to make future expansion not just possible, but easy. All it should take
is inheriting from a base class, defining its custom behavior, and registering it.
This project is currently in progress, and as such, some features are not quite complete yet. Future plans for this project
include:
- A custom Qt GUI
- AI multi-threading (allowing AIs to spend less time choosing of a move)
- Basic peer to peer networking to allow multiplayer play
- More AIs

---
Usage
---
Currently, as a proof of concept, the program will run and show a game between the two currently implemented 
AIs (min/max with alpha-beta pruning and a randomAI). Future commits will add the ability to specify each player as either
a human or one of the included AIs.


AI Algorithms
---

###Random - (RandomAI)
An AI that chooses its move randomly from a selection of all possible moves that can currently be made.

&nbsp;
###Min/Max with Alpha-Beta Pruning - (MinMaxAI)
An AI that chooses its move by simulating moves and choosing a move whose branch maximized its own score and minimized its opponents score.
Score calculations are made in the following way:\
&nbsp;&nbsp;+ the current score as defined by a game state for that player\
&nbsp;&nbsp;+ the weighted points received from capturing opponents pieces\
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; i.e. a king might have a capture score of 1,000 points making it much more important to capture vs a pawn which may have a score of 100 for example\
&nbsp;&nbsp;- the opponent's score calculated in the same manner

In order to reduce the amount of time spent simulating moves, a branch may be marked as insignificant to explore compared 
to the branch scores of previously explored branches, and will thus be skipped entirely.
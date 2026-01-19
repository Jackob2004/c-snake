# Snake
Terminal Snake game clone.

[Game Demo](https://youtu.be/YkqQpnsUE7M)

Tools used:
- C language
- ncurses library to make textual user interfaces easily

Major concepts utilized:
- memory management
- pointers
- representing data as structs
- organizing code into header files and their implementations

## Reflection
I am the most satisfied with the way I designed "menu" module. It acts as a flexible component.
I don't need to code every menu from scratch over and over again. Its flexibility can be
seen in "scoreboard" module where I utilized it for implementing pagination.

Room for improvement: 
- I am not sure whether I structured the project correctly as it is my first C project
- There is no input validation implemented besides shortening the username if it exceeds the limit
- Player name input field isn't visually appealing
- I didn't consider the fact that the game screen grows with the terminal window size
- Vertical movement may seem a little bit off due to the font size

<details>
  <summary>additional sources of help</summary>
  <ul>
    <li>Game loop design https://gameprogrammingpatterns.com/game-loop.html</li>
    <li>Function pointers https://stackoverflow.com/questions/840501/how-do-function-pointers-in-c-work</li>
    <li>Reading strings in ncurses https://stackoverflow.com/questions/26920261/read-a-string-with-ncurses-in-c$a</li>
    <li>Random int in C https://stackoverflow.com/questions/822323/how-to-generate-a-random-int-in-c$a</li>
    <li>Measure a time interval in C https://stackoverflow.com/questions/2150291/how-do-i-measure-a-time-interval-in-c</li>
  </ul>
</details>

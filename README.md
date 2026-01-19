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



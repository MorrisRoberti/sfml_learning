## Compile on Linux

> Copy this in your terminal and replace `classes.cpp` with the names of the .cpp files included in the code

`g++ main.cpp classes.cpp -o a -LC:\SFML-2.1\lib -lsfml-graphics -lsfml-window -lsfml-system`

**PAY ATTENTION**  
You have to move inside one project or another before compiling because all the entrypoints of the applications are called `main.cpp`.

> In future I will add a CMake file to compile the code in a more intelligent way, for now I'm just lazy so I don't care that much :P

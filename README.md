# lem-in
42 School project
This project is a game about ant farm. Its goal is to find the fastest path from start room to the end for all ants.
## About Lem-in
At the beginning from standart output the program recieves information about number of ants had to be leaded through path, room names (can be numbers, words, characters etc.) with coordinates and links. Here is an example:
```
20
##start 
1 23 3
2 16 7 
#comment 
3 16 3
4 16 5 
5 9 3 
6 1 5 
7 4 8 
##end 
0 9 5 
0-4 
0-6
1-3
4-3
5-2
3-5
#another comment
4-2
2-1
7-6
7-2
7-4
6-5
#another comment
```
Commands "##start" and "##end" are provided to show the start and end room information.

## Installation and usage
Simply clone repository and run following commands:
```
make
./lem_in
```
and enter your "ant farm" into standart input

## Result
In result we can see path of all ants in format ```'ant's number-room name'```. One line - one move.
```
L1-2 L2-3
L1-4 L3-2 L2-5 L4-3
L1-0 L3-4 L5-2 L2-6 L4-5 L6-3
L3-0 L5-4 L7-2 L2-0 L4-6 L6-5 L8-3
L5-0 L7-4 L9-2 L4-0 L6-6 L8-5 L10-3
L7-0 L9-4 L11-2 L6-0 L8-6 L10-5 L12-3
L9-0 L11-4 L13-2 L8-0 L10-6 L12-5 L14-3
L11-0 L13-4 L15-2 L10-0 L12-6 L14-5 L16-3
L13-0 L15-4 L17-2 L12-0 L14-6 L16-5 L18-3
L15-0 L17-4 L19-2 L14-0 L16-6 L18-5 L20-3
L17-0 L19-4 L16-0 L18-6 L20-5
L19-0 L18-0 L20-6
L20-0
```
In case of invalid "farm" program will display "Error". 

## Bonuses
There are some bonuses in my project:
Put one of this commands in the start of your map:

```##colour``` - print all output in colour for more understandable check.

```##path``` - prints before result paths of ants.

```##status``` - prints after every move number of ants that were finished and not started before, and status of rooms in format ```"room-ant's number"```

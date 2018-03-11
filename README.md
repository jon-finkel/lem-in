# LEM-IN - @42Born2Code

Lem-in is an algorithm project, the 3rd in the algorithm branch here at [42][2], where ants have to go the from a starting point to and ending point as fast as possible. Refer to the [project instructions][1] for more details.

## Algorithm

I use a modify Edmonds-Karp algorithm.

Starting with a breadth-first search, I find the shortest path, and then try to add other paths with successive bfs. If there is a collision between two paths, I calculate the optimal flow with the several combination availables and keep only the best combination. It's fast, efficient and elegant.

## Understanding the maps

```
10          // ants number
1 250 150   // Room name (1) ants it's X-Y coordonates
2 550 150
3 550 450
##start     // Next room will be start room
4 250 450
##end       // Next room will be end room
5 850 450
6 850 150
1-2         // Relations between rooms. Room 1 and 2 are linked
1-3
1-4
2-4
2-6
2-5
3-4
3-5
3-6
5-6
```

## Understanding the output

L[ant]-[room]
```
L1-2 L2-3                // Turn 1 : ant number 1 go to room 2. Ant number 2 go to room 3
L1-5 L3-2 L2-5 L4-3
L3-5 L5-2 L4-5 L6-3
L5-5 L7-2 L6-5 L8-3
L7-5 L9-2 L8-5 L10-3
L9-5 L10-5
```

## Installation

`make`

## Run

Standard mode: 

`./lem-in < [map]`

Debug mode:

`./lem-in -d < [map] | ./visu`

Show parsing rules:

`./lem-in -r`

### Debug mode

`./lem-in -d < [map]`

This allows two things : 
- When an arror occurs trying to launch a map, it will write the exact error on the stderr instead of "ERROR".
- Lauching a map, it will give more info about the map and the algorithm (number of ants, rooms, links, possible paths, chosen paths, adjacency matrix, ...).
- It is advised to disable the adjacency matrix display on very large maps with the argument `--no-matrix`, or `-n`

### Final Mark

`122/100`

[1]: https://github.com/jon-finkel/lem-in/blob/master/project_instructions/lem-in.en.pdf "Lem-in PDF"
[2]: http://42.fr "42 Paris"

# SweepMyCMine

![simpleLose](/doku/images/simpleTui_lose.png)

## What is SweepMyCMine

> SweepMyCMine my version of Minesweeper written in C99. Ncurses is used for visualization.
>
> Minesweeper is an NP-complete problem where the important thing is to leave squares on a 2D square closed or marked so that each open square has exactly the number of marked squares around it as written on the single square. At the end of the game, only the number of fields may be covered, as there are bombs in the game.

## Why does SweepMyCMine exist

> I use this project to try out different techniques of C. Nevertheless, this implementation should be playable. Furthermore, I would like to develop different algorithms for solving and compare them.

## Todos

| Todo | Prio | Description |
| ---- | ---- | ----------- |
| t-01 | 1 | test for list.c |
| t-04 | 2 | When compiling, the tests should first be run alone and the game itself should only be compiled after success. |
| t-05 | 2 | refactoring and automatic formatting |
| t-06 | 2 | Modifying the test environment with IfPrint. |
| t-08 | 3 | implement greedy solver |
| t-09 | 3 | implement linear solver |
| t-10 | 4 | implement Benchmarksystem for different solver |
| t-11 | 4 | design a more comprehensive TUI with windows and mouseinteraction (expand TUI) |

## Implementation

> todo

### Compile on your own system

> todo

	make run
	./compile.sh

> todo

## Known issues

> todo

### TUI

>| ![simpleStart](/doku/images/simpleTui_start.png) | ![simpleOpen](/doku/images/simpleTui_open.png) |
>| :----: | :----: |
>| ![simpleMark](/doku/images/simpleTui_mark.png) | ![simpleLose](/doku/images/simpleTui_lose.png) |
>
>	todo

## License

> [MIT](./LICENSE) © Michel-Schnitker

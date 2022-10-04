# SweepMyCMine

![simpleLose](/doku/images/SweepMyCMineWinBig.png)

## What is SweepMyCMine

> SweepMyCMine my version of Minesweeper written in C99. Ncurses is used for visualization.
>
> Minesweeper is an NP-complete problem where the important thing is to leave squares on a 2D field closed or marked so that each open square has exactly the number of marked squares around it as written on the single square. At the end of the game, only the number of fields may be covered, as there are bombs in the game.

## Why does SweepMyCMine exist

> I use this project to try out different techniques of C. Nevertheless, this implementation should be playable. Furthermore, I would like to develop different algorithms for solving and compare them.

## Todos

| Todo | Prio | Description |
| ---- | ---- | ----------- |
| t-01 | 1 | test for list.c |
| t-04 | 2 | When compiling, the tests should first be run alone and the game itself should only be compiled after success. |
| t-12 | 2 | implement automatic valgrind check |
| t-05 | 2 | refactoring and automatic formatting |
| t-08 | 3 | implement greedy solver |
| t-09 | 3 | implement linear solver |
| t-10 | 4 | implement Benchmarksystem for different solver |
| t-11 | 4 | design a more comprehensive TUI with windows and mouseinteraction (expand TUI) |
| t-12 | 4 | todo: features from and to Disk |
| t-13 | 4 | todo: scores fromand to Disk |
| t-14 | 4 | todo: TUI features final (numbers) |
| t-15 | 4 | todo: extend GameTests |
| t-16 | 4 | todo: count the number of moves (open / mark) |
| t-17 | 4 | todo: count the number of cursor moves (up down right left) |
| t-18 | 4 | todo: testrun with gdbHelper |
| t-19 | 4 | todo: implement compiler disable for score and features  |

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

>| ![simpleStart](/doku/images/tui_gameStart.png) | ![simpleOpen](/doku/images/tui_gameMidgame.png) |
>| :----: | :----: |
>| ![simpleMark](/doku/images/tui_gameLose.png) | ![simpleLose](/doku/images/tui_config.png) |
>| ![simpleMark](/doku/images/tui_messages.png) | ![simpleLose](/doku/images/tui_tutorial.png) |
>
>	todo

## License

> [MIT](./LICENSE) © Michel-Schnitker

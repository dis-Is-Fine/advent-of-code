# Advent Of Code 2023 in C

My solutions for Advent Of Code 2023 written in C

## Progress
| Status | Description |
| ------ | ----------- |
| ❌     | Problem not attempted yet |
| ✍     | Working on solution |
| ✅     | Problem solved |
| ⭐     | Provided explanation on how the solution works |

| day | Part 1 | Part 2 |
|-----|--------|--------|
| 1   |  ⭐   |   ⭐   |
| 2   |  ⭐   |   ✅   |
| 3   |  ✅   |   ✅   |
| 4   |  ✅   |   ✅   |
| 5   |  ✅   |   ✅   |
| 6   |  ⭐   |   ⭐   |
| 7   |  ✅   |   ✅   |
| 8   |  ✅   |   ✅   |
| 9   |  ✅   |   ✅   |
| 10  |  ✅   |   ✅   |
| 11  |  ✅   |   ✍   |


## Usage
To use my solutions navigate to folder representing day/part of puzzle, for example: **``./day 1/part 1``**


Then run precompiled executable like this: **``./solution <filePath>``** (you should replace filePath with path to your puzzle input)

After the program is run, it will output solution and information on how long the program was running
If the program is expected to run for a long time, it will output information on progress while running 


>[!NOTE]
>If precompiled solution isn't working on your machine, you can compile it with **``compile.sh``**
>
>For that, make sure you have gcc installed on your machine

## Repo stucture
In the main folder you can find subfolders called ***day #***
inside them there are folders called ***part 1*** and ***part 2***
in these folders you can find solutions to their respective puzzles
Each folder contains:
- solution.c: source file of solution
- solution: compiled executable of solution
- example.txt: example input from Advent Of Code
- compile.sh: compiling script (for gcc)
> - explanation.md: explanation of solution (***Not always present***)

# Day 2 | Part 1

## Approach
- For each line there is a Game struct with assigned ``id`` and ``valid`` set to 1 (true)
- Until whole game (line) is read get a draw (string) by reading characters until ***';'*** character
    - For each draw get color-value pair by reading characters until ***','*** character
    - Check which color is in the color-value pair
    - If value is larger than maximum amount for that color, set ``valid`` to 0 (false)
- If all draws in game are valid, add game ``id`` to ``IDsum`` 
- Print ``IDsum as solution``

## Data management
- Struct ``Game`` keeps track of:
    - int id
    - int (bool) valid
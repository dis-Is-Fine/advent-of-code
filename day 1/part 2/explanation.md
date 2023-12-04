# Day 1 | Part 2

>[!NOTE]
>Grayed-out parts of this explanation are same as in part 1

## Approach
- Create lookup table for each digit with corresponding string
> - For each line we have two variables: ``firstDigit`` and ``lastDigit`` initially set to -1
> - For each character in line we check if this character is a digit
> - If that character is a digit:
>    - If ``firstDigit`` is -1 (So this digit is the first digit in this line), we set ``firstDigit`` to digit at current character position
>   - Always override ``lastDigit`` so it always stores position of last encountered digit
- If that character is not a digit:
    - Check if there is any string corresponding to a number begining on this character
    - If there is string corresponding to that character treat is as digit and set ``firstDigit`` and ``lastDigit`` as described earlier  

> - At the end of the line we set ``totalNumber`` by multiplying ``firstDigit`` by 10 and adding ``lastDigit``
> - Add ``totalNumber`` to ``sum``
> - Print ``sum`` as solution
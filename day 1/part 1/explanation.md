# Day 1 | Part 1

## Approach
- For each line there are two variables: ``firstDigit`` and ``lastDigit`` initially set to -1
- For each character in line we check if this character is a digit
- If that character is a digit:
    - If ``firstDigit`` is -1 (So this digit is the first digit in this line), we set ``firstDigit`` to digit at current character position
    - Always override ``lastDigit`` so it always stores position of last encountered digit
- At the end of the line we set ``totalNumber`` by multiplying ``firstDigit`` by 10 and adding ``lastDigit``
- Add ``totalNumber`` to ``sum``
- Print ``sum`` as solution
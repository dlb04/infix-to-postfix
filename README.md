# itop

Infix to postfix converter made in C.

## Usage

```
make
./postfix
```

## Examples

```
[I]: 1+1
[P]: 11+
[I]: A*(B-C/D)
[P]: ABCD/-*
[I]: A*B-C
[P]: AB*C-
[I]: A*(B+C-D)
[P]: ABC+D-*
[I]: A*B-(C/D-E)
[P]: AB*CD/E--
```

## Implementation

For making this program I used the algorithm shown [here](https://iq.opengenus.org/infix-to-postfix-expression-stack/) and
made some modifications.

```
Pseudocode for the infix to postfix algorithm:
infix_to_postfix (I :: String):
    P :: String

    for c in I 
        if c is Operator:
            Pop from stack until an operator with less precedence
             is found or a Left Parenthesis is found.
            Push the new Operator.
     
        else if c is left Parenthesis:
            Push c to stack

        else if c is Right Parenthesis
            Pop and append until Left Parenthesis is found.
            Pop Left Parenthesis from stack (dont append to string).
        else
            Append to P.

    Pop everything in the stack and append to P.
    return P.
```

The pseudocode says that if an operator is found the program must pop
every operator in the stack with a higher precedence and append it to P
until a left parenthesis is found. In the actual implementation (`postfix.c`)
right and left parenthesis are treated as operators with the lowest
precedence, so the program doesn't have to check if the popped value
is a left parenthesis.

## TODO:
* Support for multicharacter identifiers/numbers.
* Evaluate literal expressions and give a result.
* Check if the infix string is valid.
* Bug fixing.
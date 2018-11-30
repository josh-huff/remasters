*** CS261 -- Data Structures

We were taught C++ mostly as a vehicle for understanding the fundamentals of 
programming (particularly OOP). Since we weren't being trained to be C++ gurus, 
and the classes were taught at an accelerated pace, the code is often wonky and 
meandering. Just as often, a strange choice in included libraries or an 
unintuitive implementation was a reflection of limitations imposed by the 
instructor's preferences and the school's server, which in late 2016 was running
a version of g++ that balked at anything newer than C++98. Half the time, I was 
joyful nearly to the point of tears just to see a clean compile.

Tic Tac Toe:

    Board.cpp / Board.hpp
    TicTacToe.cpp / TicTacToe.hpp

        The instructor for this course explicitly forbade us to use the ternary
        operator, which I was a-okay with at the time because it looked to the
        beginning coder to be utterly incomprehensible. Now that I've had some
        more experience, I'm taken by its utility; it's sometimes far more clear
        than the equivalent if/else construct. 
        
        I likely could have made this more memory efficient by passing pointers
        and such, but performance in a TicTacToe game is not quite as worthy of
        consideration as developer time, so I figured the aesthetic refactoring
        was enough to show some progress. 
        
        With that in mind, I found myself wondering if I could get the whole
        program down to less than 200 lines by using libraries other than the
        absolute essentials, especially when doing tedious things such as 
        validating and standardizing input. 
        
        The original gameState method was such an embarrassing nightmare that I
        simply had to create some helpers, which was something I was afraid of
        doing for fear of losing precious grade points. Being able to generalize
        and determine win states programmatically instead of writing a forest of
        if statements helped me realize how far I've come.  

Miscellaneous:
            
    converter.cpp
        
        A first foray into recursion. Recursion didn't "sink in" until CS325,
        and it shows. I resisted the urge to look at my first attempt, but it
        wouldn't have helped, because I have no idea how I thought those were
        supposed to work.

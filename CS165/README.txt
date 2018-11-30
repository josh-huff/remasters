*** CS165 -- Accelerated Introduction to Computer Science

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
        
    fallDistance.cpp
    
        Enjoy my facepalm moment. I included this mostly for the laugh it gave 
        me, hoping it brightens someone else's day.

    hailstone.cpp
    
        This functioned well, but the lack of brevity bothered me. I was
        especially happy to take advantage of parity to slim down the loop.

    postfixEval.cpp
    
        The old code indicated a lack of knowledge of what functions are in what
        libraries, how C-strings work (the test cases were a death trap), and a
        tenuous grasp of how postfix evaluation really works. It could likely be
        more elegant, but this is a major improvement.

    stdDev.cpp (Student.cpp / Student.hpp included as dependencies)
    
        I clearly didn't take the time to really understand how standard 
        deviation is calculated. I imagine I was in a rush and this was the last
        part of the assignment I got my grubby little mitts on before I realized
        the deadline was approaching. If I'd taken a deep breath and walked 
        through the steps as I did now while revisiting this, I'm sure I would
        have knocked it out in about fifteen minutes flat... as I did now while 
        revisiting this. Perhaps my grade suffered from my "panic response" so 
        the code I produce in the real world won't have to.
        
Still to add: 
    
    Final Project B, a model of an "Online Store"

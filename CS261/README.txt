*** CS261 -- Data Structures

Data Structures was mostly concerned with theory and implementation of ADTs. As 
the course went on, the previous week's assignments were often used to support
the next. Though it's unlikely (inadvisable, even) I'll roll my own ADTs in real
life scenarios, doing so and juggling dynamic memory management in C turned out
to be beneficial when understanding future problems, particularly in 325.

Stackapp:

    stackapp.c
    dynamicArray.c / dynArray.h
    testDynArray.c

        The functions are so basic that it is hard to code correctly and get it
        wrong, and so much of the dynamicArray.c file is skeleton code that it 
        seemed silly to show their comparison, so I haven't included the first 
        attempt. However, I felt it necessary to start fresh to ensure that
        stackapp.c could rely on a robust data structure.
        
        The test with unit tests is mostly written by course staff, with the one
        exception of the actual() function. I thought it strange that it printed
        only what it expected and not the actual contents.
        
        Stackapp does not have a previous incarnation. I ran out of time (which
        you'll notice is a common theme from this quarter in general, as I took
        261, 271, 290, and 340 concurrently), before I could give it a decent
        attempt, and simply included the file as a stub to ensure there were no
        issues regarding the makefile.
        
        main() and nextChar() came with the file. The rest is mine.

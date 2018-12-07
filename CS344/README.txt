*** CS344 -- Operating Systems

Operating Systems focused on Unix and its derivatives, particularly how concepts
like memory, processes, signals work. In my instructor evaluation, I apologized
to the professor, because his course was easily among the best designed in the 
entire program, and it almost felt like I did him a disservice by barely ekeing
out a passing grade.

I'm making up for it now by revisiting the projects that gave me the most grief.

Adventure:

    huffj.buildrooms.c

        If I'd taken the time to watch the lectures one extra time, and really
        let the power of the Unix philosophy sink in, there wouldn't have been 
        the ugly nightmare you see below the much more economical (and much more
        readable) version I came up with in a couple hours. I even took a break
        to enjoy some grub and watch Jeopardy, comfortable in the knowledge that
        I would finish this before bed. Whereas when I was taking the course, I 
        stubbornly got married to strcat(), not understanding that failing to be 
        familiar with the arrow operator and snprintf() cost me several days.
        
        Y'know. To save time. To a man with a hammer, every problem is a nail. 

        Lesson learned: don't be that guy!

    huffj.adventure.c
    
        Looking at the original code is almost as painful to look at as is the 
        Ark of the Covenant, so I'm pleased to have seen improvements across the
        board in the remaster.
    
        The commonFileManip function is the piece de la resistance. Perhaps it
        borders on monolithic and might be a little confusing at first, but I 
        had to integrate the "time" feature and decided to do so by extending
        that function with a function pointer array so it acts much like a 
        switch statement (with a clever solution for calling fetchTime() after
        initTime() writes to the currentTime file, if I do say so myself).
        
        This time around, I managed to factor out a LOT of redundancy. It's
        likely there is even more I can do to slim this down, but going from an 
        ungainly and buggy 500 lines to a svelt and spry 300 lines is good for
        me. 

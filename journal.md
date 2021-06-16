# Reece's Journal (Definitely not copying James's Journal format)

# 02/27/2021
- Starting on the Homework this week.
- I plan on implementing the second triangle checker with a pythogorean approach
rather than my previous angle calculations.
- This will use some doubles still since the length of a line needs to be computed,
but hopefully this should be sufficiently different.

# About an hour later
- I'm experiencing some difficulty in parsing my application output into a shell script
- I think I'll just re-make the applicaiton with a non-Stdin input and a numeric output.
- This will help with the differential testing.

# The next day
- I've created my application, but I'm getting differences in my differential testing
- I think this could be due to my error margin. I'll make it smaller.

# 10 minutes later
- Yep that did it! Since I've already used the code that James wrote for fuzz testing
I can basically submit.

# 02/21/2021 3:24 p.m.
- Definitely forgot to write the beginning of the day in my journal. I'll simulate the issues:
- Working on my triangle program and I hit a problem with angle calculations.
- Fixed the angles due to a radian and degree mix up
- Still have some troubles however.
- Fixed the troubles by adding some margin of error. it's not realistic for a program to
exactly calculate a value that is defined by a fixed constant like pi.
- I'm going to submit, then start working on my shell script.

# 02/21/2021 10:38 p.m.
- Finished the homework for this week.
- Will submit soom.
- Made a Shell script that will take in a specifically formatted file of integers and output a corresponding linear
program in an array latex environment.
- I hope to combine this with a web scraper to automate the
process of transcribing an online pivot tool for my MATH 407
class. It is really annoying to do it by hand and often has taken hours in some cases.
- The format has the objective function first, then the constraints in the form of their coefficients. The slack varaibles are all labeled w_i where i ranges over the amount of constraints. the variables are labeled x_j where j ranges over the length of the first row.

# 02/14/2021 5:18 p.m.
- I am starting the homework for this week.
- I am going to write a prime detector using the 6k +- 1 method from here: https://en.wikipedia.org/wiki/Primality_test
- It's going to call an exponentiation function and run the loop specified. I'll start now.

# 02/14/2021 8:05 p.m.
- This is going fairly smooth, but I'm getting weird values for some of my registers
- It seems like my modulo operation isn't working

# 02/14/2021 8:26 p.m.
- Breakthrough, I needed to put my value in %rax first, rather than %rdx. That could be made clearer in the
x86.pdf doc
- Still an issue though, 49 throws an error and 81 is prime. More numbers do work now though

# 02/14/2021 9:03 p.m.
- Another breakthrough! I need to xor my %rdx whenever I module otherwise things get funky. Now it should be finished
completely. Just need to submit it.

# 02/05/2021 7:48 p.m.
- I am starting the homework for this week.
- I want to make a priority queue using linked nodes and a tree. This can hopefully be done
using percolate up and percolate down methods. I'd prefer to do this with an array which I'd
do if I could.

# 02/06/2021 12:05 p.m.
- starting work on the project again. I asked James to see if I could avoid using the linked
structure for this assignment and he said yes. I'm excited. I'm experiencing a bug with the
storage of strings

# 02/06/2021 1 hour later
- I figure out the bug and I am considering switching to generic data types.
- I don't think I will, but if I feel the need to, I might.

# 02/07/2021 11:00 a.m.
- I finished! I'm super glad that I got this done
- This was a fun project. Now I just need to do some documentation and make an
h file.

# 02/07/2021 2:30 p.m.
- I just need to give this a quick application and we can finish!

# Another hour later
- Done with my application. It's not that useful, but the comment at the top of the file
explains it. There is no help page this time.

# 01/29/2021 10:34 p.m.
- I am starting the homework for this week.
- I want to make an arraylist implementation in C. This will use malloc to 
do all sorts of cool things. Will use a struct as well. Woo hoo.
- The program will probably just be a basic grocery list checkout type thing which
will use some features of the arraylist.

# 01/29/2021 11:41 p.m.
- I have got some solid progress on the project done, but since it looks like
James has already implemented an arraylist, I'm going to make a Hashmap. It
seems pretty difficult I suppose, but that won't stop me... Maybe
- If that plan falls through, I'll settle for making a linked list. There
couldn't possibly be anything that would go wrong with recursive struct declarations
right :)))))))))))))))))))))))))))))))

# 1/30/2021 About an hour on the next day
- I have to admit, this is going much smoother than I thought. I haven't really hit a
hard block yet. The pointers are actually pretty intuitive, and my malloc calls have
really easy cases for when to free them. Of course, I haven't done any real testing yet
so we will have to wait and see.

# 1/30/2021 8:55 p.m.
- I am close to finally being able to test my code. I have all the method headers I need, but
the resizing method is giving me some conceptual difficulty. I'm relying a lot on my 373 class rn.
- I have a feeling my actual program won't be anything special, but the machinery will be nice.
- Currently regretting not sunmitting an EC request though. This feels like the kind of thing that would do it.

# 1/31/2021 2:00 p.m.
- I have been working on this for the past two hours now and I finally have resolved all the clang errors.
- Now I have to deal with a runtime error resulting from not being able to initialize all my values to null
in my chaining hash map. I really want to get testing on all my methods right now. Very exciting!

# 1/31/2021 7:01 p.m.
- Hi journal friends. Many updates. I have finally fixed my resizing method in what can only be described as
pure jank. First it was an issue in how I could even resize my h->data in the first place, then I had memory
reusage after freed and leaks all over the place, and when I finally wrote in some very illuminating comments,
I figured out what needed to be done (use realloc and many close functions). I'm going to test the rest of my methods,
then submit.

# 1/31/2021 12:15 a.m.
- So my implementation is completely cracked. I figured it was fine until I tested it. In fact, it might be a bit of a code
puzzle to figure out what is going on. I have a feeling my loop is changing the internal structure of the map when I call
contains key, or any other method that takes a pointer and loops over it. In the end, I'm going to submit this, but I'm definitely
working on it more for EC and just for peace of mind. 
- Anyways, I'm submitting now.

# 01/22/2021 8:40 p.m.
- I am starting the new homework today, homework 3
- I want to make a heapify program I think

# About two hours later
- That went way faster than anticipated. I surpised I'm already done.
- I decided I would use VSCode for the first time since it makes the QOL much
better and nano just isn't very fun to code in.
- I made a heapify c program which you can find out more with the ./heapify -h
command
- Overall, the usage of pointers wasn't very inspired I have to admit, but it gets
the job done. Nothing here is done that an array can't do (sadly).
- Now to start on the code puzzle.

# About an hour later
-I am fully done with the code puzzle and am about the submit for the week. I look
forward to next week.

# 01/16/2021, 11:00 a.m.
- I am starting my new homework for this week.

# About two hours later
- I have my idea fleshed out, and have made some solid progress including
which arguments I want and how I'm going to process strings.
- I am currently struggling with an index error that I'll have to add
an awkward if statement to fix. Currently considering different while conditions.
- I'm going to commit to using nano until it becomes too diificult. On a side node,
maybe I should just learn vim if I'm going to spend all this time doing difficult
compiler things.

# Another 3 hours later
- I have almost finished the project. I was so caught up in coding, I forgot to do some progress journaling.
- Overall, I had most of my issues with indexing errors, which I could fix with some thought.
- I also added a new option, bringing the total to three which is fun.
- Currently the program is case sensitive, which I don't know if I like.
- I have one more bug left with my verbose option where the indexes are innaccurate.
- I also need to make sure that my code will work with lines of length 1000. I doubt it at the moment.
- Also need to check the EOF exiting problem.

# About 30 mins later
- I fixed the main bugs that permeated the code. Now I just need to test for the 1000 character issue.
- I'm also having troubles with EOF detection AGAIN. It won't terminate my program after I run it, in fact,
it simply treats that input like it didn't happen if there were characters input before it.

# The next day after about an hour
- I added some quick bug fixes, and 1000 character support. I have no idea how to fix this EOF issue, so I think
I'll keep it in as a feature of sorts. A failsafe in case you didn't actually want to hit ctrl+d. I can't seem
to find anything on the internet about this issue either in all seriousness.
- I feel like I'm almost ready to commit and push, but I want to test a few more things first.

# A few hours later
- Okay, I think I'm ready to commit and push fully. The EOF thing is a lost cause, but I added FILE reading capability now.
- This is really cool in my opinion, but I wish I could stop having this problem with EOF. To learn more, my code is secretmessage.c
and it has a help page with the -h argument. 

# COMPLETION OF HW 1 LOG
- I spent about 2 and a half hours on this homework, but most of it was spent
tooling around. In actuallity, I could get this done in about an hour and a
half.
- The most frustrating part was not understanding what was happening
from an intuitive sense like you can with most OOP once you've learned one.
- The most eye-opening thing to me was how simple this all felt. Very simple
commands. Working with very simple, even fundamental feeling, structures.
At a certain point it almost felt like math to me in a weird way.
- The only suggestion is to add a tutorial on how to do your own --help page.
There are very few resources available, and it would be nice to have it on the
main page. I actually didn't end up doing it, though I wanted to.

# EXPLNATION OF HW #1
- I made a program which takes in a phrase and outputs the vowels from that
phrase in a yodel like manner, hence the name vodeler.
- There are some interesting features here. Detection of non-vowel phrases
(things get a little...awkward), newline spacing, and even case detection.
- To escape, make sure you are on a new input otherwise Ctrl+D won't eject.


# 01/08/2021 from around 8:30 - 10:30 p.m.

## Started at around 8:30
- Made my own git branch after mistakenly pushing to main
- Learned more about how git functions
- About to start working on homework
## About 25 minutes later...
- Came up with my program vodeler, which will yodel the vowels in an input
back at the user
- About to compile it for the first time.
- RESULTS: Absolute success! Worked like I wanted it to work. Now to make
it more yodelly (if that makes any sense).
## About 10 minutes later...
- Ran into a difficulty in detecting Ctrl+D. When the user types nothing,
it works to exit the program, but when they put in a series of chars
without a newline it simply spits out the right answer, but keeps running.
- I have a feeling I'm either not detecting newlines or EOF correctly.
## About 30 minutes later...
- I managed to make it more yodelly, but I'm still having that frustrating
issue with EOF and terminating. I think I'll try to look at some examples
from class.
- I'm doing all of this journaling/programming from nano which is something
to note as well.
## About 15 minutes later...
- Still having trouble with this Ctrl+d stuff, but now I've added newlines
at the end of intermediate outputs
- Also made things more awkward when folks don't include a vowel in their
utterance.
## About 15 more minutes later...
- I think I'm going to treat this like a natural part of how this is supposed
to work. Without string parsing, there's no real way to detect an EOL in
the middle of a line that's input which makes this quite hard.
- It's not particularly problematic either. It's just slightly confusing.
- I'm going to work on a --help page, then I'll try to submit and merge.


# 01/07/2021 from around 3:00 - 5:30 p.m

- Completed setting up the VM and VS Code
- Made the git branch
- "I read the syllabus"
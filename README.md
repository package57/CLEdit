CLEdit

To build : Replace Next
To Build: Exclude

Do you edit code? 

CLEdit is a Command Line Editor based on IBM TSO edit and BIM (an extension) with additional features

why?
Imagine if you would, the olden days prior to 1980.
no PC
no keyboards
no screens
no mouse
no GUI
no nothing!

How did we code?
We used 'punch cards' 

What?
	Punch cards are sheets of heavy paper, brown, about 3 inch by 7. with one corner trimmed off, in variuous colors, very handy.
On the punch cards, there was a layout printed, 8 rows and 80 columns.
There were 8 rows and 80 colums Hint - note 8 rows.

      You the programmer would write your code in block letters on 'coding sheets', green sheets of paper a little bigger than a legal pad.
Then you would, if you were lucky enough, walk your sheets over to the 'key punch' pool - or find your own IBM 026 Card Punch, and punch out your cards youself.
A stack of punch cards would be loaded into the IBM 026 card puncher and each line of code read from the coding sheet produced a 'punched card' by you typing the code off the sheet.
The card would have small rectangular holes punched through it, in colums, that represented bytes - where ever there was a hole - that was a 1 , no hole meant 0 , zeros and ones, analog binary.

    Now imagine, you have a stack of cards, one for each line of code! Don't drop them!
Well, if you were smart, you added sequence numbers, in the last 6 columns on the coding sheets. You wrote the numbers down and tracked them youself. 
If you were really cleaver, you'd number each line in a multiple of 5 or 10  - so that you could "insert" code using the sequence number as an index.
A physical index.

  If you dropped your stack on the floor, you could place it into a card sorter and it would fix it for you - if you had sequence numbers.
Otherwise you would have to manually restack your deck comparing it to the code sheets, or re punch your cards.
In school or at work these machines and services were valuable.

   So now you have your stack, or multiple stacks, imagine one line of code is one card! I've seen programs that used multiple boxes of cards, 2000 each, on trayed carts on wheels.
Some of these progams represented several months of work. They were nearly priceless. see Sir George Williams affair 1969 Montreal Canada.
"As the police and the students fought in the halls, other students threw computer punch cards out of the windows, littering the streets above with thousands of punch cards ".
Believe me, it was a pile too thick to drive through. Millions of hours of programming were lost.

     When you were ready to run your program, you added some special cards in front and back of your stack (brown) - to compile, link and run (red), followed by your data cards(green)!
It is 'data' processing after all, we're not dialing controls here or shooting at things. You loaded your stack into a card reader,  pressed F1 , R, Send on the keyboard of the Card Reader.
Then waited for someone to gather your 'listing' off the printer. Houston Automated Spool Protocol aka 'HASP'. Then you would head back to your desk to 'desk check' your output. 
No de bug.
No watching.
No nothing.
Everything with your eyes and your head and multiple eyes were essential. You could ask for a 'core dump' and get a stack of paper or hex output. Good Luck. 

	   This is how programmers lived and data processing occured until about 1980. I started in 1982 and this is how it was done.
Actually, I remember in college in the late 70's there was only one CRT, the "main" console. There was always a collection of future Phd's surrounding it,
ciggarets hanging from their lips, deep in thought, staring at the blinking cursor. Mesmorized. 

	  Next up was the DEC writer! A dot matrix printer with a keyboard. It would spit out a line and you would type in a response.
Back and forth over and over, like DOS or a Unix terminal without a 'screen' - no CRT's yet. You would keep the box of fan fold paper and run it through on the reverse side to save paper.
It was your log of day to day exchanges between you and the computer. The only proof you had of a proper result. 

       	  The next hugh break through - storage! On disk and tapes. Punch cards could be loaded into permanent storage on 'disk' and files could be on disk - or tapes!
Eventually, if you were good, you got a screen, a crt. tiny, monochrome brown - not green yet! Forget about color or high resolution. Your files were stored in Partitioned Data Sets.
Very much like folders today, but, easier to use IMHO. 

	    Now that you had a screen you could log on to Time Sharing Option (TS0) a CUI 'desktop' created at IBM in Toronto. From there you could manipulate settings and files
There were plenty of functions, always evolving amd improving yet at the end of the day it was a cui, no mouse, no copy / paste.  

So what could you do?

   	Well, a lot actually. even more dare I say than you can today with the most advance IDE editors out there. Don't freak out, I love intellisense etc, but sometimes they get in the way.
Hundreds of millions of lines of code form the backbone of modern buisness even today. All created without a GUI. I'm reponsable for several million lines myself. Sure I like Visual Studio etc as much as
the next person, but, sometimes I find it annoying and clumsy.

    Hence I wrote CLEdit. It will run anywhere, it uses C++, MySQL and wxWidgets for the GUI part. And when I say GUI I mean that in the very simplest of terms. Remember I never needed one. 
Also CLEdit combined with all the other files in my GITHUB repository package57, is like a 'book',  or a reference of code that is actually usefull, instructive, powerful and educational.
But most important of all - it works and it's understandable. At least I try to make it so.
The repository is full of very usefull code samples and examples with explainations with real world applications. Like processing data. Imagine.

The Fundamental Pricipals for programming is to master these three concepts:
    Sequence - what needs to happen first, and so on  
    Condition - under what conditions  
    Iteration - looping, doing things again and again, over and over consistently and accurately

    The next most important thing to remember is: The very basic requiremnt is that you program 'works'. How did it work? How long did it take to run? What resources were needed?
What difficulties were encountered? What was accomplished? What went wrong? How do you fix that? You will quickly forget why you wrote what you wrote - so be as clear as possible
with your code 'style', don't get fancy. The computer can handle millions of instructions. Modern compilers and pre compilers will 'fancy' up your logic for you - even if that wasn't your plan.
see C++ CASE

    Remember Syntax is Syntax, but people are people and you brain can only handle so much pain. C++ will have you asking "what the hell does that mean" all day into tomorrow. C++ is dumb.
The only thing about it that I like is it's 'typed' and supports structured programming techniques. Oh and if you want to, you can create "objects", but in 40 professionsl years I never did once!    

	 There are three big blocks to CLEdit - all in C++. I know. C++ is, what it is! 
CLEdit is the GUI 
CLEditCF provides file functions
CLEditDB provides database functions using MySQL 

       So....CLEdit is similar to the editor I used for 40 years, on big iron computers aka TSO/Edit
I've set the file size limit is 25,000 lines. The biggest single program I ever coded was 23,000 lines called HKOP0203.
I have seen bigger, ZF9100 - 95,000 lines! Imagine that in cards, almost 48 boxes. You'd need a van.  
  
Key Board Commands 
ENTER: Process Screen - process what you entered
   F5: Find - repeat find
  END: Bottom - scroll to the bottom of the file
 HOME: Home - scroll to the top oof the file
   F7: Up - page up
   F8: Down - page down
   F1: Help - provide these notes :)
   F6: Change - repeat change

Primary Commands (apply button) 
"create filename" - create a file from a block of Copy code 
"change fromstring to string all" - change a string to another string everywhere
"change fromstring to string" - one at a time
"copy flename" - into the file After a line location   
"exclude"  - exclude all line from view  
"find string" - find a string 
"open filename" - open a file
"save" - save the current file
"saveas filename" - save the current file with a different name
"exit" - terminate the application. bye,end,quit,leave will work just as well
"fromstage mydb mytable" - get a file from a database name table name - MySQL loves many tables more than many rows!
"tostage mydb mytable" - store the file in a database name table name
"bottom" - scroll to the bottom of the file
"home" - scroll to the top of the file
"up" - page up
"down" - page down
"help" - provides these notes in the Log file

Line Commands - entered to the left overlaying the line numbers
'A' - place a copyied line or copy block after this line - as many places as you want, multiple after 
'B' - place a copyied line or copy block after this line - as many places as you want, multiple before
'C' - copy a line
'CC' - copy a block,  CC on one line, CC on another line anywhere in the file  
'D' - delete a line
'DD' - delete a block of lines
'I' - insert a line
'M' - move a line after or before another line
'MM' - move a block of lines after or before another line
'O' - overlay a line with the contents of a moved line - all the space in the overlay line will be replaced with the data from the moved line and the moved line will dissappear   
'OO' - pverlay a block of lie with the data from a corresoponding move block 
'R' - repeat a line
'RR' - repeat a block of lines 
'>' - tab a line right
'>>' - tab a block of lines right 
'<' - tab left
'<<' - tab a block of lines left
'X' - exclude a line from view / impact
'XX' - exclude a block of lines from view / impact













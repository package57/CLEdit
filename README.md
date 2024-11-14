CLEdit

do you edit code? 

CLEdit is a Command Line Editor based on IBM TSO edit and BIM (an extension) with additional features

why?
imagine if you would, the olden days. no keyboards, no screens, no mouse no GUI no nothing! 
how did we code? we used 'punch cards' 
what? 
punch cards are sheets of heavy paper, brown, about 3 inch by 7. with one corner trimmed off, in variuous colors (handy)
on the punch cards, there was a layout ptinted, rows and columns.
there were 8 rows and 80 colums Hint - note 8 rows
you the programmer would write your code in block letters on 'coding sheets', green a little bigger than a legal pad.
then you would, if you were lucky enough, walk your sheets over to the 'key punch' pool - or find your own IBM 026 Card Punch
a stack of punch cards would be loaded into the 026 and each line of code from the coding sheet produced a 'punched card'.
the card would have small rectangular holes punched through it - that represented bytes - where ever there was a hole - that was a 1 , no hole meant 0 , zeros and ones, analog binary 
now imagine, you have a stack of cards, one for each line of code! Don't drop them!
well, if you were smart, you added sequence numbers, in the last 6 columns on the coding sheets
if you were really cleaver, you'd number each line in a multiple of 5 - so that you could "insert" code using the sequence number as an index
a physical index
if you dropped your stack on the floor, you could places it into a card sorter and it would fix it for you - if you had sequence numbers
otherwise you would have to manually restack your deck comparing to the code sheets, or re punch your sheets
in school or at work these machines and services were valuable
so now you have your stack, or multiple stacks, imagine one line of code is one card!
when you were ready to run your program, you added some special cards in front of your stack (brown) - compile, link and run cards (red), followed by your data cards(green)!
it is 'data' processing after all
you loaded your stack into a card reader,  pressed F1 , R, Send on the keyboard and waited for someone to gather your 'listing' off the printer
then you would head back to your desk to 'desk check' your output 
no de bug, no watching, no nothing. everything with your eyes and your head and multiple eyes were essential 
this is how programmers lived and data processing occured until about 1980.
I started in 1982 and this is how it was done. Actually, I remember in college in the late 70's there was one CRT, the "main" console 
there was always a collection of future Phd's surrounding it , ciggaretts hanging from their lips, deep in thought 

next up was the DEC writer!
a dot matrix printer with a keyboard
it would spit out a line and you would type a response
back and forth over and over, like DOS or a Unix terminal without a 'screen' - no CRT's yet
you would keep the box of fan fold paper and run it through on the reverse side to save paper
it was your log of day to day exchanges between you and te computer
also, a hugh break through - storage! 
punch cards could be loaded into permanent storage on 'disk' and files could be on disk - or tapes!

eventually, if you were good, you got a screen, a crt. tiny, monochrome brown - not green yet! 
forget about color or high resolution

now that you had a screen you could log on to Time Sharing Option (TS0) a CUI 'desktop'
from there you could manipulate settings and files - there were plenty of functions - always evolving amd improving
yet at the end of the day it was a cui, no mouse, no copy / paste

so what could you do? well, a lot actually. even more dare I say than you can today with the most advance IDE editors out there
don't freak out, I love intellisense etc, but sometimes they get in the way

hence I wrote CLEdit, it will run anywhere, it uses C++, MySQL and wxWidgets for the GUI part
and when I say GUI I mean that in the very simplest terms. 
also CLEdit combined with all the other files in my GITHUB repository package57, is like a 'book',  or a reference of code - that is usefull, instructive, powerful and educational
but most important of all - it works and it's understandable. At least I try to make it so.
the repository is full of very usefull code sampes and examples with explainations


there are three big blocks to CLEdit - all in C++. I know. C++ is, what it is! 
CLEdit is the GUI 
CLEditCF provides file functions
CLEdit provides database functions using MySQL 

So....CLEdit is similar to the editor I used for 40 years, on big iron computers
Note: the file size limit is 25,000 lines. the biggest single program I ever coded was 23,000 lines called HKOP0203. 
  
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
create - create a file from a block of Copy code 
change - change a string to another string
copy   - 
exclude - exclude line from view or impact 
find - find a string
open - open a file
save - save the current file
saveas - save the current file with a different name  
exit - get out
fromstage - get a file from a database name table name - the name of the table is the name of the file MySQL loves many tables more than many rows! 
tostage - store the file in a database name table name 
bottom - scroll to the bottom of the file 
home - scroll to the toip of the file
up - page up
down - page down
help - provides these notes
change - change a string to another string, repeat one by one or all if you are brave  

Line Commands
A - place a copyied line or copy block after this line - as many places as you want, multiple after 
B - place a copyied line or copy block after this line - as many places as you want, multiple before
C - copy a line
CC - copy a block,  CC on one line, CC on another line anywhere in the file  
D - delete a line
DD - delete a block of lines 
M - move a line after or before another line
MM - move a block of lines after or before another line
O - overlay a line with the contents of a moved line - all the space in the overlay line will be replaced with the data from the moved line and the moved line will dissappear   
OO - pverlay a block of lie with the data from a corresoponding move block 
R - repeat a line
RR - repeat a block of lines 
> - tab a line right
>> - tab a block of lines right 
< - tab left
<< - tab a block of lines left
X - exclude a line from view / impact
XX - exclude a block of lines from view / impact
I - insert a line












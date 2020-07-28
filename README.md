
# Design Doc

## Printf, What does it do?
Essencially it's a function that when called will produce a formated string out of 
the inputs. The Formating is limited in scope but handles a surprisingly large number
of permutations.

## How is it used?
The ft printf() function is called with a number of parameters. These are a string
(usually in "" quotes) and the variabes (defined either in the function call
or before) that will in some way modify the string. This modified string is the
final product.

So what does the algorythm that handles the string and it's parameters look like?

#### Summary of the Overall Algorythm
Assuming the inputs are correct this is how the algorythm treats them.
First the entirety of the inputs (a format string and acompanying optional variables)
are passed to the main parsing function which is responsible for dividing the
inputs into ones containing a % and thus a specifier and those which contain
only characters from the first string.
If a % specifier is found, the format string starting from that % is sent to be parsed
by the spec parser. This function sorts through the string to identify flags,
width, precision and size by calling on the flag parser functions, and then
aggegating that information into a single easy to read structure variable.
This variable along with the format string are then passed to the respective
function corresponding to which type of % specifier it is. The handler function
modifies the format string in accordance with the flags and returns a new string.
This string is retrived by the main parsing function and send to the pflist append
functions to be added as an element to the linked list containing all the processed
strings from the origional format.
If on the other hand parsing hq finds no % specifier, it copies all that is left
and sends it to the pflist append functions to be added to the same linked list.
In the even that some charaters exist before a % specifier they are added as their
own element to the linked list before the % specifier is treated and added.
Finally, once the entire format string has been processed and added to the linked
list, and assuming it all went well, the linked list is sent by the root
ft printf function to a display function which prints them on screen.

#### A few things to note:
Because the format string is processed in order, the linked list is by default
in order, which is rather conveinient.
Unlike the origional printf, this version does not make use of a buffer and
instead dynamically allocates memory. While this is more memory intesive, it does
mean UTF-8 charaters are intrinsically/natively supported.
Seems like there is nothing that can be done to handle bad va arg list inputs
the OG printf handles that during compilation I think... Ignoring it then.
Currently we send a pointer to va list ap which is more efficient.
Unfortunately i decided that %lc and %ls would not be supported, not enought time
to figure out exactly how Pascal's implementation works...


## The Nitty Gritty
Printf is a surprisingly complicated function in particular because of how it's
different options (specefiers, flags, width, precision & size) can interact.
The next sections will detail what all these options are, how they interact,
what algorythms i use to produce particular outcomes, and what can be found in
each of my files and functions.

### Options

#### Specefiers
d: A signed decimal integer, subject to size modifications
i: Essencially the same as %d. (Seems to be depricated, but mine works).
B: Signed base converted integer, base is specified by additional va list
arg, can be any valid symbols.
b: Unsigned binary integer, subject to size modifications.
u: Unsigned decimal integer, subject to size modifications.
o: Unsigned ocatal integer, subject to size modifications.
x: Lowercase unsigned hexadecimal integer, subject to size modifications.
X: Uppercase unsigned hexadecimal integer, subject to size modifications.
c: Single Character.
s: String of Characters.
p: Pointer address.
N: ?
n: Stores number of characters written at the integer addess passed as arg.
%: Writes a single % modulo.

#### Flags
0: Left-padding is '0's rather than ' ', applies to numbers and characters.
'#': Prepends a designation of base type to standard bases, oct, hex, bin.
+: Prepends any number with its respective sign, '+' or '-'.
-: Left Justifies result, padding cannot be '0's, only spaces.
Space: Prepends a space before everything else, except in case where '+'
flag is called.

#### Width, Precision and Size
Width and Precision can be specified either in the format string or as seperate
arguments passed through va list. If they are passed through va list they may
also contain the '-' flag which will be treated as though it were in the format
string.




##### Sizes
l:	long, also wchar t
ll:	long long
h:	short int
hh:	signed char
j:	intmax t
z:	size t

How do I deal with the various sizes?
Well first of all i distinguish between numbers and string-like entities. I also
distinguish between unsigned and signed numbers. From these groupings I go about
assigning specific "casts" according to the size flag. There are some specific
things i don't handle, like wchar t for %ls and %lc, but besides that i handles
all the main size flags in all permutations. As far as handling the "casting"
portion of things, I took a very simple aproach. Everything is declared as the
largest possible varible type, and the output from va arg list is cast to the
correct size and stored in that oversized variable. That way evyerthing fits.
Given the low number of variables passed in any given printf function call, I
decided that a little overkill wasn't anything to worry about.




### Parsing

#### Parsing Main
The crux of this algorythm, is distiguishing between % specefiers in the format 
string and the filler chars (everything else). So we cycle through the format
string looking for '%' with the findchar function, if we find one we remember
it's possition in the string relative to where we started, if that possition is
further along that where we started we know there must be filler characters.
Those filler characters are treated by the listify not spec function which is
given the current start and relative possition of the next % spec (as calculated).
It adds the filler characters to a linked list containing all the final output
strings in order. Then the format string starting from the relative possition of
the new found % spec is passed to the spec parsing function. The results are also
added to the linked list. Anything left over after no more % specs are found are
handed to the same listify not spec function to be added to the linked list. If
there are no % specs, everything is handed to the listify not spec function.

m is the size of the thing that was created from the format str and specs/flags
ret is c is the len of format that was read to get through 1 % thing.


#### Spec Parsing
Spec parsing mostly outsources work but it serves as a main switch or junction.
First it initialized the param structure type variable, next it calls the flag
parsing function, then it determins the % spec with findchar, which is send to
pick handler which send all the relevant information to the right handler
function. It returns the size of the % spec that was read from the format string
but a string containing the processed results and the length of that result are
communicated back to parsing hq using pointers.

t param p is never malloc'd and nothign in it is either, and it never moves up
the tree, only down branches, so it doesn't need to be freed, it will die as
soon as it's instance of parse specs is complete.


#### Flag Parsing (also includes width, precision and size parsing)
This may be the most elaborate of the parsing files but it's also the most
'redundant'. Everything (format string starting immediately the % of the spec,
the param structure, and the va arguments list) is passed to the flag parsing
function. It uses a findchar in a while to loop through the format string until
it reaches a char that isn't a flag, precision, width or size (in that order).

Precision:


Width:


Size:
Similarly to spec parsing, it cycles through the format string as long as it
finds a valid size flag (using findchar). Because the results (it did or did not
find a certain flag) are stored as bits of an int in the t params var, and they
are set in this order: h, hh, l, ll, z, j; the setting of these bits is rather
redundante and can be optimized for shorter code. Namely, doing math around the
i indicator resulting from the findchar. It is fairly straight forward. First
h, hh, l and ll are handled, because in the event an h is found, the correct bit
must be switched on, but if another h is found, the single h bit is switched back
off and the double h bit is switched on. Same applies to l and ll. j and z are
more straight forward, they are or they aren't. The order and values as shown by
the defines in the .h explain the factors and other math around i to make it all
work as intended while not being completly explicit and thus redundant.

Presently, i do not in any way test if multiple sizes have been switched on...






### Handlers


#### Handle Int
Handle int is split into 2 main functions, one for signed and the other for
unsigned numbers. Each of these also have their own respective casting functions
which handle the transfer from va arg list to an in memory variable. That switch
occures with a if forest.

Signed:


Unsigned:
The '+' flag works the way you would expect it to on an unsigned number. If the
width is large enough, a '+' replaces a space or a '0', if the width is too small
a '+' is added anyway increasing the len of the resulting string. This obviously
doesn't apply to '-', for negative numbers the value wraps.



%0+15d is fine
%0 15d is fine
%0-15d is NOT
%0#15d is Undefined (mine ignores #)

Ok so: 0 and - it says 0 is ignored if - is present regardless of the order, mind ignores 0 and still prints

%15-d is invalid but mine does not care...
same with + space, any flags really, flags before wid and prec, but 0 can be either...
but
%.015d works just fine with 0 being not a number but the flag...

%l15d is invalid, but mine works, (not anymore, we fixed it)

I haven't secured for if send a not long and ask for a long, or the oposit ?

seems i have fixed a lot...

Ok so i have a define for when the num passed is 0 (not sure why)
Ok the very specific case where num = 0 and prec = 0 you display nothing for the number


%+4d if d smaller in len than 4, and positive, you should end up with 4 char printed in total: space + 2 numbers
(this is not tested but PFT)
Ok here's something weird, where there's a neg number but no '+' flag and there is a space, it is ignored as though there were a '+' flag...
Solution: neg still 0 if pos and -1 if neg number, but not factored into len imediately. Instead, we calculate plen relative to the len
which represents the number of digits only, then we add 1 if there is a sign, + or -. This new len is used to calculate wlen and everything else.
The main diference is that we now treat pos num with + flag the same as neg num.



Ok so this is how B works. B is for turning any number into a base that you provide,
if you don't provide a base, it's like yo, no base...
The number comes first then the base...
If the base is invalide it's like the fuck you need a real base...




#### Handle Pointer:
Like most other specs, if prec is 0 becomes an empty string to which wid is
applied the rest of the flags. (prec is zero() handles part of this).

#### Handle Str
If there is a space: '% s', then even if the string passed is null, a space
is printed. Not actually sure if that is correct behavior, but seemed right...
One quirk of Handle str, because it is supposed to print (null) if it is passed
NULL, it needs to be able to distinguish between a function fucking up and
being passed NULL from the get go...
nstrdup i made handles this, it's not generic but it works and is secure.

#### Handle Char (lives in handle str.c)
Ok so here is the bit that's really quite tricky. In the even you get a -
and a width > 1 and a precision == 0, then you should print only as many
spaces as the width, but i'm not sure i can do that without the plen var...
Doesn't seem like it, gonna leave it as such...
The Space flag is undefined in real printf, i define it as working as a normal space
flag, but it gets overriden by '-' flag.

#### Handle Modulo
Space is not a valid flag, it has no effect, left untreated. Width can be any size.
Is secure once again because of the fill with and fjoin combination.



### Everything Else

#### Base Conversions
The three Base Conversion functions are capable of taking a positive number
as large as an unsigned long long, any base, checking that base and returning
the converted number as an allocated string.
Note, they only take positive numers, for casting size reasons.
The math is rather straight forward. You modulo your number by the size of
the base to get the right most digit, then you divide by the base size to get
rid of that digit from the number. Repeat until you have a number smaller than
the base size, that is your last digit (the left most one of the OG number).
The add char functions is a little intensive, copies all current digits to
transfer them to a new string that has been allocated with 1 additional byte
to accomodate the new char.

Ok so we changed some thigns a bit, the largrest possible string si the llmax
in binary, which is 63 1's long, thus a 64 char string include the \0.
Thus i allocate a string of 64, fill it back to front and then strdup the end
starting from the furthest digit from the last position.
EX: ..........11011010001010101\0
Dup starts here




#### Pfelem List
ft new pfelem():
creates a new var of type pf elem, and populates it with the
arguments passed to it (a str and a size).

ft pflist append():
appends a pfelem to a pfelem list.

ft str to elem():
turns a string into a new pfelem with new pfelem, but not
necessarily the whole string, only up to the len that was specified as an
argument. Don't free cp in this func because it is stored in the linked list
as the final output, str from which it comes gets freed right after, each link
is added, but there is a new cp for each link, so don't free till printed with
display.

ft pflist del all(): 




#### Display
Called from ft printf() once the whole format has been processed successfully,
it goes through the linked list that has been created to contain the strings
and prints them before freeing the element of the linked list.
It also handles the ( N ) specifier, counting the number of char printed and
displaying that number should an element containing only '\0' be come accross.


#### Major Extra
ft pos itoa():
A regular itoa but only handles positive numbers so can be an unsigned long
long, the largest number.

ft latoi(): Len Atoi
Called from Parse Flags.c, it is a regular atoi which also counts the string
size of the number it is converting from a string to an int, the result is
stored in a pointer to an int and it's length is the return value;
For Security reasons:
You pass it a pointer to the int that will hold the value of the string that
is being atoi'ed; the result essencially. The return is the length of the int
that has been created. This way, not the other way around (passing a pointer
to an int that will contain the lenght of the result) because in the event
of failure, this way we say the len is -1, which clearly is never a valid
option if success.
return (-8) if error because i do rlen += latoi and since rlen can already
be > 0, i don't know how much to decrese by to have it be exactly -1, so
way to big ret and <= -1 if check.


ft fstrjoin():
A secure version of strjoin(), can take either pointers sent in param being
NULL. Not the same as in GNL.
Ok so anything you send it will be freed, even if there is an error, which is
rather handy. Thus if i call a fill with func and send the result to fjoin,
even if the fjoin fails the fill with is free, so i don't need to handle that
error case.

#### Minor Extra
ft fstrlen():
A secure version of strlen(), can take a NULL pointer passed in parameter.

ft scott free():
A short cut function, it takes a str and bzero, free and sets it to NULL.

ft fill with():
Mallocs an amount of memory + 1 and fills it with the requested char and
NULL terminates.
IE it creates a str x long of a given char.

ft fstrdup():
A secure version of strdup.






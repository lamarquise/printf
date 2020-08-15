
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
First the entirety of the inputs (a format string and acompanying optional
variables) are passed to the main parsing function which is responsible for
dividing the inputs into ones containing a % and thus a specifier and those
which contain only characters from the first string.
If a % specifier is found, the format string starting from that % is sent to
be parsed by the spec parser. This function sorts through the string to identify
flags, width, precision and size by calling on the flag parser functions, and
then aggegating that information into a single easy to read structure variable.
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



Seems like my standard/goto is to free at the lowest point, rather than at the
point of creation. So when something fucks up, i free what needs to be free then
and there, rather than returning falls all the way up to the point of creation
and freeing then. Reason being, while i think for the most part my achitecture is
a tree, I am fairly certain some instances of vars being created and migrated to
parallel or above the point of creation, exist. This as policy, i free imediately.

Wait ok so it's more like 1 level above the point of failur mostly.
So like I call a function, it fails, in the function that called it, i free shit.
Except fstrjoin, cuz that shit frees under normal circumstances so needs to also
free if failure...

Actually that does not apply for lst (freed at point of creation if error) but that
might be the only one.

Amendament to the freeing policy: Free at point of creation as much as possible,
shorter and deals with the possibility that the thing failed to be sent to a func
(which in case of error was suppoed to free it... but can't).


So far there is only 1 point of failure that results in a unpatchable leak, if
pflist del all() fails there are leak, obvi, since it handles the everything at
the end...


For future reference, an fstrjoin where on of the arguments is assigned the result
is bad practice, if it fails and the fstrjoin can't free that argument, then you
end up with a leak...

One thing that could be better, when there is a an empty string, and the size is 0,
meaning its a normal empty string not a %n or whatever, it still creates a pfelem
and adds it to the linked list, kinda unnecessary...

In the event of failure midst printing, everythat that has already been printed
remains. There does not appear to be much i can do about that.

I am fairly certain that the correct return in the event of an error is -1, and
the number of char printed upon success.

Might add a few things, like printing arrays and to files and such later, but lets
be honest, prolly not unless i need that sort of thing.


### Structures and Defines

There are two sets of Defines, the first relates the flags to their bit position in
the int in which they are stored. The bit position is writen in hexadecimal for
added clarity. The second relates the size flags to their bit position in much the
same way.

I created two structures for this function, t param and t pfelem. T param is used
to store all the information relating to a %, it contains a char and 4 ints,
representing the specefier, flag, width, precision and size. An instance of t param
is generated for each % come accross in the format string. T pfelem is a linked list
structure. Each % and the strings of chars between them in the format string are
stored in order in an element of the linked list of this type. It is rather simple,
just a pointer to the char contents, an int representing their size, and a pointer
to the next element in the list.

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
N: Prints the number of chars written at the point it is called since the last %N call.
n: Stores number of characters written at the integer addess passed as arg. (the real one)
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

Can't do i += ft spec parsing instead of c = ... and i += c after, cuz the format
string could be any length, so would have to subtract a really big number, and
risk a bunch of stuff..

This may be one of the most refined functions i have ever writen....

ft list add() exists to facilitate the freeing of the new pfelem in the case of
error, it breaks up the creation of a new pfelem from str to elem, and the
transfering of that elem to the lst with append lst.

ft listify not spec():
Does a little math and securely adds everything that isn't a spec to the pflist.
Returns -1 because ft printf works better if recieves -1 as error value.


In case of Error:
lst if freed in ft printf(), str is freed in parsing HQ, tmp exists only in listify
and is freed there, s exist as a proxy for tmp or str and is freed one above,
so either in listify or HQ depending on where it was called.


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

Return is -1 if error since ret otherwise represents the number of char read,
which i think could be 0 ? maybe ?

"0#+- .123456789 'star' hljz"


#### Flag Parsing (also includes width, precision and size parsing)
This may be the most elaborate of the parsing files but it's also the most
'redundant'. Everything (format string starting immediately the % of the spec,
the param structure, and the va arguments list) is passed to the flag parsing
function. It uses a findchar in a while to loop through the format string until
it reaches a char that isn't a flag, precision, width or size (in that order).

While in findchar loop, if ret < 1 by end, -1 the whole thing, i think 1 better
than 0 cuz means hasn't stayed stationary, but only works for first flag, pretty
much useless later...


Precision:
If using star to pass precision as an argument, if the value is negative it is
treated as though there is no precision.
psize is precision size
rlen is read length

Ok so when theres a . but no number or star, correct behavior is to still
produce something.
Thus don't worry about latoi not -1ing the whole thing when there's no number
passed, incorrect char are handled elsewehere (by findchar in main flag parsing
func).


Width:
wsize is width size, absolutely necessary to initialize it.


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

Now secure against multiple flags and too many of a single flag.





### Handlers


#### Handle Int
Handle int is split into 2 main functions, one for signed and the other for
unsigned numbers. Each of these also have their own respective casting functions
which handle the transfer from va arg list to an in memory variable. That switch
occures with a if forest.

Precision: pads with '0's on right, unaffected by '-', takes precedent over width.
0s added on left never right of num unless a float ???
Width: pads with ' 's on right, OR '0's if '0' flag,
OR left justify with ' '  not '0' if '-'

signs + or - do not count in precision but do count in width...
0x of # does not count in precision but does in width...


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


%+4d if d smaller in len than 4, and positive, you should end up
with 4 char printed in total: space + 2 numbers
(this is not tested but PFT)
Ok here's something weird, where there's a neg number but no '+' flag
and there is a space, it is ignored as though there were a '+' flag...
Solution: neg still 0 if pos and -1 if neg number, but not factored into
len imediately. Instead, we calculate plen relative to the len
which represents the number of digits only, then we add 1 if there is
a sign, + or -. This new len is used to calculate wlen and everything else.
The main diference is that we now treat pos num with + flag the same as neg num.

Precision is calculated without sign + or -. Width is calculated with sign - or + (if + flag).



Ok so this is how B works. B is for turning any number into a base that you provide,
if you don't provide a base, it's like yo, no base...
The number comes first then the base...
If the base is invalide it's like the fuck you need a real base...


0x or 0o or 0b or whatever must be counted as part of width but not as a part of the precision...



Gen Arg Str I():
Manages most of the setting of the string recovered from va arg list, in accordance
with the flags and options.

The str in question is passed as a pointer to a string, and freed in all error
cases.
NO
Str is freed by handle int in case of error, gen arg str frees everything it creates
in case of error.

Additionally, a pointer to t param p, the len of str and neg (indicating it's
sign) are also passed as arguments. The precision and width are modified to take the
len and sign into account. Then begins the process of creating the strings that will
be attached in front and behind the main result string. (details not provided here).
Essencially it invloves creating the correct numer of the correct char and attaching
it in the correct place, rather fineky.
In oder to meed the norm, a few functions containing sub processes of gen arg str i
were created in Gen Arg Str.c 


everything else is free bellow, either defined in func or by fjoin which free's so much shit...


Ok new policy, free things at point of allocation, that way if i pass a thing
and it fails to get passed, the free happens after not in the place it didn't get
passed to. Also seems to be a lot fewer scott free funciton calls...




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

Gen Arg Str S():
Most of the inards were passed of to functions created in gen arg str.c
Similar to one for Ints, the str created by the Handle gets freed in case
of error above the gen arg str.

ft h str wid():
Handle Str Width(), deals with the width for gen arg str s in handle str.c
Moved to Handle Str from Gen Arg Str cuz self contained and needed the room.
Many of the frees in error cases are handled by fstrjoin.

ft str has wid():
h str wid() was too long so moved some of it.

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
Frees are a bit insanely overlly redundant, but id rather that than leaks...


### Everything Else

##### Gen Arg Strs

ft add hash():
Only used by handle int.c Its an if tree for mallocing the correct symboles to
prepend numbers with in the even they not be base 10 and have the Hash flag.

ft h int space():
Exists to help int wid fit in 25 lines, not my favorit, some ugly conditions.

ft h int wid():
Handle Int Width(), only used by gen arg str i in handle int.c

ft prec is zero():
Used by handle Str and Pointer, used in the very particular case that there is
a precision and it is 0, need to create an empty string.
Must free str here cuz the whole point is that it is replaced by an empty string.

ft h str prec():
Handle Str Precision(), deals with the precision for gen arg str s in handle str.c



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
Creates a new var of type pf elem, and populates it with the
arguments passed to it (a str and a size).

ft pflist append():
Appends a pfelem to a pfelem list.

ft str to elem():
Turns a string into a new pfelem with new pfelem, but not
necessarily the whole string, only up to the len that was specified as an
argument. Don't free cp in this func because it is stored in the linked list
as the final output, str from which it comes gets freed right after, each link
is added, but there is a new cp for each link, so don't free till printed with
display.
A few things added to accomodate the %n and %N specs, bit of a patch, but its
near the end so it's acceptable.
Str of HQ sent here to be turned into cp, str is freed in HQ in both error and
success cases. Cp is only freed in str to elem() in error case, else it is freed
by pfelem del all() or display del() at very end.
There is a tiny potencial for it to segfault in the event of num or size being
equal to -1 starting half way through... Memcpy doesn't handle things so well.
Use memcpy for the very specific case where the string we want to copy starts
with \0.


ft pflist del all(): 
Ok so it cycles through a list freeing the contents and the elems, returns -1
in all cases, error or success because printf error value is -1.



#### Display
Called from ft printf() once the whole format has been processed successfully,
it goes through the linked list that has been created to contain the strings
and prints them before freeing the element of the linked list.
It also handles the ( N ) specifier, counting the number of char printed and
displaying that number should an element containing only '\0' be come accross.

If size of elem is 0 it doesn't even make the call to have anything (nothing)
printed, useless to have the elem of the linked list, but kinda too late for
that now.

ft handle sn():
Handle Small Number, deals with %n, not complicated just needed the space.
Kinda hard to know if it is truly secure, the user could mess it all up if
they wanted to...

ft disp bn():
Display Big Number, deals with %N, just prints, also simple, needed space.



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
Made to turn string into a long so can manage addresses/pointers.

ft fstrjoin():
A secure version of strjoin(), can take either pointers sent in param being
NULL. Not the same as in GNL.
Ok so anything you send it will be freed, even if there is an error, which is
rather handy. Thus if i call a fill with func and send the result to fjoin,
even if the fjoin fails the fill with is free, so i don't need to handle that
error case.

ft cstrjoin():
Joins a single char to a pointer to a string, frees the pointer it receives
no matter what (error or not). Reallocates new string to be sent back.

ft fill with():
Mallocs an amount of memory + 1 and fills it with the requested char and
NULL terminates.
IE it creates a str x long of a given char.

#### Minor Extra
ft fstrlen():
A secure version of strlen(), can take a NULL pointer passed in parameter.
Returns 0 if NULL input.

ft scott free():
A short cut function, it takes a str and bzero, free and sets it to NULL.
Policy regarding Scott Free is ret -1 if an int, 0 if not checked or needs
to be NULL cuz char star.
Need to cast in the return if using it to spoof a NULL.

ft fstrdup():
A secure version of strdup.

ft nstrdup():
An strdup for those times when you need to verify success with a number.
If it is possible for one of the arguments to be an empty string and for
that to be a valid input, then this function is what you need.
The if (!og) ret(1) is my printf specific, making this not eligible for
my libft, but a modified version could be added.

ft nstrlen():
Another candidate for the libft, like scott free you tell it the return you
want in case of error. I could prolly replace fstrlen with it in many cases
by having it return 0...
Mainly useful in Handle Int, since the return was fstrlen, but in the event
of a NULL pointer being sent, it would still return 0. Not anymore.





# Design Doc

## Printf, What does it do?
Essencially it's a function that when called will produce a formated string out of 
the inputs. The Formating is limited in scope but handles a surprisingly large number
of permutations.



## How does the function work?
The ft_printf() function is called with a number of parameters. These are a string
(usually in "" quotes) and the variabes (defined either in the function call
or before) that will in some way modify the string. This string is the ultimate product.

So what does the algorythm that handles the string and it's parameters look like?


Collect the params
parcours the string until specifier
cut up into linked list
treat specifier and flags
puts final product into an elem of linked list type
elem is attached to linked list
linked list is parcouru and printed assuming there were no errors
it can be printed in dif places depending on which version of printf was called.

There are more details in the "Deal with specefiers and flags" part of this algo... 





### Ft_Printf.c

ft_printf():
Simple and straight forward, it inits a few variables, the linked list,
and does some basic checks before calling the first beefy func.



### Pfelem_List.c

ft_new_pfelem():
Creates a new element of t_pfelem structure type.

ft_plist_append():


pfelem_append():
Appends a list of t_pfelem type, does not create its own new elem, that
is passed as a param. Easier to send a **lst rather than *lst.

ft_buf_to_elem():
Takes a string (sourced from *format) and creates a new elem containing
that str.

ft_pflist_del_all():




### Parser.c

ft_HQ():
Does the majority of the work of going though *format, includes a loop
that looks for %s and seperates *format into bits that can be stored in
linked list.



### Parse_Buffer.c

ft_field_parsing():
Called from ft_HQ(), this function takes *format after a % has been reached,
calls flag, width and precition recovering funcs before determining the
specifier and routing the appropriate function.
Imporantly, this function returns the number of char of *format that have
been read after a %.



### Parse_Flags.c

ft_flag_parsing():
Called from ft_field_parsing() to recover all but the specifiers, uses
bitwise to store the flags.

ft_get_precision():
Called from ft_flag_parsing() once a '.' is reached, this finds and stores
the value of the precision.

ft_get_width():
Called from ft_flag_parsing() once a non 0 digit is reached, it finds
and stores the value of the width.

ft_get_size():
Called from ft_flag_parsing() when any of lhzj are reached, not sure how
it stores them yet...



## HANDLER FUNCTIONS

### Handle_Int.c

ft_handle_int():
Called from ft_field_parsing() after the flags, width, precision and size have
been parsed.
First it discerns between specifiers ( diuxXbB ) and collects the value from
va_list.
Then works through the specifiers aprefixing or appending tmp as need be
using a middle out sort of methode (ie, start with tmp, and add to front and
back). Uses a special ft_fstrjoin() and ft_fill_with(), for this.
Finally it sets the final result = *str.


### Handle_Str.c

ft_handle_str():
Called from ft_field_parsing(), very similar to ft_handle_int(), it handles
( cs ) specifiers, basically the same structure for dealing with flags.


### Handle_Pointer.c

ft_handle_pointer():
Called from ft_field_parsing(), very similar to ft_handle_int(), handles ( p )


### Handle_Modulo.c

ft_handle_modulo():
Called from ft_field_parsing(), very similar to ft_handle_int(), handles ( % )


### Base_Conversion.c

ft_add_char():
Basically a strjoin() but prefixes a single char to a *str, mallocs a new str
and frees the old one if possible.
Used by ft_any_base_convert() to prefix its result.
It has a char* return so we can secure the malloc.

ft_base_check():
Checks if a base is valid, no repeating char, also returns the size of the base

ft_any_base_convert():
Called in ft_handle_int() for multiple specifiers, converts any int to a given
base, returning a *str.


### Display.c

ft_display_del():
Called from ft_printf() once the whole *format has been processed successfully,
it goes through the linked list that has been created to contain the strings
and prints them before freeing the element of the linked list.
It also handles the ( N ) specifier, counting the number of char printed and
displaying that number should an element containing only '\0' be come accross.


### Extra.c

ft_latoi():
Called from Parse_Flags.c, it is a regular atoi which also counts the string
size of the number it is converting from a string to an int, this number is
stored in an int* passed as a param.

ft_scott_free():
A short cut function, it takes a **str and bzero, free and sets it to NULL.

ft_fill_with():
Mallocs an amount of memory + 1 and fills it with the requested char and
NULL terminates.
IE it creates a str x long of a given char.

ft_fstrlen():
A secure version of strlen(), can take a NULL pointer passed in parameter.

ft_fstrjoin():
A secure version of strjoin(), can take either pointers sent in param being
NULL. Not the same as in GNL, does not free anything...




I think that's it.

Oh yea, the Makefile is dope tho...













Basically everything has changed, i think


Ft_Printf.c:

ft_printf():
Simple and straight forward, it inits a few variables, the linked list,
and does some basic checks before calling the first bulky func.



Pfelem_List.c:

new_pfelem():
Creates a new element of t_pfelem structure type.

pfelem_append():
Appends a list of t_pfelem type, does not create its own new elem, that
is passed as a param.

ft_buf_to_elem():
Takes a string (sourced from *format) and creates a new elem containing
that str.



Parser.c:

ft_HQ():
Does the majority of the work of going though *format, includes a loop
that looks for %s and seperates *format into bits that can be stored in
linked list.



Parse_Buffer.c:

ft_field_parsing():
Called from ft_HQ(), this function takes *format after a % has been reached,
calls flag, width and precition recovering funcs before determining the
specifier and routing the appropriate function.
Imporantly, this function returns the number of char of *format that have
been read after a %.



Parse_flags.c:

ft_flag_parsing():
Called from ft_field_parsing() to recover all but the specifiers, uses
bitwise to store the flags.

ft_get_precision():
Called from ft_flag_parsing() once a '.' is reached, this finds and stores
the value of the precision.

ft_get_width():
Called from ft_flag_parsing() once a non 0 digit is reached, it finds
and stores the value of the width.

Do i want a function that handles casting here too ???




HANDLER FUNCTIONS

Handle_Int.c:

?


Handle_Str.c

?






ft_printf is a function

Files:
felem_list.c
ft_printf.c
initflags.c


Starts at ft_printf.c
Recieves the format string and the arguments
The argmuments must be processes using va_args stuff (not sure how yet)
The format string is processed by func format_specifier which returns
a filled element of felem type to func ft_printf
ft_printf calls functions to check the element and append it to flst LL

format_specifier starts by looking for %
if it finds a % it looks for the specifier
Things will happen from there to make sure the specifier is managed and 
linked to correct argument passed to ft_printf
If no %, reads sting until end or %, takes section and puts in a new elem
to be returned to ft_printf


felem_list.c
Contains new_felem and flist_append
The first creates and fills new felems returning them
The second takes the flist and new felem and appends one to the other


initflags.c
Contains a flag check (incomplete)
and
a function which initiates a static var table of all the flag types,
or at least i think that's what it should do.





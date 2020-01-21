

Basically everything has changed, i think


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





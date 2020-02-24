Welcome to HyperDox, or my "internet project" as my professor called it!

This is a relatively easy to understand program, you can enter a directory containing .dox
files to be read or type "default" to use a directory I've already set up.

The program will read through all of the .dox files and calculate statistics about each file,
as well as process any "links" within the files. An example of a link within a file would be
"|Test.dox:|", this string is replaced with "<x>" where x is equal to what number link it is
in the file. You can then use a command to visit links within a specific file.

When starting up HyperDox and after entering a directory, all .dox files within that directory
will be printed, as well as a list of commands:

g (document name) - gets the document with name inputted.
f (search word) - displays a list of occurances of search word.
a (link number) - displays the text at the location of link number.
l - lists all documents that can be displayed.
h - display this list.
q - quit the program.
s - display current document's stats.

From here you can see a list of documents, visit documents, search for words, or display stats.
I should mention, when using the 'f' command, a list of links will be displayed that look like what's
listed below. You can also use the 'a' command to visit these links.
[166] |Top.dox|1676:panda
[167] |Top.dox|1925:panda
[168] |Top.dox|2073:panda
[169] |Zoos.dox|0:panda
[170] |Zoos.dox|122:panda
[171] |Zoos.dox|260:panda
[172] |Zoos.dox|425:panda
[173] |Zoos.dox|510:panda
  ^              ^
Link number     Position in file

Thanks for checking out HyperDox!

-Ellienn Tatar
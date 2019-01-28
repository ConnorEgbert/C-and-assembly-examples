# C and assemblp examples

Projects included:
* Ahentafel generator
	* Determines lineage from base 10 integer, base 2 integer, or relational string
	* Usage: `make` then `./ahentafel`
	* also has command line parameter input
* Multi threaded racing simulator (pthread)
	* Races cars across the screen. Sometimes they run out of gas. Truly riveting.
	* Usage: `make` then `./pt-cruisers`
* Dynamic memory word counting program
	* I included the bee movie script in case you were curious.
	* Usage: `make` then `./bst < beemovie.txt`
* String encoding program
	* Program to demonstrate understanding of bit manipulation
	* Usage: `make` then `./file-bitsets <string1> <string2>`

Assembly code is compiled with RASM and linked using RLINK. If you would like to use a different assembler/linker, change the assembler and linker variables in the Makefiles to your own preference. Compatibility issues may arise when using a different set of build tools.

* Sum
    * Adds numbers using assembly code
* Add ASCII
    * Adds numbers from user input
* Fraction Simplification
    * Simplifies fractions to use mixed notation.
    * Assumes that the fraction can be simplified using only integers.
* Polymorphic function calls
    * Demonstrates polymorphic function calls using virtual function tables with a set size.

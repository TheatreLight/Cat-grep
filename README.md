# Bash utilities - cat and grep for windows: wincat & wingrep.

There are no such a powerful utilities for working with files in Windows. Becuase of this I decided to write them.

## Wincat.

Implement the next Unix flags:
-b, --nimber-nonblank
      number nonempty output lines, overrides -n;
-e    equivalent to -vE;
-E    display $ at end of each line;
-n, --number
      number all output lines;
-s, --squeeze-blank
      suppress repeated output lines;
-t    equivalent -vT;
-T    display TAB character as ^I;
-v    use ^ and M- notation, except for LFD and TAB.

## Wingrep.

Implement the next Unix flags:
-e PATTERNS use PATTERNS as patterns. If this option use multiple times or combined with the -f option, search for all patterns given;
-f FILE     obtain patterns from FILE, one per line;
-i          ignore case;
-v          invert sense of matching, to select non-matching lines;
-c          supress normal output, instead print a count for matching lines for each input file;
-l          Suppress normal output; instead print the name of each input file from which output would normally have been printed;
-o          Print  only  the matched (non-empty) parts of a matching line, with each such part on a separate output line;
-s          Suppress error messages about nonexistent or unreadable files;
-h          Suppress  the  prefixing  of file names on output;
-n          Prefix each line of output with the 1-based line number within its input file.

To build and compile these apps you should have a Make and GCC (mingw64 or msys).
Simply download the repository, go to the src/ directory and type 'make'. It wil be compile both apps.
To run test scripts type 'make test'.



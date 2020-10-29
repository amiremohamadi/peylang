#include <cstdio>
#include <iostream>
#include <parser.tab.h>

#define VERSION "0.0.9"

extern int yyparse();
extern FILE *yyin;

int main(int argc, char **argv) {

  if (argc > 1) {
    yyin = fopen(argv[1], "r+");
  } else {
    std::cout << R"(
  _  _   /'/    )\,/,/(_   \ \
   `//-.|  (  ,\\)\//\)\/_  ) |
   //___\   `\\\/\\/\/\\///'  /
,-"~`-._ `"--'_   `"""`  _ \`'"~-,_
\       `-.  '_`.      .'_` \ ,-"~`/
 `.__.-'`/   (-\        /-) |-.__,'
   ||   |     \O)  /^\ (O/  |
   `\\  |         /   `\    /
     \\  \       /      `\ /
      `\\ `-.  /' .---.--.\
        `\\/`~(, '()      ('
         /(O) \\   _,.-.,_)
        //  \\ `\'`      /
  pey  / |  ||   `""""~"`
     /'  |__||
           `o 
		)"
              << "\n";
    std::cout << "Peyman programming language " << VERSION << "\n";
    std::cout << "WARNING: INTERACTIVE MODE IS BUGGY YET, TRY THIS INSTEAD:\n"
              << "usage: peyman file_name.pey\n\n";
  }
  yyparse();

  fclose(yyin);
  return 0;
}

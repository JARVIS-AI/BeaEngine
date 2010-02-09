#include <iostream>
#include "unittest/thirdparty/sexpr/sexp.h"


int main (int argc, char* argv[])
{
  const size_t BUFF_LEN = 1024;
  char buff [BUFF_LEN];
  sexp_t* s1 = new_sexp_atom ( "asm", 4, SEXP_SQUOTE);
  sexp_t* s2 = new_sexp_atom ( "100", 4, SEXP_BASIC);
  s1->next = s2;
  sexp_t* e1 = new_sexp_list (s1);
  
  sexp_t* s0 = new_sexp_atom ( "dat", 4, SEXP_SQUOTE);
  s0->next = e1;
  sexp_t* e = new_sexp_list (s0);

  print_sexp (buff, BUFF_LEN, e);
  std::cout << buff << std::endl;
  destroy_sexp (e);
  return 0;
}

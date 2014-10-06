# include "ixemelle_criterion.h"


# define SEP_LINE "---------------\n"


void test_crit ( const char * str ) {
  ixemelle_criterion crit ;
  int res ;
  fprintf ( stdout , "%s\n" , str ) ;
  res = ixemelle_criterion_create ( & crit , str ) ;
  ixemelle_criterion_fprint ( stdout, crit ) ;
  if ( XMLIGHT_CRITERION_OK != res ) {
    fprintf ( stdout , "\nERREUR code : %d" , res );
  }
  fputs ( "\n" SEP_LINE , stdout ) ;
  ixemelle_criterion_destroy ( & crit ) ;
}


int main ( void ) {
  fputs ( SEP_LINE , stdout ) ;
  test_crit ( " name [  key = \"value\" ]" ) ;
  test_crit ( " . name [  key = \"value\" ]" ) ;
  test_crit ( " [  key = \"value\" ]" ) ;
  test_crit ( " . [  key = \"value\" ]" ) ;
  test_crit ( " name " ) ;
  test_crit ( " . name " ) ;
  test_crit ( "-> name [  key = \"value\" ]" ) ;
  test_crit ( " --> name [  key = \"value\" ]" ) ;
  test_crit ( " <- name [  key = \"value\" ]" ) ;
  test_crit ( " <-- name [  key = \"value\" ]" ) ;
  test_crit ( "s  <-- a <- f -> s --> d" ) ;
  test_crit ( " <-- [  key = \"value\" ]" ) ;
  test_crit ( " <-- [  key = \"value\" ] . [p=\"\"]" ) ;
  return 0 ;
}

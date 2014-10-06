# include <stdlib.h>   /* malloc */
# include <string.h>   /* memcpy */
# include <stdio.h>    /* printf */

# include "list_forest.h"


/**
   value => int
   element => double
*/


static void test_list_forest_copy_value ( const void * value , void ** pt ) {
  * pt = NULL ;
  * pt = (void *) malloc ( sizeof ( int ) ) ;
  memcpy ( * pt , value , sizeof ( int ) );
}

static void test_list_forest_copy_element ( const void * value , void ** pt ) {
  * pt = malloc ( sizeof ( double ) ) ;
  memcpy ( * pt , value , sizeof ( double ) );
}


static void test_list_forest_free_value ( void ** pt ) {
  free ( * pt ) ;
  * pt = NULL ;
}

static void test_list_forest_free_element ( void ** pt ) {
  free ( * pt ) ;
  * pt = NULL ;
}

static void test_list_forest_fprint_value ( FILE * f ,
					    void * pt ) {
  fprintf ( f , "%d" , *(int *) pt ) ;
}

static void test_list_forest_fprint_element ( FILE * f ,
					      void * pt ) {
  fprintf ( f , "%g" , *(double *) pt ) ;
}

/* nombre de values pour tester la file */
# define VAL_MAX 5

/* Nombre de parcours pour le test */
# define NB_PARCOURS 5



int main ( void ) {

  list_forest lf ;

  /* CREATION */
  list_forest_create ( & lf ,
		       & test_list_forest_copy_value , 
		       & test_list_forest_free_value , 
		       & test_list_forest_copy_element , 
		       & test_list_forest_free_element ) ;
  /* ADDITION */ 
  {
    list_forest_position pos ;
    int i , j , k ;
    double b = 3.14 ;
    list_forest_position_create ( lf , & pos ) ;

    for ( i = 0 ; i < VAL_MAX ; i ++ ) {
      list_forest_add_left_son ( pos , (void *) & i ) ;
      list_forest_position_left_son ( pos ) ;
      for ( j = 1 ; j <= i ; j ++ ) {
	b *= j ;
	list_forest_add_next_brother ( pos , (void *) & b ) ;
	list_forest_position_next_brother ( pos ) ;
	for ( k = 1 ; k <= j ; k ++ ) {
	  b += k ;
	  list_forest_add_element ( pos , &b ) ;
	  list_forest_position_element_next ( pos ) ;
	}
      }
    }
    list_forest_position_destroy ( & pos ) ;
    list_forest_position_create ( lf , & pos ) ;
    list_forest_position_left_son ( pos ) ;
    for ( i = 0 ; i < VAL_MAX ; i ++ ) {
      list_forest_add_left_son ( pos , (void *) & i ) ;
      list_forest_position_left_son ( pos ) ;
      for ( j = 1 ; j <= i ; j ++ ) {
	b *= j ;
	list_forest_add_next_brother ( pos , (void *) & b ) ;
	list_forest_position_next_brother ( pos ) ;
	for ( k = 1 ; k <= j ; k ++ ) {
	  b += k ;
	  list_forest_add_element ( pos , &b ) ;
	  list_forest_position_element_next ( pos ) ;
	}
      }
    }
    list_forest_position_destroy ( & pos ) ;
  }

  /* PRINT */
  list_forest_fprint ( stdout , lf , test_list_forest_fprint_value , test_list_forest_fprint_element ) ;

  /* DESTRUCTION */ 
  list_forest_destroy ( & lf ) ; 
 
  return 0 ;
}

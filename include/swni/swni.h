#ifndef SWNI_H_
#define SWNI_H_

#include <stdlib.h>
#include <wn.h>
#include <swni/wni.h>
#include <glib.h>

#define MAX_SENSE_DIGITS 5

typedef struct {
	char* definition;
	char* defn_pos;
	GSList* examples;
} defn_t;

typedef struct {
	GSList* defn_list;
	gchar* class;
	gchar* familiarity;
} defn_list_t;

typedef struct {
    GSList* definitions_list;
    GSList* synonyms_list;
} swni_t;

/***
 *  swni_get_definition_list()
 *
 *  Returns a GSList pointer filled with 
 *  definitions of the word if any.
 *  
 *  
 *  Paramaters:
 *    The word you want the definition for
 *	  as a string.
 *  Returns:
 *    NULL, if a definition does not exist.
 *    
 *    
 **/
swni_t* swni_get_definitions_list(gchar* word);

/***
 *  swni_get_synonyms()
 *
 *  Returns a GSList pointer filled with 
 *  synonyms belonging to the word.
 *  
 *  
 *  Paramaters:
 *    The word you want the synonyms for.
 *	  
 *  Returns:
 *    NULL, if no synonyms exist.
 *    
 *    
 **/
static GSList* swni_get_synonyms();

/***
 *  swni_destroy_definitions_list()
 *
 *  Frees memory that was allocated to  
 *  the GSList.
 *  
 *  
 *  Paramaters:
 *    The definitions list.
 *	  
 *  Returns:
 *    none 
 *    
 *    
 **/
void 	swni_destroy_definitions_list(GSList* defn_list);


/***
 *  swni_destroy_synonyms_list()
 *
 *  Frees memory that was allocated to  
 *  the GSList.
 *  
 *  
 *  Paramaters:
 *    The synonyms list.
 *	  
 *  Returns:
 *    none 
 *    
 *    
 **/
void swni_destroy_synonyms_list(GSList* synonyms_list);

void swni_wni_free();

/* helper functions */
static void free_examples_list(GSList* examples_list);
static guint8 get_frequency(guint sense_count);

#endif

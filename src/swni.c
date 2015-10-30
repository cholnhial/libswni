#include <swni/swni.h>

/* globals */
static gchar *familiarity[] = {"extremely rare","very rare","rare","uncommon","common", "familiar","very familiar","extremely familiar"};
static GSList *results = NULL;


	/***
	 *  swni_get_definition()
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
swni_t*
swni_get_definitions_list (gchar * word)
{
  g_assert (word != NULL);



  GSList *def_list = NULL, *definitions_list = NULL, *example = NULL;
  WNIDefinitionItem *def_item = NULL;
  WNIDefinition *defn = NULL;

  glong count = 0;
  gchar *str_list_item = NULL;
  gchar str_count[MAX_SENSE_DIGITS] = "";

  gchar *definition = NULL;

  guint16 total_results = 0;
  guint8 total_pos = 0;

  count = WORDNET_INTERFACE_ALL;
  gboolean advanced_mode = TRUE;


  swni_t* swni_def = g_malloc(sizeof(swni_t));
  memset(swni_def, 0, sizeof(swni_t));

  /* begin search */
  wni_request_nyms (word, &results, (WNIRequestFlags) count, advanced_mode);

  if (results)
    {
      total_results = 0;
      total_pos = 0;

      def_list =
	((WNIOverview *) ((WNINym *) results->data)->data)->definitions_list;
      while (def_list)
	{
	  if (def_list->data)
	    {
	      def_item = (WNIDefinitionItem *) def_list->data;
	      definitions_list = def_item->definitions;

	      defn_list_t *defn_list = g_malloc (sizeof (defn_list_t));
	      memset (defn_list, 0, sizeof (defn_list_t));
	      defn_list->class = g_strdup (partnames[def_item->pos]);

	      count = 1;
	      while (definitions_list)
		{
		  defn_t *defn_single = g_malloc (sizeof (defn_t));
		  memset (defn_single, 0, sizeof (defn_t));
		  defn = (WNIDefinition *) definitions_list->data;

		  total_results++;
		  g_snprintf (str_count, MAX_SENSE_DIGITS, "%3d",
			      total_results);

		  g_snprintf (str_count, MAX_SENSE_DIGITS, "%2d",
			      (int) count);
		  defn_single->defn_pos = g_strdup (str_count);
		  defn_single->definition = g_strdup (defn->definition);



		  definitions_list = g_slist_next (definitions_list);

		  example = defn->examples;
		  while (example)
		    {

		      defn_single->examples =
			g_slist_append (defn_single->examples,
					g_strdup (example->data));
		      example = g_slist_next (example);
		    }
		  count++;

		  defn_list->defn_list =
		    g_slist_append (defn_list->defn_list, defn_single);
		}

	      defn_list->familiarity =
		g_strdup (familiarity[get_frequency (count - 1)]);

	      swni_def->definitions_list = g_slist_append (swni_def->definitions_list, defn_list);
	    }

	  def_list = g_slist_next (def_list);
	  total_pos++;
	}
    
    swni_def->synonyms_list = swni_get_synonyms();
    }
    
  return swni_def;

}

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
static GSList *
swni_get_synonyms ()
{
 // g_assert (word != NULL);

 
  GSList *synonyms_list = NULL;

  unsigned short i = 0;
  WNINym *temp_nym = NULL;
  GSList *temp_results = results;
  WNIPropertyItem *temp_property = NULL;
  GSList *properties = NULL;
  WNIRequestFlags id;


  while (temp_results)
    {
      temp_nym = (WNINym *) temp_results->data;
      if (temp_nym->id == WORDNET_INTERFACE_OVERVIEW)
	{
	  properties = ((WNIOverview *) temp_nym->data)->synonyms_list;


	  while (properties)
	    {
	      temp_property = (WNIPropertyItem *) properties->data;
	      if (temp_property)
		{
		  //   gtk_tree_store_append(tree_store, &iter, NULL);
		  //  text_weight = PANGO_WEIGHT_NORMAL;

		  // check if synonym has more than one mapping
		  // we try to get the 2nd term (I.e. index 1) instead of checking the length; parsing the whole list is insane
		  if (NULL != g_slist_nth (temp_property->mapping, 1))


		    //gtk_tree_store_set(tree_store, &iter, 0, temp_property->term, 1, text_weight, -1);
		    synonyms_list =
		      g_slist_append (synonyms_list,
				      g_strdup ((char *) temp_property->
						term));
		}
	      properties = g_slist_next (properties);
	    }


	}

      temp_results = g_slist_next (temp_results);
    }

  return synonyms_list;
}

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
void
swni_destroy_definitions_list (GSList * defn_list)
{
  //g_assert (defn_list != NULL);
  if(defn_list == NULL) {
  	return;
  }
  
  for (GSList * iter = defn_list; iter != NULL; iter = iter->next)
    {
	    defn_list_t *def_list = (defn_list_t *) iter->data;
	    g_free (def_list->familiarity);
	    g_free(def_list->class);

        for(GSList* def_iter = def_list->defn_list; def_iter != NULL; def_iter = def_iter->next) {
           defn_t* defn = (defn_t*) def_iter->data; 
           g_free(defn->defn_pos);
           g_free(defn->definition);
           free_examples_list(defn->examples);
           g_free(defn);

        }
        
        g_free(def_list);
	}
   
}

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
void
swni_destroy_synonyms_list (GSList * synonyms_list)
{
  //g_assert (synonyms_list != NULL);
  if(synonyms_list == NULL) {
  	return;
  }

  for (GSList * iter = synonyms_list; iter != NULL; iter = iter->next)
    {
        
        g_free(iter->data);
	}
   
}

void
swni_wni_free ()
{
  wni_free (&results);
  results = NULL;
}

static guint8
get_frequency (guint sense_count)
{
  guint8 frequency = 0;

  if (sense_count == 0)
    frequency = 0;
  if (sense_count == 1)
    frequency = 1;
  if (sense_count == 2)
    frequency = 2;
  if (sense_count >= 3 && sense_count <= 4)
    frequency = 3;
  if (sense_count >= 5 && sense_count <= 8)
    frequency = 4;
  if (sense_count >= 9 && sense_count <= 16)
    frequency = 5;
  if (sense_count >= 17 && sense_count <= 32)
    frequency = 6;
  if (sense_count > 32)
    frequency = 7;

  return frequency;
}

static void free_examples_list(GSList* examples_list)
{
    for(GSList* iter = examples_list; iter != NULL; iter = iter->next) {
        g_free(iter->data);
    }
}

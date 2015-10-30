#include <swni/swni.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) 
{

char buffer[1024];

while(TRUE) {
printf("Type a word>>");
fgets(buffer, 1024, stdin);
buffer[strlen(buffer) - 1] = 0;
GSList* defn_list = NULL;
GSList* synonyms_list = NULL;
swni_t* swni_defs = swni_get_definitions_list(buffer);
if(swni_defs->synonyms_list == NULL &&  swni_defs->definitions_list == NULL) {
    printf("No definition found.\n");
}
defn_list = swni_defs->definitions_list;
synonyms_list = swni_defs->synonyms_list;  
if(defn_list) {
    for(GSList* iter = defn_list; iter != NULL; iter = iter->next) {
        defn_list_t* def_list = (defn_list_t*) iter->data;
        printf("Class: %s\n", def_list->class);
        printf("Familiarity: %s\n", def_list->familiarity);
        for(GSList* iter2 = def_list->defn_list; iter2 != NULL; iter2 = iter2->next) {
            defn_t* defn = (defn_t*) iter2->data;

            printf("%s. %s\n", defn->defn_pos, defn->definition);
            GSList* example = defn->examples;
            while(example) {
                printf(" %s", (char*) example->data);
                example = g_slist_next(example);

                if(example) {
                    printf("; ");
                }

            }
                printf("\n");
            }
        }
        

    if(synonyms_list) {
        printf("Synonyms: ");
        for(GSList* iter = synonyms_list; iter != NULL; iter = iter->next) {
            
           printf("%s, ", (char*) iter->data); 
        }
        printf("\n");
    } 

    swni_wni_free();
    swni_destroy_definitions_list(defn_list);

    }
   }
/*swni_t* swni_def = swni_get_definitions_list("help");
GSList* definitions_list = swni_def->definitions_list;
GSList* synonyms_list = swni_def->synonyms_list; */

/*for(GSList* iter_def_list = definitions_list; iter_def_list != NULL; iter_def_list = iter_def_list->next) {
defn_list_t* defn = (defn_list_t*) iter_def_list->data;

printf("Class: %s, Familiarity: %s\n", defn->class, defn->familiarity);

}*/

/*for(GSList* iter = synonyms_list; iter != NULL; iter = iter->next) {
    printf("%s\n", (char*) iter->data);
} */


}

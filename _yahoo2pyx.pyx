
cdef extern from "yahoo2.h":
    cdef enum yahoo_status:
        YAHOO_STATUS_AVAILABLE = 0
        YAHOO_STATUS_BRB
        YAHOO_STATUS_BUSY
        YAHOO_STATUS_NOTATHOME
        YAHOO_STATUS_NOTATDESK
        YAHOO_STATUS_NOTINOFFICE
        YAHOO_STATUS_ONPHONE
        YAHOO_STATUS_ONVACATION
        YAHOO_STATUS_OUTTOLUNCH
        YAHOO_STATUS_STEPPEDOUT
        YAHOO_STATUS_INVISIBLE = 12
        YAHOO_STATUS_CUSTOM = 99
        YAHOO_STATUS_IDLE = 999
        YAHOO_STATUS_OFFLINE = 0x5a55aa56
        YAHOO_STATUS_NOTIFY = 0x16

    cdef struct yab:
        char *id
        char *fname
        char *lname
        char *nname
        char *email
        char *hphone
        char *wphone
        char *mphone
        int dbid

    cdef struct yahoo_buddy:
        char *group
        char *id
        char *real_name
        yab *yab_entry

    cdef struct _YList:
        _YList *next
        _YList *prev
        void *data
    ctypedef _YList YList

    ctypedef int (*YListCompFunc)(void *, void *)
    ctypedef void (*YListFunc)(void *, context)
    
    YList *y_list_append(YList *list, void *data)
    YList *y_list_prepend(YList *list, void *data)
    YList *y_list_remove_link(YList *list, YList * link)
    YList *y_list_remove(YList *list, void *data)

    YList *y_list_insert_sorted(YList * list, void * data, YListCompFunc comp)
    
    YList *y_list_copy(YList * list)
    
    YList *y_list_concat(YList * list, YList * add)
    
    YList *y_list_find(YList * list,  void *data)
    YList *y_list_find_custom(YList * list, void *data, YListCompFunc comp)
    
    YList *y_list_nth(YList * list, int n)
    
    void y_list_foreach(YList * list, YListFunc fn, user_data)
    
    void y_list_free_1(YList * list)
    void y_list_free(YList * list)
    int  y_list_length(YList * list)
    int  y_list_empty(YList * list)
    int  y_list_singleton(YList * list)
    


    int yahoo_init(char *username, char *password)
    void yahoo_login(int id, int initial)

cdef extern from "callbacks.h":
    pass

class YConnectionHandle:
    def __init__(self):
        pass

    def __del__(self):
        unregister_handler(self.id)

    def connect(self, char *name, char *password):
        self.id = yahoo_init(name, password)
        register_handler(self.id, self)
        yahoo_login(self.id, YAHOO_STATUS_INVISIBLE)

    def _login_response(self, int succ, char *url): 
        pass

#    def _got_ignore(self, YList *igns):
#        pass

HANDLER_MAP = {}

cdef void register_handler(int id, handle):
   global HANDLER_MAP
   HANDLER_MAP[id] = handle

cdef void unregister_handler(int id):
   global HANDLER_MAP
   if id in HANDLER_MAP:
       del HANDLER_MAP[id]

# Name: ext_yahoo_login_response
# * 	Called when the login process is complete
# * Params:
# * 	id   - the id that identifies the server connection
# * 	succ - enum yahoo_login_status
# * 	url  - url to reactivate account if locked
# */
cdef public void ext_yahoo_login_response "ext_yahoo_login_response" (int id, int succ, char *url):
    global HANDLER_MAP
    target = HANDLER_MAP.get(id)
    if target:
        if url == NULL:
            target._login_response(succ, '')
        else:
            target._login_response(succ, url) 

cdef void convert_buddylist_item(void *item, context):
   cdef yahoo_buddy *buddy
   buddy =  <yahoo_buddy*>item
   context.append({'group' : buddy.group, 'id' : buddy.id, 'real_name' : buddy.real_name})

cdef convert_buddylist(YList *target):
    result = []
    y_list_foreach(target, convert_buddylist_item, result)
    return result

#/*
# * Name: ext_yahoo_got_buddies
# * 	Called when the contact list is got from the server
# * Params:
# * 	id   - the id that identifies the server connection
# * 	buds - the buddy list
# */
cdef public void ext_yahoo_got_buddies "ext_yahoo_got_buddies" (int id, YList * buds):
    global HANDLER_MAP
    target = HANDLER_MAP.get(id)
    if target:
        target._got_buddies(convert_buddylist(buds))




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
    ctypedef void (*YListFunc)(void *, void *)


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

    cdef enum yahoo_input_condition:
        YAHOO_INPUT_READ = 1 << 0,
        YAHOO_INPUT_WRITE = 1 << 1,
        YAHOO_INPUT_EXCEPTION = 1 << 2


    int  yahoo_read_ready(int id, int fd, void *data)
    int  yahoo_write_ready(int id, int fd, void *data)


cdef extern from "yahoo2_callbacks.h":
    ctypedef void (*yahoo_connect_callback)(int fd, int error, void *callback_data)


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

cdef class YReadHandler:
    cdef int id, fd
    cdef void *data

    def __call__(self):
        yahoo_read_ready(self.id, self.fd, self.data)

cdef class YWriteHandler:
    cdef int id, fd
    cdef void *data
    def __call__(self):
        yahoo_write_ready(self.id, self.fd, self.data)


cdef class YConnectionCallback:
    cdef yahoo_connect_callback callback
    cdef void *data

    def __call__(self, fd, error):
        self.callback(fd, error, self.data)

class YConnectionManager:
    def __init__(self):
        self.__id = 0
        self.__handlers = {}

    def next_id(self):
        self.__id = self.__id + 1
        return self.__id

    def connect_async(self, host, port, callback):
        # what do we do with this tag??
        self.begin_connect(host, port, callback)
        return self.next_id()

    def begin_connect(self, host, port, callback):
        pass

    def connect(self, host, port):
        pass

    def add_read_handler(self, fd, handler):
        pass

    def add_write_handler(self, fd, handler):
        pass

    def remove_handler(self, tag):
        pass


#/*
# * Name: ext_yahoo_connect_async
# * 	Connect to a host:port asynchronously.  This function should return
# * 	immediately returing a tag used to identify the connection handler,
# * 	or a pre-connect error (eg: host name lookup failure).
# * 	Once the connect completes (successfully or unsuccessfully), callback
# * 	should be called (see the signature for yahoo_connect_callback).
# * 	The callback may safely be called before this function returns, but
# * 	it should not be called twice.
# * Params:
# * 	id   - the id that identifies this connection
# * 	host - the host to connect to
# * 	port - the port to connect on
# * 	callback - function to call when connect completes
# * 	callback_data - data to pass to the callback function
# * Returns:
# * 	a unix file descriptor to the socket
# */
cdef public int ext_yahoo_connect_async(int id, char *host, int port, 
                                         yahoo_connect_callback callback, void *callback_data):
   cdef YConnectionCallback cb
   cb = YConnectionCallback()
   cb.callback = callback
   cb.data = callback_data
   
   # do I need to know the id?
   return MANAGER.connect_async(host, port, cb)

#    def _got_ignore(self, YList *igns):
#        pass

HANDLER_MAP = {}
MANAGER = None

cdef void set_connection_manager(manager):
   global MANAGER
   MANAGER = manager

cdef void register_handler(int id, handle):
   global HANDLER_MAP
   HANDLER_MAP[id] = handle

cdef void unregister_handler(int id):
   global HANDLER_MAP
   if id in HANDLER_MAP:
       del HANDLER_MAP[id]

# Name: ext_yahoo_login_response
# *     Called when the login process is complete
# * Params:
# *     id   - the id that identifies the server connection
# *     succ - enum yahoo_login_status
# *     url  - url to reactivate account if locked
# */
cdef public void ext_yahoo_login_response(int id, int succ, char *url):
    global HANDLER_MAP
    target = HANDLER_MAP.get(id)
    if target:
        if url == NULL:
            target._login_response(succ, '')
        else:
            target._login_response(succ, url) 

cdef void convert_buddylist_item(void *item, void *data):
   cdef yahoo_buddy *buddy
   cdef object context
   context = <object>data
   buddy =  <yahoo_buddy*>item
   context.append({'group' : buddy.group, 'id' : buddy.id, 'real_name' : buddy.real_name})

cdef convert_buddylist(YList *target):
    result = []
    y_list_foreach(target, convert_buddylist_item, result)
    return result

#/*
# * Name: ext_yahoo_got_buddies
# *     Called when the contact list is got from the server
# * Params:
# *     id   - the id that identifies the server connection
# *     buds - the buddy list
# */
cdef public void ext_yahoo_got_buddies "ext_yahoo_got_buddies" (int id, YList * buds):
    global HANDLER_MAP
    target = HANDLER_MAP.get(id)
    if target:
        target._got_buddies(convert_buddylist(buds))


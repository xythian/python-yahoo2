import socket
from errno import EALREADY, EINPROGRESS, EWOULDBLOCK, ECONNRESET, \
     ENOTCONN, ESHUTDOWN, EINTR, EISCONN, errorcode


cdef extern from "yahoo2.h":
    cdef enum yahoo_log_level:
        YAHOO_LOG_NONE = 0
        YAHOO_LOG_FATAL
        YAHOO_LOG_ERR
        YAHOO_LOG_WARNING
        YAHOO_LOG_NOTICE
        YAHOO_LOG_INFO
        YAHOO_LOG_DEBUG

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

    cdef enum yahoo_login_status:
        YAHOO_LOGIN_OK = 0
        YAHOO_LOGIN_UNAME = 3
        YAHOO_LOGIN_PASSWD = 13
        YAHOO_LOGIN_LOCK = 14
        YAHOO_LOGIN_DUPL = 99
        YAHOO_LOGIN_SOCK = -1

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
    


    cdef int yahoo_set_log_level(yahoo_log_level level)

    int yahoo_init(char *username, char *password)
    void yahoo_login(int id, int initial)

    ctypedef enum yahoo_input_condition:
        YAHOO_INPUT_READ = 1 << 0,
        YAHOO_INPUT_WRITE = 1 << 1,
        YAHOO_INPUT_EXCEPTION = 1 << 2


    int  yahoo_read_ready(int id, int fd, void *data)
    int  yahoo_write_ready(int id, int fd, void *data)


cdef extern from "yahoo2_callbacks.h":
    ctypedef void (*yahoo_connect_callback)(int fd, int error, void *callback_data)

class log_level:
    NONE = YAHOO_LOG_NONE
    FATAL = YAHOO_LOG_FATAL
    ERR =  YAHOO_LOG_ERR
    WARNING = YAHOO_LOG_WARNING
    NOTICE = YAHOO_LOG_NOTICE
    INFO = YAHOO_LOG_INFO
    DEBUG = YAHOO_LOG_DEBUG


def set_log_level(level):
    yahoo_set_log_level(level)

class IDSource:
    def __init__(self):
        self.__id = 0

    def next(self):
        self.__id = self.__id + 1
        return self.__id

cdef class ConnectionHandle:
    cdef int cid
    cdef char *host
    cdef int port
    cdef void *read_data
    cdef void *write_data
    cdef void *connect_data
    cdef yahoo_connect_callback connect_callback
    cdef readonly int read_tag, write_tag
    cdef int _readable, _writable
    cdef object sock

    def __init__(self, cid, host, port):
        self.cid = cid
        self.host = host
        self.port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.setblocking(0)
        self.read_tag = ID_SOURCE.next()
        self.write_tag = ID_SOURCE.next()

    def fileno(self):
        return self.sock.fileno()

    def readable(self):
        return bool(self.readable)
    
    def writable(self):
        return bool(self.writable)

    cdef void async_connect(self, yahoo_connect_callback callback, void *data):
        self.connect_callback = callback
        self.connect_data = data
        err = self.sock.connect_ex((self.host, self.port))
        if err in (EINPROGRESS, EALREADY, EWOULDBLOCK):
            return
        elif err in (0, EISCONN):
            self.handle_connect()

    cdef int connect(self):
        self.sock.setblocking(1)
        result = self.sock.connect_ex((self.host, self.port))
        self.sock.setblocking(0)
        return result

    cdef void _handle_connect(self):
        if self.connect_callback is not NULL:
            self.connect_callback(self.fileno(), 0, self.connect_data)
            self.connect_callback = NULL
 
    cdef void _handle_read(self):
        if self._readable:
           yahoo_read_ready(self.cid, self.fileno(), self.read_data)          

    cdef void _handle_write(self):
        if self._writable:
           yahoo_write_ready(self.cid, self.fileno(), self.write_data)
  
    def handle_read(self):  self._handle_read()
    def handle_write(self): self._handle_write()
    def handle_connect(self): self._handle_connect()

    


#/*
# * Name: ext_yahoo_connect_async
# *     Connect to a host:port asynchronously.  This function should return
# *     immediately returing a tag used to identify the connection handler,
# *     or a pre-connect error (eg: host name lookup failure).
# *     Once the connect completes (successfully or unsuccessfully), callback
# *     should be called (see the signature for yahoo_connect_callback).
# *     The callback may safely be called before this function returns, but
# *     it should not be called twice.
# * Params:
# *     id   - the id that identifies this connection
# *     host - the host to connect to
# *     port - the port to connect on
# *     callback - function to call when connect completes
# *     callback_data - data to pass to the callback function
# * Returns:
# *     a unix file descriptor to the socket
# */
cdef public int ext_yahoo_connect_async(int id, char *host, int port, 
                                         yahoo_connect_callback callback, void *callback_data):
   cdef ConnectionHandle handle
   handle = ConnectionHandle(id, host, port)
   handle.connect_callback = callback
   handle.connect_data = callback_data
   handle.async_connect(callback, callback_data)
   HANDLER_MAP[id].connections.append(handle)
   MANAGER.add(handle)
   return handle.fileno()

#/*
# * Name: ext_yahoo_connect
# *     Connect to a host:port
# * Params:
# *     host - the host to connect to
# *     port - the port to connect on
# * Returns:
# *     a unix file descriptor to the socket
# */
cdef public int ext_yahoo_connect "ext_yahoo_connect" (char *host, int port):
  cdef ConnectionHandle handle
  handle = ConnectionHandle(host, port)
  err = handle.connect()
  if err in (0, EISCONN):
      return handle.fileno()
  else:
      return err


ID_SOURCE = IDSource()
HANDLER_MAP = {}
MANAGER = None

def set_connection_manager(manager):
   global MANAGER
   MANAGER = manager

cdef void register_handler(int id, handle):
   global HANDLER_MAP
   # TODO: weak ref
   HANDLER_MAP[id] = handle

cdef void unregister_handler(int id):
   global HANDLER_MAP
   if id in HANDLER_MAP:
       del HANDLER_MAP[id]

class YConnectionHandle:
    def __init__(self):
        self.connections = []

    def __del__(self):
        unregister_handler(self.id)

    def connect(self, name, password):
        self.id = yahoo_init(name, password)
        register_handler(self.id, self)
        yahoo_login(self.id, YAHOO_STATUS_INVISIBLE)

    def _login_response(self, succ, url): 
        pass



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
            target._login_response(succ, 'none')
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
cdef public void ext_yahoo_got_buddies(int id, YList * buds):
    global HANDLER_MAP
    target = HANDLER_MAP.get(id)
    if target:
        target._got_buddies(convert_buddylist(buds))


#/*
# * Name: ext_yahoo_add_handler
# *     Add a listener for the fd.  Must call yahoo_read_ready
# *     when a YAHOO_INPUT_READ fd is ready and yahoo_write_ready
# *     when a YAHOO_INPUT_WRITE fd is ready.
# * Params:
# *     id   - the id that identifies the server connection
# *     fd   - the fd on which to listen
# *     cond - the condition on which to call the callback
# *     data - callback data to pass to yahoo_*_ready
# *     
# * Returns: a tag to be used when removing the handler
# */
cdef public int ext_yahoo_add_handler "ext_yahoo_add_handler" (int id, int fd, yahoo_input_condition cond, void *data):
    cdef ConnectionHandle conn
    handle =  HANDLER_MAP.get(id)
    if handle is not None:
        for ch in handle.connections:
            if ch.fileno() == fd:
                conn = ch
    if conn is None:
       print 'Unknown connection referenced by ext_yahoo_add_handler: ', (id, fd)
       return -1
    if cond == YAHOO_INPUT_READ:
        conn.read_data = data
        conn._readable = 1
        return conn.read_tag
    elif cond == YAHOO_INPUT_WRITE:
        conn._writable = 1
        conn.write_data = data
        return conn.write_tag
    else:
        # TODO: how do handle errors here?  If we raise an exception here in a callback, will it propgage
        # once we have control again?
        print 'Unknown COND referenced by ext_yahoo_add_handler', cond
        return -1
    

#/*
# * Name: ext_yahoo_remove_handler
# *     Remove the listener for the fd.
# * Params:
# *     id   - the id that identifies the connection
# *     tag  - the handler tag to remove
# */
cdef public void ext_yahoo_remove_handler "ext_yahoo_remove_handler" (int id, int tag):
    cdef ConnectionHandle conn
    handle =  HANDLER_MAP.get(id)
    if handle is not None:
        for conn in handle.connections:
            if conn.read_tag == tag:
                conn._readable = 0
                conn.read_data = NULL
                if not conn._writable:
                    MANAGER.remove(conn)
                return
            elif conn.write_tag == tag:
                conn._writable = 0
                conn.write_data = NULL
                if not conn._readable:
                    MANAGER.remove(conn)
                return
    #print 'Unknown connection referenced by ext_yahoo_remove_handler: ', (id, tag)


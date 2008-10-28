import _yahoo2
from _yahoo2 import YConnectionHandle
from collections import defaultdict
import asyncore, socket

#
# In this cut, leave the ownership of the sockets to the binding
# eventually be nice to expose socket creation to the app layer
#

class Handle(asyncore.dispatcher):
    def __init__(self, handle):
        asyncore.dispatcher.__init__(self)
        self.handle = handle
        self._fileno = self.handle.fileno()
        self.add_channel()

    def fileno(self):
        return self.handle.fileno()
        
    def readable(self):
        return self.handle.readable()

    def writable(self):
        return self.handle.writable()

    def handle_connect(self):
        self.handle.handle_connect()

    def handle_read(self):
        self.handle.handle_read()

    def handle_write(self):
        self.handle.handle_write()

    def handle_close(self):
        self.handle.handle_close()
        self.del_channel()

class YConnectionManager:
    def __init__(self):
        self.handles = {}

    def add(self, handle):
        self.handles[handle] = Handle(handle)

    def remove(self, handle):
        try:
            self.handles[handle].del_channel()
            del self.handles[handle]
        except KeyError:
            pass

def init():
    _yahoo2.set_log_level(_yahoo2.log_level.LOG_DEBUG)
    _yahoo2.set_connection_manager(YConnectionManager())

def run():    
    asyncore.loop()

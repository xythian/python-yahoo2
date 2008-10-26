from _yahoo2pyx import *

import asynccore

class YFDHandle:
    def __init__(self, fd):
        self.fd = fd
        self.readers = {}
        self.writers = {}

    def readable(self):
        return len(self.readers) > 0

    def writable(self):
        return len(self.writers) > 0

    def fileno(self):
        return self.fd

    def add_reader(self, tag, handler):
        self.readers[tag] = handler
        return tag

    def add_writer(self, tag, handler):
        self.writers[tag] = handler
        return tag
    
class connection_opener(asynccore.dispatcher):
    def handle_connect(self):
        pass

class connection_writer(asyncore.dispatcher):
    def __init__(self, handle):
        self.handle = handle

    def writable(self):
        return True

class connection_reader(asyncore.dispatcher):
    def __init__(self, handle):
        self.handle = handle

def run(self):
    asyncore.loop()

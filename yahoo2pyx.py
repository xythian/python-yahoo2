from _yahoo2pyx import *

import asynccore

class connection_opener(asynccore.dispatcher):
    def handle_connect(self):
        pass

class connection_writer(asyncore.dispatcher):
    def __init__(self, handle):
        self.handle = handle

    def writable(self):
        return True

def connection_reader(asyncore.dispatcher):
    def __init__(self, handle):
        self.handle = handle

def run(self):
    asyncore.loop()

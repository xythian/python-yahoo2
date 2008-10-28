import yahoo2
import sys
from optparse import OptionParser


class MyHandle(yahoo2.YConnectionHandle):
    def _login_response(self, succ, url):
        print 'Response: ', succ, url

    # if this was done, we'd have event handlers for all the interesting callbacks here
    # also the Pyrex layer would actually call them....

def main():
    # a script that takes password on the command line is a bad idea, generally...
    parser = OptionParser()
    parser.add_option("-u", "--user", dest="user", default="", help="Username.")
    parser.add_option("-p", "--password", dest="password", default="", help="Password.")
    (options, args) = parser.parse_args()
    if not options.user or not options.password:
        parser.print_help()
        sys.exit(1)
    yahoo2.init()
    conn = MyHandle()
    yahoo2.set_log_level(yahoo2.log_level.DEBUG)
    conn.connect(options.user, options.password)
    yahoo2.run()

if __name__ == '__main__':
    main()




#!/usr/bin/env python3

import os.path
import smartd.app
from tornado import ioloop, web, options
from smartd import secret
from smartd.util import ifttt

options.define('address', default='127.0.0.1', help='HTTP server address.')
options.define('port', default=8888, help='HTTP server port.')
options.define('timezone', default='Asia/Shanghai', help='Timezone.')

options.define('secret', default=secret.SECRET, help='Cookie secret.')
options.define('key', default=secret.KEY, help='Client secret.')

Root = os.path.dirname(__file__)

def rel_path(p):
  return os.path.join(Root, p)

def main():
  app = smartd.app.make_app(cookie_secret=options.options.secret,
                            template_path=rel_path('template'),
                            static_path=rel_path('static'),
                            debug=True)
  app.listen(options.options.port, options.options.address)
  ifttt.init()
  ioloop.IOLoop.current().start()

if __name__ == '__main__':
  main()

#!/usr/bin/env python3

import os.path
import smartd.app
from tornado import ioloop, web, options

options.define('port', default=8888, help='HTTP server port.')
options.define('secret', default='9be11db93e203cea096e49d3ddc8db78', help='Cookie secret.')
options.define('key', default='c959240243fc2aa96514678f288447b6', help='Sensor secret.')

Root = os.path.dirname(__file__)

def rel_path(p):
  return os.path.join(Root, p)

def main():
  app = smartd.app.make_app(cookie_secret=options.options.secret,
                            template_path=rel_path('template'),
                            static_path=rel_path('static'),
                            debug=True)
  smartd.app.init_template(rel_path('template'))
  app.listen(options.options.port)
  ioloop.IOLoop.current().start()

if __name__ == '__main__':
  main()

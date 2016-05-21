from smartd import app
from smartd.view import base
from smartd.model import data
from tornado import web, gen, options

def size_format(num, suffix='B'):
  for unit in ['', 'Ki', 'Mi', 'Gi', 'Ti', 'Pi', 'Ei', 'Zi']:
    if abs(num) < 1024.0:
      return "%3.1f%s%s" % (num, unit, suffix)
    num /= 1024.0
  return "%.1f%s%s" % (num, 'Yi', suffix)

@app.route('Home', '/')
class MainHandler(base.BaseHandler):
  @gen.coroutine
  def get(self):
    self.render('main.html', count=(yield data.count()), size=(yield data.total_size()),
                format=size_format)


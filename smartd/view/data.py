from smartd import app
from smartd.model import data
from smartd.util import event
from smartd.view import base
from tornado import web
from tornado import gen
from tornado import options

@app.route('/data/([^/]+)/(.+)')
class DataHandler(base.BaseHandler):
  @gen.coroutine
  def get(self, category, type):
    print('data get category: {0}, type: {1}'.format(category, type))
    to_int = lambda _: int(_) if self.get_query_argument('int', 'true') == 'true' else _
    l = yield data.get_list(category, type, int(self.get_query_argument('count', 1000)))
    l.reverse()
    x = [doc['_id'].generation_time.strftime('%Y-%m-%d %X') for doc in l]
    y = [to_int(doc['value']) for doc in l]
    self.json({'x':x, 'y':y})

  @gen.coroutine
  def post(self, category, type):
    if self.get_body_argument('key', None) != options.options.key:
      self.json({'error': 'not implemented'})
      print('data post failed: wrong key')
      return
    value = self.get_body_argument('value', None)
    print('data post category: {0}, type: {1}, value: {2}'.format(category, type, value))
    yield data.put(category, type, value)
    yield event.publish('data-updated', {'category': category, 'type': type})
    self.json({})

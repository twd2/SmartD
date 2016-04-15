import json
from smartd import app, util
import smartd.util.datetime
from smartd.model import data
from smartd.util import event
from smartd.view import base
from tornado import web
from tornado import gen
from tornado import options

@app.route('History', '/history/([^/]+)/(.+)')
class HistoryHandler(base.BaseHandler):
  @gen.coroutine
  def get(self, category, type):
    to_float = lambda _: float(_) if self.get_query_argument('float', 'true') == 'true' else _
    l = yield data.get_list(category, type, int(self.get_query_argument('count', 2880)))
    l.reverse()
    x = [util.datetime.strtime(doc['_id'].generation_time) for doc in l]
    y = [to_float(doc['value']) for doc in l]
    self.render('history.html', category=category, type=type,
                data_x=json.dumps(x), data_y=json.dumps(y))
    #self.json({'x':x, 'y':y})


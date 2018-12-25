from smartd import app, util
import smartd.util.datetime
from smartd.view import base
from smartd.util import event
from tornado import web
from tornado import gen
from tornado import options

@app.route('Magic', '/magic/([0-9a-z\-]+)')
class MagicHandler(base.BaseHandler):
  @gen.coroutine
  def get(self, function):
    self.json({'function': function})

  @gen.coroutine
  def post(self, function):
    password = str(self.get_body_argument('password', ''))
    if not function:
      self.json({'error': 'no function'})
      return
    yield event.publish('on-function-' + function, {'password': password})
    self.json({})


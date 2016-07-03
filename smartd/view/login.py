from smartd import app, util
import smartd.util.datetime
from smartd.view import base
from tornado import web
from tornado import gen
from tornado import options

@app.route('Login', '/login')
class LoginHandler(base.BaseHandler):
  @gen.coroutine
  def post(self):
    username = str(self.get_body_argument('username', ''))
    password = str(self.get_body_argument('password', ''))
    if not username:
      self.json({'error': 'no username'})
      return
    #TODO(twd2): check
    self.redirect('/')

from smartd import app
from smartd.view import base
from smartd.model import data
from tornado import web, gen, options

@app.route('Home', '/')
class MainHandler(base.BaseHandler):
  @gen.coroutine
  def get(self):
    self.render('main.html', count=(yield data.count()))


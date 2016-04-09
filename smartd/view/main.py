from smartd import app
from smartd.view import base
from tornado import web
from tornado import options

@app.route('Home', '/')
class MainHandler(base.BaseHandler):
  def get(self):
    self.render('main.html')


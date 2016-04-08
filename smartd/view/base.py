import json
from smartd import app
from tornado import web
from tornado import options
from tornado import template

class BaseHandler(web.RequestHandler):
  def prepare(self):
    pass
  
  #def render(self, name, **kwargs):
  #  self.write(app.template_loader.load(name).generate(static_url=self.static_url, **kwargs))

  def json(self, obj):
    self.write(json.dumps(obj))

import json
from smartd import app
from tornado import web
from tornado import options
from tornado import template

class BaseHandler(web.RequestHandler):
  def initialize(self, name):
    self.name = name

  def prepare(self):
    pass
  
  def render(self, template_name, **kwargs):
    super(BaseHandler, self).render(template_name, name=self.name, **kwargs)

  def json(self, obj):
    self.write(json.dumps(obj))

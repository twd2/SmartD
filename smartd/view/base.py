import json
from smartd import app, util
import smartd.util.datetime
from tornado import web, options, template

class BaseHandler(web.RequestHandler):
  def initialize(self, name):
    self.name = name

  def prepare(self):
    pass
  
  def render(self, template_name, **kwargs):
    super(BaseHandler, self).render(template_name,
                                    name=self.name, strtime=util.datetime.strtime, **kwargs)

  def json(self, obj):
    self.write(json.dumps(obj))

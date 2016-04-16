import json
from os import path
from smartd import app, util
import smartd.util.datetime
from tornado import web, options, template

class BaseHandler(web.RequestHandler):
  def initialize(self, name):
    self.name = name

  def prepare(self):
    pass

  def bower_url(self, url):
    return path.join(self.static_url('bower_components'), url)

  def render(self, template_name, **kwargs):
    super(BaseHandler, self).render(template_name,
                                    name=self.name, strtime=util.datetime.strtime,
                                    bower_url=self.bower_url, **kwargs)

  def json(self, obj):
    self.write(json.dumps(obj))

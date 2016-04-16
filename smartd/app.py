from tornado import ioloop, web, options, template

App = None
template_loader = None
_routes = []

def route(name, r):
  def decorate(cls):
    _routes.append(web.URLSpec(r, cls, kwargs={'name': name}, name=name))
    return cls
  return decorate

def make_app(**kwargs):
  global App
  from smartd.view import data
  from smartd.view import main
  from smartd.view import plant
  from smartd.view import env
  from smartd.view import history
  App = web.Application(_routes, **kwargs)
  return App

def init_template(p):
  global template_loader
  template_loader = template.Loader(p)

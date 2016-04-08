from tornado import ioloop, web, options, template

template_loader = None
Routes = []

def route(r):
  def decorate(cls):
    Routes.append((r, cls))
    return cls
  return decorate

def make_app(**kwargs):
  from smartd.view import data
  from smartd.view import main
  from smartd.view import plant
  return web.Application(Routes, **kwargs)

def init_template(p):
  global template_loader
  template_loader = template.Loader(p)

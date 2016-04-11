from smartd.util import event, mailer
from tornado import gen

def init():
  event.subscribe(_ifttt, ['data-updated'])

@gen.coroutine
def _ifttt(key, value):
  pass


from smartd.util import event
from tornado import gen

def init():
  event.subscribe(on_door, ['on-function-door'])

@gen.coroutine
def on_door(key, value):
  #print(key, value)
  #TODO(twd2): forward to door openner
  pass

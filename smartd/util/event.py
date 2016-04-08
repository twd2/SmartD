from tornado import gen

_subscribers = {}

@gen.coroutine
def publish(key, value):
  coroutines = [subscriber(key, value)
                for subscriber, key_set in _subscribers.items()
                if key in key_set]
  return coroutines

def subscribe(callback, keys):
  assert isinstance(keys, (set, list, tuple))
  _subscribers[callback] = keys

def unsubscribe(callback):
  if callback in _subscribers:
    del _subscribers[callback]



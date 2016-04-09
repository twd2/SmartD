from smartd import app
from smartd.model import data
from smartd.util import event
from smartd.view import base
from smartd.view import ws
from tornado import web, options, gen

@app.route('Environment', '/env')
class EnvHandler(base.BaseHandler):
  @gen.coroutine
  def get(self):
    self.render('env.html', humidity=(yield data.get('env', 'humidity')),
                temperature=(yield data.get('env', 'temperature')),
                light=(yield data.get('env', 'light')),
                distance=(yield data.get('env', 'distance')))

@app.route('Environment WebSocket', '/env-ws')
class EnvWSHandler(ws.BaseHandler):
  def open(self):
    event.subscribe(self._on_event, ['data-updated'])
    self.json({"event":"updated","type":"humidity"})
    self.json({"event":"updated","type":"temperature"})
    self.json({"event":"updated","type":"light"})
    self.json({"event":"updated","type":"distance"})

  def on_close(self):
    event.unsubscribe(self._on_event)
    print("WebSocket closed")
  
  def _on_event(self, key, value):
    assert key == 'data-updated'
    if value['category'] == 'env':
      self.json({'event': 'updated', 'type': value['type']})

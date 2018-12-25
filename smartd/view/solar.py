from smartd import app
from smartd.model import data
from smartd.util import event
from smartd.view import base
from smartd.view import ws
from tornado import web, options, gen

@app.route('Solar', '/solar')
class SolarHandler(base.BaseHandler):
  @gen.coroutine
  def get(self):
    self.render('solar.html', voltage=(yield data.get('solar', 'voltage')),
                current=(yield data.get('solar', 'current')),
                power=(yield data.get('solar', 'power')))

@app.route('Solar WebSocket', '/solar-ws')
class SolarWSHandler(ws.BaseHandler):
  def open(self):
    event.subscribe(self._on_event, ['data-updated'])
    self.json({'event': 'updated', 'type': 'voltage'})
    self.json({'event': 'updated', 'type': 'current'})
    self.json({'event': 'updated', 'type': 'power'})

  def on_close(self):
    event.unsubscribe(self._on_event)
    print('WebSocket closed')
  
  def _on_event(self, key, value):
    assert key == 'data-updated'
    if value['category'] == 'solar':
      self.json({'event': 'updated', 'type': value['type']})


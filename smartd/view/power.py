from smartd import app
from smartd.model import data
from smartd.util import event
from smartd.view import base
from smartd.view import ws
from tornado import web, options, gen

@app.route('Power', '/power')
class PowerHandler(base.BaseHandler):
  @gen.coroutine
  def get(self):
    self.render('power.html', voltage=(yield data.get('power', 'voltage')),
                current=(yield data.get('power', 'current')),
                power=(yield data.get('power', 'power')))

@app.route('Power WebSocket', '/power-ws')
class PowerWSHandler(ws.BaseHandler):
  def open(self):
    event.subscribe(self._on_event, ['data-updated'])
    self.json({"event":"updated","type":"voltage"})
    self.json({"event":"updated","type":"current"})
    self.json({"event":"updated","type":"power"})

  def on_close(self):
    event.unsubscribe(self._on_event)
    print("WebSocket closed")
  
  def _on_event(self, key, value):
    assert key == 'data-updated'
    if value['category'] == 'power':
      self.json({'event': 'updated', 'type': value['type']})


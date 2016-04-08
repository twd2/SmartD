from smartd import app
from smartd.model import data
from smartd.util import event
from smartd.view import base
from smartd.view import ws
from tornado import web, options, gen

@app.route('/plant')
class PlantHandler(base.BaseHandler):
  @gen.coroutine
  def get(self):
    self.render('plant.html', humidity=(yield data.get('plant', 'humidity')),
                temperature=(yield data.get('plant', 'temperature')),
                light=(yield data.get('plant', 'light')),
                tank=(yield data.get('plant', 'tank')))

@app.route('/plant-ws')
class PlantHandler(ws.BaseHandler):
  def open(self):
    event.subscribe(self._on_event, ['data-updated'])
    self.json({"event":"updated","type":"humidity"})
    self.json({"event":"updated","type":"temperature"})
    self.json({"event":"updated","type":"light"})
    self.json({"event":"updated","type":"tank"})

  def on_message(self, message):
    self.write_message(u"You said: " + message)

  def on_close(self):
    event.unsubscribe(self._on_event)
    print("WebSocket closed")
  
  def _on_event(self, key, value):
    assert key == 'data-updated'
    if value['category'] == 'plant':
      self.json({'event': 'updated', 'type': value['type']})

from smartd import app
from smartd.model import data
from smartd.util import event
from smartd.view import base
from smartd.view import ws
from tornado import web, options, gen

@app.route('Plant', '/plant')
class PlantHandler(base.BaseHandler):
  @gen.coroutine
  def get(self):
    history = yield data.get_list('plant', 'watered', count=50)
    self.render('plant.html', moisture=(yield data.get('plant', 'moisture')),
                temperature=(yield data.get('plant', 'temperature')),
                illumination=(yield data.get('plant', 'illumination')),
                distance=(yield data.get('plant', 'distance')),
                history=history)

@app.route('Plant WebSocket', '/plant-ws')
class PlantWSHandler(ws.BaseHandler):
  def open(self):
    event.subscribe(self._on_event, ['data-updated'])
    self.json({"event":"updated","type":"moisture"})
    self.json({"event":"updated","type":"temperature"})
    self.json({"event":"updated","type":"illumination"})
    self.json({"event":"updated","type":"distance"})

  def on_close(self):
    event.unsubscribe(self._on_event)
    print("WebSocket closed")
  
  def _on_event(self, key, value):
    assert key == 'data-updated'
    if value['category'] == 'plant':
      self.json({'event': 'updated', 'type': value['type']})

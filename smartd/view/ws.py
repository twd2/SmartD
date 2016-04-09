import json
from tornado import websocket

class BaseHandler(websocket.WebSocketHandler):
  def initialize(self, name):
    self.name = name

  def json(self, obj):
    self.write_message(json.dumps(obj))


import json
from tornado import websocket

class BaseHandler(websocket.WebSocketHandler):
  def json(self, obj):
    self.write_message(json.dumps(obj))


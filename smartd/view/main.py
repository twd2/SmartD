import os
import psutil
from smartd import app
from smartd.view import base
from smartd.model import data
from smartd.util import format
from tornado import web, gen, options

def get_cpu_info():
  cpu_count = psutil.cpu_count()
  return {'count': cpu_count,
          'load': os.getloadavg(),
          'percent': os.getloadavg()[0] * 100 / cpu_count}

def get_mem_info():
  mem_info = psutil.virtual_memory()
  return {'total': mem_info.total, 'available': mem_info.available, 'percent': mem_info.percent}

def get_disk_info():
  disk_info = psutil.disk_usage('/')
  return {'total': disk_info.total, 'used': disk_info.used, 'percent': disk_info.percent}

def get_net_info():
  net_info = psutil.net_io_counters()
  return {'sent': net_info.bytes_sent, 'recv': net_info.bytes_recv}

@app.route('Home', '/')
class MainHandler(base.BaseHandler):
  @gen.coroutine
  def get(self):
    cpu_info = get_cpu_info()
    mem_info = get_mem_info()
    disk_info = get_disk_info()
    net_info = get_net_info()

    count = yield data.count()
    if count > 0:
      size = yield data.total_size()
    else:
      size = 0
    self.render('main.html', count=count, size=size, format=format.size_format,
                cpu_info=cpu_info, mem_info=mem_info, disk_info=disk_info, net_info=net_info)

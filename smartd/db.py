from motor import motor_tornado
from tornado import options

options.define('db_host', default='localhost', help='Database hostname or IP address.')
options.define('db_name', default='test', help='Database name.')

class Database(object):
  _instance = None

  def __new__(cls):
    if not cls._instance:
      client = motor_tornado.MotorClient(options.options.db_host)
      cls._instance = motor_tornado.MotorDatabase(client, options.options.db_name)
    return cls._instance

class Collection(object):
  _instances = {}

  def __new__(cls, name):
    if name not in cls._instances:
      cls._instances[name] = motor_tornado.MotorCollection(Database(), name)
    return cls._instances[name]


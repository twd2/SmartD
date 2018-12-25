from smartd import db
from tornado import gen
from tornado import ioloop

@gen.coroutine
def put(category, type, value):
  coll = db.Collection('data')
  return (yield coll.insert_one({'category': category,
                                 'type': type,
                                 'value': value}))

@gen.coroutine
def get(category, type):
  l = yield get_list(category, type, 1)
  if len(l) > 0:
    return l[0]
  else:
    return None

@gen.coroutine
def count(category=None, type=None):
  query = {}
  if category:
    query['category'] = category
  if type:
    query['type'] = type
  coll = db.Collection('data')
  return (yield coll.count_documents(query))

@gen.coroutine
def total_size():
  db_ = db.Database()
  stats = yield db_.command('collStats', 'data')
  return stats['storageSize'] + stats['totalIndexSize']

@gen.coroutine
def get_list(category, type, count=100):
  coll = db.Collection('data')
  return (yield coll.find({'category': category,
                           'type': type}).sort('_id', -1).limit(count).to_list(count))

@gen.coroutine
def ensure_indexes():
  coll = db.Collection('data')
  yield coll.ensure_index([('category', 1), ('type', 1)])
  yield coll.ensure_index([('category', 1), ('type', 1), ('_id', -1)])

@gen.coroutine
def main():
  yield ensure_indexes()
  print((yield get('plant', 'test')))
  print((yield get_list('plant', 'test', 50)))

if __name__ == '__main__':
  ioloop.IOLoop.current().run_sync(main)


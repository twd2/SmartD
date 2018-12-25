import datetime
import pytz
from tornado import options

def strtime(dt):
  tz_utc = pytz.timezone('UTC')
  tz_local = pytz.timezone(options.options.timezone)
  dt_local = dt.replace(tzinfo=tz_utc).astimezone(tz_local)
  return dt_local.strftime('%Y-%m-%d %X')


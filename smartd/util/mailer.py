import smtplibaio
from email.mime import text
from tornado import options, gen

options.define('smtp_host', default='', help='SMTP server')
options.define('smtp_port', default=465, help='SMTP server')
options.define('smtp_user', default='', help='SMTP username')
options.define('smtp_password', default='', help='SMTP password')
options.define('mail_from', default='', help='Mail from')

@gen.coroutine
def send_mail(to, subject, content):
  msg = text.MIMEText(content, _subtype='html', _charset='UTF-8')
  msg['Subject'] = subject
  msg['From'] = options.options.mail_from
  msg['To'] = to
  server = smtplibaio.SMTP_SSL()
  yield server.connect(host=options.options.smtp_host, port=options.options.smtp_port)
  yield server.ehlo()
  yield server.login(options.options.smtp_user, options.options.smtp_password)
  yield server.sendmail(options.options.mail_from, to, msg.as_string())
  return (yield server.quit())


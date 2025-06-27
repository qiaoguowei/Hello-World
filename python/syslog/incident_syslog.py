import syslog

f = open('./11', 'rb')
incident_string = f.read()
f.close()

syslog.openlog(logoption=syslog.LOG_INFO, facility=syslog.LOG_LOCAL3)
syslog.syslog(str(incident_string))

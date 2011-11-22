import smtplib
import os
from email.MIMEMultipart import MIMEMultipart
from email.MIMEBase import MIMEBase
from email.MIMEText import MIMEText
from email.Utils import COMMASPACE, formatdate
from email import Encoders
import urllib2


def website_is_down(url):
    try:
        page = urllib2.urlopen(url)
        if page.code >= 500:
            return True, "HTTP Code: %s" % page.code
        else:
            return False, "HTTP Code: %s" % page.code

    except urllib2.HTTPError, e:
        if e.getcode() >= 500:
            return True, "HTTP Code: %s" % e.getcode()
        else:
            return False, str(e)

    except urllib2.URLError, e:
        return True, str(e)

    return False, "We check page code_status and URLErrors and seems nothing wrong."
    

def send_mail(send_to, subject, text, send_from="admin@mitnk.com", files=[], fail_silently=True):
    assert type(send_to) == list
    assert type(files) == list

    msg = MIMEMultipart()
    msg['From'] = send_from
    msg['To'] = COMMASPACE.join(send_to)
    msg['Date'] = formatdate(localtime=True)
    msg['Subject'] = subject
  
    msg.attach( MIMEText(text) )

    for f in files:
        part = MIMEBase('application', "octet-stream")
        part.set_payload( open(f, "rb").read() )
        Encoders.encode_base64(part)
        part.add_header('Content-Disposition', 'attachment; filename="%s"' % os.path.basename(f))
        msg.attach(part)

    try:
        smtp = smtplib.SMTP("smtp.gmail.com", 587)

        smtpserver = 'smtp.gmail.com'
        smtpuser = 'admin@mitnk.com'         # set SMTP username here
        smtppass = 'xxxxxx'   # set SMTP password here

        smtp.ehlo()
        smtp.starttls()
        smtp.ehlo()
        smtp.login(smtpuser, smtppass)
        smtp.sendmail(send_from, send_to, msg.as_string())
        smtp.close()
    except:
        if not fail_silently:
            raise


import os
import smtplib

from email import Encoders
from email.MIMEBase import MIMEBase
from email.MIMEMultipart import MIMEMultipart
from email.MIMEText import MIMEText
from email.Utils import COMMASPACE, formatdate
from email.header import Header

class GSMTP(object):
    def __init__(self, username, password):
        assert('@' in username)
        self.username = username
        self.password = password

    def send_mail(self, send_to, subject, text="", html=None, files=[], fail_silently=False):
        assert (type(send_to) == list or type(send_to) == tuple)
        assert (type(files) == list or type(files) == tuple)

        msg = MIMEMultipart()
        msg['From'] = self.username
        msg['To'] = COMMASPACE.join(send_to)
        msg['Date'] = formatdate(localtime=True)
        msg['Subject'] = Header(subject, "utf-8")
      
        msg.attach(MIMEText(text, 'plain', 'utf-8'))
        if html:
            part_html = MIMEText(html, 'html', 'utf-8')
            msg.attach(part_html)

        for f in files:
            basename = str(Header(os.path.basename(f), 'utf-8'))
            part = MIMEBase('application', "octet-stream", charset="utf-8")
            part.set_payload(open(f, "rb").read())
            Encoders.encode_base64(part)
            part.add_header('Content-Disposition', 'attachment; filename="%s"' % basename)
            msg.attach(part)

        try:
            smtp = smtplib.SMTP("smtp.gmail.com", 587)
            smtpserver = 'smtp.gmail.com'
            smtpuser = self.username
            smtppass = self.password
            smtp.ehlo()
            smtp.starttls()
            smtp.ehlo()
            smtp.login(smtpuser, smtppass)
            smtp.sendmail(self.username, send_to, msg.as_string())
            smtp.quit()
        except:
            if not fail_silently:
                raise

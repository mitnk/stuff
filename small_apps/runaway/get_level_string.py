from pprint import pprint
import re
import urllib2
from BeautifulSoup import BeautifulSoup

name='mitnk'
password='python'

def get_level_string():
    url = "http://www.hacker.org/runaway/index.php?" + 'name=' + name + '&password=' + password
    try:
        page = urllib2.urlopen(url, timeout=4)
    except urllib2.URLError, e:
        return str(e)

    soup = BeautifulSoup(page)
    tag = soup.find("param", {'name': 'FlashVars'})
    tag_value = tag['value']
    info = {}
    result = re.search(r'FVterrainString=([\.X]+)', tag_value)
    if result:
        info['FVterrainStrin'] = result.group(1)

    result = re.search(r'FVinsMax=(\d+)', tag_value)
    if result:
        info['FVinsMax'] = result.group(1)
    result = re.search(r'FVinsMin=(\d+)', tag_value)
    if result:
        info['FVinsMin'] = result.group(1)

    result = re.search(r'FVboardX=(\d+)', tag_value)
    if result:
        info['FVboardX'] = result.group(1)
    result = re.search(r'FVboardY=(\d+)', tag_value)
    if result:
        info['FVboardY'] = result.group(1)

    result = re.search(r'FVlevel=(\d+)', tag_value)
    if result:
        info['FVlevel'] = result.group(1)

    return info

pprint(get_level_string())

import os
import os.path
import re
import urllib
import urllib2

from BeautifulSoup import BeautifulSoup

def get_chapter_list(url):
    page = urllib2.urlopen(url)
    soup = BeautifulSoup(page, fromEncoding="gb18030")
    print u"Reading information of %s ..." % soup.findAll("h1")[0].string

    tag = soup.find("table", {"class": "list_bg_table"})
    if not tag:
        print "Chapter table not found."

    chapter_list = tag.findAll("td")
    manman_list = []
    for chapter in chapter_list:
        a_tag = chapter.find('a')
        if not a_tag: # Blank td tag
            continue

        chapter_name = a_tag.string
        url = a_tag["href"]
        manman_list.append([chapter_name.strip(), url])

    manman_list.reverse()
    for chapter_name, url in manman_list:
        download_all_images(url, chapter_name)


def download_all_images(url, dir_name):
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)
        print "Created directory: %s" % dir_name
    else:
        if os.listdir(dir_name):
            print "Non-Empty directory %s exists, skip this chapter." % dir_name
            return

    print "Begin to download %s ..." % dir_name

    page = urllib2.urlopen(url)
    soup = BeautifulSoup(page)
    javascripts = soup.findAll(text=lambda text: text.parent.name == "script")
    image_script = ""
    for js in javascripts:
        if "new Array" in js:
            image_script = js
            break

    if not image_script:
        print "Javascript of image src not found."

    result = re.search(r'new Array\(([^;]+)\);', image_script)
    if not result:
        print "Image SRC not found."

    image_list = result.group(1).replace('"', '').split(',')
    print "Total Images: %s" % len(image_list)

    host = "http://54.manmankan.com"
    bad_images = 0
    count_downloaded = 0
    first_image_is_invalid = False
    for image_src in image_list:
        num = str("%3d" % count_downloaded).replace(' ', '0')
        image_ext = image_src.split(".")[-1]
        local_file_name = "%s/%s.%s" % (dir_name, num, image_ext)
        url = host + image_src
        urllib.urlretrieve(url, local_file_name)
        
        # Image too small, means it is bad images (Smaller than 10K)
        # Sometimes, valid images also are very small, 
        # so, We need to determine whether the first is invalid.
        if os.path.getsize(local_file_name) < 10000: 
            if count_downloaded == 0:
                first_image_is_invalid = True

            if first_image_is_invalid:
                print "Invalid image (too small in size) found:", image_src
                print "Saved to %s\r\n" % local_file_name

            bad_images += 1
            if bad_images >= 3 and first_image_is_invalid:
                error_info = u"Error Images found to fetch %s. Skipped this chapter\r\n" % dir_name
                print error_info
                f = open("%s/errors.log" % dir_name, "w")
                f.write(error_info.encode('utf-8'))
                f.close()
                return

        count_downloaded += 1

        if count_downloaded % 10 == 1:
            print "Downloaded:", local_file_name

if __name__ == "__main__":
    get_chapter_list("http://www.manmankan.com/html/409/index.asp")

import os
import os.path
import pickle
import re
import urllib
import urllib2

from BeautifulSoup import BeautifulSoup

def save_image_list_to_cache(dir_name, image_list):
    if not image_list or not dir_name:
        return
    output = open('%s/image_list.pkl' % dir_name, 'wb')
    pickle.dump(image_list, output)
    output.close()

def get_image_list_from_cache(dir_name):
    try:
        pkl_file = open('%s/image_list.pkl' % dir_name, 'rb')
    except IOError:
        return None

    image_list = pickle.load(pkl_file)
    pkl_file.close()
    return image_list

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


def get_image_list(url):
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
    return result.group(1).replace('"', '').split(',')

def download_all_images(url, dir_name):
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)
        print u"Created directory: %s" % dir_name

    # Save image_list to cache, no need fetching from website everytime
    image_list = get_image_list_from_cache(dir_name)
    if not image_list:
        image_list = get_image_list(url)
        save_image_list_to_cache(dir_name, image_list)

    # -1 for image_list.pkl file in the same directory
    image_count_existing = len(os.listdir(dir_name)) - 1
    if len(image_list) == image_count_existing:
        print u"%s seems already finished, skip this chapter." % dir_name
        return

    number_from = 0
    if image_count_existing != 0:
        # Let's fetch from the last image, in case it's not fully downloaded
        number_from = image_count_existing - 1

    print "Begin to download %s ..." % dir_name
    print "Total images to download: %s" % (len(image_list) - number_from)

    host = "http://54.manmankan.com"
    bad_images = 0
    count_downloaded = number_from + 1
    first_image_is_invalid = False
    for image_src in image_list[number_from:]:
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
    get_chapter_list("http://www.manmankan.com/html/381/index.asp")

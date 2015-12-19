# -*- coding: UTF-8 -*-

import re
import urllib,urllib2
import os
import urlparse


def FindNextUrlWithWord(url, word):
    if not (url in checkedPages):
        checkedPages.append(url)
        content = urllib2.urlopen(url).read()

        #finding all links and making them absolute
        linksList = re.findall('href="(.*?)"', content)
        absoluteLinksList = [urlparse.urljoin(url, k) for k in linksList]

        if word in content: #looking for word on page
            print 'Found new page with word'
            DownloadPage(url)
        for link in absoluteLinksList:
            #looking for word in new link if it's a webpage
            extension = link.split('.', 1)[-1]
            if '.htm' in extension:
                FindNextUrlWithWord(link, word)

def SavePageToFile(folder,page):
    f = open(folder + '.html', 'w')
    f.write(page)
    f.close()

def SwitchBackToPrevDir():
    folderParts = os.getcwd().split('\\')[:-1] #get current folder

    #change folder to prev
    filePath = folderParts[0] + '\\'
    for i in range (1,len(folderParts)):
        filePath += folderParts[i] + '\\'
    os.chdir(filePath)

def DownloadPage(url):
    checkedPages.append(url)
    page = urllib2.urlopen(url).read()
    print page

    #finding all links and making them absolute
    links = re.findall('src="(.*?)"', page) + re.findall('href="(.*?)"', page)
    convertedFiles = [urlparse.urljoin(url, n) for n in links]

    #creating folder for pageFiles
    folder =  re.findall('<title>(.*?)</title>', page)[0]
    os.mkdir(folder)
    os.chdir(folder)

    #downloading files to this folder
    for i in range(len(links)):
        url = links[i]
        fileName = url.rsplit('/', 1)[-1]
        try:
            if '.' in fileName: #download file
                urllib.urlretrieve(convertedFiles[i], fileName)
                print url, folder + '/' + fileName
                page = page.replace(url, folder + '/' + fileName)
        except:
            print 'incorrect url'

    SwitchBackToPrevDir()
    SavePageToFile(folder,page)

url = "https://python.org"
word = 'programming'
checkedPages = [] #list of already used urls

FindNextUrlWithWord(url, word)
print 'Program has finished.'
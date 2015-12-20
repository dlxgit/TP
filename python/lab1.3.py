# -*- coding: UTF-8 -*-

import re
import urllib,urllib2
import os
import urlparse


def FindNextUrlWithWord(url, word):
    if not checkedPages.has_key(url):
        checkedPages[url] = 1
        content = urllib2.urlopen(url).read()

        #finding all links and making them absolute
        linksList = re.findall('href="(.*?)"', content)
        absoluteLinksList = [urlparse.urljoin(url, k) for k in linksList]

        if word in content: #looking for word on page
            print 'Found new page with word'
            checkedPages[url] = 1
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

def GetCorrectFileName(name):
    invalidSymbols = ['/', '|','"','*',':','?', '<', '>','\\' ]
    correctName = ''
    for symbol in name:
        if symbol not in invalidSymbols:
            correctName += symbol
    return correctName

def DownloadPage(url):
    page = urllib2.urlopen(url).read()
    print page

    #finding all links and making them absolute
    links = re.findall('src="(.*?)"', page) + re.findall('href="(.*?)"', page)
    convertedFiles = [urlparse.urljoin(url, n) for n in links]

    #creating folder for pageFiles
    namePart =  re.findall('<title>(.*?)</title>', page)[0]
    folder = GetCorrectFileName(namePart)
    os.mkdir(folder)
    os.chdir(folder)

    #downloading files to this folder
    for i in range(len(links)):
        url = links[i]
        namePart = url.rsplit('/', 1)[-1]
        fileName = GetCorrectFileName(namePart)
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
checkedPages = {}
FindNextUrlWithWord(url, word)
print 'Program has finished.'
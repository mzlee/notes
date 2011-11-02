#!/bin/sh -e

time chrome --app=http://google.com --start-maximized  2>> browser.timing
echo '' >> browser.timing

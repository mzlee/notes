#!/bin/sh -e

time chrome --app=http://google.com --incognito --start-maximized --new-http 2>> incog.timing
echo '' >> incog.timing

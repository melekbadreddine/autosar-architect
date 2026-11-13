#!/bin/sh
java -Xss1m -Xmx512m -jar "`dirname $0`/plugins/org.eclipse.equinox.launcher_1.3.0.v20140415-2008.jar" -application org.eclipse.equinox.p2.director -repository "file:$1" -installIU "$2.feature.group"

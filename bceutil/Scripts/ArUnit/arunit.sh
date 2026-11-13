#!/bin/sh
java -Xss8m -Xmx4096m -jar "`dirname $0`/plugins/org.eclipse.equinox.launcher_1.3.0.v20140415-2008.jar" $*

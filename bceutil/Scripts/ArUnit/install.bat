@echo off

java -Xss128m -Xmx2G -jar "%~dp0\plugins\org.eclipse.equinox.launcher_1.3.0.v20140415-2008" -application org.eclipse.equinox.p2.director -repository "file:%1" -installIU "%2.feature.group"
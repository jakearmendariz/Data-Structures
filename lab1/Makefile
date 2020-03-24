#--------------------------
#This makefile should archive both .classes
#

JAVASRC    = HelloUser.java HelloUser2.java
SOURCES    = README Makefile $(JAVASRC)
MAINCLASS  = HelloUser2
CLASSES    = HelloUser.class HelloUser2.class
JARFILE    = Hello

all: $(JARFILE)

$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(CLASSES)
	rm Manifest
	chmod +x $(JARFILE)

$(CLASSES): $(JAVASRC)
	javac -Xlint $(JAVASRC)
clean:
	rm $(CLASSES)

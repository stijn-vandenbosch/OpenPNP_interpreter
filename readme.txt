= Titel van het project:  PNP controller met OpenPNP =

== door:  Stijn Vandenbosch ==

== Korte beschrijving ==
Het discovery bordje ontvangt commando's via tcp(23) commando's van OpenPNP. Vervolgens
worden de commando's geïnterpreteerd en worden de uitgangen aangestuurd. Op het display 
wordt het laatste commando en de huidige positie van het systeem weergegeven.

Ter demonstratie zijn een aantal van deze uitgangen naar buiten gebracht via een 
printje dat ik thuis geëtst heb. De uitgangen worden zichtbaar gemaakt op leds.

== Libs, compiler en apps ==
 
 - lwip version 2.1.2
 - CubeMX version 6.0.1
 - System workbench (SW4STM32) 4.6.3
 - OpenPNP version: 2020-05-31_18-59-01.9fedc53

== Bestanden aangemaakt/aangepast ==

   Aangepaste bestanden:
	- main.c
	- main.h
   Aangemaakte bestanden:
	- actuators.c / .h
	- buttons.c / .h
	- coms.c / .h
	- gcode.c / .h
	- motion.c / .h

== Opmerkingen == 
   Aansluitingen
	-volg het kiCAD schema voor de LED's
	-sluit het bordje aan op het netwerk (static 192.168.1.69/24)
   Software
	-open de map openpnp
	-voer openPnP.exe uit
	-ga naar machine setup > Driver > GcodeDriver > communication
	-kijk na of TCP aan staat en dat het ip adres en poort(23) kloppen

	-file > open job >  openpnp/samples/pnp-test/pnp-test.job.xml
	-maak connectie met de 'machine' links onder op de aan knop
	-job > start

== Bronvermeldingen == 
	https://github.com/openpnp/openpnp/wiki

== Optioneel: Extra's ==
	-printje getekend en geëtst
	-cppcheck uitgevoerd
	-versie controle op github: https://github.com/stijn-vandenbosch/OpenPNP_interpreter

# Time-stamp: <15 May 99 23:26:16 Michael Bischoff>
# Makefile to convert nice card sets from pysol-2.0.2 for xpat
# requires gnu make, the pnm-tools, and (of course) the great cards from pysol,
# found at ftp://ftp.metalab.unc.de/pub/Linux/games/solitaire

PYSOLCARDDIR = /usr/games/lib/pysol-cardsets-2.02/data/cardset-pysol-large
CARDBACK = back11

all:
	cp -p ../dummy.xpm Ranks.xpm
	cp -p ../dummy.xpm Suits.xpm
	giftopnm $(PYSOLCARDDIR)/$(CARDBACK).gif | ppmtoxpm > Cardback1.xpm
	../docvt $(PYSOLCARDDIR) 01 Ace
	../docvt $(PYSOLCARDDIR) 02 Deuce
	../docvt $(PYSOLCARDDIR) 03 Three
	../docvt $(PYSOLCARDDIR) 04 Four
	../docvt $(PYSOLCARDDIR) 05 Five
	../docvt $(PYSOLCARDDIR) 06 Six
	../docvt $(PYSOLCARDDIR) 07 Seven
	../docvt $(PYSOLCARDDIR) 08 Eight
	../docvt $(PYSOLCARDDIR) 09 Nine
	../docvt $(PYSOLCARDDIR) 10 Ten
	../docvt $(PYSOLCARDDIR) 11 Jack
	../docvt $(PYSOLCARDDIR) 12 Queen
	../docvt $(PYSOLCARDDIR) 13 King


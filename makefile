#
# Minta makefile
#

# set this to something if debug version should be created
DEBUG  = 

# adjust this as desired/required
CFLAGS = -g -Wall -fno-exceptions -fno-rtti
CC     = gcc $(CFLAGS)
I      = e:/prog/emx/include/

# where the various files are (to be) kept; no trailing slashes please!
SRC    = src
TMP    = tmp
OUT    = out
DATA   = $(SRC)/data

# -------------------------------------------------------------------------

.IF $(DEBUG)
    o=o
    $(TMP)/%.$(o) : $(SRC)/%.cpp ; $(CC) -o $@ -c $<
.ELSE
    o=obj
    $(TMP)/%.$(o) : $(SRC)/%.cpp ; $(CC) -o $@ -Zomf -Zsys -Zmt -O2 -c $<
.END

# -- 'big' targes ---------------------------------------------------------

default:      all
all:          minta ressources

distr .IGNORE:  all
	copy "$(OUT)\*.dll" "distr"
	copy "$(OUT)\*.hlp" "distr"
	copy "$(OUT)\*.exe" "distr"
	del "distr\*~"
	del "distr\*.INI"

minta:        $(OUT)/minta.exe
ressources:   english deutsch francais nedrlnds norsk russian magyar italiano

english:      $(OUT)\english.dll $(OUT)/english.hlp
deutsch:      $(OUT)\deutsch.dll $(OUT)/deutsch.hlp
francais:     $(OUT)\francais.dll $(OUT)/francais.hlp
norsk:        $(OUT)\norsk.dll $(OUT)/norsk.hlp
nedrlnds:     $(OUT)\nedrlnds.dll $(OUT)/nedrlnds.hlp
russian:      $(OUT)\russian.dll
magyar:       $(OUT)\magyar.dll
italiano:     $(OUT)\italiano.dll $(OUT)/italiano.hlp

# -- 'small' targets ------------------------------------------------------

$(OUT)/minta.exe:       \
			$(TMP)/about.$(o) \
                        $(TMP)/finddir.$(o) \
                        $(TMP)/helper.$(o) \
                        $(TMP)/minta.$(o) \
                        $(TMP)/mp3.$(o) \
                        $(TMP)/mp3disp.$(o) \
                        $(TMP)/genlist.$(o) \
                        $(TMP)/lister.$(o) \
                        $(TMP)/renamer.$(o) \
                        $(TMP)/rstring.$(o) \
                        $(TMP)/settings.$(o) \
                        $(TMP)/status.$(o) \
                        $(TMP)/threads.$(o) \
                        $(TMP)/toolbar.$(o) \
                        $(TMP)/minta.res \
                        $(SRC)/minta.def
.IF $(DEBUG)
	$(CC) -o $(OUT)/minta -Zmt -lstdcpp $(TMP)/*.$(o) $(SRC)/minta.def
	emxbind -bpq e:/prog/emx/bin/emxl $(OUT)/minta
# FIXME the above is probably totally wrong now ...
.ELSE
	$(CC) -o $(OUT)/minta.exe -Zomf -Zsys -Zmt -s -lstdcpp $<
.END

$(TMP)/minta.res:      $(SRC)/minta.rc $(SRC)/minta.ico
	rc -r "$(SRC)/minta.rc" "$@"

$(TMP)/helper.$(o):     $(SRC)/version.h $(SRC)/helper.cpp

# -- language ressources --------------------------------------------------

$(OUT)\english.dll:     $(TMP)/english.res \
                        $(SRC)/english/english.def \
                        $(SRC)/dll.obj
	link386 /nologo $(SRC)\dll, $@ /align:16, nul,, $(SRC)\english\english.def
	rc $(TMP)/english.res $@
	eautil $@ f:\tmp\dll.ea /s
	del "f:\tmp\dll.ea"

$(TMP)/english.res:     $(SRC)/english/english.rc \
                        $(SRC)/id.h \
                        $(SRC)/common.rc \
                        $(SRC)/version.h
	rc -i $I -i $(SRC) -cc 1 -cp 850 -r $(SRC)/english/english.rc $@

$(OUT)/english.hlp:     $(SRC)/english/english.ipf $(SRC)/common.ipf \
                        $(DATA)/teamlogo.bmp $(DATA)/godzilla.bmp \
                        $(DATA)/minta.bmp
	ipfc /D:001 /C:850 $(SRC)/english/english.ipf $@

# -------------------------------------------------------------------------

$(OUT)\deutsch.dll:     $(TMP)/deutsch.res \
                        $(SRC)/deutsch/deutsch.def \
                        $(SRC)/dll.obj
	link386 /nologo $(SRC)\dll, $@ /align:16, nul,, $(SRC)\deutsch\deutsch.def
	rc $(TMP)/deutsch.res $@
	eautil $@ f:\tmp\dll.ea /s
	del "f:\tmp\dll.ea"

$(TMP)/deutsch.res:     $(SRC)/deutsch/deutsch.rc \
                        $(SRC)/id.h \
                        $(SRC)/common.rc \
                        $(SRC)/version.h
	rc -i $I -i $(SRC) -cc 49 -cp 850 -r $(SRC)/deutsch/deutsch.rc $@

$(OUT)/deutsch.hlp:     $(SRC)/deutsch/deutsch.ipf $(SRC)/common.ipf \
                        $(DATA)/teamlogo.bmp $(DATA)/godzilla.bmp \
                        $(DATA)/minta.bmp
	ipfc /D:049 /C:850 $(SRC)/deutsch/deutsch.ipf $@

# -------------------------------------------------------------------------

$(OUT)\francais.dll:     $(TMP)/francais.res \
                        $(SRC)/francais/francais.def \
                        $(SRC)/dll.obj
	link386 /nologo $(SRC)\dll, $@ /align:16, nul,, $(SRC)\francais\francais.def
	rc $(TMP)/francais.res $@
	eautil $@ f:\tmp\dll.ea /s
	del "f:\tmp\dll.ea"

$(TMP)/francais.res:     $(SRC)/francais/francais.rc \
                        $(SRC)/id.h \
                        $(SRC)/common.rc \
                        $(SRC)/version.h
	rc -i $I -i $(SRC) -cc 33 -cp 850 -r $(SRC)/francais/francais.rc $@

$(OUT)/francais.hlp:     $(SRC)/francais/francais.ipf $(SRC)/common.ipf \
                        $(DATA)/teamlogo.bmp $(DATA)/godzilla.bmp \
                        $(DATA)/minta.bmp
	ipfc /D:033 /C:850 $(SRC)/francais/francais.ipf $@

# -------------------------------------------------------------------------

$(OUT)\norsk.dll:     $(TMP)/norsk.res \
                        $(SRC)/norsk/norsk.def \
                        $(SRC)/dll.obj
	link386 /nologo $(SRC)\dll, $@ /align:16, nul,, $(SRC)\norsk\norsk.def
	rc $(TMP)/norsk.res $@
	eautil $@ f:\tmp\dll.ea /s
	del "f:\tmp\dll.ea"

$(TMP)/norsk.res:     $(SRC)/norsk/norsk.rc \
                        $(SRC)/id.h \
                        $(SRC)/common.rc \
                        $(SRC)/version.h
	rc -i $I -i $(SRC) -cc 47 -cp 865 -r $(SRC)/norsk/norsk.rc $@

$(OUT)/norsk.hlp:     $(SRC)/norsk/norsk.ipf $(SRC)/common.ipf \
                        $(DATA)/teamlogo.bmp $(DATA)/godzilla.bmp \
                        $(DATA)/minta.bmp
	ipfc /D:47 /C:865 $(SRC)/norsk/norsk.ipf $@

# -------------------------------------------------------------------------

$(OUT)\nedrlnds.dll:     $(TMP)/nedrlnds.res \
                        $(SRC)/nedrlnds/nedrlnds.def \
                        $(SRC)/dll.obj
	link386 /nologo $(SRC)\dll, $@ /align:16, nul,, $(SRC)\nedrlnds\nedrlnds.def
	rc $(TMP)/nedrlnds.res $@
	eautil $@ f:\tmp\dll.ea /s
	del "f:\tmp\dll.ea"

$(TMP)/nedrlnds.res:     $(SRC)/nedrlnds/nedrlnds.rc \
                        $(SRC)/id.h \
                        $(SRC)/common.rc \
                        $(SRC)/version.h
	rc -i $I -i $(SRC) -cc 31 -cp 850 -r $(SRC)/nedrlnds/nedrlnds.rc $@

$(OUT)/nedrlnds.hlp:     $(SRC)/nedrlnds/nedrlnds.ipf $(SRC)/common.ipf \
                        $(DATA)/teamlogo.bmp $(DATA)/godzilla.bmp \
                        $(DATA)/minta.bmp
	ipfc /D:031 /C:850 $(SRC)/nedrlnds/nedrlnds.ipf $@

# -------------------------------------------------------------------------

$(OUT)\russian.dll:     $(TMP)/russian.res \
                        $(SRC)/russian/russian.def \
                        $(SRC)/dll.obj
	link386 /nologo $(SRC)\dll, $@ /align:16, nul,, $(SRC)\russian\russian.def
	rc $(TMP)/russian.res $@
	eautil $@ f:\tmp\dll.ea /s
	del "f:\tmp\dll.ea"

$(TMP)/russian.res:     $(SRC)/russian/russian.rc \
                        $(SRC)/id.h \
                        $(SRC)/common.rc \
                        $(SRC)/version.h
	rc -i $I -i $(SRC) -cc 7 -cp 866 -r $(SRC)/russian/russian.rc $@

# -------------------------------------------------------------------------

$(OUT)\magyar.dll:     $(TMP)/magyar.res \
                        $(SRC)/magyar/magyar.def \
                        $(SRC)/dll.obj
	link386 /nologo $(SRC)\dll, $@ /align:16, nul,, $(SRC)\magyar\magyar.def
	rc $(TMP)/magyar.res $@
	eautil $@ f:\tmp\dll.ea /s
	del "f:\tmp\dll.ea"

$(TMP)/magyar.res:     $(SRC)/magyar/magyar.rc \
                        $(SRC)/id.h \
                        $(SRC)/common.rc \
                        $(SRC)/version.h
	rc -i $I -i $(SRC) -cc 36 -cp 850 -r $(SRC)/magyar/magyar.rc $@

# -------------------------------------------------------------------------

$(OUT)\italiano.dll:     $(TMP)/italiano.res \
                        $(SRC)/italiano/italiano.def \
                        $(SRC)/dll.obj
	link386 /nologo $(SRC)\dll, $@ /align:16, nul,, $(SRC)\italiano\italiano.def
	rc $(TMP)/italiano.res $@
	eautil $@ f:\tmp\dll.ea /s
	del "f:\tmp\dll.ea"

$(TMP)/italiano.res:     $(SRC)/italiano/italiano.rc \
                        $(SRC)/id.h \
                        $(SRC)/common.rc \
                        $(SRC)/version.h
	rc -i $I -i $(SRC) -cc 39 -cp 437 -r $(SRC)/italiano/italiano.rc $@

$(OUT)/italiano.hlp:     $(SRC)/italiano/italiano.ipf $(SRC)/common.ipf \
                        $(DATA)/teamlogo.bmp $(DATA)/godzilla.bmp \
                        $(DATA)/minta.bmp
	ipfc /D:039 /C:437 $(SRC)/italiano/italiano.ipf $@

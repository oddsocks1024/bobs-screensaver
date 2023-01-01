bin_PROGRAMS = bobs
bobs_SOURCES = bobs.c \
bobs_bouncefx.c \
bobs_burstfx.c \
bobs_fountainfx.c \
bobs_wobblefx.c \
bobs_multiplyfx.c \
bobs_spinburstfx.c \
bobs_rainfx.c \
bobs_textures.c \
bobs_timers.c \
bobs.h \
bobs_random.c

bobs_LDFLAGS = @LDFLAGS@
bobs_CPPFLAGS = $(all_includes) @SDL_CFLAGS@ @X_CFLAGS@ @GLU_CFLAGS@ @GL_CFLAGS@
bobs_LDADD = @SDL_LIBS@ @X_PRE_LIBS@ @X_LIBS@ @X_EXTRA_LIBS@ @GLU_LIBS@ @GL_LIBS@

install-exec-hook:
	if test "@GNOMESAVER@" = "yes" ; then \
	if test -d "$(DESTDIR)@GNOME_LNK_DIR@"; then echo "OK"; else $(MKDIR_P) "$(DESTDIR)@GNOME_LNK_DIR@"; fi; \
	cd "$(DESTDIR)@GNOME_LNK_DIR@"; \
	if test -e bobs$(EXEEXT); then rm -f bobs$(EXEEXT); else echo "OK"; fi; \
	$(LN_S) $(DESTDIR)$(bindir)/bobs$(EXEEXT) bobs$(EXEEXT); \
	fi;

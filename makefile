# ----------------------------
# Makefile Options
# ----------------------------

NAME = GRFC1
ICON = icon.png
DESCRIPTION = "Graphics test"
COMPRESSED = NO
ARCHIVED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)

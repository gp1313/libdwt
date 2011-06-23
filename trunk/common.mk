ROOT = $(dir $(lastword $(MAKEFILE_LIST)))

NAME = dwt
VERSION := $(shell cat $(ROOT)/VERSION)
DATE := $(shell date -R)
AUTHORS := $(shell cat $(ROOT)/AUTHORS)

.DEFAULT_GOAL := all

.PHONY: version help

version:
	@echo "$(VERSION)"

help:
	@echo "To print this help type 'make help'."
	@echo "To print version type 'make version'."
	@echo "To make an example application type 'make' in example folder."
	@echo "If you want to build any binary for another architecture type 'make ARCH=<arch>', where ARCH is one of 'x86_64' (for PC) or 'microblaze' (for EdkDSP platform)."
	@echo "In case of any problems contact '$(AUTHORS)'."

include $(ROOT)/arch.mk

EDKDSP_SERVER = ibarina@pcbarina.fit.vutbr.cz
EDKDSP_CLIENT = 192.168.0.10
.PHONY: upload
upload: all
	cat $(BIN) | ssh $(EDKDSP_SERVER) "curl -n -T - -Q \"-SITE CHMOD 777 /tmp/$(BIN)\" ftp://$(EDKDSP_CLIENT)/tmp/$(BIN)"
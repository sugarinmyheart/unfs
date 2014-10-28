#
# Copyright (C) 2006-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=fpkg
PKG_RELEASE:=2014-10-18

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
	SECTION:=firefly-extra
	CATEGORY:=Firefly-Extra
	TITLE:= A tools for package managerment
endef

define Build/Compile
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DIR) $(1)/opt/app/
	$(INSTALL_DIR) $(1)/opt/app/defalut/icon/
	$(INSTALL_DIR) $(1)/usr/local
	$(INSTALL_DIR) $(1)/etc/config
	cp ./res/logo.png $(1)/opt/app/defalut/icon/large.png
	cp ./res/logo.png $(1)/opt/app/defalut/icon/small.png
	$(INSTALL_DIR) $(1)/www/opt/
	cp ./app $(1)/www/opt/app -a
	cp ./localshell $(1)/usr/local/ -rf
	$(INSTALL_BIN) ./fpkg $(1)/usr/bin/fpkg
	$(INSTALL_BIN) ./config/fpkg $(1)/etc/config/fpkg
endef


$(eval $(call BuildPackage,$(PKG_NAME)))


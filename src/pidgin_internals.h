/*
 * ZNC Helper
 * Copyright (C) 2012 Konrad Gräfe
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1301, USA.
 */

#ifndef PIDGIN_INTERNALS_H
#define PIDGIN_INTERNALS_H

#include <gtkconv.h>
#include <gtkimhtml.h>
#include <circbuffer.h>

GtkTextTag *get_buddy_tag(PurpleConversation *conv, const char *who, PurpleMessageFlags flag, gboolean create);
const char *get_text_tag_color(GtkTextTag *tag);
const GdkColor *get_nick_color(PidginConversation *gtkconv, const char *name);

struct irc_conn {
	PurpleAccount *account;
	GHashTable *msgs;
	GHashTable *cmds;
	char *server;
	int fd;
	guint timer;
	guint who_channel_timer;
	GHashTable *buddies;

	gboolean ison_outstanding;
	GList *buddies_outstanding;

	char *inbuf;
	int inbuflen;
	int inbufused;

	GString *motd;
	GString *names;
	struct _whois {
		char *nick;
		char *away;
		char *userhost;
		char *name;
		char *server;
		char *serverinfo;
		GString *channels;
		int ircop;
		int identified;
		int idle;
		time_t signon;
	} whois;
	PurpleRoomlist *roomlist;
	PurpleSslConnection *gsc;

	gboolean quitting;

	PurpleCircBuffer *outbuf;
	guint writeh;

	time_t recv_time;

	char *mode_chars;
	char *reqnick;
	gboolean nickused;
};

struct irc_msg_old {
	char *name;
	char *format;
	void (*cb)(struct irc_conn *irc, const char *name, const char *from, char **args);
};

struct irc_msg_2_10_8 {
	char *name;
	char *format;
	int req_cnt;
	void (*cb)(struct irc_conn *irc, const char *name, const char *from, char **args);
};

#endif /* PIDGIN_INTERNALS_H */
